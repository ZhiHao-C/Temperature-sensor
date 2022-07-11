#include <REGX52.H>
#include "onewire.h"
#include "LCD1602.h"
void DS18b20_convert_T()
{
	onewire_init();
	onewire_sentbyte(0xcc);//���Ͳ���ָ�� Skip ROM��CCh�����˺��ָ��������������������ã�
	onewire_sentbyte(0x44);//���Ͳ���ָ�� Convert T��44h��������һ���¶�ת���������������ݣ�
}


float DS18b20_read_T()
{
	unsigned char TLSB,TMSB;
	int temp;
	float T;
	onewire_init();
	onewire_sentbyte(0xcc);
	onewire_sentbyte(0xbe);//���Ͳ���ָ�� Read Scratchpad��BEh������ȡ�ݴ��������ݣ�
	TLSB=onewire_receivebyte();
	TMSB=onewire_receivebyte();
//	LCD_ShowBinNum(1,1,TMSB,8);
//	LCD_ShowBinNum(1,9,TLSB,8);
	temp=(TMSB<<8)|TLSB;//�൱�ڱ��һ��16λ��2�ֽڣ�����
	T=temp/16.0;        //��Ϊ���λ����2��0�η�����2�ĸ�4�η�
	return T;
}