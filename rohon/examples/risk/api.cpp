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


///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
void fpRHMonitorApi::OnFrontConnected(){ 
    bConnected.store(true);
    
    LOGI("Front[%s:%d] connected.", remoteAddr, remotePort);
};

///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
///@param nReascRHMonitorApi::On ����ԭ��
///        0x1001 �����ʧ��
///        0x1002 ����дʧ��
///        0x2001 ����������ʱ
///        0x2002 ��������ʧ��
///        0x2003 �յ�������
void fpRHMonitorApi::OnFrontDisconnected(int nReason) { 
    bConnected.store(false);

    LOGW("Front[%s:%d] disconnected: %02x", remoteAddr, remotePort, nReason);
};

///����˻���½��Ӧ
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

///����˻��ǳ���Ӧ
void fpRHMonitorApi::OnRspUserLogout(CRHMonitorUserLogoutField *pRspUserLoginField, CRHRspInfoField *pRHRspInfoField){
    CHK_RSP(pRHRspInfoField, "Request user logout");
};

//��ѯ����˻���Ӧ
void fpRHMonitorApi::OnRspQryMonitorAccounts(CRHQryInvestorField *pRspMonitorUser, CRHRspInfoField *pRHRspInfoField, bool isLast){};

///��ѯ�˻��ʽ���Ӧ
void fpRHMonitorApi::OnRspQryInvestorMoney(CRHTradingAccountField *pRHTradingAccountField, CRHRspInfoField *pRHRspInfoField, bool isLast){};

///��ѯ�˻��ֲ���Ϣ��Ӧ
void fpRHMonitorApi::OnRspQryInvestorPosition(CRHMonitorPositionField *pRHMonitorPositionField, CRHRspInfoField *pRHRspInfoField, bool isLast){};

//ƽ��ָ���ʧ��ʱ����Ӧ
void fpRHMonitorApi::OnRspOffsetOrder(CRHMonitorOffsetOrderField *pMonitorOrderField, CRHRspInfoField *pRHRspInfoField, bool isLast){};

///����֪ͨ
void fpRHMonitorApi::OnRtnOrder(CRHOrderField *pOrder){};

///�ɽ�֪ͨ
void fpRHMonitorApi::OnRtnTrade(CRHTradeField *pTrade){};

///�˻��ʽ����仯�ر�
void fpRHMonitorApi::OnRtnInvestorMoney(CRHTradingAccountField *pRohonTradingAccountField){};

///�˻�ĳ��Լ�ֲֻر�
void fpRHMonitorApi::OnRtnInvestorPosition(CRHMonitorPositionField *pRohonMonitorPositionField){};

void fpRHMonitorApi::waitBool(std::atomic<bool>* flag, bool v)
{
    while(true) { 
        bool check = flag->load() == v;

        if(check) break;
    }
};

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
    waitBool(&bConnected, true);

    LOGI("Request login for user: %s\n", pUserLoginField->UserID);

    return pApi->ReqUserLogin(pUserLoginField, nRequestID);
};

//�˻��ǳ�
int fpRHMonitorApi::ReqUserLogout(CRHMonitorUserLogoutField *pUserLogoutField)
{
    waitBool(&bLogin, true);

    return pApi->ReqUserLogout(pUserLogoutField, nRequestID);
};

//��ѯ���й�����˻�
int fpRHMonitorApi::ReqQryMonitorAccounts(CRHMonitorQryMonitorUser *pQryMonitorUser)
{
    waitBool(&bLogin, true);

    return pApi->ReqQryMonitorAccounts(pQryMonitorUser, nRequestID);
};

///��ѯ�˻��ʽ�
int fpRHMonitorApi::ReqQryInvestorMoney(CRHMonitorQryInvestorMoneyField *pQryInvestorMoneyField)
{
    waitBool(&bLogin, true);

    return pApi->ReqQryInvestorMoney(pQryInvestorMoneyField, nRequestID);
};

///��ѯ�˻��ֲ�
int fpRHMonitorApi::ReqQryInvestorPosition(CRHMonitorQryInvestorPositionField *pQryInvestorPositionField)
{
    waitBool(&bLogin, true);

    return pApi->ReqQryInvestorPosition(pQryInvestorPositionField, nRequestID);
};

//��Server����ǿƽ����
int fpRHMonitorApi::ReqOffsetOrder(CRHMonitorOffsetOrderField *pMonitorOrderField)
{
    waitBool(&bLogin, true);

    return pApi->ReqOffsetOrder(pMonitorOrderField, nRequestID);
};

//��������������Ϣ
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