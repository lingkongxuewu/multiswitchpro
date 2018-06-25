
/*--------------------------------文*件*信*息-----------------------------
* 文件名：  Comm.h
* 版　本：  v1.0
* 创建人：   
* 日  期：   
------------------------------------------------------------------------*/
/***********************************************************************/
#ifndef __COM_H__
#define __COM_H__

#include	"_Include.h"
	/*-----宏定义---------------------*/	
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
		
	/*-----结构体数据类型定义---------*/
	typedef struct 
	{
	    U16  RingBufRxCtr;
	    U8  *RingBufRxInPtr;
	    U8  *RingBufRxOutPtr;
	    U8   RingBufRx[COMM_RX_BUF_SIZE];
	    U16  RingBufTxCtr;	   //TX数组中存放的数据个数
	    U8  *RingBufTxInPtr;	   //存放数据的临时指针变量
	    U8  *RingBufTxOutPtr;
	    U8   RingBufTx[COMM_TX_BUF_SIZE];
	} COMM_RING_BUF;



	
	/*-----常量（表格等）声明---------*/
	/*-----函数声明-------------------*/
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
/*-------------变量声明--------------*/
COMM_EXT COMM_RING_BUF	xdata	CommBuf;
COMM_EXT	bdata	bit		CommRxFlag;		//通信接收标志位
COMM_EXT	bdata	bit		CommTxFlag;		//通信发送标志位
#endif