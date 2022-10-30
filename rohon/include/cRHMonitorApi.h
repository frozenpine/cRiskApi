#pragma once
#ifndef C_MONITOR_API_H
#define C_MONITOR_API_H

#if defined(ISLIB) && defined(WIN32)
#ifdef CMONITORAPI_EXPORTS
#define C_API __declspec(dllexport)
#else
#define C_API __declspec(dllimport)
#endif
#else
#ifdef CMONITORAPI_EXPORTS
#define C_API __attribute__((visibility("default")))
#else
#define C_API __attribute__((visibility("default")))
#endif
#endif

#ifndef _WIN32
#define __cdecl
#endif
#define APPWINAPI __cdecl

#ifdef __cplusplus
#ifndef NULL
#define NULL 0
#endif
extern "C"
{
#else
#define NULL ((void *)0)
#endif

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <memory.h>

#include "RHUserApiDataType.h"
#include "RHUserApiStruct.h"

    // C API ʵ��
    typedef uintptr_t CRHMonitorInstance;

    /// ���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
    typedef void(APPWINAPI *CbOnFrontConnected)(CRHMonitorInstance instance);
    C_API void SetCbOnFrontConnected(CRHMonitorInstance instance, CbOnFrontConnected handler);

    /// ���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
    ///@param nReason ����ԭ��
    ///         0x1001 �����ʧ��
    ///         0x1002 ����дʧ��
    ///         0x2001 ����������ʱ
    ///         0x2002 ��������ʧ��
    ///         0x2003 �յ�������
    typedef void(APPWINAPI *CbOnFrontDisconnected)(CRHMonitorInstance instance, int nReason);
    C_API void SetCbOnFrontDisconnected(CRHMonitorInstance instance, CbOnFrontDisconnected handler);

    /// ����˻���½��Ӧ
    typedef void(APPWINAPI *CbOnRspUserLogin)(
        CRHMonitorInstance instance,
        struct CRHMonitorRspUserLoginField *pRspUserLoginField,
        struct CRHRspInfoField *pRHRspInfoField,
        int nRequestID);
    C_API void SetCbOnRspUserLogin(CRHMonitorInstance instance, CbOnRspUserLogin handler);

    /// ����˻��ǳ���Ӧ
    typedef void(APPWINAPI *CbOnRspUserLogout)(
        CRHMonitorInstance instance,
        struct CRHMonitorUserLogoutField *pRspUserLoginField,
        struct CRHRspInfoField *pRHRspInfoField,
        int nRequestID);
    C_API void SetCbOnRspUserLogout(CRHMonitorInstance instance, CbOnRspUserLogout handler);

    /// ��ѯ����˻���Ӧ
    typedef void(APPWINAPI *CbOnRspQryMonitorAccounts)(
        CRHMonitorInstance instance,
        struct CRHQryInvestorField *pRspMonitorUser,
        struct CRHRspInfoField *pRHRspInfoField,
        int nRequestID, bool isLast);
    C_API void SetCbOnRspQryMonitorAccounts(CRHMonitorInstance instance, CbOnRspQryMonitorAccounts handler);

    /// ��ѯ�˻��ʽ���Ӧ
    typedef void(APPWINAPI *CbOnRspQryInvestorMoney)(
        CRHMonitorInstance instance,
        struct CRHTradingAccountField *pRHTradingAccountField,
        struct CRHRspInfoField *pRHRspInfoField,
        int nRequestID, bool isLast);
    C_API void SetCbOnRspQryInvestorMoney(CRHMonitorInstance instance, CbOnRspQryInvestorMoney handler);

    /// ��ѯ�˻��ֲ���Ϣ��Ӧ
    typedef void(APPWINAPI *CbOnRspQryInvestorPosition)(
        CRHMonitorInstance instance,
        struct CRHMonitorPositionField *pRHMonitorPositionField,
        struct CRHRspInfoField *pRHRspInfoField,
        int nRequestID, bool isLast);
    C_API void SetCbOnRspQryInvestorPosition(CRHMonitorInstance instance, CbOnRspQryInvestorPosition handler);

    /// ƽ��ָ���ʧ��ʱ����Ӧ
    typedef void(APPWINAPI *CbOnRspOffsetOrder)(
        CRHMonitorInstance instance,
        struct CRHMonitorOffsetOrderField *pMonitorOrderField,
        struct CRHRspInfoField *pRHRspInfoField,
        int nRequestID, bool isLast);
    C_API void SetCbOnRspOffsetOrder(CRHMonitorInstance instance, CbOnRspOffsetOrder handler);

    /// ����֪ͨ
    typedef void(APPWINAPI *CbOnRtnOrder)(CRHMonitorInstance instance, struct CRHOrderField *pOrder);
    C_API void SetCbOnRtnOrder(CRHMonitorInstance instance, CbOnRtnOrder handler);

    /// �ɽ�֪ͨ
    typedef void(APPWINAPI *CbOnRtnTrade)(CRHMonitorInstance instance, struct CRHTradeField *pTrade);
    C_API void SetCbOnRtnTrade(CRHMonitorInstance instance, CbOnRtnTrade handler);

    /// �˻��ʽ����仯�ر�
    typedef void(APPWINAPI *CbOnRtnInvestorMoney)(CRHMonitorInstance instance, struct CRHTradingAccountField *pRohonTradingAccountField);
    C_API void SetCbOnRtnInvestorMoney(CRHMonitorInstance instance, CbOnRtnInvestorMoney handler);

    /// �˻�ĳ��Լ�ֲֻر�
    typedef void(APPWINAPI *CbOnRtnInvestorPosition)(CRHMonitorInstance instance, struct CRHMonitorPositionField *pRohonMonitorPositionField);
    C_API void SetCbOnRtnInvestorPosition(CRHMonitorInstance instance, CbOnRtnInvestorPosition handler);

    typedef struct CbVirtualTable
    {
        CbOnFrontConnected cOnFrontConnected;
        CbOnFrontDisconnected cOnFrontDisconnected;
        CbOnRspUserLogin cOnRspUserLogin;
        CbOnRspUserLogout cOnRspUserLogout;
        CbOnRspQryMonitorAccounts cOnRspQryMonitorAccounts;
        CbOnRspQryInvestorMoney cOnRspQryInvestorMoney;
        CbOnRspQryInvestorPosition cOnRspQryInvestorPosition;
        CbOnRspOffsetOrder cOnRspOffsetOrder;
        CbOnRtnOrder cOnRtnOrder;
        CbOnRtnTrade cOnRtnTrade;
        CbOnRtnInvestorMoney cOnRtnInvestorMoney;
        CbOnRtnInvestorPosition cOnRtnInvestorPosition;
    } callback_t;

    C_API void SetCallbacks(CRHMonitorInstance instance, callback_t *vt);

    /// ����MonitorApi
    C_API CRHMonitorInstance CreateRHMonitorApi();
    /// ɾ���ӿڶ�����
    ///@remark ����ʹ�ñ��ӿڶ���ʱ,���øú���ɾ���ӿڶ���
    C_API void Release(CRHMonitorInstance instance);

    /// ��ʼ��
    ///@remark ��ʼ�����л���,ֻ�е��ú�,�ӿڲſ�ʼ����
    C_API void Init(CRHMonitorInstance instance, const char *ip, unsigned int port);

    /// �˻���½
    C_API int ReqUserLogin(CRHMonitorInstance instance, struct CRHMonitorReqUserLoginField *pUserLoginField, int nRequestID);

    // �˻��ǳ�
    C_API int ReqUserLogout(CRHMonitorInstance instance, struct CRHMonitorUserLogoutField *pUserLogoutField, int nRequestID);

    // ��ѯ���й�����˻�
    C_API int ReqQryMonitorAccounts(CRHMonitorInstance instance, struct CRHMonitorQryMonitorUser *pQryMonitorUser, int nRequestID);

    /// ��ѯ�˻��ʽ�
    C_API int ReqQryInvestorMoney(CRHMonitorInstance instance, struct CRHMonitorQryInvestorMoneyField *pQryInvestorMoneyField, int nRequestID);

    /// ��ѯ�˻��ֲ�
    C_API int ReqQryInvestorPosition(CRHMonitorInstance instance, struct CRHMonitorQryInvestorPositionField *pQryInvestorPositionField, int nRequestID);

    // ��Server����ǿƽ����
    C_API int ReqOffsetOrder(CRHMonitorInstance instance, struct CRHMonitorOffsetOrderField *pMonitorOrderField, int nRequestID);

    // ��������������Ϣ
    C_API int ReqSubPushInfo(CRHMonitorInstance instance, struct CRHMonitorSubPushInfo *pInfo, int nRequestID);

#ifdef __cplusplus
}
#endif

#endif