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
    ///初始化
    ///@remark 初始化运行环境,只有调用后,接口才开始工作
    void Init(const char *ip, unsigned int port);

    ///账户登陆
    int ReqUserLogin(CRHMonitorReqUserLoginField *pUserLoginField);

    //账户登出
    int ReqUserLogout();

    //查询所有管理的账户
    int ReqQryMonitorAccounts();

    ///查询账户资金
    int ReqQryInvestorMoney(CRHMonitorQryInvestorMoneyField *pQryInvestorMoneyField);

    ///查询账户持仓
    int ReqQryInvestorPosition(CRHMonitorQryInvestorPositionField *pQryInvestorPositionField);

    //给Server发送强平请求
    int ReqOffsetOrder(CRHMonitorOffsetOrderField *pMonitorOrderField);

    //订阅主动推送信息
    int ReqSubPushInfo(CRHMonitorSubPushInfo *pInfo);

    void Release();

    ///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
    virtual void OnFrontConnected();

    ///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
    ///@param nReason 错误原因
    ///        0x1001 网络读失败
    ///        0x1002 网络写失败
    ///        0x2001 接收心跳超时
    ///        0x2002 发送心跳失败
    ///        0x2003 收到错误报文
    virtual void OnFrontDisconnected(int nReason);

    ///风控账户登陆响应
    virtual void OnRspUserLogin(CRHMonitorRspUserLoginField *pRspUserLoginField, CRHRspInfoField *pRHRspInfoField);

    ///风控账户登出响应
    virtual void OnRspUserLogout(CRHMonitorUserLogoutField *pRspUserLoginField, CRHRspInfoField *pRHRspInfoField);

    //查询监控账户响应
    virtual void OnRspQryMonitorAccounts(CRHQryInvestorField *pRspMonitorUser, CRHRspInfoField *pRHRspInfoField, bool isLast);

    ///查询账户资金响应
    virtual void OnRspQryInvestorMoney(CRHTradingAccountField *pRHTradingAccountField, CRHRspInfoField *pRHRspInfoField, bool isLast);

    ///查询账户持仓信息响应
    virtual void OnRspQryInvestorPosition(CRHMonitorPositionField *pRHMonitorPositionField, CRHRspInfoField *pRHRspInfoField, bool isLast);

    //平仓指令发送失败时的响应
    virtual void OnRspOffsetOrder(CRHMonitorOffsetOrderField *pMonitorOrderField, CRHRspInfoField *pRHRspInfoField, bool isLast);

    ///报单通知
    virtual void OnRtnOrder(CRHOrderField *pOrder);

    ///成交通知
    virtual void OnRtnTrade(CRHTradeField *pTrade);

    ///账户资金发生变化回报
    virtual void OnRtnInvestorMoney(CRHTradingAccountField *pRohonTradingAccountField);

    ///账户某合约持仓回报
    virtual void OnRtnInvestorPosition(CRHMonitorPositionField *pRohonMonitorPositionField);
};