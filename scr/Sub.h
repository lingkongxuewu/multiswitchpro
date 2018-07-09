/*--------------------------------文*件*信*息-----------------------------
* 文件名：  Sub.h
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
//***********************************************************************/
#ifndef __SUB_H__

	#define __SUB_H__
	/*-----宏定义---------------------*/
	/*-----结构体数据类型定义---------*/
	/*-----常量（表格等）声明---------*/
	/*-----函数声明-------------------*/

	void Comm_PutInt32u (U32 val);	
	void Comm_PutInt32s (S32 val);
	void Comm_PutInt16u (U16 val);
	void Comm_PutInt16s (S16 val);
	void Comm_PutInt8u (U8 val);
	S8 Sub_Str2Int8s (U8* str);
	
	void Sub_SysRst (void);
	void Sub_BufBubble (S32* p1,U32* p2,U8 n);
	void Sub_BufBubble16s(S16* id,U16* x,U8 n);
//	void Sub_AngCalValGet (float* a,float* k,int16u adc,int8u tag);
//	void Sub_AngCalValCnt (int16u adc0,int16u adc1,int32s ang0,int32s ang1,float* a,float* k);	 //HXL 12/8/28
	
	U8 Sub_Str2Int32sAng (S32 *val,U8* str);
	U8 Sub_Str2Int8u (U8* str);
	U8 Sub_Str2Int32s (S32 *outdata,U8* str);
//	int8u Sub_Str2Int16s (int16s *outdata,int8u* str);
	U8 Sub_Str2Int16u (U16 *temp,U8* str);
	void  Sub_Int32s2Str (char* s,S32 ang);
	void Sub_Int32u2Str (char* s,U32 val);
	void  Sub_Int16u2Str (char* s,U16 adc);
	void  Sub_Int16s2Str (char* s,S16 temp);
	void  Sub_Int8u2Str (char* s,U8 val);
	
	void Sub_SendOk (void);
	void Sub_SendErr (void);
	void Sub_SendAngXY (void);
	void Sub_SendAngXYP (void);
	void Sub_SendAngXCal (U8 i);
	void Sub_SendAngYCal (U8 i);
	void Sub_SendTempCal (U8 i);
	void Sub_SendID (void);
	void Sub_SendAdcTXY (U16 temp,S32 x,S32 y);
	void Sub_SendSoftVer (void);
	void Sub_SendSysNum (void);
	void Sub_SendTCalTest (void);
	void Sub_SendOffset (S32 val);
	void Sub_SendPrmtAll(void);
	void Sub_BufBubble2 (U16* id,S32* x,S32* y,U8 n);	  
	U8 Sub_StralarmCheck(S32 *val,U8* str);
	void Comm_PutNewLine(void);
	void SendTo595OneGroup(U8 data_8u);
	void SendTo595TwoGroup(U8 data_8u);
	void SendTo595ThreeGroup(U8 data_8u);
	
	void Sub_SendMcuT(S16 temp,U16 tadc);		
#endif
/*-----------------------------------*/
#ifdef   __SUB_C__
#define  SUB_EXT
#else
#define	 SUB_EXT  extern
#endif
/*-------------变量声明--------------*/


