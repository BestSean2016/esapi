#include "TapQuoteAPI.h"
#include "TapAPIError.h"
#include "Quote.h"
#include "QuoteConfig.h"

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
    //取得API的版本信息
    cout << GetTapQuoteAPIVersion() << endl;

    //创建API实例
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
            cout << "创建API实例失败，错误码：" << iResult <<endl;
            return -1;
    }

    //设定ITapQuoteAPINotify的实现类，用于异步消息的接收
    Quote objQuote;
    pAPI->SetAPINotify(&objQuote);


    //启动测试，订阅行情
    objQuote.SetAPI(pAPI);
    objQuote.RunTest();

    return 0;
}
