
#include "_Include.h"


U8 Part_pin;



union UU32 byte1,byte2,byte3;

void One_Driver_595SendByte(U8* temp)
{
	U8 i,j;

	ST_CP = 0;	     //�洢�Ĵ���ʱ��

	for(i=0;i<Total595;i++)
	{
		for(j=0;j<8;j++)
		{
			SH_CP = 0;		  //��λ�Ĵ���ʱ��

			if((temp[Total595-1-i]<<j)&0x80)		//�ȷ����������һ���ֽڵ����λ
			SER = 1;
			else
			SER = 0;

			SH_CP = 1;		  //SH_CP������ʱ��λ�Ĵ����е����ݰ��ռ�����ʽ�����ƶ�һλ
		}
	}

	ST_CP = 1;	 //������ʱ��λ�Ĵ����е����ݽ���洢��
}

void Two_Driver_595SendByte(U8* temp)
{
	U8 i,j;

	ST_CP0 = 0;	     //�洢�Ĵ���ʱ��

	for(i=0;i<Total595;i++)
	{
		for(j=0;j<8;j++)
		{
			SH_CP0 = 0;		  //��λ�Ĵ���ʱ��

			if((temp[Total595-1-i]<<j)&0x80)		//�ȷ����������һ���ֽڵ����λ
			SER0 = 1;
			else
			SER0 = 0;

			SH_CP0 = 1;		  //SH_cp������ʱ��λ�Ĵ����е����ݰ��ռ�����ʽ�����ƶ�һλ
		}
	}

	ST_CP0 = 1;	 //������ʱ��λ�Ĵ����е����ݽ���洢��
}

void Three_Driver_595SendByte(U8* temp)
{
	U8 i,j;

	ST_CP1 = 0;	     //�洢�Ĵ���ʱ��

	for(i=0;i<Total595;i++)
	{
		for(j=0;j<8;j++)
		{
			SH_CP1 = 0;		  //��λ�Ĵ���ʱ��

			if((temp[Total595-1-i]<<j)&0x80)		//�ȷ����������һ���ֽڵ����λ
			SER1 = 1;
			else
			SER1 = 0;

			SH_CP1 = 1;		  //SH_cp������ʱ��λ�Ĵ����е����ݰ��ռ�����ʽ�����ƶ�һλ
		}
	}

	ST_CP1 = 1;	 //������ʱ��λ�Ĵ����е����ݽ���洢��
}
