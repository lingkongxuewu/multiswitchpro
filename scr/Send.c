/*--------------------------------��*��*��*Ϣ-----------------------------
* �ļ�����  Send.c
* �桡����  v1.0
* ��  ����  100T˫�� ���Ϻ�İ汾
* �����ˣ�  
* ��  �ڣ�  
--------------------------------------------------------------------------
*��ǰ�汾:	v1.0
*�� �� ��:
*�ա�  ��:
----------------------------------�޸�����--------------------------------
1��
2��
3��
4��
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
// *��    �ܣ�
// *��    �ڣ�CommTimerʱ�䵽 ��CommRxFlag�н�����ɱ�־
// *��    �ڣ�
// *��    ע��
// *�������ʣ�
//***********************************************************************/
void Send_TimeProc (void)
{   static xdata U8 rx_buf[COMM_RX_BUF_SIZE];
    static U8* ptr;
    static U8 xdata i;
    static U8 xdata err;
    static U8 xdata cmd;

//    if(COMM_TRAN==Comm_StateGet()) return;		 //COMM_TRAN==0��CommTimer����0����1����COM����CommTimer��û��0����0
    if(CommRxFlag==0)   return;					 //���ձ�־
    CommRxFlag = 0;
    ptr=rx_buf;									 
    for(i=0;i<COMM_RX_BUF_SIZE;i++)
    {   
		*ptr++=Comm_GetChar(&err);				  //�����ջ����������� ȡ������	rx_buf
        if(err==COMM_RX_EPT)					 //COMM_RX_EPT ==1	ȡ���־
        break;
    }
    if(i<3)
    {
        return;
    }
    if((0x0D!=rx_buf[i-2])||(0x0A!=rx_buf[i-1]))	 //�жϺ���λ�����Ƿ��ǻس�����
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
// *��    �ܣ�
// *��    �ڣ�
// *��    �ڣ�
// *��    ע��
// *�������ʣ�
//***********************************************************************/
static void Send_RDeal ( char* buf,U8 n)
{   
//	U8 xdata data_8u;

	if(0==strncmp(buf,"rd m,",4))
	{
		if(n!=6)return;
//		data_8u=Sub_Str2Int8u(&buf[8]);
		Comm_PutStr("yang ",5);
		TI0 =1;
	}

//		if(n!=15)return;
//		data_8u=Sub_Str2Int8u(&buf[8]);

}
//***********************************************************************/
// *��    �ܣ�
// *��    �ڣ�
// *��    �ڣ�
// *��    ע��
// *�������ʣ�
//***********************************************************************/
static void Send_SDeal ( char* buf,U8 n)
{   
	U8 xdata data_8u,temp;
	U8 xdata arr[2]={0};

	if(0==strncmp(buf,"set on,",7))
	{
	   if(n!=11)return;
	   data_8u = Sub_Str2Int8u(&buf[7]);
	   switch(Part_pin)
	   {
	   		case 1:
				byte1.U32 = pow(2,data_8u);
				One_Driver_595SendByte(byte1.U8);
				Comm_PutStr("set on,",7);
				Comm_PutStr(&buf[7],2);
				Sub_SendOk();
			break;
			case 2:
				if(data_8u<32)
				{
					byte1.U32 = pow(2,data_8u);
					One_Driver_595SendByte(byte1.U8);
				}
				else
				{
					temp = data_8u -32;
					byte2.U32 = pow(2,temp);
					Two_Driver_595SendByte(byte2.U8);
				}
				Comm_PutStr("set on,",7);
				Comm_PutStr(&buf[7],2);
				Sub_SendOk();
			break;
			case 3:
				if(data_8u<32)
				{
					byte1.U32 = pow(2,data_8u);
					One_Driver_595SendByte(byte1.U8);
				}
				else if(data_8u>=32&&data_8u<64)
				{
					temp = data_8u -32;
					byte2.U32 = pow(2,temp);
					Two_Driver_595SendByte(byte2.U8);
				}
				else
				{
					temp = data_8u -64;
					byte3.U32 = pow(2,temp);
					Three_Driver_595SendByte(byte3.U8);
				}

				Comm_PutStr("set on,",7);
				Comm_PutStr(&buf[7],2);
				Sub_SendOk();

			break;
			default:
				Sub_SendErr();

	   }

	}

	else if(0==strncmp(buf,"set part,",9))
	{
		if(n!=13)return;
		data_8u = Sub_Str2Int8u(&buf[9]);
		Part_pin = data_8u;

		Comm_PutStr("set part,",9);
		Comm_PutStr(&buf[9],2);
		Sub_SendOk();
	}
}


//***********************************************************************/
