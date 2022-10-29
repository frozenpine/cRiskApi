#pragma execution_character_set("utf-8")
#include "api.h"

static cRHMonitorApi* api = NULL;

const char* ip = "129.211.138.170";
const int port = 20002;
const char* riskUser = "rdcesfk";
const char* riskPass = "888888";

int main() {
	api = new cRHMonitorApi();

	api->Init(ip, port);

	CRHMonitorReqUserLoginField login = CRHMonitorReqUserLoginField{ 0 };
	memcpy(&login.UserID, riskUser, sizeof(login.UserID) - 1);
	memcpy(&login.Password, riskPass, sizeof(login.Password) - 1);

	api->ReqUserLogin(&login);

	while (true) { ; }
}
