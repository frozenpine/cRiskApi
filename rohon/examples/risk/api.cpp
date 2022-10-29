#include <stdio.h>

#include "api.h"

#define FMTI(fmt) "[INFO ] " fmt "\n"
#define FMTW(fmt) "[WARNI] " fmt "\n"
#define FMTE(fmt) "[ERROR] " fmt "\n"
#define LOGI(fmt, ...) fprintf(stderr, FMTI(fmt), __VA_ARGS__)
#define LOGW(fmt, ...) fprintf(stderr, FMTW(fmt), __VA_ARGS__)
#define LOGE(fmt, ...) fprintf(stderr, FMTE(fmt), __VA_ARGS__)

#define CHK_RSP(rsp, msg) do { \
    if ((rsp)->ErrorID != 0) { \
        LOGE("%s failed[%d]: %s", (msg), (rsp)->ErrorID, (rsp)->ErrorMsg); \
        return; \
    } \
    LOGI("%s success: %s", (msg), (rsp)->ErrorMsg); \
} while (false)


///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
void fpRHMonitorApi::OnFrontConnected(){ 
    bConnected.store(true);
    
    LOGI("Front[%s:%d] connected.", remoteAddr, remotePort);
};

///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
///@param nReascRHMonitorApi::On 错误原因
///        0x1001 网络读失败
///        0x1002 网络写失败
///        0x2001 接收心跳超时
///        0x2002 发送心跳失败
///        0x2003 收到错误报文
void fpRHMonitorApi::OnFrontDisconnected(int nReason) { 
    bConnected.store(false);

    LOGW("Front[%s:%d] disconnected: %02x", remoteAddr, remotePort, nReason);
};

///风控账户登陆响应
void fpRHMonitorApi::OnRspUserLogin(CRHMonitorRspUserLoginField *pRspUserLoginField, CRHRspInfoField *pRHRspInfoField){
    CHK_RSP(pRHRspInfoField, "Request user login");

    memcpy(&loginInfo, pRspUserLoginField, sizeof(loginInfo));

    LOGI(
        "Risk user[%s] logged in: %s %s", 
        pRspUserLoginField->UserID, 
        pRspUserLoginField->TradingDay, 
        pRspUserLoginField->LoginTime
    );
};

///风控账户登出响应
void fpRHMonitorApi::OnRspUserLogout(CRHMonitorUserLogoutField *pRspUserLoginField, CRHRspInfoField *pRHRspInfoField){
    CHK_RSP(pRHRspInfoField, "Request user logout");
};

//查询监控账户响应
void fpRHMonitorApi::OnRspQryMonitorAccounts(CRHQryInvestorField *pRspMonitorUser, CRHRspInfoField *pRHRspInfoField, bool isLast){};

///查询账户资金响应
void fpRHMonitorApi::OnRspQryInvestorMoney(CRHTradingAccountField *pRHTradingAccountField, CRHRspInfoField *pRHRspInfoField, bool isLast){};

///查询账户持仓信息响应
void fpRHMonitorApi::OnRspQryInvestorPosition(CRHMonitorPositionField *pRHMonitorPositionField, CRHRspInfoField *pRHRspInfoField, bool isLast){};

//平仓指令发送失败时的响应
void fpRHMonitorApi::OnRspOffsetOrder(CRHMonitorOffsetOrderField *pMonitorOrderField, CRHRspInfoField *pRHRspInfoField, bool isLast){};

///报单通知
void fpRHMonitorApi::OnRtnOrder(CRHOrderField *pOrder){};

///成交通知
void fpRHMonitorApi::OnRtnTrade(CRHTradeField *pTrade){};

///账户资金发生变化回报
void fpRHMonitorApi::OnRtnInvestorMoney(CRHTradingAccountField *pRohonTradingAccountField){};

///账户某合约持仓回报
void fpRHMonitorApi::OnRtnInvestorPosition(CRHMonitorPositionField *pRohonMonitorPositionField){};

void fpRHMonitorApi::waitBool(std::atomic<bool>* flag, bool v)
{
    while(true) { 
        bool check = flag->load() == v;

        if(check) break;
    }
};

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
    waitBool(&bConnected, true);

    LOGI("Request login for user: %s\n", pUserLoginField->UserID);

    return pApi->ReqUserLogin(pUserLoginField, nRequestID);
};

//账户登出
int fpRHMonitorApi::ReqUserLogout(CRHMonitorUserLogoutField *pUserLogoutField)
{
    waitBool(&bLogin, true);

    return pApi->ReqUserLogout(pUserLogoutField, nRequestID);
};

//查询所有管理的账户
int fpRHMonitorApi::ReqQryMonitorAccounts(CRHMonitorQryMonitorUser *pQryMonitorUser)
{
    waitBool(&bLogin, true);

    return pApi->ReqQryMonitorAccounts(pQryMonitorUser, nRequestID);
};

///查询账户资金
int fpRHMonitorApi::ReqQryInvestorMoney(CRHMonitorQryInvestorMoneyField *pQryInvestorMoneyField)
{
    waitBool(&bLogin, true);

    return pApi->ReqQryInvestorMoney(pQryInvestorMoneyField, nRequestID);
};

///查询账户持仓
int fpRHMonitorApi::ReqQryInvestorPosition(CRHMonitorQryInvestorPositionField *pQryInvestorPositionField)
{
    waitBool(&bLogin, true);

    return pApi->ReqQryInvestorPosition(pQryInvestorPositionField, nRequestID);
};

//给Server发送强平请求
int fpRHMonitorApi::ReqOffsetOrder(CRHMonitorOffsetOrderField *pMonitorOrderField)
{
    waitBool(&bLogin, true);

    return pApi->ReqOffsetOrder(pMonitorOrderField, nRequestID);
};

//订阅主动推送信息
int fpRHMonitorApi::ReqSubPushInfo(CRHMonitorSubPushInfo *pInfo)
{
    waitBool(&bLogin, true);

    return pApi->ReqSubPushInfo(pInfo, nRequestID);
};

void fpRHMonitorApi::Release()
{
    if (NULL != pApi)
    {
        pApi->Release();
    }
}