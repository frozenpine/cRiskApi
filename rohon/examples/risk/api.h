#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <memory.h>
#include <assert.h>
#include <atomic>

#include "RHMonitorApi.h"

class cRHMonitorApi : CRHMonitorSpi
{
public:
    cRHMonitorApi() : nRequestID(0), bConnected(false), bLogin(false), remotePort(0)
    {
        createInstance();

        memset(remoteAddr, 0, sizeof(remoteAddr));
        memset(&loginInfo, 0, sizeof(loginInfo));
    };

protected:
    ~cRHMonitorApi()
    {
        Release();
    }

private:
    CRHMonitorApi *pApi;
    char remoteAddr[16];
    int remotePort;
    std::atomic_int nRequestID;
    std::atomic_bool bConnected;
    std::atomic_bool bLogin;
    CRHMonitorReqUserLoginField loginInfo;

    void
    createInstance()
    {
        pApi = CRHMonitorApi::CreateRHMonitorApi();

        assert(pApi != NULL);

        pApi->RegisterSpi(this);
    }

protected:
    void waitBool(std::atomic<bool> *flag, bool v);

public:
    ///��ʼ��
    ///@remark ��ʼ�����л���,ֻ�е��ú�,�ӿڲſ�ʼ����
    void
    Init(const char *ip, unsigned int port);

    ///�˻���½
    int ReqUserLogin(CRHMonitorReqUserLoginField *pUserLoginField);

    //�˻��ǳ�
    int ReqUserLogout(CRHMonitorUserLogoutField *pUserLogoutField);

    //��ѯ���й�����˻�
    int ReqQryMonitorAccounts(CRHMonitorQryMonitorUser *pQryMonitorUser);

    ///��ѯ�˻��ʽ�
    int ReqQryInvestorMoney(CRHMonitorQryInvestorMoneyField *pQryInvestorMoneyField);

    ///��ѯ�˻��ֲ�
    int ReqQryInvestorPosition(CRHMonitorQryInvestorPositionField *pQryInvestorPositionField);

    //��Server����ǿƽ����
    int ReqOffsetOrder(CRHMonitorOffsetOrderField *pMonitorOrderField);

    //��������������Ϣ
    int ReqSubPushInfo(CRHMonitorSubPushInfo *pInfo);

    void Release();

    ///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
    virtual void OnFrontConnected();

    ///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
    ///@param nReason ����ԭ��
    ///        0x1001 �����ʧ��
    ///        0x1002 ����дʧ��
    ///        0x2001 ����������ʱ
    ///        0x2002 ��������ʧ��
    ///        0x2003 �յ�������
    virtual void OnFrontDisconnected(int nReason);

    ///����˻���½��Ӧ
    virtual void OnRspUserLogin(CRHMonitorRspUserLoginField *pRspUserLoginField, CRHRspInfoField *pRHRspInfoField);

    ///����˻��ǳ���Ӧ
    virtual void OnRspUserLogout(CRHMonitorUserLogoutField *pRspUserLoginField, CRHRspInfoField *pRHRspInfoField);

    //��ѯ����˻���Ӧ
    virtual void OnRspQryMonitorAccounts(CRHQryInvestorField *pRspMonitorUser, CRHRspInfoField *pRHRspInfoField, bool isLast);

    ///��ѯ�˻��ʽ���Ӧ
    virtual void OnRspQryInvestorMoney(CRHTradingAccountField *pRHTradingAccountField, CRHRspInfoField *pRHRspInfoField, bool isLast);

    ///��ѯ�˻��ֲ���Ϣ��Ӧ
    virtual void OnRspQryInvestorPosition(CRHMonitorPositionField *pRHMonitorPositionField, CRHRspInfoField *pRHRspInfoField, bool isLast);

    //ƽ��ָ���ʧ��ʱ����Ӧ
    virtual void OnRspOffsetOrder(CRHMonitorOffsetOrderField *pMonitorOrderField, CRHRspInfoField *pRHRspInfoField, bool isLast);

    ///����֪ͨ
    virtual void OnRtnOrder(CRHOrderField *pOrder);

    ///�ɽ�֪ͨ
    virtual void OnRtnTrade(CRHTradeField *pTrade);

    ///�˻��ʽ����仯�ر�
    virtual void OnRtnInvestorMoney(CRHTradingAccountField *pRohonTradingAccountField);

    ///�˻�ĳ��Լ�ֲֻر�
    virtual void OnRtnInvestorPosition(CRHMonitorPositionField *pRohonMonitorPositionField);
};