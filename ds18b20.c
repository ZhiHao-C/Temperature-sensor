#include <REGX52.H>
#include "onewire.h"
#include "LCD1602.h"
void DS18b20_convert_T()
{
	onewire_init();
	onewire_sentbyte(0xcc);//发送操作指令 Skip ROM【CCh】：此后的指令将对在线所有器件起作用；
	onewire_sentbyte(0x44);//发送操作指令 Convert T【44h】：启动一次温度转换而无需其他数据；
}


float DS18b20_read_T()
{
	unsigned char TLSB,TMSB;
	int temp;
	float T;
	onewire_init();
	onewire_sentbyte(0xcc);
	onewire_sentbyte(0xbe);//发送操作指令 Read Scratchpad【BEh】：读取暂存器的内容；
	TLSB=onewire_receivebyte();
	TMSB=onewire_receivebyte();
//	LCD_ShowBinNum(1,1,TMSB,8);
//	LCD_ShowBinNum(1,9,TLSB,8);
	temp=(TMSB<<8)|TLSB;//相当于变成一个16位（2字节）数据
	T=temp/16.0;        //因为最低位不是2的0次方而是2的负4次方
	return T;
}