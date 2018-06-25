/*--------------------------------文*件*信*息-----------------------------
* 文件名：  Time.c
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
#define   __TIMER_C__
#include "_Include.h"

static xdata U8 count;
static xdata U8 count_in;
U16 xdata sum_temp;
U8  xdata vas;



//***********************************************************************/
// *功    能：
// *入    口：
// *出    口：
// *备    注：
// *函数性质：
//***********************************************************************/
void Timer2_Init (void)
{	
	U8 SfrPage_ = SFRPAGE;
	SFRPAGE = ACTIVE_PAGE;	
	TMR2CN  = 0x00;							// Stop Timer2; Clear TF2;	
	CKCON  |= 0x10;							// Select SYSCLK for timer 2 source		0x30
	TMR2RL  = -(SYSCLK/1000);				// Init reload value for 1ms			65536-(SYSCLK/10000)--100us
	TMR2	= 0xFFFF;						// Set to reload immediately
	IP |= 0x40;
	ET2	  	= 1;							// Enable Timer2 interrupts
	TR2	  	= 1;							// Start Timer2
	SFRPAGE = SfrPage_;
	MainTime4Cnt=3990;
}	



/***********************************************************************/
// *功能：
// *入口：主动发送时间周期，轮询COMM的时间周期
// *出口：
// *备注：
// *函数性质：
/***********************************************************************/
#if 1
void Timer2_ISR (void) interrupt 5
{
	TF2H = 0;								// Clear Timer2 interrupt flag
	Timer2_TaskInIsr();
}

/***********************************************************************/

#define	MAIN_TIME1_INIT	(1000/100)
#define	MAIN_TIME2_INIT	(1000/8)
#define	MAIN_TIME3_INIT	(1000/2)
#define	MAIN_TIME4_INIT	(1000/1)

//static   U8 MainTime4En  = OFF;

/***********************************************************************/
// *功能：定时器2 控制主动发送模式的频率和时间周期
// *入口：
// *出口：
// *备注：
// *函数性质：
/***********************************************************************/

void Timer2_TaskInIsr (void)
{				
	Comm_TimerProc();						// CommTimer=10 轮询COMM的时间周期

}
#endif


