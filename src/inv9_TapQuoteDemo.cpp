#include "inv9_TapQuoteAPI.h"
#include "inv9_TapAPIError.h"
#include "inv9_Quote.h"
#include "inv9_QuoteConfig.h"

#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

void ShowBuf(char* buf,int len)
{
    printf("===================\n");
        for(int i=0; i < len; ++i)
    {
        if(i%32==0){
            printf("\n");
        }
        printf("0x%x(%c) ", buf[i], buf[i]);
    }
    printf("===================\n");
}

int main_inv9_quote(int argc, char* argv[])
{
    //ȡ��API�İ汾��Ϣ
    cout << GetTapQuoteAPIVersion() << endl;

    //����APIʵ��
    TAPIINT32 iResult = TAPIERROR_SUCCEED;
    TapAPIApplicationInfo stAppInfo;
//    memset(&stAppInfo, '-', sizeof(stAppInfo));
//    ShowBuf(stAppInfo.AuthCode ,515);
    APIStrncpy(stAppInfo.AuthCode, DEFAULT_AUTHCODE);
    //printf("sizeof(stAppInfo.AuthCode):%d\n",sizeof(stAppInfo.AuthCode));
    //APIStrncpy(stAppInfo.AuthCode, "DEFAULT_AUTHCODE", 512);// sizeof(stAppInfo.AuthCode) - 2);
    ShowBuf(stAppInfo.AuthCode ,515);
    //cout << stAppInfo.AuthCode<< endl;
    cout << "====="<< endl;
    cout << strlen(stAppInfo.AuthCode) << endl;
    ITapQuoteAPI *pAPI = CreateTapQuoteAPI(&stAppInfo, iResult);
    if (NULL == pAPI){
            cout << "����APIʵ��ʧ�ܣ������룺" << iResult <<endl;
            return -1;
    }

    //�趨ITapQuoteAPINotify��ʵ���࣬�����첽��Ϣ�Ľ���
    Quote_inv9 objQuote;
    pAPI->SetAPINotify(&objQuote);


    //�������ԣ���������
    objQuote.SetAPI(pAPI);
    objQuote.RunTest();

    return 0;
}

#ifndef LIBINV9QUOTE_LIBRARY
int main(int argc, char* argv[]) {
    return main_inv9_quote(argc, argv);
}
#endif
