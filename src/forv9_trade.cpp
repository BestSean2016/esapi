#include "forv9_Trade.h"
#include "forv9_iTapAPIError.h"
#include "forv9_TradeConfig.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <memory.h>

using namespace std;


#define _UNIX
#ifdef _UNIX
char *strcpy_s(char *buf, const size_t buflen, const char *str) {
  if (strlen(str) > buflen - 1) {
      strncpy(buf, str, buflen - 1);
      buf[buflen - 1] = 0;
  } else
      strcpy(buf, str);
  return buf;
}

//const size_t buflen,
char *strncpy_s(char *buf, const char *str, const int n) {
  strncpy(buf, str, (size_t)n);
  //buf[min(buflen, (size_t)n)] = 0;
  return buf;
}

char* strcat_s(char* buf, const size_t buflen, const char* src) {
    if  (strlen(buf) + strlen(src) >= buflen)
        return (0);

    return strcat(buf, src);
}

int fopen_s(FILE** fp, const char* filepath, const char* mode) {
    *fp = fopen(filepath, mode);
    return (*fp == NULL ? -1 : 0);
}

void itoa(unsigned long val, char *buf, unsigned radix) {
  char *p;         /* pointer to traverse string */
  char *firstdig;  /* pointer to first digit */
  char temp;       /* temp char */
  unsigned digval; /* value of digit */

  p = buf;
  firstdig = p; /* save pointer to first digit */

  do {
    digval = (unsigned)(val % radix);
    val /= radix; /* get next digit */

    /* convert to ascii and store */
    if (digval > 9)
      *p++ = (char)(digval - 10 + 'a'); /* a letter */
    else
      *p++ = (char)(digval + '0'); /* a digit */
  } while (val > 0);

  /* We now have the digit of the number in the buffer, but in reverse
  order.  Thus we reverse them now. */

  *p-- = '\0'; /* terminate string; p points to last digit */

  do {
    temp = *p;
    *p = *firstdig;
    *firstdig = temp; /* swap *p and *firstdig */
    --p;
    ++firstdig;           /* advance to next two digits */
  } while (firstdig < p); /* repeat until halfway */
}

void localtime_s(struct tm* ttm, time_t* tt) {
  (void)localtime_r(tt, ttm);
}

#endif // UNIX


Trade_fv9::Trade_fv9(void):
	m_pAPI(NULL),
	m_bIsAPIReady(false)
{
}


Trade_fv9::~Trade_fv9(void)
{
}


void Trade_fv9::SetAPI(ITapTradeAPI *pAPI)
{
	m_pAPI = pAPI;
}


void Trade_fv9::printHelp()
{
	cout<<"---------------------------------\n"
		<<"iTapTradeAPI_Demo CMD\n"
		<<"--->1 : order test \n"
		<<"--->2 : cancle order test\n"
		<<"--->3 : qry fund test\n"
		<<"--->4 : qry hold test\n"
		<<"--->5 : modify order test\n"
		<<"--->6 : qry commdity\n"
		<<"--->H : help\n"
		<<"----------------------------------\n"
		<<endl;
}

void Trade_fv9::loopCmd()
{
	this->printHelp();
	while(1)
	{
		char cmd;
		cin>>cmd;
		switch (cmd)
		{
			case '1': this->t_insertOrder(); break;
			case '2': this->t_canncelOrder();break;
			case '3': this->t_qryFund();break;
			case '4': this->t_qryPostion();break;
			case '5': this->t_modify();break;
			case '6': this->t_qryCommdity(); break;
			case 'H': this->printHelp();break;
			default:
				break;
		}
	}
}


void Trade_fv9::t_insertOrder()
{
	TAPIINT32 iErr = TAPIERROR_SUCCEED;
		//�µ�
	TapAPINewOrder stNewOrder;


	strcpy(stNewOrder.AccountNo, DEFAULT_ACCOUNT_NO);			
	strcpy(stNewOrder.ExchangeNo, DEFAULT_EXCHANGE_NO);		
	stNewOrder.CommodityType = DEFAULT_COMMODITY_TYPE;		
	strcpy(stNewOrder.CommodityNo, DEFAULT_COMMODITY_NO);		
	strcpy(stNewOrder.ContractNo, DEFAULT_CONTRACT_NO);				
	stNewOrder.OrderType = DEFAULT_ORDER_TYPE;			
	stNewOrder.OrderSource = TAPI_ORDER_SOURCE_ESUNNY_API;		
	stNewOrder.TimeInForce = TAPI_ORDER_TIMEINFORCE_GFD;		
	stNewOrder.OrderSide = DEFAULT_ORDER_SIDE;						
	stNewOrder.OrderPrice = DEFAULT_ORDER_PRICE;		
	stNewOrder.OrderQty = DEFAULT_ORDER_QTY;					
	
	m_uiSessionID = 0;
	iErr = m_pAPI->InsertOrder(&m_uiSessionID, &stNewOrder);
	if(TAPIERROR_SUCCEED != iErr) {
		cout << "InsertOrder Error:" << iErr <<endl;
		return;
	}
}

void Trade_fv9::t_canncelOrder()
{
	TAPISTR_20 orderno;
	cout<<"cancle operator :insert orderno"<<endl;
	cin>>orderno;

	TapAPIOrderCancelReq req;
	memset(&req,0,sizeof(req));
    strncpy_s(req.OrderNo,orderno,strlen(orderno));

	TAPIUINT32 reqid = 0;
	TAPIINT32 iErr = TAPIERROR_SUCCEED;

	iErr = m_pAPI->CancelOrder(&reqid,&req);
	if(iErr!= TAPIERROR_SUCCEED){
		cout<< "cancle Error:"<<iErr<<endl;
	}
}

void Trade_fv9::t_qryFund()
{
	TapAPIFundReq req;
	memset(&req,0,sizeof(req));
    strncpy_s(req.AccountNo,DEFAULT_ACCOUNT_NO,strlen(DEFAULT_ACCOUNT_NO));

	TAPIINT32 iErr = TAPIERROR_SUCCEED;
	iErr = m_pAPI->QryFund(&m_uiSessionID,&req);
	if(iErr!= TAPIERROR_SUCCEED){
		cout<<"t_qryFund Error:"<<iErr<<endl;
	}
}

void Trade_fv9::t_qryPostion()
{
	TapAPIPositionQryReq req;
	memset(&req,0,sizeof(req));
    strncpy_s(req.AccountNo,DEFAULT_ACCOUNT_NO,strlen(DEFAULT_ACCOUNT_NO));

	TAPIINT32 iErr = TAPIERROR_SUCCEED;
	iErr = m_pAPI->QryPosition(&m_uiSessionID,&req);
	if(iErr!= TAPIERROR_SUCCEED){
		cout<<"t_qryHold Error:"<<iErr<<endl;
	}
}

void Trade_fv9::t_modify()
{
	TapAPIAmendOrder req;
	TAPISTR_20	orderNo;
	TAPIREAL64 orderPrice;
	TAPIUINT32 orderQty;		
	cout<<"t_modify test"<<endl;
	cout<<"insert orderno"<<endl;
	cin>>orderNo;
	cout<<"insert price"<<endl;
	cin>>orderPrice;
	cout<<"insert qty"<<endl;
	cin>>orderQty;
	
	strncpy_s(req.OrderNo,orderNo,strlen(orderNo));
	strncpy_s(req.ReqData.AccountNo,DEFAULT_ACCOUNT_NO,strlen(DEFAULT_ACCOUNT_NO));
	req.ReqData.OrderPrice = orderPrice;
	req.ReqData.OrderQty = orderQty;

	TAPIINT32  iErr = TAPIERROR_SUCCEED;
	iErr=m_pAPI->AmendOrder(&m_uiSessionID,&req);
	if(iErr!=TAPIERROR_SUCCEED){
		cout<<"t_modify Error:"<<iErr<<endl;
	}
}

void Trade_fv9::t_qryCommdity()
{
	TAPIINT32 iErr = TAPIERROR_SUCCEED;
	iErr = m_pAPI->QryCommodity(&m_uiSessionID);
}

void Trade_fv9::RunTest()
{
	if(NULL == m_pAPI) {
		cout << "Error: m_pAPI is NULL." << endl;
		return;
	}

	TAPIINT32 iErr = TAPIERROR_SUCCEED;


	//�趨������IP���˿�
	iErr = m_pAPI->SetHostAddress(DEFAULT_IP, DEFAULT_PORT);
	if(TAPIERROR_SUCCEED != iErr) {
		cout << "SetHostAddress Error:" << iErr <<endl;
		return;
	}

	//��¼������
	TapAPITradeLoginAuth stLoginAuth;
	memset(&stLoginAuth, 0, sizeof(stLoginAuth));
	strcpy(stLoginAuth.UserNo, DEFAULT_USERNAME);
	strcpy(stLoginAuth.Password, DEFAULT_PASSWORD);
	stLoginAuth.ISModifyPassword = APIYNFLAG_NO;
	iErr = m_pAPI->Login(&stLoginAuth);
	if(TAPIERROR_SUCCEED != iErr) {
		cout << "Login Error:" << iErr <<endl;
		return;
	}
	

	//�ȴ�APIReady
	m_Event.WaitEvent();
	if (!m_bIsAPIReady){
		cout << "API is not ready";
		return;
	}

	this->loopCmd();


	while (true)
	{
		m_Event.WaitEvent();
	}	
}

void TAP_CDECL Trade_fv9::OnConnect()
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade_fv9::OnRspLogin( TAPIINT32 errorCode, const TapAPITradeLoginRspInfo *loginRspInfo )
{
	if(TAPIERROR_SUCCEED == errorCode) {
		cout << "��¼�ɹ����ȴ�API��ʼ��..." << endl;

	} else {
		cout << "��¼ʧ�ܣ�������:" << errorCode << endl;
		m_Event.SignalEvent();	
	}
}

void TAP_CDECL Trade_fv9::OnAPIReady()
{
	cout << "API��ʼ�����" << endl;
	m_bIsAPIReady = true;
	m_Event.SignalEvent();	
}

void TAP_CDECL Trade_fv9::OnDisconnect( TAPIINT32 reasonCode )
{
	cout << "API�Ͽ�,�Ͽ�ԭ��:"<<reasonCode << endl;
}

void TAP_CDECL Trade_fv9::OnRspChangePassword( TAPIUINT32 sessionID, TAPIINT32 errorCode )
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade_fv9::OnRspSetReservedInfo( TAPIUINT32 sessionID, TAPIINT32 errorCode, const TAPISTR_50 info )
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade_fv9::OnRspQryAccount( TAPIUINT32 sessionID, TAPIUINT32 errorCode, TAPIYNFLAG isLast, const TapAPIAccountInfo *info )
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade_fv9::OnRspQryFund( TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIFundData *info )
{
	cout << __FUNCTION__ << " is called." << endl;

	cout <<"errorcode ="<<errorCode<<endl;

	if(isLast=='Y') return;

	cout<<"����:"<<info->CurrencyNo<<","
		<<"Ȩ��:"<<info->Balance<<","
		<<"����:"<<info->Available<<","
		<<"��LME��ӯ:"<<info->PositionProfit<<","
		<<"LME��ӯ:"<<info->LmePositionProfit<<endl;
	
	
}

void TAP_CDECL Trade_fv9::OnRtnFund( const TapAPIFundData *info )
{
	//cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade_fv9::OnRspQryExchange( TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIExchangeInfo *info )
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade_fv9::OnRspQryCommodity( TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPICommodityInfo *info )
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade_fv9::OnRspQryContract( TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPITradeContractInfo *info )
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade_fv9::OnRtnContract( const TapAPITradeContractInfo *info )
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade_fv9::OnRtnOrder( const TapAPIOrderInfoNotice *info )

{
	cout << __FUNCTION__ << " is called." << endl;

	if(NULL == info){
		return;
	}

	if (info->ErrorCode != 0) {
		cout << "������������һ������ί����Ϣ�Ĵ���" << info->ErrorCode << endl;
	} else {
		if (info->OrderInfo) {
			if (0!= info->OrderInfo->ErrorCode){
				cout << "����ʧ�ܣ�"
					<< "������:"<<info->OrderInfo->ErrorCode << ","
					<< "ί�б��:"<<info->OrderInfo->OrderNo
					<<endl;
			} else{
				cout << "�����ɹ���"
					<< "Ʒ��:"<<info->OrderInfo->CommodityNo<< ","
					<<"��Լ:"<<info->OrderInfo->ContractNo<<","
					<< "״̬:"<<info->OrderInfo->OrderState << ","
					<< "ί�б��:"<<info->OrderInfo->OrderNo<< ","
					<<endl;
			}
		}
	}

}

void TAP_CDECL Trade_fv9::OnRspOrderAction( TAPIUINT32 sessionID, TAPIUINT32 errorCode, const TapAPIOrderActionRsp *info )
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade_fv9::OnRspQryOrder( TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIOrderInfo *info )
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade_fv9::OnRspQryOrderProcess( TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIOrderInfo *info )
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade_fv9::OnRspQryFill( TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIFillInfo *info )
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade_fv9::OnRtnFill( const TapAPIFillInfo *info )
{
	cout << __FUNCTION__ << " is called." << endl;
	cout<< "Ʒ��" <<info->CommodityNo << ","
		<< "��Լ" <<info->ContractNo << ","
		<< "�ɽ���"<<info->MatchPrice << ","
		<< "�ɽ���"<<info->MatchQty <<endl;
}

void TAP_CDECL Trade_fv9::OnRspQryPosition( TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIPositionInfo *info )
{
	cout << __FUNCTION__ << " is called." << endl;

	cout <<"errorcode ="<<errorCode<<endl;

	if(isLast=='Y') return;

	cout<< "Ʒ��" << info->CommodityNo <<","
	<< "��Լ" << info->ContractNo << ","
	<< "�ֲ���"<< info->PositionQty <<","
	<< "�ֲּ�"<< info->PositionPrice<<endl;

}

void TAP_CDECL Trade_fv9::OnRtnPosition( const TapAPIPositionInfo *info )
{
	cout << __FUNCTION__ << " is called." << endl;
	cout<< "Ʒ��" << info->CommodityNo <<","
		<< "��Լ" << info->ContractNo << ","
		<< "�ֲ���"<< info->PositionQty <<","
		<< "�ֲּ�"<< info->PositionPrice<<endl;
}

void TAP_CDECL Trade_fv9::OnRspQryClose( TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPICloseInfo *info )
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade_fv9::OnRtnClose( const TapAPICloseInfo *info )
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade_fv9::OnRtnPositionProfit( const TapAPIPositionProfitNotice *info )
{
	cout << __FUNCTION__ << " is called." << endl;
}
void TAP_CDECL Trade_fv9::OnRspQryCurrency(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPICurrencyInfo *info)
{

}

void TAP_CDECL Trade_fv9::OnRspQryTradeMessage(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPITradeMessage *info)
{
}

void TAP_CDECL Trade_fv9::OnRtnTradeMessage(const TapAPITradeMessage *info)
{
}

void TAP_CDECL Trade_fv9::OnRspQryHisOrder(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIHisOrderQryRsp *info)
{
}

void TAP_CDECL Trade_fv9::OnRspQryHisOrderProcess(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIHisOrderProcessQryRsp *info)
{
}

void TAP_CDECL Trade_fv9::OnRspQryHisMatch(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIHisMatchQryRsp *info)
{
}

void TAP_CDECL Trade_fv9::OnRspQryHisPosition(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIHisPositionQryRsp *info)
{
}

void TAP_CDECL Trade_fv9::OnRspQryHisDelivery(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIHisDeliveryQryRsp *info)
{
}

void TAP_CDECL Trade_fv9::OnRspQryAccountCashAdjust(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIAccountCashAdjustQryRsp *info)
{
}

void TAP_CDECL Trade_fv9::OnRspQryBill(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIBillQryRsp *info)
{
}

void TAP_CDECL Trade_fv9::OnExpriationDate(ITapTrade::TAPIDATE date, int days)
{
}

void TAP_CDECL Trade_fv9::OnRspQryAccountFeeRent(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountFeeRentQryRsp *info)
{
}

void TAP_CDECL Trade_fv9::OnRspQryAccountMarginRent(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountMarginRentQryRsp *info)
{

}
