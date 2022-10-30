#include <memory.h>
#include <assert.h>

#include "RHMonitorApi.h"
#include "cRHMonitorApi.h"

class C_API cRHMonitorApi : CRHMonitorSpi
{
public:
    cRHMonitorApi()
    {
        memset(&vtCallbacks, 0, sizeof(callback_t));

        createInstance();
    };
    cRHMonitorApi(callback_t *vt)
    {
        SetCallback(vt);

        createInstance();
    };

protected:
    ~cRHMonitorApi()
    {
        Release();
    }

private:
    CRHMonitorApi *pApi;
    callback_t vtCallbacks;

    void
    createInstance()
    {
        pApi = CRHMonitorApi::CreateRHMonitorApi();

        assert(pApi != NULL);

        pApi->RegisterSpi(this);
    }

public:
    void SetCallback(callback_t *vt)
    {
        memcpy(&vtCallbacks, vt, sizeof(callback_t));
    }

    void SetCbOnFrontConnected(CbOnFrontConnected handler)
    {
        vtCallbacks.cOnFrontConnected = handler;
    }

    void SetCbOnFrontDisconnected(CbOnFrontDisconnected handler)
    {
        vtCallbacks.cOnFrontDisconnected = handler;
    }

    void SetCbOnRspUserLogin(CbOnRspUserLogin handler)
    {
        vtCallbacks.cOnRspUserLogin = handler;
    }

    void SetCbOnRspUserLogout(CbOnRspUserLogout handler)
    {
        vtCallbacks.cOnRspUserLogout = handler;
    }

    void SetCbOnRspQryMonitorAccounts(CbOnRspQryMonitorAccounts handler)
    {
        vtCallbacks.cOnRspQryMonitorAccounts = handler;
    }

    void SetCbOnRspQryInvestorMoney(CbOnRspQryInvestorMoney handler)
    {
        vtCallbacks.cOnRspQryInvestorMoney = handler;
    }

    void SetCbOnRspQryInvestorPosition(CbOnRspQryInvestorPosition handler)
    {
        vtCallbacks.cOnRspQryInvestorPosition = handler;
    }

    void SetCbOnRspOffsetOrder(CbOnRspOffsetOrder handler)
    {
        vtCallbacks.cOnRspOffsetOrder = handler;
    }

    void SetCbOnRtnOrder(CbOnRtnOrder handler)
    {
        vtCallbacks.cOnRtnOrder = handler;
    }

    void SetCbOnRtnTrade(CbOnRtnTrade handler)
    {
        vtCallbacks.cOnRtnTrade = handler;
    }

    void SetCbOnRtnInvestorMoney(CbOnRtnInvestorMoney handler)
    {
        vtCallbacks.cOnRtnInvestorMoney = handler;
    }

    void SetCbOnRtnInvestorPosition(CbOnRtnInvestorPosition handler)
    {
        vtCallbacks.cOnRtnInvestorPosition = handler;
    }

    /// ��ʼ��
    ///@remark ��ʼ�����л���,ֻ�е��ú�,�ӿڲſ�ʼ����
    void
    Init(const char *ip, unsigned int port)
    {
        pApi->Init(ip, port);
    };

    /// �˻���½
    int ReqUserLogin(CRHMonitorReqUserLoginField *pUserLoginField, int nRequestID)
    {
        return pApi->ReqUserLogin(pUserLoginField, nRequestID);
    };

    // �˻��ǳ�
    int ReqUserLogout(CRHMonitorUserLogoutField *pUserLogoutField, int nRequestID)
    {
        return pApi->ReqUserLogout(pUserLogoutField, nRequestID);
    };

    // ��ѯ���й�����˻�
    int ReqQryMonitorAccounts(CRHMonitorQryMonitorUser *pQryMonitorUser, int nRequestID)
    {
        return pApi->ReqQryMonitorAccounts(pQryMonitorUser, nRequestID);
    };

    /// ��ѯ�˻��ʽ�
    int ReqQryInvestorMoney(CRHMonitorQryInvestorMoneyField *pQryInvestorMoneyField, int nRequestID)
    {
        return pApi->ReqQryInvestorMoney(pQryInvestorMoneyField, nRequestID);
    };

    /// ��ѯ�˻��ֲ�
    int ReqQryInvestorPosition(CRHMonitorQryInvestorPositionField *pQryInvestorPositionField, int nRequestID)
    {
        return pApi->ReqQryInvestorPosition(pQryInvestorPositionField, nRequestID);
    };

    // ��Server����ǿƽ����
    int ReqOffsetOrder(CRHMonitorOffsetOrderField *pMonitorOrderField, int nRequestID)
    {
        return pApi->ReqOffsetOrder(pMonitorOrderField, nRequestID);
    };

    // ��������������Ϣ
    int ReqSubPushInfo(CRHMonitorSubPushInfo *pInfo, int nRequestID)
    {
        return pApi->ReqSubPushInfo(pInfo, nRequestID);
    };

    /// ���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
    void OnFrontConnected()
    {
        if (!vtCallbacks.cOnFrontConnected)
            return;

        vtCallbacks.cOnFrontConnected(CRHMonitorInstance(this));
    };

    /// ���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
    ///@param nReason ����ԭ��
    ///         0x1001 �����ʧ��
    ///         0x1002 ����дʧ��
    ///         0x2001 ����������ʱ
    ///         0x2002 ��������ʧ��
    ///         0x2003 �յ�������
    void OnFrontDisconnected(int nReason)
    {
        if (!vtCallbacks.cOnFrontDisconnected)
            return;

        vtCallbacks.cOnFrontDisconnected(CRHMonitorInstance(this), nReason);
    };

    /// ����˻���½��Ӧ
    void OnRspUserLogin(CRHMonitorRspUserLoginField *pRspUserLoginField, CRHRspInfoField *pRHRspInfoField, int nRequestID){};

    /// ����˻��ǳ���Ӧ
    void OnRspUserLogout(CRHMonitorUserLogoutField *pRspUserLoginField, CRHRspInfoField *pRHRspInfoField, int nRequestID){};

    // ��ѯ����˻���Ӧ
    void OnRspQryMonitorAccounts(CRHQryInvestorField *pRspMonitorUser, CRHRspInfoField *pRHRspInfoField, int nRequestID, bool isLast){};

    /// ��ѯ�˻��ʽ���Ӧ
    void OnRspQryInvestorMoney(CRHTradingAccountField *pRHTradingAccountField, CRHRspInfoField *pRHRspInfoField, int nRequestID, bool isLast){};

    /// ��ѯ�˻��ֲ���Ϣ��Ӧ
    void OnRspQryInvestorPosition(CRHMonitorPositionField *pRHMonitorPositionField, CRHRspInfoField *pRHRspInfoField, int nRequestID, bool isLast){};

    // ƽ��ָ���ʧ��ʱ����Ӧ
    void OnRspOffsetOrder(CRHMonitorOffsetOrderField *pMonitorOrderField, CRHRspInfoField *pRHRspInfoField, int nRequestID, bool isLast){};

    /// ����֪ͨ
    void OnRtnOrder(CRHOrderField *pOrder){};

    /// �ɽ�֪ͨ
    void OnRtnTrade(CRHTradeField *pTrade){};

    /// �˻��ʽ����仯�ر�
    void OnRtnInvestorMoney(CRHTradingAccountField *pRohonTradingAccountField){};

    /// �˻�ĳ��Լ�ֲֻر�
    void OnRtnInvestorPosition(CRHMonitorPositionField *pRohonMonitorPositionField){};

    void Release()
    {
        memset(&vtCallbacks, 0, sizeof(callback_t));

        if (NULL != pApi)
        {
            pApi->Release();
        }
    }
};

#ifdef __cplusplus
extern "C"
{
#endif

    C_API CRHMonitorInstance CreateRHMonitorApi()
    {
        cRHMonitorApi *instance = new cRHMonitorApi();

        return CRHMonitorInstance(instance);
    }

    C_API void Release(CRHMonitorInstance instance)
    {
        ((cRHMonitorApi *)instance)->Release();
    }

    C_API void Init(CRHMonitorInstance instance, const char *ip, unsigned int port)
    {
        ((cRHMonitorApi *)instance)->Init(ip, port);
    }

    C_API int ReqUserLogin(CRHMonitorInstance instance, struct CRHMonitorReqUserLoginField *pUserLoginField, int nRequestID)
    {
        return ((cRHMonitorApi *)instance)->ReqUserLogin(pUserLoginField, nRequestID);
    }

    C_API int ReqUserLogout(CRHMonitorInstance instance, struct CRHMonitorUserLogoutField *pUserLogoutField, int nRequestID)
    {
        return ((cRHMonitorApi *)instance)->ReqUserLogout(pUserLogoutField, nRequestID);
    }

    C_API int ReqQryMonitorAccounts(CRHMonitorInstance instance, struct CRHMonitorQryMonitorUser *pQryMonitorUser, int nRequestID)
    {
        return ((cRHMonitorApi *)instance)->ReqQryMonitorAccounts(pQryMonitorUser, nRequestID);
    }

    C_API int ReqQryInvestorMoney(CRHMonitorInstance instance, struct CRHMonitorQryInvestorMoneyField *pQryInvestorMoneyField, int nRequestID)
    {
        return ((cRHMonitorApi *)instance)->ReqQryInvestorMoney(pQryInvestorMoneyField, nRequestID);
    }

    C_API int ReqQryInvestorPosition(CRHMonitorInstance instance, struct CRHMonitorQryInvestorPositionField *pQryInvestorPositionField, int nRequestID)
    {
        return ((cRHMonitorApi *)instance)->ReqQryInvestorPosition(pQryInvestorPositionField, nRequestID);
    }

    C_API int ReqOffsetOrder(CRHMonitorInstance instance, struct CRHMonitorOffsetOrderField *pMonitorOrderField, int nRequestID)
    {
        return ((cRHMonitorApi *)instance)->ReqOffsetOrder(pMonitorOrderField, nRequestID);
    }

    C_API int ReqSubPushInfo(CRHMonitorInstance instance, struct CRHMonitorSubPushInfo *pInfo, int nRequestID)
    {
        return ((cRHMonitorApi *)instance)->ReqSubPushInfo(pInfo, nRequestID);
    }

    C_API void SetCallbacks(CRHMonitorInstance instance, callback_t *vt)
    {
        ((cRHMonitorApi *)instance)->SetCallback(vt);
    }

    C_API void SetCbOnFrontConnected(CRHMonitorInstance instance, CbOnFrontConnected handler)
    {
        ((cRHMonitorApi *)instance)->SetCbOnFrontConnected(handler);
    }

    C_API void SetCbOnFrontDisconnected(CRHMonitorInstance instance, CbOnFrontDisconnected handler)
    {
        ((cRHMonitorApi *)instance)->SetCbOnFrontDisconnected(handler);
    }

    C_API void SetCbOnRspUserLogin(CRHMonitorInstance instance, CbOnRspUserLogin handler)
    {
        ((cRHMonitorApi *)instance)->SetCbOnRspUserLogin(handler);
    }

    C_API void SetCbOnRspUserLogout(CRHMonitorInstance instance, CbOnRspUserLogout handler)
    {
        ((cRHMonitorApi *)instance)->SetCbOnRspUserLogout(handler);
    }

    C_API void SetCbOnRspQryMonitorAccounts(CRHMonitorInstance instance, CbOnRspQryMonitorAccounts handler)
    {
        ((cRHMonitorApi *)instance)->SetCbOnRspQryMonitorAccounts(handler);
    }

    C_API void SetCbOnRspQryInvestorMoney(CRHMonitorInstance instance, CbOnRspQryInvestorMoney handler)
    {
        ((cRHMonitorApi *)instance)->SetCbOnRspQryInvestorMoney(handler);
    }

    C_API void SetCbOnRspQryInvestorPosition(CRHMonitorInstance instance, CbOnRspQryInvestorPosition handler)
    {
        ((cRHMonitorApi *)instance)->SetCbOnRspQryInvestorPosition(handler);
    }

    C_API void SetCbOnRspOffsetOrder(CRHMonitorInstance instance, CbOnRspOffsetOrder handler)
    {
        ((cRHMonitorApi *)instance)->SetCbOnRspOffsetOrder(handler);
    }

    C_API void SetCbOnRtnOrder(CRHMonitorInstance instance, CbOnRtnOrder handler)
    {
        ((cRHMonitorApi *)instance)->SetCbOnRtnOrder(handler);
    }

    C_API void SetCbOnRtnTrade(CRHMonitorInstance instance, CbOnRtnTrade handler)
    {
        ((cRHMonitorApi *)instance)->SetCbOnRtnTrade(handler);
    }

    C_API void SetCbOnRtnInvestorMoney(CRHMonitorInstance instance, CbOnRtnInvestorMoney handler)
    {
        ((cRHMonitorApi *)instance)->SetCbOnRtnInvestorMoney(handler);
    }

    C_API void SetCbOnRtnInvestorPosition(CRHMonitorInstance instance, CbOnRtnInvestorPosition handler)
    {
        ((cRHMonitorApi *)instance)->SetCbOnRtnInvestorPosition(handler);
    }

#ifdef __cplusplus
}
#endif