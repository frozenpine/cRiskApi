#include "api.h"

static fpRHMonitorApi* api = NULL;

// const char* ip = "129.211.138.170";
const char* ip = "210.22.96.58";

// const int port = 20002;
const int port = 11102;

// const char* riskUser = "rdcesfk";
const char* riskUser = "rdfk";

const char* riskPass = "888888";

const char* brokerID = "RohonDemo";

int main() {
	api = new fpRHMonitorApi(brokerID);

	LOGI("Rohon risk api instance[0x%x] created.", (void *)api);

	api->Init(ip, port);

	CRHMonitorReqUserLoginField login = CRHMonitorReqUserLoginField{ 0 };
	memcpy(&login.UserID, riskUser, sizeof(login.UserID) - 1);
	memcpy(&login.Password, riskPass, sizeof(login.Password) - 1);

	api->ReqUserLogin(&login);

	api->ReqQryMonitorAccounts();

	api->ReqQryAllInvestorMoney();

	api->ReqQryAllInvestorPosition();

	while (true) { ; }
}
