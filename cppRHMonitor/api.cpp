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


///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
void fpRHMonitorApi::OnFrontConnected()
{
    LOGI("Front[%s:%d] connected.", remoteAddr.c_str(), remotePort);
    
    setBoolFlag(&bConnected, true);
};

///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
///@param nReascRHMonitorApi::On ����ԭ��
///        0x1001 �����ʧ��
///        0x1002 ����дʧ��
///        0x2001 ����������ʱ
///        0x2002 ��������ʧ��
///        0x2003 �յ�������
void fpRHMonitorApi::OnFrontDisconnected(int nReason)
{
    LOGW("Front[%s:%d] disconnected: %02x", remoteAddr.c_str(), remotePort, nReason);
    
    setBoolFlag(&bConnected, false);
};

///����˻���½��Ӧ
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

///����˻��ǳ���Ӧ
void fpRHMonitorApi::OnRspUserLogout(
    CRHMonitorUserLogoutField *pRspUserLoginField, 
    CRHRspInfoField *pRHRspInfoField,
    int nRequestID)
{
    CHK_RSP(pRHRspInfoField, "Response user logout");

    setBoolFlag(&bLogin, false);
};

//��ѯ����˻���Ӧ
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

///��ѯ�˻��ʽ���Ӧ
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

///��ѯ�˻��ֲ���Ϣ��Ӧ
void fpRHMonitorApi::OnRspQryInvestorPosition(
    CRHMonitorPositionField *pRHMonitorPositionField, 
    CRHRspInfoField *pRHRspInfoField, 
    int nRequestID, bool isLast)
{
    CHK_RSP(pRHRspInfoField, "Response query position");
};

//ƽ��ָ���ʧ��ʱ����Ӧ
void fpRHMonitorApi::OnRspOffsetOrder(
    CRHMonitorOffsetOrderField *pMonitorOrderField, 
    CRHRspInfoField *pRHRspInfoField, 
    int nRequestID, bool isLast)
{
    CHK_RSP(pRHRspInfoField, "Response offset order");
};

///����֪ͨ
void fpRHMonitorApi::OnRtnOrder(CRHOrderField *pOrder){};

///�ɽ�֪ͨ
void fpRHMonitorApi::OnRtnTrade(CRHTradeField *pTrade){};

///�˻��ʽ����仯�ر�
void fpRHMonitorApi::OnRtnInvestorMoney(CRHTradingAccountField *pRohonTradingAccountField){};

///�˻�ĳ��Լ�ֲֻر�
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

///��ʼ��
///@remark ��ʼ�����л���,ֻ�е��ú�,�ӿڲſ�ʼ����
void fpRHMonitorApi::Init(const char *ip, unsigned int port)
{
    pApi->Init(ip, port);

    remoteAddr.assign(ip);
    remotePort = port;
};

///�˻���½
int fpRHMonitorApi::ReqUserLogin(CRHMonitorReqUserLoginField *pUserLoginField)
{
    waitBoolFlag(&bConnected, true);

    LOGI("Request login for user: %s", pUserLoginField->UserID);
    memcpy(&loginInfo, pUserLoginField, sizeof(loginInfo));

    return pApi->ReqUserLogin(pUserLoginField, nRequestID++);
};

//�˻��ǳ�
int fpRHMonitorApi::ReqUserLogout()
{
    waitBoolFlag(&bLogin, true);

    CRHMonitorUserLogoutField logout = CRHMonitorUserLogoutField{0};
    memcpy(&logout.UserID, &loginInfo.UserID, sizeof(logout.UserID) - 1);

    LOGI("Request logout for user: %s", loginInfo.UserID);

    return pApi->ReqUserLogout(&logout, nRequestID++);
};

//��ѯ���й�����˻�
int fpRHMonitorApi::ReqQryMonitorAccounts()
{
    waitBoolFlag(&bLogin, true);

    CRHMonitorQryMonitorUser qry = CRHMonitorQryMonitorUser{0};
    memcpy(&qry.UserID, &loginInfo.UserID, sizeof(qry.UserID) - 1);

    LOGI("Query accounts for user: %s", loginInfo.UserID);

    return pApi->ReqQryMonitorAccounts(&qry, nRequestID++);
};

///��ѯ�˻��ʽ�
int fpRHMonitorApi::ReqQryInvestorMoney(CRHMonitorQryInvestorMoneyField *pQryInvestorMoneyField)
{
    waitBoolFlag(&bLogin, true);

    return pApi->ReqQryInvestorMoney(pQryInvestorMoneyField, nRequestID++);
};

///��ѯ�����˻��ʽ�
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

///��ѯ�˻��ֲ�
int fpRHMonitorApi::ReqQryInvestorPosition(CRHMonitorQryInvestorPositionField *pQryInvestorPositionField)
{
    waitBoolFlag(&bLogin, true);

    return pApi->ReqQryInvestorPosition(pQryInvestorPositionField, nRequestID++);
};

///��ѯ�����˻��ֲ�
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

//��Server����ǿƽ����
int fpRHMonitorApi::ReqOffsetOrder(CRHMonitorOffsetOrderField *pMonitorOrderField)
{
    waitBoolFlag(&bLogin, true);

    return pApi->ReqOffsetOrder(pMonitorOrderField, nRequestID++);
};

//��������������Ϣ
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