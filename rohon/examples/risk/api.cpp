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


///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
void cRHMonitorApi::OnFrontConnected(){ 
    bConnected = true;
    
    LOGE("Front[%s:%d] connected.", remoteAddr, remotePort);
};

///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
///@param nReascRHMonitorApi::On ����ԭ��
///        0x1001 �����ʧ��
///        0x1002 ����дʧ��
///        0x2001 ����������ʱ
///        0x2002 ��������ʧ��
///        0x2003 �յ�������
void cRHMonitorApi::OnFrontDisconnected(int nReason) { 
    bConnected = false;

    LOGE("Front[%s:%d] disconnected: %02x", remoteAddr, remotePort, nReason);
};

///����˻���½��Ӧ
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

///����˻��ǳ���Ӧ
void cRHMonitorApi::OnRspUserLogout(CRHMonitorUserLogoutField *pRspUserLoginField, CRHRspInfoField *pRHRspInfoField){
    CHK_RSP(pRHRspInfoField, "Request user logout");
};

//��ѯ����˻���Ӧ
void cRHMonitorApi::OnRspQryMonitorAccounts(CRHQryInvestorField *pRspMonitorUser, CRHRspInfoField *pRHRspInfoField, bool isLast){};

///��ѯ�˻��ʽ���Ӧ
void cRHMonitorApi::OnRspQryInvestorMoney(CRHTradingAccountField *pRHTradingAccountField, CRHRspInfoField *pRHRspInfoField, bool isLast){};

///��ѯ�˻��ֲ���Ϣ��Ӧ
void cRHMonitorApi::OnRspQryInvestorPosition(CRHMonitorPositionField *pRHMonitorPositionField, CRHRspInfoField *pRHRspInfoField, bool isLast){};

//ƽ��ָ���ʧ��ʱ����Ӧ
void cRHMonitorApi::OnRspOffsetOrder(CRHMonitorOffsetOrderField *pMonitorOrderField, CRHRspInfoField *pRHRspInfoField, bool isLast){};

///����֪ͨ
void cRHMonitorApi::OnRtnOrder(CRHOrderField *pOrder){};

///�ɽ�֪ͨ
void cRHMonitorApi::OnRtnTrade(CRHTradeField *pTrade){};

///�˻��ʽ����仯�ر�
void cRHMonitorApi::OnRtnInvestorMoney(CRHTradingAccountField *pRohonTradingAccountField){};

///�˻�ĳ��Լ�ֲֻر�
void cRHMonitorApi::OnRtnInvestorPosition(CRHMonitorPositionField *pRohonMonitorPositionField){};

void cRHMonitorApi::waitBool(std::atomic<bool>* flag, bool v)
{
    while(*flag != v){ ; }
};

///��ʼ��
///@remark ��ʼ�����л���,ֻ�е��ú�,�ӿڲſ�ʼ����
void cRHMonitorApi::Init(const char *ip, unsigned int port)
{
    pApi->Init(ip, port);

    memcpy(remoteAddr, ip, sizeof(remoteAddr) - 1);
    remotePort = port;
};

///�˻���½
int cRHMonitorApi::ReqUserLogin(CRHMonitorReqUserLoginField *pUserLoginField)
{
    waitBool(&bConnected, true);

    return pApi->ReqUserLogin(pUserLoginField, nRequestID);
};

//�˻��ǳ�
int cRHMonitorApi::ReqUserLogout(CRHMonitorUserLogoutField *pUserLogoutField)
{
    waitBool(&bLogin, true);

    return pApi->ReqUserLogout(pUserLogoutField, nRequestID);
};

//��ѯ���й�����˻�
int cRHMonitorApi::ReqQryMonitorAccounts(CRHMonitorQryMonitorUser *pQryMonitorUser)
{
    waitBool(&bLogin, true);

    return pApi->ReqQryMonitorAccounts(pQryMonitorUser, nRequestID);
};

///��ѯ�˻��ʽ�
int cRHMonitorApi::ReqQryInvestorMoney(CRHMonitorQryInvestorMoneyField *pQryInvestorMoneyField)
{
    waitBool(&bLogin, true);

    return pApi->ReqQryInvestorMoney(pQryInvestorMoneyField, nRequestID);
};

///��ѯ�˻��ֲ�
int cRHMonitorApi::ReqQryInvestorPosition(CRHMonitorQryInvestorPositionField *pQryInvestorPositionField)
{
    waitBool(&bLogin, true);

    return pApi->ReqQryInvestorPosition(pQryInvestorPositionField, nRequestID);
};

//��Server����ǿƽ����
int cRHMonitorApi::ReqOffsetOrder(CRHMonitorOffsetOrderField *pMonitorOrderField)
{
    waitBool(&bLogin, true);

    return pApi->ReqOffsetOrder(pMonitorOrderField, nRequestID);
};

//��������������Ϣ
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