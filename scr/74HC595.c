
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
			SH_CP = 0;	NOP();	  //��λ�Ĵ���ʱ��
			if((temp[i]<<j)&0x80)		//�ȷ����������һ���ֽڵ����λ Total595-1-i
			SER = 0;
			else
			SER = 1;

			SH_CP = 1;	NOP();	  //SH_CP������ʱ��λ�Ĵ����е����ݰ��ռ�����ʽ�����ƶ�һλ
		}
	  NOP();
	}
	OE = 0;
	ST_CP = 0;	 NOP();   //�洢�Ĵ���ʱ��
	ST_CP = 1;	 NOP();		//������ʱ��λ�Ĵ����е����ݽ���洢��
}

void Two_Driver_595SendByte(U8* temp)
{
	U8 i,j;

	OE0 = 1;
	for(i=0;i<Total595;i++)
	{
		for(j=0;j<8;j++)
		{
			SH_CP0 = 0;	NOP();	  //��λ�Ĵ���ʱ��
			if((temp[i]<<j)&0x80)		//�ȷ����������һ���ֽڵ����λ Total595-1-i
			SER0 = 0;
			else
			SER0 = 1;

			SH_CP0 = 1;	NOP();	  //SH_CP������ʱ��λ�Ĵ����е����ݰ��ռ�����ʽ�����ƶ�һλ
		}
	  NOP();
	}
	OE0 = 0;
	ST_CP0 = 0;	 NOP();   //�洢�Ĵ���ʱ��
	ST_CP0 = 1;	 NOP();		//������ʱ��λ�Ĵ����е����ݽ���洢��
}

void Three_Driver_595SendByte(U8* temp)
{

	U8 i,j;

	OE1 = 1;
	for(i=0;i<Total595;i++)
	{
		for(j=0;j<8;j++)
		{
			SH_CP1 = 0;	NOP();	  //��λ�Ĵ���ʱ��
			if((temp[i]<<j)&0x80)		//�ȷ����������һ���ֽڵ����λ 
			SER1 = 0;
			else
			SER1 = 1;

			SH_CP1 = 1;	NOP();	  //SH_CP������ʱ��λ�Ĵ����е����ݰ��ռ�����ʽ�����ƶ�һλ
		}
	  NOP();
	}
	OE1 = 0;
	ST_CP1 = 0;	 NOP();   //�洢�Ĵ���ʱ��
	ST_CP1 = 1;	 NOP();		//������ʱ��λ�Ĵ����е����ݽ���洢��
}
