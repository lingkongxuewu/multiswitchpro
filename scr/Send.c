/*--------------------------------文*件*信*息-----------------------------
* 文件名：  Send.c
* 版　本：  v1.0
* 描  述：  100T双轴 整合后的版本
* 创建人：  
* 日  期：  
--------------------------------------------------------------------------
*当前版本:	v1.0
*修 改 人:
*日　  期:
----------------------------------修改履历--------------------------------
1、
2、
3、
4、
------------------------------------------------------------------------*/
#define   __SEND_C__
#include  "_Include.h"

static void Send_RDeal ( char* buf,U8 n);
static void Send_CDeal ( char* buf,U8 n);
static void Send_SDeal ( char* buf,U8 n);



code U16  SendSpeed[]={3990,943,462,298,223,168,146,119,103,85};
							// 1/4   1   2   3   4   5   6   7   8   9
							
    //                          0    1     2     3      4      5      6      7      8      9      
    code U32 Braud[10] = { 1200, 2400, 4800, 9600, 14400, 19200, 38400, 56000, 57600, 115200 };


//***********************************************************************/
// *功    能：
// *入    口：CommTimer时间到 ，CommRxFlag有接收完成标志
// *出    口：
// *备    注：
// *函数性质：
//***********************************************************************/
void Send_TimeProc (void)
{   static xdata U8 rx_buf[COMM_RX_BUF_SIZE];
    static U8* ptr;
    static U8 xdata i;
    static U8 xdata err;
    static U8 xdata cmd;

//    if(COMM_TRAN==Comm_StateGet()) return;		 //COMM_TRAN==0，CommTimer减到0返回1进入COM处理，CommTimer减没到0返回0
    if(CommRxFlag==0)   return;					 //接收标志
    CommRxFlag = 0;
    ptr=rx_buf;									 
    for(i=0;i<COMM_RX_BUF_SIZE;i++)
    {   
		*ptr++=Comm_GetChar(&err);				  //将接收缓冲区的数据 取出存入	rx_buf
        if(err==COMM_RX_EPT)					 //COMM_RX_EPT ==1	取完标志
        break;
    }

    if(i<3)
    {
        return;
    }
    if((0x0D!=rx_buf[i-2])||(0x0A!=rx_buf[i-1]))	 //判断后两位数据是否是回车换行
    return;


	cmd=rx_buf[0];
    switch(cmd)
    { 
	  case 'r': Send_RDeal(rx_buf,i);
                break;
      case 's': Send_SDeal(rx_buf,i);
                break;
    }
}
//***********************************************************************/
// *功    能：
// *入    口：
// *出    口：
// *备    注：
// *函数性质：
//***********************************************************************/
static void Send_RDeal ( char* buf,U8 n)
{   
//	U8 xdata data_8u;

	if(0==strncmp(buf,"rd m",4))
	{
		if(n!=6)return;
//		data_8u=Sub_Str2Int8u(&buf[8]);
		Comm_PutStr("yang",4);
		Comm_SendSta();
	}

//		if(n!=15)return;
//		data_8u=Sub_Str2Int8u(&buf[8]);

}
//***********************************************************************/
// *功    能：
// *入    口：
// *出    口：
// *备    注：
// *函数性质：
//***********************************************************************/
static void Send_SDeal ( char* buf,U8 n)
{   
	U8 xdata data_8u,temp,temp1;
	U8 xdata arr[2]={0};
	byte1.U32 = 0;

	if(0==strncmp(buf,"set on,",7))
	{
		if(n!=11)return;
		data_8u = Sub_Str2Int8u(&buf[7]);
		if(data_8u == 0)
		return;
		data_8u-=1;

		if(data_8u<32)
		{
			SendTo595OneGroup(data_8u);
		}
		else if(data_8u>=32&&data_8u<64)
		{
			temp = data_8u -32;
			SendTo595TwoGroup(temp);
		}
		else if(data_8u>=64 && data_8u<96)
		{
			temp1 = data_8u -64;
			SendTo595ThreeGroup(temp1);
		}
		else
		{
			Comm_PutStr("error!",6);
			Comm_SendSta();
		}
		
		Comm_PutStr("set on,",7);
		Comm_PutStr(&buf[7],2);
		Sub_SendOk();

	}
	else
		Sub_SendErr();

}


//***********************************************************************/
