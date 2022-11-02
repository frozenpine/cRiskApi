#include "api.h"

#define CHK_RSP(rsp, msg)                                                      \
    do                                                                         \
    {                                                                          \
        if (NULL == rsp) break;                                                \
        if ((rsp)->ErrorID > 0)                                                \
        {                                                                      \
            LOGE("%s failed[%d]: %s", (msg), (rsp)->ErrorID, (rsp)->ErrorMsg); \
            return;                                                            \
        }                                                                      \
        LOGI("%s success: %s", (msg), (rsp)->ErrorMsg);                        \
    } while (false)


///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
void fpRHMonitorApi::OnFrontConnected()
{
    LOGI("Front[%s:%d] connected.", remoteAddr.c_str(), remotePort);
    
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
    LOGW("Front[%s:%d] disconnected: %02x", remoteAddr.c_str(), remotePort, nReason);
    
    setBoolFlag(&bConnected, false);
};

///风控账户登陆响应
void fpRHMonitorApi::OnRspUserLogin(
    CRHMonitorRspUserLoginField *pRspUserLoginField, 
    CRHRspInfoField *pRHRspInfoField,
    int nRequestID)
{
    CHK_RSP(pRHRspInfoField, "Response user login");

    LOGI(
        "Risk user[%s] logged in: %s %s",
        loginInfo.UserID,
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
    CHK_RSP(pRHRspInfoField, "Response user logout");

    setBoolFlag(&bLogin, false);
};

//查询监控账户响应
void fpRHMonitorApi::OnRspQryMonitorAccounts(
    CRHQryInvestorField *pRspMonitorUser, 
    CRHRspInfoField *pRHRspInfoField, 
    int nRequestID, bool isLast)
{
    CHK_RSP(pRHRspInfoField, "Response query accounts");

    if (NULL != pRspMonitorUser) {
        LOGI("Managed account: %s.%s", brokerID.c_str(), pRspMonitorUser->InvestorID);

        CRHQryInvestorField* investor = (CRHQryInvestorField*)malloc(sizeof(CRHQryInvestorField));
        assert(investor != NULL);
        memset(investor, 0, sizeof(CRHQryInvestorField));
        memcpy(investor, pRspMonitorUser, sizeof(CRHQryInvestorField));

        std::string identity = investor->BrokerID;
        identity.append(".");
        identity.append(investor->InvestorID);

        investorsCache[identity] = investor;
    }

    if (isLast) {
        LOGI("All managed account queried.");
        setBoolFlag(&bInvestorReady, true);
    }
};

///查询账户资金响应
void fpRHMonitorApi::OnRspQryInvestorMoney(
    CRHTradingAccountField *pRHTradingAccountField, 
    CRHRspInfoField *pRHRspInfoField, 
    int nRequestID, bool isLast)
{
    CHK_RSP(pRHRspInfoField, "Response query money");

    if (NULL != pRHTradingAccountField) {
        fprintf(stderr, "[%s] Account[%s]'s money:\n", pRHTradingAccountField->TradingDay, pRHTradingAccountField->AccountID);
        fprintf(stderr, "PreBalance: %.2f\n", pRHTradingAccountField->PreBalance);
        fprintf(stderr, "Balance: %.2f\n", pRHTradingAccountField->Balance);
        fprintf(stderr, "Available: %.2f\n", pRHTradingAccountField->Available);
        fprintf(stderr, "Interest: %.2f\n", pRHTradingAccountField->Interest);
        fprintf(stderr, "Deposit: %.2f\n", pRHTradingAccountField->Deposit);
        fprintf(stderr, "Withdraw: %.2f\n", pRHTradingAccountField->Withdraw);
        fprintf(stderr, "CurrMargin: %.2f\n", pRHTradingAccountField->CurrMargin);
        fprintf(stderr, "Commission: %.2f\n", pRHTradingAccountField->Commission);
        fprintf(stderr, "CloseProfit: %.2f\n", pRHTradingAccountField->CloseProfit);
        fprintf(stderr, "OpenProfit: %.2f\n", pRHTradingAccountField->PositionProfit);
    }
};

///查询账户持仓信息响应
void fpRHMonitorApi::OnRspQryInvestorPosition(
    CRHMonitorPositionField *pRHMonitorPositionField, 
    CRHRspInfoField *pRHRspInfoField, 
    int nRequestID, bool isLast)
{
    CHK_RSP(pRHRspInfoField, "Response query position");
};

//平仓指令发送失败时的响应
void fpRHMonitorApi::OnRspOffsetOrder(
    CRHMonitorOffsetOrderField *pMonitorOrderField, 
    CRHRspInfoField *pRHRspInfoField, 
    int nRequestID, bool isLast)
{
    CHK_RSP(pRHRspInfoField, "Response offset order");
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

    remoteAddr.assign(ip);
    remotePort = port;
};

///账户登陆
int fpRHMonitorApi::ReqUserLogin(CRHMonitorReqUserLoginField *pUserLoginField)
{
    waitBoolFlag(&bConnected, true);

    LOGI("Request login for user: %s", pUserLoginField->UserID);
    memcpy(&loginInfo, pUserLoginField, sizeof(loginInfo));

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

///查询所有账户资金
int fpRHMonitorApi::ReqQryAllInvestorMoney()
{
    waitBoolFlag(&bInvestorReady, true);

    int rtn = 0;

    for (auto iter = investorsCache.begin(); iter != investorsCache.end(); iter++) {
        CRHMonitorQryInvestorMoneyField money = CRHMonitorQryInvestorMoneyField{ 0 };

        // memcpy(&money.BrokerID, brokerID.c_str(), sizeof(money.BrokerID) - 1);
        memcpy(&money.BrokerID, iter->second->BrokerID, sizeof(money.BrokerID) - 1);
        memcpy(&money.InvestorID, iter->second->InvestorID, sizeof(money.InvestorID) - 1);

        LOGI("Query investor[%s]'s money.", iter->second->InvestorID);

        rtn = ReqQryInvestorMoney(&money);

        if (0 != rtn) break;
    }

    return rtn;
}

///查询账户持仓
int fpRHMonitorApi::ReqQryInvestorPosition(CRHMonitorQryInvestorPositionField *pQryInvestorPositionField)
{
    waitBoolFlag(&bLogin, true);

    return pApi->ReqQryInvestorPosition(pQryInvestorPositionField, nRequestID++);
};

///查询所有账户持仓
int fpRHMonitorApi::ReqQryAllInvestorPosition()
{
    waitBoolFlag(&bInvestorReady, true);

    int rtn = 0;

    for (auto iter = investorsCache.begin(); iter != investorsCache.end(); iter++) {
        CRHMonitorQryInvestorPositionField pos = CRHMonitorQryInvestorPositionField{ 0 };

        // memcpy(&pos.BrokerID, brokerID.c_str(), sizeof(pos.BrokerID) - 1);
        memcpy(&pos.BrokerID, iter->second->BrokerID, sizeof(pos.BrokerID) - 1);
        memcpy(&pos.InvestorID, iter->second->InvestorID, sizeof(pos.InvestorID) - 1);

        LOGI("Query investor[%s]'s position.", iter->second->InvestorID);

        rtn = ReqQryInvestorPosition(&pos);

        if (0 != rtn) break;
    }

    return rtn;
}

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