#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <memory.h>
#include <assert.h>
#include <atomic>
#include <stdio.h>
#include <thread>
#include <map>
#include <string>

#include "RHMonitorApi.h"

#ifndef THREAD_ID
#define THREAD_ID
static inline unsigned int get_thread_id()
{
    std::hash<std::thread::id> hasher;
    return hasher(std::this_thread::get_id());
}
#endif

#define FMTI(fmt) "[TID: %5u] [INFO ] " fmt "\n"
#define FMTW(fmt) "[TID: %5u] [WARNI] " fmt "\n"
#define FMTE(fmt) "%s(%d)-<%s> [TID: %5u] [ERROR] " fmt "\n"
#define LOGI(fmt, ...) fprintf(stderr, FMTI(fmt), get_thread_id(), ##__VA_ARGS__)
#define LOGW(fmt, ...) fprintf(stderr, FMTW(fmt), get_thread_id(), ##__VA_ARGS__)
#define LOGE(fmt, ...) fprintf(stderr, FMTE(fmt), __FILE__, __LINE__, __FUNCTION__, get_thread_id(), ##__VA_ARGS__)

class fpRHMonitorApi : public CRHMonitorSpi
{
public:
    fpRHMonitorApi(const char *brokerID) : nRequestID(0), remotePort(0), bConnected(false), bLogin(false), bInvestorReady(false)
    {
        createInstance();

        this->brokerID.assign(brokerID);
        memset(&loginInfo, 0, sizeof(loginInfo));
    };

protected:
    ~fpRHMonitorApi()
    {
        Release();
    }

private:
    CRHMonitorApi *pApi;

    std::string remoteAddr;
    int remotePort;
    std::string brokerID;

    std::atomic_int nRequestID;

    std::atomic_bool bConnected;
    std::atomic_bool bLogin;
    std::atomic_bool bInvestorReady;

    CRHMonitorReqUserLoginField loginInfo;
    std::map<std::string, CRHQryInvestorField *> investorsCache;

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

    //��ѯ���й������˻�
    int ReqQryMonitorAccounts();

    ///��ѯ�˻��ʽ�
    int ReqQryInvestorMoney(CRHMonitorQryInvestorMoneyField *pQryInvestorMoneyField);

    ///��ѯ�����˻��ʽ�
    int ReqQryAllInvestorMoney();

    ///��ѯ�˻��ֲ�
    int ReqQryInvestorPosition(CRHMonitorQryInvestorPositionField *pQryInvestorPositionField);

    ///��ѯ�����˻��ֲ�
    int ReqQryAllInvestorPosition();

    //��Server����ǿƽ����
    int ReqOffsetOrder(CRHMonitorOffsetOrderField *pMonitorOrderField);

    //��������������Ϣ
    int ReqSubPushInfo(CRHMonitorSubPushInfo *pInfo);

    void Release();

    ///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
    virtual void OnFrontConnected();

    ///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ���������
    ///@param nReason ����ԭ��
    ///        0x1001 �����ʧ��
    ///        0x1002 ����дʧ��
    ///        0x2001 ����������ʱ
    ///        0x2002 ��������ʧ��
    ///        0x2003 �յ�������
    virtual void OnFrontDisconnected(int nReason);

    ///����˻���½��Ӧ
    virtual void OnRspUserLogin(CRHMonitorRspUserLoginField *pRspUserLoginField, CRHRspInfoField *pRHRspInfoField, int nRequestID);

    ///����˻��ǳ���Ӧ
    virtual void OnRspUserLogout(CRHMonitorUserLogoutField *pRspUserLoginField, CRHRspInfoField *pRHRspInfoField, int nRequestID);

    //��ѯ����˻���Ӧ
    virtual void OnRspQryMonitorAccounts(CRHQryInvestorField *pRspMonitorUser, CRHRspInfoField *pRHRspInfoField, int nRequestID, bool isLast);

    ///��ѯ�˻��ʽ���Ӧ
    virtual void OnRspQryInvestorMoney(CRHTradingAccountField *pRHTradingAccountField, CRHRspInfoField *pRHRspInfoField, int nRequestID, bool isLast);

    ///��ѯ�˻��ֲ���Ϣ��Ӧ
    virtual void OnRspQryInvestorPosition(CRHMonitorPositionField *pRHMonitorPositionField, CRHRspInfoField *pRHRspInfoField, int nRequestID, bool isLast);

    //ƽ��ָ���ʧ��ʱ����Ӧ
    virtual void OnRspOffsetOrder(CRHMonitorOffsetOrderField *pMonitorOrderField, CRHRspInfoField *pRHRspInfoField, int nRequestID, bool isLast);

    ///����֪ͨ
    virtual void OnRtnOrder(CRHOrderField *pOrder);

    ///�ɽ�֪ͨ
    virtual void OnRtnTrade(CRHTradeField *pTrade);

    ///�˻��ʽ����仯�ر�
    virtual void OnRtnInvestorMoney(CRHTradingAccountField *pRohonTradingAccountField);

    ///�˻�ĳ��Լ�ֲֻر�
    virtual void OnRtnInvestorPosition(CRHMonitorPositionField *pRohonMonitorPositionField);
};