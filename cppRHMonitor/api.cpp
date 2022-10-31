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

///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
void fpRHMonitorApi::OnFrontConnected()
{
    LOGI("Front[%s:%d] connected.", remoteAddr, remotePort);
    
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
    LOGW("Front[%s:%d] disconnected: %02x", remoteAddr, remotePort, nReason);
    
    setBoolFlag(&bConnected, false);
};

///����˻���½��Ӧ
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

///����˻��ǳ���Ӧ
void fpRHMonitorApi::OnRspUserLogout(
    CRHMonitorUserLogoutField *pRspUserLoginField, 
    CRHRspInfoField *pRHRspInfoField,
    int nRequestID)
{
    CHK_RSP(pRHRspInfoField, "Request user logout");

    setBoolFlag(&bLogin, false);
};

//��ѯ����˻���Ӧ
void fpRHMonitorApi::OnRspQryMonitorAccounts(
    CRHQryInvestorField *pRspMonitorUser, 
    CRHRspInfoField *pRHRspInfoField, 
    int nRequestID, bool isLast)
{
    CHK_RSP(pRHRspInfoField, "Request query accounts");
};

///��ѯ�˻��ʽ���Ӧ
void fpRHMonitorApi::OnRspQryInvestorMoney(
    CRHTradingAccountField *pRHTradingAccountField, 
    CRHRspInfoField *pRHRspInfoField, 
    int nRequestID, bool isLast)
{
    CHK_RSP(pRHRspInfoField, "Request query money");
};

///��ѯ�˻��ֲ���Ϣ��Ӧ
void fpRHMonitorApi::OnRspQryInvestorPosition(
    CRHMonitorPositionField *pRHMonitorPositionField, 
    CRHRspInfoField *pRHRspInfoField, 
    int nRequestID, bool isLast)
{
    CHK_RSP(pRHRspInfoField, "Request query position");
};

//ƽ��ָ���ʧ��ʱ����Ӧ
void fpRHMonitorApi::OnRspOffsetOrder(
    CRHMonitorOffsetOrderField *pMonitorOrderField, 
    CRHRspInfoField *pRHRspInfoField, 
    int nRequestID, bool isLast)
{
    CHK_RSP(pRHRspInfoField, "Request offset order");
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

    memcpy(remoteAddr, ip, sizeof(remoteAddr) - 1);
    remotePort = port;
};

///�˻���½
int fpRHMonitorApi::ReqUserLogin(CRHMonitorReqUserLoginField *pUserLoginField)
{
    waitBoolFlag(&bConnected, true);

    LOGI("Request login for user: %s", pUserLoginField->UserID);

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

///��ѯ�˻��ֲ�
int fpRHMonitorApi::ReqQryInvestorPosition(CRHMonitorQryInvestorPositionField *pQryInvestorPositionField)
{
    waitBoolFlag(&bLogin, true);

    return pApi->ReqQryInvestorPosition(pQryInvestorPositionField, nRequestID++);
};

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