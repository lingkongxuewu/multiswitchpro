#include "_Include.h"

void init_port(void)
{
	U8 SfrPage = SFRPAGE;
	SFRPAGE = CONFIG_PAGE;
	
	P0SKIP  |= 0x0F;	//skip P0.0 P0.1 p0.2 p0.3 
	P0MDIN  &= ~0x01;   //set P0.0 analog input(VREF)
	P0MDOUT |= 0x10;    //set P0.4 push-pull
	P1MDOUT |= 0xFF;    //set P1.0...P1.7 push-pull
	P2MDOUT	|= 0x0F;    //set P2.0...P2.3 push-pull
	XBR0 = 0x01;  		//enable UART I/O
	XBR2 = 0x40;		//enable crossbar
	SFRPAGE = SfrPage;
}

static void init_clk(void)
{
	U8 SfrPage_ = SFRPAGE;
	SFRPAGE = CONFIG_PAGE;
	OSCICN |= 0xC7;		//24M					  

	CLKSEL = 0X00;				//	选择内部振荡器作为系统时钟
	while((OSCICN & 0x10) == 0);//	等待时钟稳定
	VDM0CN = 0xA0;				//	Enable VDD monitor and high threshold
	RSTSRC = 0x02;				//	Enable VDD monitor as a reset source

	SFRPAGE = SfrPage_;	
}

void init_sys(void)
{
	init_clk();
	init_port();
	Comm_HardwareInit();
	Comm_SoftwareInit();
	Timer2_Init();
}