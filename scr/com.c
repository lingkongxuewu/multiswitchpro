/*--------------------------------文*件*信*息-----------------------------
* 文件名：  Comm.c
* 版　本：  v1.0
* 创建人：   
* 日  期：   
#define   __COM_C__

//***********************************************************************/

#define   __COMM_C__
#include "_Include.h"
/*-----变量定义-------------------*/

static U16  xdata	CommTimer;

//***********************************************************************/
// *功    能：
// *入    口：
// *出    口：
// *备    注：
// *函数性质：
//***********************************************************************/
void Comm_Isr (void) interrupt INTERRUPT_UART0
{	
	U8 temp;
	U8 err;
		
	if(TI0==1)								// Check if transmit flag is set
	{	
		TI0=0;								// Clear interrupt flag
		temp=Comm_GetTxChar(&err);
		if(COMM_TX_EPT!=err)
		{	
 			SBUF0 = temp;					// Transmit to Hyperterminal
			CommTxFlag = 1;
		}
		else
		{	
//			Comm_SendStop();
			CommTxFlag = 0;
		}

	}

	if(RI0==1)
	{
		RI0=0;								//Clear interrupt flag
		temp=SBUF0;							// Read a character from UART	
		#ifdef	COMM_485
		if(CommTxFlag == 0)					
		#endif
		{
			Comm_PutRxChar(temp);
			Comm_TimerInit();
		}
	}
	
	if(OVR0 == 1)
	{	
		OVR0 = 0;
	}
}
//***********************************************************************/
void Comm_HardwareInit (void)
{	
	U8 SfrPage_ = SFRPAGE;	
	
	SFRPAGE = CONFIG_PAGE;
	SCON0 = 0x10;							  
	// Baud Rate = [BRG Clock / (65536 - (SBRLH0:SBRLL0))] x 1/2 x 1/Prescaler

	#if	((SYSCLK / BAUDRATE / 2 / 0xFFFF) < 1)
			SBRL0 = -(SYSCLK / BAUDRATE / 2);
			SBCON0 |= 0x03;						 // Set prescaler to 1*/
	#elif ((SYSCLK / BAUDRATE / 2 / 0xFFFF) < 4)
			SBRL0 = -(SYSCLK / BAUDRATE / 2 / 4);
			SBCON0 &= ~0x03;
			SBCON0 |= 0x01;						 // Set prescaler to 4
	#elif ((SYSCLK / BAUDRATE / 2 / 0xFFFF) < 12)
			SBRL0 = -(SYSCLK / BAUDRATE / 2 / 12);
			SBCON0 &= ~0x03;					  // Set prescaler to 12
	#else
			SBRL0 = -(SYSCLK / BAUDRATE / 2 / 48);
			SBCON0 &= ~0x03;
			SBCON0 |= 0x02;						 // Set prescaler to 48
	#endif
	
	IP |= 0x10;								    // Make UART high priority
	ES0 = 1;								    // Enable UART0 interrupts
		
	SBCON0 |= 0x40;							    // Enable baud rate generator
	TI0 = 1;									// Indicate TX0 ready
//	PS0 = 1;
	SFRPAGE = SfrPage_;
}
//***********************************************************************/
void Comm_SoftwareInit (void)
{	
    COMM_RING_BUF *p_buf=&CommBuf;
		
	p_buf->RingBufRxCtr= 0;
	p_buf->RingBufRxInPtr  = &p_buf->RingBufRx[0];
	p_buf->RingBufRxOutPtr = &p_buf->RingBufRx[0];
	p_buf->RingBufTxCtr= 0;
	p_buf->RingBufTxInPtr  = &p_buf->RingBufTx[0];
	p_buf->RingBufTxOutPtr = &p_buf->RingBufTx[0];	
}
//***********************************************************************/
// *功    能：
// *入    口：
// *出    口：
// *备    注：
// *函数性质：
void Comm_SendSta (void)
{	
	TI0=1;
}
//***********************************************************************/
//void Comm_SendStop (void)
//{
//	UART_R();
//}
//***********************************************************************/
//***********************************************************************/
//***********************************************************************/
//***********************************************************************/
// *功    能： 获取com数据区将要TX的数据
// *入    口： RingBufTxCtr 存储的数据量，RingBufTxOutPtr 输出数据的指针
// *出    口：
// *备    注：
// *函数性质：
//***********************************************************************/
U8 Comm_GetTxChar (U8 *err)
{	
	COMM_RING_BUF *p_buf=&CommBuf;
	U8 c;
	
	ISR_DIS();
	if (p_buf->RingBufTxCtr > 0)
	{	p_buf->RingBufTxCtr--;
		c = *p_buf->RingBufTxOutPtr++;
		if (p_buf->RingBufTxOutPtr == &p_buf->RingBufTx[COMM_TX_BUF_SIZE])
		{	p_buf->RingBufTxOutPtr = &p_buf->RingBufTx[0];
		}
		*err = COMM_NO_ERR;
		ISR_EN();
		return (c);
	}
	else
	{	*err = COMM_TX_EPT;
		ISR_EN();
		return (0);
	}
}
//***********************************************************************/
//***********************************************************************/
// *功    能： 将要TX的数据填入com数据区
// *入    口： RingBufTxCtr 存储的数据量，RingBufTxInPtr 输入数据的指针
// *出    口：
// *备    注：
// *函数性质：
//***********************************************************************/
U8 Comm_PutChar (U8 c)
{	
	COMM_RING_BUF *p_buf=&CommBuf;
	
	ISR_DIS();
	if (p_buf->RingBufTxCtr < COMM_TX_BUF_SIZE)
	{	p_buf->RingBufTxCtr++;
		*p_buf->RingBufTxInPtr++ = c;
		if (p_buf->RingBufTxInPtr == &p_buf->RingBufTx[COMM_TX_BUF_SIZE])
		{	p_buf->RingBufTxInPtr = &p_buf->RingBufTx[0];
		}
		ISR_EN();
		return (COMM_NO_ERR);
	}
	else
	{	
		ISR_EN();
		return (COMM_TX_FULL);
	}
}



//***********************************************************************/
//***********************************************************************/
// *功    能： 将接收的数据填入com数据区
// *入    口： RingBufRxCtr 存储的数据量，RingBufRxInPtr 填入数据的指针
// *出    口：
// *备    注：
// *函数性质：
//***********************************************************************/

void Comm_PutRxChar (U8 c)
{	
	COMM_RING_BUF *p_buf=&CommBuf;
	
	ISR_DIS();
	if (p_buf->RingBufRxCtr < COMM_RX_BUF_SIZE)
	{	p_buf->RingBufRxCtr++;
		*p_buf->RingBufRxInPtr++ = c;
		if (p_buf->RingBufRxInPtr == &p_buf->RingBufRx[COMM_RX_BUF_SIZE])
		{	p_buf->RingBufRxInPtr = &p_buf->RingBufRx[0];
		}
	}
	ISR_EN();
}
//***********************************************************************/
// *功    能： 将接收的数据取出com数据区
// *入    口： RingBufRxCtr 存储的数据量，RingBufRxInPtr 填入数据的指针
// *出    口：
// *备    注：
// *函数性质：
//***********************************************************************/
U8 Comm_GetChar (U8 *err)
{	
	COMM_RING_BUF *p_buf=&CommBuf;
	U8 c;
	
	ISR_DIS();
	if (p_buf->RingBufRxCtr > 0)
	{	p_buf->RingBufRxCtr--;
		c = *p_buf->RingBufRxOutPtr++;
		if (p_buf->RingBufRxOutPtr == &p_buf->RingBufRx[COMM_RX_BUF_SIZE])
		{	p_buf->RingBufRxOutPtr = &p_buf->RingBufRx[0];
		}
		*err = COMM_NO_ERR;
		ISR_EN();
		return (c);
	}
	else
	{	*err = COMM_RX_EPT;
		ISR_EN();
		return (0);
	}
}

//***********************************************************************/
void Comm_PutStr (U8* ptr,U8 n)
{	
	U8 i;
	
	for(i=0;i<n;i++)
	{	
		Comm_PutChar(*ptr++);
	}
}


//***********************************************************************/
// *功    能：
// *入    口：
// *出    口：
// *备    注：
// *函数性质：
//***********************************************************************/
void Comm_TimerInit (void)
{
	CommTimer=10;			   //中断接收数据完毕一帧数据后，调用
}
//***********************************************************************/
void Comm_TimerProc (void)
{
	if( CommTimer>0 ) 
	{   
	if(--CommTimer==0) 
	CommRxFlag=1;         //liuliu     2013-02-22
	}
}
//***********************************************************************/

//***********************************************************************/