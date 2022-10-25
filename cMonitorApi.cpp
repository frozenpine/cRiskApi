#include <memory.h>
#include <assert.h>

#include "RHMonitorApi.h"
#include "cMonitorApi.h"

C_API class cRHMonitorApi : CRHMonitorSpi
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
        memset(&vtCallbacks, 0, sizeof(callback_t));

        if (NULL != pApi)
        {
            pApi->Release();
        }
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
    ///初始化
    ///@remark 初始化运行环境,只有调用后,接口才开始工作
    void Init(const char *ip, unsigned int port)
    {
        pApi->Init(ip, port);
    };

    ///账户登陆
    int ReqUserLogin(CRHMonitorReqUserLoginField *pUserLoginField, int nRequestID)
    {
        pApi->ReqUserLogin(pUserLoginField, nRequestID);
    };

    //账户登出
    int ReqUserLogout(CRHMonitorUserLogoutField *pUserLogoutField, int nRequestID)
    {
        pApi->ReqUserLogout(pUserLogoutField, nRequestID);
    };

    //查询所有管理的账户
    int ReqQryMonitorAccounts(CRHMonitorQryMonitorUser *pQryMonitorUser, int nRequestID)
    {
        pApi->ReqQryMonitorAccounts(pQryMonitorUser, nRequestID);
    };

    ///查询账户资金
    int ReqQryInvestorMoney(CRHMonitorQryInvestorMoneyField *pQryInvestorMoneyField, int nRequestID)
    {
        pApi->ReqQryInvestorMoney(pQryInvestorMoneyField, nRequestID);
    };

    ///查询账户持仓
    int ReqQryInvestorPosition(CRHMonitorQryInvestorPositionField *pQryInvestorPositionField, int nRequestID)
    {
        pApi->ReqQryInvestorPosition(pQryInvestorPositionField, nRequestID);
    };

    //给Server发送强平请求
    int ReqOffsetOrder(CRHMonitorOffsetOrderField *pMonitorOrderField, int nRequestID)
    {
        pApi->ReqOffsetOrder(pMonitorOrderField, nRequestID);
    };

    //订阅主动推送信息
    int ReqSubPushInfo(CRHMonitorSubPushInfo *pInfo, int nRequestID)
    {
        pApi->ReqSubPushInfo(pInfo, nRequestID);
    };

    ///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
    void OnFrontConnected()
    {
        if (!vtCallbacks.cOnFrontConnected)
            return;

        vtCallbacks.cOnFrontConnected(this);
    };

    ///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
    ///@param nReason 错误原因
    ///        0x1001 网络读失败
    ///        0x1002 网络写失败
    ///        0x2001 接收心跳超时
    ///        0x2002 发送心跳失败
    ///        0x2003 收到错误报文
    void OnFrontDisconnected(int nReason)
    {
        if (!vtCallbacks.cOnFrontDisconnected)
            return;

        vtCallbacks.cOnFrontDisconnected(this, nReason);
    };

    ///风控账户登陆响应
    void OnRspUserLogin(CRHMonitorRspUserLoginField *pRspUserLoginField, CRHRspInfoField *pRHRspInfoField, int nRequestID){};

    ///风控账户登出响应
    void OnRspUserLogout(CRHMonitorUserLogoutField *pRspUserLoginField, CRHRspInfoField *pRHRspInfoField, int nRequestID){};

    //查询监控账户响应
    void OnRspQryMonitorAccounts(CRHQryInvestorField *pRspMonitorUser, CRHRspInfoField *pRHRspInfoField, int nRequestID, bool isLast){};

    ///查询账户资金响应
    void OnRspQryInvestorMoney(CRHTradingAccountField *pRHTradingAccountField, CRHRspInfoField *pRHRspInfoField, int nRequestID, bool isLast){};

    ///查询账户持仓信息响应
    void OnRspQryInvestorPosition(CRHMonitorPositionField *pRHMonitorPositionField, CRHRspInfoField *pRHRspInfoField, int nRequestID, bool isLast){};

    //平仓指令发送失败时的响应
    void OnRspOffsetOrder(CRHMonitorOffsetOrderField *pMonitorOrderField, CRHRspInfoField *pRHRspInfoField, int nRequestID, bool isLast){};

    ///报单通知
    void OnRtnOrder(CRHOrderField *pOrder){};

    ///成交通知
    void OnRtnTrade(CRHTradeField *pTrade){};

    ///账户资金发生变化回报
    void OnRtnInvestorMoney(CRHTradingAccountField *pRohonTradingAccountField){};

    ///账户某合约持仓回报
    void OnRtnInvestorPosition(CRHMonitorPositionField *pRohonMonitorPositionField){};
};

#ifdef __cplusplus
extern "C"
{
#endif

    C_API CRHMonitorInstance CreateRHMonitorApi()
    {
        cRHMonitorApi *instance = new (cRHMonitorApi);

        return instance;
    }

    C_API void SetCallbacks(CRHMonitorInstance instance, callback_t *vt)
    {
        ((cRHMonitorApi *)instance)->SetCallback(vt);
    }

#ifdef __cplusplus
}
#endif