#ifndef __74HC595_H__
#define __74HC595_H__

/*∫Í∂®“Â*/
#define Total595 4

sbit SER = P1^0;
sbit ST_CP = P1^1;
sbit SH_CP = P1^2;
sbit OE = P1^3;

sbit SER0 = P1^4;
sbit ST_CP0 = P1^5;
sbit SH_CP0 = P1^6;
sbit OE0 = P1^7;

sbit SER1 = P2^0;
sbit ST_CP1 = P2^1;
sbit SH_CP1 = P2^2;
sbit OE1 = P2^3;

void One_Driver_595SendByte(U8* temp);
void Two_Driver_595SendByte(U8* temp);
void Three_Driver_595SendByte(U8* temp);


extern U8 Part_pin;
extern union UU32 byte1,byte2,byte3;


#endif