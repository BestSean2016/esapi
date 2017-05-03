#include "TapQuoteAPI.h"
#include "TapAPIError.h"
#include "Quote.h"
#include "QuoteConfig.h"

#include <iostream>
#include <string.h>
using namespace std;

int main_forv9_quote(int argc, char* argv[])
{
	//ȡ��API�İ汾��Ϣ
	cout << GetTapQuoteAPIVersion() << endl;

	//����APIʵ��
	TAPIINT32 iResult = TAPIERROR_SUCCEED;
	TapAPIApplicationInfo stAppInfo;
	strcpy(stAppInfo.AuthCode, DEFAULT_AUTHCODE);
	strcpy(stAppInfo.KeyOperationLogPath, "");
	ITapQuoteAPI *pAPI = CreateTapQuoteAPI(&stAppInfo, iResult);
	if (NULL == pAPI){
		cout << "����APIʵ��ʧ�ܣ������룺" << iResult <<endl;
		return -1;
	}

	//�趨ITapQuoteAPINotify��ʵ���࣬�����첽��Ϣ�Ľ���
	Quote objQuote;
	pAPI->SetAPINotify(&objQuote);
	

	//�������ԣ���������
	objQuote.SetAPI(pAPI);
	objQuote.RunTest();


	return 0;
}