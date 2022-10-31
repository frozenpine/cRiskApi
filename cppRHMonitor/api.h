#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <memory.h>
#include <assert.h>
#include <atomic>
#include <stdio.h>
#include <thread>

#include "RHMonitorApi.h"

#define FMTI(fmt) "[TID: %5d] [INFO ] " fmt "\n"
#define FMTW(fmt) "[TID: %5d] [WARNI] " fmt "\n"
#define FMTE(fmt) "[TID: %5d] [ERROR] " fmt "\n"
#define LOGI(fmt, ...) fprintf(stderr, FMTI(fmt), std::this_thread::get_id(), __VA_ARGS__)
#define LOGW(fmt, ...) fprintf(stderr, FMTW(fmt), std::this_thread::get_id(), __VA_ARGS__)
#define LOGE(fmt, ...) fprintf(stderr, FMTE(fmt), std::this_thread::get_id(), __VA_ARGS__)

class fpRHMonitorApi : CRHMonitorSpi
{
public:
    fpRHMonitorApi() : nRequestID(0), remotePort(0), bConnected(false), bLogin(false)
    {
        createInstance();

        memset(remoteAddr, 0, sizeof(remoteAddr));
        memset(&loginInfo, 0, sizeof(loginInfo));
    };

protected:
    ~fpRHMonitorApi()
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
    void setBoolFlag(std::atomic_bool *flag, bool v);
    void waitBoolFlag(std::atomic_bool *flag, bool v);

public:
    ///��ʼ��
    ///@remark ��ʼ�����л���,ֻ�е��ú�,�ӿڲſ�ʼ����
    void Init(const char *ip, unsigned int port);

    ///�˻���½
    int ReqUserLogin(CRHMonitorReqUserLoginField *pUserLoginField);

    //�˻��ǳ�
    int ReqUserLogout();

    //��ѯ���й�����˻�
    int ReqQryMonitorAccounts();

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