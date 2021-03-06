/*--------------------------------文*件*信*息-----------------------------
* 文件名：  Sub.c
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
#define   __SUB_C__
#include  "_Include.h"
//***********************************************************************/
void Sub_16SBufSwitch (S16* buf,U8 i,U8 j);

U8 xdata DispBuf[50];

#if 1
//***********************************************************************/
// *功    能：
// *入    口：
// *出    口：
// *备    注：
// *函数性质：16有符号位转BCD 值存DisBuf数组，后将BCD存于发送缓冲区
//***********************************************************************/
//void Comm_PutInt16s (S16 val)
//{
//	Sub_Int16s2Str(DispBuf,val);
//	Comm_PutStr((U8*)DispBuf,6);
//}

//void Sub_Int16u2Str (char* s,U16 val)
//{
//	s[0] = val/10000+'0';
//	val  = val%10000;
//	s[1] = val/1000+'0';
//	val  = val%1000;
//	s[2] = val/100+'0';
//	val  = val%100;
//	s[3] = val/10+'0';
//	s[4] = val%10+'0';
//}
//***********************************************************************/
// *功    能：
// *入    口：
// *出    口：
// *备    注：
// *函数性质：16无符号位转BCD 值存DisBuf数组，后将BCD存于发送缓冲区
//***********************************************************************/
//void Comm_PutInt16u (U16 val)
//{
//	Sub_Int16u2Str(DispBuf,val);
//	Comm_PutStr((U8*)DispBuf,5);
//}
//***********************************************************************/
// *功    能：
// *入    口：
// *出    口：
// *备    注：
// *函数性质：8位无符号位转BCD 值存DisBuf数组，后将BCD存于发送缓冲区
//***********************************************************************/
//void Comm_PutInt8u (U8 val)
//{
//	Sub_Int8u2Str(DispBuf,val);
//	Comm_PutStr((U8*)DispBuf,3);
//}
#endif

//void Comm_PutInt32u (U32 val)
//{
//	Sub_Int32u2Str(DispBuf,val);
//	Comm_PutStr(DispBuf,8);
//	Comm_PutChar(10);
//}
//***********************************************************************/
//***********************************************************************/
// *功    能：
// *入    口：
// *出    口：
// *备    注：
// *函数性质：将回车换行的ASCII值存TX缓冲区
//***********************************************************************/
void Comm_PutNewLine (void)
{
	Comm_PutChar(0x0D);
	Comm_PutChar(0x0A);
}
//***********************************************************************/
// *功    能：
// *入    口：
// *出    口：
// *备    注：
// *函数性质：Send "ok"
//***********************************************************************/
void Sub_SendOk (void)
{	
	char* str={",OK"};
	Comm_PutStr((U8*)str,3);
	Comm_PutNewLine();
	Comm_SendSta();
}
//***********************************************************************/
void Sub_SendErr (void)
{	char* str={"ERR"};
	
	
	Comm_PutStr((U8*)str,3);
	Comm_PutNewLine();
	Comm_SendSta();
}

//***********************************************************************/
//int8u Sub_Str2Int16s (int16s *val,int8u* str)
//{	int16u temp;
//	if(FALSE==Sub_Str2Int16u(&temp,&str[1]))return (FALSE);
//	
//	if(str[0]=='+')
//	{	*val = temp;
//		return TRUE;
//	}
//	else if(str[0]=='-')
//	{	*val = -temp;
//		return TRUE;
//	}
//	return FALSE;
//}
//***********************************************************************/
//***********************************************************************/
U8 Sub_Str2Int8u (U8* str)
{	U8 xdata val;	
	
	if((str[0]<'0')||(str[0]>'9'))return(100);
	if((str[1]<'0')||(str[1]>'9'))return(100);
	val=(str[0]-'0')*10+(str[1]-'0');
	return  val;
}
//***********************************************************************/


/***********************************************************************/
//void Sub_Int8u2Str (char* s,U8 val)
//{
//	s[0] = val/100+'0';
//	val  = val%100;
//	s[1] = val/10+'0';
//}

//void Sub_Int32u2Str (char* s,U32 val)
//{	
//	if(val>16777215)val = 16777215; 	//数值溢出2013-7-15 11:56AM修改增加
//	s[0] = val/10000000+'0';
//	val  = val%10000000;
//	s[1] = val/1000000+'0';
//	val  = val%1000000;	
//	s[2] = val/100000+'0';
//	val  = val%100000;	
//	s[3] = val/10000+'0';
//	val  = val%10000;
//	s[4] = val/1000+'0';
//	val  = val%1000;
//	s[5] = val/100+'0';
//	val  = val%100;
//	s[6] = val/10+'0';
//	s[7] = val%10+'0';
//}

void SendTo595OneGroup(U8 data_8u)
{
	if(data_8u<=7)
		{
			byte1.U8[3] = pow(2,data_8u);
			One_Driver_595SendByte(byte1.U8);
		}
		else if(data_8u>7 && data_8u<=15)
		{
			byte1.U8[2] = pow(2,(data_8u-8));
			One_Driver_595SendByte(byte1.U8);
		}
		else if(data_8u>15 && data_8u<=23)
		{
			byte1.U8[1] = pow(2,(data_8u-16));
			One_Driver_595SendByte(byte1.U8);
		}
		else if(data_8u>23 && data_8u<=31)
		{
			byte1.U8[0] = pow(2,(data_8u-24));
			One_Driver_595SendByte(byte1.U8);
		}
		else
		{
			Comm_PutStr("error!",6);
			Comm_SendSta();
			return;
		}
}

void SendTo595TwoGroup(U8 data_8u)
{
	if(data_8u<=7)
		{
			byte1.U8[3] = pow(2,data_8u);
			Two_Driver_595SendByte(byte1.U8);
		}
		else if(data_8u>7 && data_8u<=15)
		{
			byte1.U8[2] = pow(2,(data_8u-8));
			Two_Driver_595SendByte(byte1.U8);
		}
		else if(data_8u>15 && data_8u<=23)
		{
			byte1.U8[1] = pow(2,(data_8u-16));
			Two_Driver_595SendByte(byte1.U8);
		}
		else if(data_8u>23 && data_8u<=31)
		{
			byte1.U8[0] = pow(2,(data_8u-24));
			Two_Driver_595SendByte(byte1.U8);
		}
		else
		{
			Comm_PutStr("error!",6);
			Comm_SendSta();
			return;
		}
}

void SendTo595ThreeGroup(U8 data_8u)
{
	if(data_8u<=7)
		{
			byte1.U8[3] = pow(2,data_8u);
			Three_Driver_595SendByte(byte1.U8);
		}
		else if(data_8u>7 && data_8u<=15)
		{
			byte1.U8[2] = pow(2,(data_8u-8));
			Three_Driver_595SendByte(byte1.U8);
		}
		else if(data_8u>15 && data_8u<=23)
		{
			byte1.U8[1] = pow(2,(data_8u-16));
			Three_Driver_595SendByte(byte1.U8);
		}
		else if(data_8u>23 && data_8u<=31)
		{
			byte1.U8[0] = pow(2,(data_8u-24));
			Three_Driver_595SendByte(byte1.U8);
		}
		else
		{
			Comm_PutStr("error!",6);
			Comm_SendSta();
			return;
		}
}

 //HXL 12/8/28 
//***********************************************************************/
