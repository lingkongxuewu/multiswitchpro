
#include "_Include.h"

union UU32 byte1,byte2,byte3;

void One_Driver_595SendByte(U8* temp)
{
	U8 i,j;

	OE = 1;
	for(i=0;i<Total595;i++)
	{
		for(j=0;j<8;j++)
		{
			SH_CP = 0;	NOP();	  //移位寄存器时钟
			if((temp[i]<<j)&0x80)		//先发送数组最后一个字节的最高位 Total595-1-i
			SER = 0;
			else
			SER = 1;

			SH_CP = 1;	NOP();	  //SH_CP上升沿时移位寄存器中的数据按照级联方式依次移动一位
		}
	  NOP();
	}
	OE = 0;
	ST_CP = 0;	 NOP();   //存储寄存器时钟
	ST_CP = 1;	 NOP();		//上升沿时移位寄存器中的数据进入存储器
}

void Two_Driver_595SendByte(U8* temp)
{
	U8 i,j;

	OE0 = 1;
	for(i=0;i<Total595;i++)
	{
		for(j=0;j<8;j++)
		{
			SH_CP0 = 0;	NOP();	  //移位寄存器时钟
			if((temp[i]<<j)&0x80)		//先发送数组最后一个字节的最高位 Total595-1-i
			SER0 = 0;
			else
			SER0 = 1;

			SH_CP0 = 1;	NOP();	  //SH_CP上升沿时移位寄存器中的数据按照级联方式依次移动一位
		}
	  NOP();
	}
	OE0 = 0;
	ST_CP0 = 0;	 NOP();   //存储寄存器时钟
	ST_CP0 = 1;	 NOP();		//上升沿时移位寄存器中的数据进入存储器
}

void Three_Driver_595SendByte(U8* temp)
{

	U8 i,j;

	OE1 = 1;
	for(i=0;i<Total595;i++)
	{
		for(j=0;j<8;j++)
		{
			SH_CP1 = 0;	NOP();	  //移位寄存器时钟
			if((temp[i]<<j)&0x80)		//先发送数组最后一个字节的最高位 
			SER1 = 0;
			else
			SER1 = 1;

			SH_CP1 = 1;	NOP();	  //SH_CP上升沿时移位寄存器中的数据按照级联方式依次移动一位
		}
	  NOP();
	}
	OE1 = 0;
	ST_CP1 = 0;	 NOP();   //存储寄存器时钟
	ST_CP1 = 1;	 NOP();		//上升沿时移位寄存器中的数据进入存储器
}
