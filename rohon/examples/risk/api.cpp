#include <stdio.h>

#include "api.h"

#define LOGE(fmt, ...) fprintf(stderr, (fmt), __VA_ARGS__)

#define CHK_RSP(rsp, msg) do { \
    if ((rsp)->ErrorID != 0) { \
        LOGE("%s failed[%d]: %s\n", (msg), (rsp)->ErrorID, (rsp)->ErrorMsg); \
        return; \
    } \
    LOGE("%s success: %s\n", (msg), (rsp)->ErrorMsg); \
} while (false)


///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
void cRHMonitorApi::OnFrontConnected(){ 
    bConnected = true;
    
    LOGE("Front[%s:%d] connected.", remoteAddr, remotePort);
};

///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
///@param nReascRHMonitorApi::On 错误原因
///        0x1001 网络读失败
///        0x1002 网络写失败
///        0x2001 接收心跳超时
///        0x2002 发送心跳失败
///        0x2003 收到错误报文
void cRHMonitorApi::OnFrontDisconnected(int nReason) { 
    bConnected = false;

    LOGE("Front[%s:%d] disconnected: %02x", remoteAddr, remotePort, nReason);
};

///风控账户登陆响应
void cRHMonitorApi::OnRspUserLogin(CRHMonitorRspUserLoginField *pRspUserLoginField, CRHRspInfoField *pRHRspInfoField){
    CHK_RSP(pRHRspInfoField, "Request user login");

    memcpy(&loginInfo, pRspUserLoginField, sizeof(loginInfo));

    LOGE(
        "Risk user[%s] logged in: %s %s\n", 
        pRspUserLoginField->UserID, 
        pRspUserLoginField->TradingDay, 
        pRspUserLoginField->LoginTime
    );
};

///风控账户登出响应
void cRHMonitorApi::OnRspUserLogout(CRHMonitorUserLogoutField *pRspUserLoginField, CRHRspInfoField *pRHRspInfoField){
    CHK_RSP(pRHRspInfoField, "Request user logout");
};

//查询监控账户响应
void cRHMonitorApi::OnRspQryMonitorAccounts(CRHQryInvestorField *pRspMonitorUser, CRHRspInfoField *pRHRspInfoField, bool isLast){};

///查询账户资金响应
void cRHMonitorApi::OnRspQryInvestorMoney(CRHTradingAccountField *pRHTradingAccountField, CRHRspInfoField *pRHRspInfoField, bool isLast){};

///查询账户持仓信息响应
void cRHMonitorApi::OnRspQryInvestorPosition(CRHMonitorPositionField *pRHMonitorPositionField, CRHRspInfoField *pRHRspInfoField, bool isLast){};

//平仓指令发送失败时的响应
void cRHMonitorApi::OnRspOffsetOrder(CRHMonitorOffsetOrderField *pMonitorOrderField, CRHRspInfoField *pRHRspInfoField, bool isLast){};

///报单通知
void cRHMonitorApi::OnRtnOrder(CRHOrderField *pOrder){};

///成交通知
void cRHMonitorApi::OnRtnTrade(CRHTradeField *pTrade){};

///账户资金发生变化回报
void cRHMonitorApi::OnRtnInvestorMoney(CRHTradingAccountField *pRohonTradingAccountField){};

///账户某合约持仓回报
void cRHMonitorApi::OnRtnInvestorPosition(CRHMonitorPositionField *pRohonMonitorPositionField){};

void cRHMonitorApi::waitBool(std::atomic<bool>* flag, bool v)
{
    while(*flag != v){ ; }
};

///初始化
///@remark 初始化运行环境,只有调用后,接口才开始工作
void cRHMonitorApi::Init(const char *ip, unsigned int port)
{
    pApi->Init(ip, port);

    memcpy(remoteAddr, ip, sizeof(remoteAddr) - 1);
    remotePort = port;
};

///账户登陆
int cRHMonitorApi::ReqUserLogin(CRHMonitorReqUserLoginField *pUserLoginField)
{
    waitBool(&bConnected, true);

    return pApi->ReqUserLogin(pUserLoginField, nRequestID);
};

//账户登出
int cRHMonitorApi::ReqUserLogout(CRHMonitorUserLogoutField *pUserLogoutField)
{
    waitBool(&bLogin, true);

    return pApi->ReqUserLogout(pUserLogoutField, nRequestID);
};

//查询所有管理的账户
int cRHMonitorApi::ReqQryMonitorAccounts(CRHMonitorQryMonitorUser *pQryMonitorUser)
{
    waitBool(&bLogin, true);

    return pApi->ReqQryMonitorAccounts(pQryMonitorUser, nRequestID);
};

///查询账户资金
int cRHMonitorApi::ReqQryInvestorMoney(CRHMonitorQryInvestorMoneyField *pQryInvestorMoneyField)
{
    waitBool(&bLogin, true);

    return pApi->ReqQryInvestorMoney(pQryInvestorMoneyField, nRequestID);
};

///查询账户持仓
int cRHMonitorApi::ReqQryInvestorPosition(CRHMonitorQryInvestorPositionField *pQryInvestorPositionField)
{
    waitBool(&bLogin, true);

    return pApi->ReqQryInvestorPosition(pQryInvestorPositionField, nRequestID);
};

//给Server发送强平请求
int cRHMonitorApi::ReqOffsetOrder(CRHMonitorOffsetOrderField *pMonitorOrderField)
{
    waitBool(&bLogin, true);

    return pApi->ReqOffsetOrder(pMonitorOrderField, nRequestID);
};

//订阅主动推送信息
int cRHMonitorApi::ReqSubPushInfo(CRHMonitorSubPushInfo *pInfo)
{
    waitBool(&bLogin, true);

    return pApi->ReqSubPushInfo(pInfo, nRequestID);
};

void cRHMonitorApi::Release()
{
    if (NULL != pApi)
    {
        pApi->Release();
    }
}