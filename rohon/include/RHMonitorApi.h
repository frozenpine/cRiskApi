/////////////////////////////////////////////////////////////////////////
///@system 融航期货交易平台
///@company 上海融航信息技术有限公司
///@file RHMonitorApi.h
///@brief 定义了客户端接口
/// 20180910 create by Haosc
///
/////////////////////////////////////////////////////////////////////////

#if !defined(RH_RHMONITORAPI_H)
#define RH_RHMONITORAPI_H

#if _MSC_VER > 1000
#pragma once
#pragma execution_character_set("utf-8")
#endif // _MSC_VER > 1000

#include "RHUserApiStruct.h"

#if defined(ISLIB) && defined(WIN32)
#ifdef LIB_RHMONITOR_API_EXPORT
#define RHMONITOR_API_EXPORT_NEW __declspec(dllexport)
#else
#define RHMONITOR_API_EXPORT_NEW __declspec(dllimport)
#endif
#else
#define RHMONITOR_API_EXPORT_NEW __attribute__((visibility("default")))
#endif

class CRHMonitorSpi
{
public:
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected(){};

	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	virtual void OnFrontDisconnected(int nReason){};

	///风控账户登陆响应
	virtual void OnRspUserLogin(CRHMonitorRspUserLoginField *pRspUserLoginField, CRHRspInfoField *pRHRspInfoField, int nRequestID){};

	///风控账户登出响应
	virtual void OnRspUserLogout(CRHMonitorUserLogoutField *pRspUserLoginField, CRHRspInfoField *pRHRspInfoField, int nRequestID){};

	//查询监控账户响应
	virtual void OnRspQryMonitorAccounts(CRHQryInvestorField *pRspMonitorUser, CRHRspInfoField *pRHRspInfoField, int nRequestID, bool isLast){};

	///查询账户资金响应
	virtual void OnRspQryInvestorMoney(CRHTradingAccountField *pRHTradingAccountField, CRHRspInfoField *pRHRspInfoField, int nRequestID, bool isLast){};

	///查询账户持仓信息响应
	virtual void OnRspQryInvestorPosition(CRHMonitorPositionField *pRHMonitorPositionField, CRHRspInfoField *pRHRspInfoField, int nRequestID, bool isLast){};

	//平仓指令发送失败时的响应
	virtual void OnRspOffsetOrder(CRHMonitorOffsetOrderField *pMonitorOrderField, CRHRspInfoField *pRHRspInfoField, int nRequestID, bool isLast){};

	///报单通知
	virtual void OnRtnOrder(CRHOrderField *pOrder){};

	///成交通知
	virtual void OnRtnTrade(CRHTradeField *pTrade){};

	///账户资金发生变化回报
	virtual void OnRtnInvestorMoney(CRHTradingAccountField *pRohonTradingAccountField){};

	///账户某合约持仓回报
	virtual void OnRtnInvestorPosition(CRHMonitorPositionField *pRohonMonitorPositionField){};
};

class RHMONITOR_API_EXPORT_NEW CRHMonitorApi
{
public:
	///创建MonitorApi
	static CRHMonitorApi *CreateRHMonitorApi();
	///删除接口对象本身
	///@remark 不再使用本接口对象时,调用该函数删除接口对象
	virtual void Release() = 0;

	///初始化
	///@remark 初始化运行环境,只有调用后,接口才开始工作
	virtual void Init(const char *ip, unsigned int port) = 0;

	///注册回调接口
	///@param pSpi 派生自回调接口类的实例
	virtual void RegisterSpi(CRHMonitorSpi *pSpi) = 0;

	///账户登陆
	virtual int ReqUserLogin(CRHMonitorReqUserLoginField *pUserLoginField, int nRequestID) = 0;

	//账户登出
	virtual int ReqUserLogout(CRHMonitorUserLogoutField *pUserLogoutField, int nRequestID) = 0;

	//查询所有管理的账户
	virtual int ReqQryMonitorAccounts(CRHMonitorQryMonitorUser *pQryMonitorUser, int nRequestID) = 0;

	///查询账户资金
	virtual int ReqQryInvestorMoney(CRHMonitorQryInvestorMoneyField *pQryInvestorMoneyField, int nRequestID) = 0;

	///查询账户持仓
	virtual int ReqQryInvestorPosition(CRHMonitorQryInvestorPositionField *pQryInvestorPositionField, int nRequestID) = 0;

	//给Server发送强平请求
	virtual int ReqOffsetOrder(CRHMonitorOffsetOrderField *pMonitorOrderField, int nRequestID) = 0;

	//订阅主动推送信息
	virtual int ReqSubPushInfo(CRHMonitorSubPushInfo *pInfo, int nRequestID) = 0;
};

#endif