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
	//ȡ��API�İ汾��Ϣ
	cout << GetITapTradeAPIVersion() << endl;

	//����APIʵ��
	TAPIINT32 iResult = TAPIERROR_SUCCEED;
	TapAPIApplicationInfo stAppInfo;
	strcpy(stAppInfo.AuthCode, DEFAULT_AUTHCODE);
	strcpy(stAppInfo.KeyOperationLogPath, "\\log");
	ITapTradeAPI *pAPI = CreateITapTradeAPI(&stAppInfo, iResult);
	if (NULL == pAPI){
		cout << "����APIʵ��ʧ�ܣ������룺" << iResult <<endl;
		return -1;
	}

	//�趨ITapTradeAPINotify��ʵ���࣬�����첽��Ϣ�Ľ���
    Trade_fv9 objTrade;
	pAPI->SetAPINotify(&objTrade);
	

	//�������ԣ��µ�
	objTrade.SetAPI(pAPI);
	objTrade.RunTest();


	return 0;
}

#ifndef LIBFV9TRADE_LIBRARY
int main(int argc, char* argv[]) {
    return main_forv9_trade(argc, argv);
}
#endif //LIBFV9TRADE_LIBRARY
