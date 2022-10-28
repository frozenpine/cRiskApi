#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <memory.h>
#include <assert.h>

#include "RHMonitorApi.h"

class cRHMonitorApi : CRHMonitorSpi
{
public:
    cRHMonitorApi()
    {
        createInstance();
    };

protected:
    ~cRHMonitorApi()
    {
        Release();
    }

private:
    CRHMonitorApi *pApi;
    bool isConnected;
    bool isLoggedIn;
    char remoteIP[16];
    int remotePort;
    CRHMonitorReqUserLoginField loginInfo;
    int requestID;

    void
    createInstance()
    {
        pApi = CRHMonitorApi::CreateRHMonitorApi();

        assert(pApi != NULL);

        pApi->RegisterSpi(this);
    }

public:
    ///初始化
    ///@remark 初始化运行环境,只有调用后,接口才开始工作
    void
    Init(const char *ip, unsigned int port)
    {
        memcpy(remoteIP, ip, sizeof(remoteIP));
        remotePort = port;

        pApi->Init(ip, port);
    };

    ///账户登陆
    int ReqUserLogin(CRHMonitorReqUserLoginField *pUserLoginField, int nRequestID)
    {
        memcpy(&loginInfo, pUserLoginField, sizeof(loginInfo));

        return pApi->ReqUserLogin(pUserLoginField, nRequestID);
    };

    //账户登出
    int ReqUserLogout(CRHMonitorUserLogoutField *pUserLogoutField, int nRequestID)
    {
        return pApi->ReqUserLogout(pUserLogoutField, nRequestID);
    };

    //查询所有管理的账户
    int ReqQryMonitorAccounts(CRHMonitorQryMonitorUser *pQryMonitorUser, int nRequestID)
    {
        return pApi->ReqQryMonitorAccounts(pQryMonitorUser, nRequestID);
    };

    ///查询账户资金
    int ReqQryInvestorMoney(CRHMonitorQryInvestorMoneyField *pQryInvestorMoneyField, int nRequestID)
    {
        return pApi->ReqQryInvestorMoney(pQryInvestorMoneyField, nRequestID);
    };

    ///查询账户持仓
    int ReqQryInvestorPosition(CRHMonitorQryInvestorPositionField *pQryInvestorPositionField, int nRequestID)
    {
        return pApi->ReqQryInvestorPosition(pQryInvestorPositionField, nRequestID);
    };

    //给Server发送强平请求
    int ReqOffsetOrder(CRHMonitorOffsetOrderField *pMonitorOrderField, int nRequestID)
    {
        return pApi->ReqOffsetOrder(pMonitorOrderField, nRequestID);
    };

    //订阅主动推送信息
    int ReqSubPushInfo(CRHMonitorSubPushInfo *pInfo, int nRequestID)
    {
        return pApi->ReqSubPushInfo(pInfo, nRequestID);
    };

    ///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
    void OnFrontConnected(){};

    ///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
    ///@param nReason 错误原因
    ///        0x1001 网络读失败
    ///        0x1002 网络写失败
    ///        0x2001 接收心跳超时
    ///        0x2002 发送心跳失败
    ///        0x2003 收到错误报文
    void OnFrontDisconnected(int nReason){};

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

    void Release()
    {
        if (NULL != pApi)
        {
            pApi->Release();
        }
    }
};