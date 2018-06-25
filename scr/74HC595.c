
#include "_Include.h"


U8 Part_pin;



union UU32 byte1,byte2,byte3;

void One_Driver_595SendByte(U8* temp)
{
	U8 i,j;

	ST_CP = 0;	     //存储寄存器时钟

	for(i=0;i<Total595;i++)
	{
		for(j=0;j<8;j++)
		{
			SH_CP = 0;		  //移位寄存器时钟

			if((temp[Total595-1-i]<<j)&0x80)		//先发送数组最后一个字节的最高位
			SER = 1;
			else
			SER = 0;

			SH_CP = 1;		  //SH_CP上升沿时移位寄存器中的数据按照级联方式依次移动一位
		}
	}

	ST_CP = 1;	 //上升沿时移位寄存器中的数据进入存储器
}

void Two_Driver_595SendByte(U8* temp)
{
	U8 i,j;

	ST_CP0 = 0;	     //存储寄存器时钟

	for(i=0;i<Total595;i++)
	{
		for(j=0;j<8;j++)
		{
			SH_CP0 = 0;		  //移位寄存器时钟

			if((temp[Total595-1-i]<<j)&0x80)		//先发送数组最后一个字节的最高位
			SER0 = 1;
			else
			SER0 = 0;

			SH_CP0 = 1;		  //SH_cp上升沿时移位寄存器中的数据按照级联方式依次移动一位
		}
	}

	ST_CP0 = 1;	 //上升沿时移位寄存器中的数据进入存储器
}

void Three_Driver_595SendByte(U8* temp)
{
	U8 i,j;

	ST_CP1 = 0;	     //存储寄存器时钟

	for(i=0;i<Total595;i++)
	{
		for(j=0;j<8;j++)
		{
			SH_CP1 = 0;		  //移位寄存器时钟

			if((temp[Total595-1-i]<<j)&0x80)		//先发送数组最后一个字节的最高位
			SER1 = 1;
			else
			SER1 = 0;

			SH_CP1 = 1;		  //SH_cp上升沿时移位寄存器中的数据按照级联方式依次移动一位
		}
	}

	ST_CP1 = 1;	 //上升沿时移位寄存器中的数据进入存储器
}
