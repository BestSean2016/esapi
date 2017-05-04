#include <iostream>
#include <string.h>
#include "forv9_iTapTradeAPI.h"
#include "forv9_iTapAPIError.h"
#include "forv9_Trade.h"
#include "forv9_TradeConfig.h"


using namespace std;
using namespace ITapTrade;

int main_forv9_trade(int argc, char* argv[])
{
	//取得API的版本信息
	cout << GetITapTradeAPIVersion() << endl;

	//创建API实例
	TAPIINT32 iResult = TAPIERROR_SUCCEED;
	TapAPIApplicationInfo stAppInfo;
	strcpy(stAppInfo.AuthCode, DEFAULT_AUTHCODE);
	strcpy(stAppInfo.KeyOperationLogPath, "\\log");
	ITapTradeAPI *pAPI = CreateITapTradeAPI(&stAppInfo, iResult);
	if (NULL == pAPI){
		cout << "创建API实例失败，错误码：" << iResult <<endl;
		return -1;
	}

	//设定ITapTradeAPINotify的实现类，用于异步消息的接收
    Trade_fv9 objTrade;
	pAPI->SetAPINotify(&objTrade);
	

	//启动测试，下单
	objTrade.SetAPI(pAPI);
	objTrade.RunTest();


	return 0;
}

#ifndef LIBFV9TRADE_LIBRARY
int main(int argc, char* argv[]) {
    return main_forv9_trade(argc, argv);
}
#endif //LIBFV9TRADE_LIBRARY
