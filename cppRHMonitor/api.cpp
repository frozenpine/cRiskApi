#include "api.h"

#define CHK_RSP(rsp, msg)                                                      \
    do                                                                         \
    {                                                                          \
        if ((rsp)->ErrorID != 0)                                               \
        {                                                                      \
            LOGE("%s failed[%d]: %s", (msg), (rsp)->ErrorID, (rsp)->ErrorMsg); \
            return;                                                            \
        }                                                                      \
        LOGI("%s success: %s", (msg), (rsp)->ErrorMsg);                        \
    } while (false)

///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
void fpRHMonitorApi::OnFrontConnected()
{
    LOGI("Front[%s:%d] connected.", remoteAddr, remotePort);
    
    setBoolFlag(&bConnected, true);
};

///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
///@param nReascRHMonitorApi::On 错误原因
///        0x1001 网络读失败
///        0x1002 网络写失败
///        0x2001 接收心跳超时
///        0x2002 发送心跳失败
///        0x2003 收到错误报文
void fpRHMonitorApi::OnFrontDisconnected(int nReason)
{
    LOGW("Front[%s:%d] disconnected: %02x", remoteAddr, remotePort, nReason);
    
    setBoolFlag(&bConnected, false);
};

///风控账户登陆响应
void fpRHMonitorApi::OnRspUserLogin(
    CRHMonitorRspUserLoginField *pRspUserLoginField, 
    CRHRspInfoField *pRHRspInfoField,
    int nRequestID)
{
    CHK_RSP(pRHRspInfoField, "Request user login");

    memcpy(&loginInfo, pRspUserLoginField, sizeof(loginInfo));

    LOGI(
        "Risk user[%s] logged in: %s %s",
        pRspUserLoginField->UserID,
        pRspUserLoginField->TradingDay,
        pRspUserLoginField->LoginTime);

    setBoolFlag(&bLogin, true);
};

///风控账户登出响应
void fpRHMonitorApi::OnRspUserLogout(
    CRHMonitorUserLogoutField *pRspUserLoginField, 
    CRHRspInfoField *pRHRspInfoField,
    int nRequestID)
{
    CHK_RSP(pRHRspInfoField, "Request user logout");

    setBoolFlag(&bLogin, false);
};

//查询监控账户响应
void fpRHMonitorApi::OnRspQryMonitorAccounts(
    CRHQryInvestorField *pRspMonitorUser, 
    CRHRspInfoField *pRHRspInfoField, 
    int nRequestID, bool isLast)
{
    CHK_RSP(pRHRspInfoField, "Request query accounts");
};

///查询账户资金响应
void fpRHMonitorApi::OnRspQryInvestorMoney(
    CRHTradingAccountField *pRHTradingAccountField, 
    CRHRspInfoField *pRHRspInfoField, 
    int nRequestID, bool isLast)
{
    CHK_RSP(pRHRspInfoField, "Request query money");
};

///查询账户持仓信息响应
void fpRHMonitorApi::OnRspQryInvestorPosition(
    CRHMonitorPositionField *pRHMonitorPositionField, 
    CRHRspInfoField *pRHRspInfoField, 
    int nRequestID, bool isLast)
{
    CHK_RSP(pRHRspInfoField, "Request query position");
};

//平仓指令发送失败时的响应
void fpRHMonitorApi::OnRspOffsetOrder(
    CRHMonitorOffsetOrderField *pMonitorOrderField, 
    CRHRspInfoField *pRHRspInfoField, 
    int nRequestID, bool isLast)
{
    CHK_RSP(pRHRspInfoField, "Request offset order");
};

///报单通知
void fpRHMonitorApi::OnRtnOrder(CRHOrderField *pOrder){};

///成交通知
void fpRHMonitorApi::OnRtnTrade(CRHTradeField *pTrade){};

///账户资金发生变化回报
void fpRHMonitorApi::OnRtnInvestorMoney(CRHTradingAccountField *pRohonTradingAccountField){};

///账户某合约持仓回报
void fpRHMonitorApi::OnRtnInvestorPosition(CRHMonitorPositionField *pRohonMonitorPositionField){};

void fpRHMonitorApi::waitBoolFlag(std::atomic_bool* flag, bool v)
{
    while (true) {
        if (flag->load() == v) break;
    }
}

void fpRHMonitorApi::setBoolFlag(std::atomic_bool* flag, bool v)
{
    flag->store(v);
}

///初始化
///@remark 初始化运行环境,只有调用后,接口才开始工作
void fpRHMonitorApi::Init(const char *ip, unsigned int port)
{
    pApi->Init(ip, port);

    memcpy(remoteAddr, ip, sizeof(remoteAddr) - 1);
    remotePort = port;
};

///账户登陆
int fpRHMonitorApi::ReqUserLogin(CRHMonitorReqUserLoginField *pUserLoginField)
{
    waitBoolFlag(&bConnected, true);

    LOGI("Request login for user: %s", pUserLoginField->UserID);

    return pApi->ReqUserLogin(pUserLoginField, nRequestID++);
};

//账户登出
int fpRHMonitorApi::ReqUserLogout()
{
    waitBoolFlag(&bLogin, true);

    CRHMonitorUserLogoutField logout = CRHMonitorUserLogoutField{0};
    memcpy(&logout.UserID, &loginInfo.UserID, sizeof(logout.UserID) - 1);

    LOGI("Request logout for user: %s", loginInfo.UserID);

    return pApi->ReqUserLogout(&logout, nRequestID++);
};

//查询所有管理的账户
int fpRHMonitorApi::ReqQryMonitorAccounts()
{
    waitBoolFlag(&bLogin, true);

    CRHMonitorQryMonitorUser qry = CRHMonitorQryMonitorUser{0};
    memcpy(&qry.UserID, &loginInfo.UserID, sizeof(qry.UserID) - 1);

    LOGI("Query accounts for user: %s", loginInfo.UserID);

    return pApi->ReqQryMonitorAccounts(&qry, nRequestID++);
};

///查询账户资金
int fpRHMonitorApi::ReqQryInvestorMoney(CRHMonitorQryInvestorMoneyField *pQryInvestorMoneyField)
{
    waitBoolFlag(&bLogin, true);

    return pApi->ReqQryInvestorMoney(pQryInvestorMoneyField, nRequestID++);
};

///查询账户持仓
int fpRHMonitorApi::ReqQryInvestorPosition(CRHMonitorQryInvestorPositionField *pQryInvestorPositionField)
{
    waitBoolFlag(&bLogin, true);

    return pApi->ReqQryInvestorPosition(pQryInvestorPositionField, nRequestID++);
};

//给Server发送强平请求
int fpRHMonitorApi::ReqOffsetOrder(CRHMonitorOffsetOrderField *pMonitorOrderField)
{
    waitBoolFlag(&bLogin, true);

    return pApi->ReqOffsetOrder(pMonitorOrderField, nRequestID++);
};

//订阅主动推送信息
int fpRHMonitorApi::ReqSubPushInfo(CRHMonitorSubPushInfo *pInfo)
{
    waitBoolFlag(&bLogin, true);

    return pApi->ReqSubPushInfo(pInfo, nRequestID++);
};

void fpRHMonitorApi::Release()
{
    if (NULL != pApi)
    {
        pApi->Release();
    }
}