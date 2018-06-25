
/*--------------------------------��*��*��*Ϣ-----------------------------
* �ļ�����  Comm.h
* �桡����  v1.0
* �����ˣ�   
* ��  �ڣ�   
------------------------------------------------------------------------*/
/***********************************************************************/
#ifndef __COM_H__
#define __COM_H__

#include	"_Include.h"
	/*-----�궨��---------------------*/	
	#define  COMM_RX_BUF_SIZE     200
	#define  COMM_TX_BUF_SIZE     200

	#define BAUDRATE        	9600           	// Baud rate of UART in bps
	#define COMM_NO_ERR			0
	#define COMM_RX_EPT			1
	#define COMM_TX_FULL		2
	#define COMM_TX_EPT			3
	#define	COMM_STOP			1
	#define COMM_TRAN			0
	#define	ISR_EN()		    EA=1
	#define	ISR_DIS()		    EA=0
		
	/*-----�ṹ���������Ͷ���---------*/
	typedef struct 
	{
	    U16  RingBufRxCtr;
	    U8  *RingBufRxInPtr;
	    U8  *RingBufRxOutPtr;
	    U8   RingBufRx[COMM_RX_BUF_SIZE];
	    U16  RingBufTxCtr;	   //TX�����д�ŵ����ݸ���
	    U8  *RingBufTxInPtr;	   //������ݵ���ʱָ�����
	    U8  *RingBufTxOutPtr;
	    U8   RingBufTx[COMM_TX_BUF_SIZE];
	} COMM_RING_BUF;



	
	/*-----���������ȣ�����---------*/
	/*-----��������-------------------*/
	void  Comm_HardwareInit (void);
	void  Comm_SoftwareInit (void);
	void  Comm_SendSta (void);
	void  Comm_SendStop (void);
	U8 Comm_GetChar (U8 *err);
	U8 Comm_PutChar (U8 c);
	U8 Comm_GetTxChar (U8 *err);
	void  Comm_PutRxChar (U8 c);
	void  Comm_TimerInit (void);
	void  Comm_TimerProc (void);
	U8 Comm_StateGet (void);
	void  Comm_PutStr (U8* ptr,U8 n);
	void  Sub_SendVer(void);
	void Comm_ClrRxBuf (void);
    struct XtoStr Comm_XtoStr(U8 temp);
    void Display_Char(U32 temp);
    void Float2Byte(float floatNum,U8* byteArry);
    void Debug_Displayad(U8 RegAdd,U8 NumOfBytes);

/*-----------------------------------*/
#ifdef   __COMM_C__
#define  COMM_EXT
#else
#define	 COMM_EXT  extern
#endif
/*-------------��������--------------*/
COMM_EXT COMM_RING_BUF	xdata	CommBuf;
COMM_EXT	bdata	bit		CommRxFlag;		//ͨ�Ž��ձ�־λ
COMM_EXT	bdata	bit		CommTxFlag;		//ͨ�ŷ��ͱ�־λ
#endif