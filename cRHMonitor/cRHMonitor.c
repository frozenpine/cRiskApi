#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

#include "cRHMonitorApi.h"

#ifndef THREAD_ID
#define THREAD_ID
static inline unsigned long get_thread_id()
{
#ifdef _WIN32
    return GetCurrentThreadId();
#else
    return pthread_self();
#endif
}
#endif

#define FMTI(fmt) "[TID: %5ul] [INFO ] " fmt "\n"
#define FMTW(fmt) "[TID: %5ul] [WARNI] " fmt "\n"
#define FMTE(fmt) "%s(%d)-<%s> [TID: %5ul] [ERROR] " fmt "\n"
#define LOGI(fmt, ...) fprintf(stderr, FMTI(fmt), get_thread_id(), ##__VA_ARGS__)
#define LOGW(fmt, ...) fprintf(stderr, FMTW(fmt), get_thread_id(), ##__VA_ARGS__)
#define LOGE(fmt, ...) fprintf(stderr, FMTE(fmt), __FILE__, __LINE__, __FUNCTION__, get_thread_id(), ##__VA_ARGS__)

#define CHK_RSP(rsp, msg)                                                      \
    do                                                                         \
    {                                                                          \
        if (NULL == rsp)                                                       \
            break;                                                             \
        if ((rsp)->ErrorID > 0)                                                \
        {                                                                      \
            LOGE("%s failed[%d]: %s", (msg), (rsp)->ErrorID, (rsp)->ErrorMsg); \
            return;                                                            \
        }                                                                      \
        LOGI("%s success: %s", (msg), (rsp)->ErrorMsg);                        \
    } while (false)

// const char* ip = "129.211.138.170";
const char *ip = "210.22.96.58";

// const int port = 20002;
const int port = 11102;

// const char* riskUser = "rdcesfk";
const char *riskUser = "rdfk";

const char *riskPass = "888888";

const char *brokerID = "RohonDemo";

static int requestID = 0;

void cOnFrontConnected(CRHMonitorInstance instance)
{
    LOGI("Front connected: %s:%d", ip, port);

    struct CRHMonitorReqUserLoginField login;
    memset(&login, 0, sizeof(login));

    memcpy(&login.UserID, riskUser, sizeof(login.UserID) - 1);
    memcpy(&login.Password, riskPass, sizeof(login.Password) - 1);

    LOGI("Request user login: %s", riskUser);
    ReqUserLogin(instance, &login, requestID++);
}

void cOnRspUserLogin(
    CRHMonitorInstance instance,
    struct CRHMonitorRspUserLoginField *pRspUserLoginField,
    struct CRHRspInfoField *pRHRspInfoField,
    int nRequestID)
{
    if (NULL != pRHRspInfoField)
    {
        if (pRHRspInfoField->ErrorID > 0)
        {
            LOGE("User[%s] login failed: %s", riskUser, pRHRspInfoField->ErrorMsg);
            return;
        }
    }

    if (NULL != pRspUserLoginField)
    {
        LOGI("User[%s] logged in: %s %s", riskUser, pRspUserLoginField->TradingDay, pRspUserLoginField->LoginTime);
    }
}

int main()
{
    CRHMonitorInstance instance = CreateRHMonitorApi();

    SetCbOnFrontConnected(instance, cOnFrontConnected);
    SetCbOnRspUserLogin(instance, cOnRspUserLogin);

    Init(instance, ip, port);

    while (true)
    {
        ;
    }
}
