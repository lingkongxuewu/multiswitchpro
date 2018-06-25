#include "main.h"
#include "_Include.h"

void main()
{
	SFRPAGE = ACTIVE_PAGE;    		// Set for PCA0MD
	PCA0MD &= ~0x40;          		// WDTE = 0 (clear watchdog timer enable)
	init_sys();
	delay_ms(250);

	while(1)
	{
		Send_TimeProc();
	}

}