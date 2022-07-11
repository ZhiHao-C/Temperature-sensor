#include <REGX52.H>
#include "ds18b20.h"
#include "LCD1602.h"
#include "onewire.h"
#include "keycode.h"
#include "AT24C02.h"
#include "delay.h"
#define unchar unsigned char
unchar keynum;
float T,TSHOW;
char TLOW,THIGHT;
void main ()
{
	THIGHT=AT24C02_readbyte(0x01);
	TLOW=AT24C02_readbyte(0x02);
	if(THIGHT>125|| TLOW<-55||THIGHT<TLOW){THIGHT=26;TLOW=12;}
	LCD_Init();
	LCD_ShowChar(1,1,'T');
	LCD_ShowString(1,2,":");
	LCD_ShowString(2,1,"TH");
	LCD_ShowString(2,9,"TL");
	LCD_ShowString(2,3,":");
	LCD_ShowString(2,11,":");
	LCD_ShowSignedNum(2,4,THIGHT,3);
	LCD_ShowSignedNum(2,12,TLOW,3);
//	LCD_ShowString(1,1,"temperature");
	while (1)
	{
		DS18b20_convert_T();
		T=DS18b20_read_T();
		keynum=key();
		if(T<0)
		{
			LCD_ShowString(1,3,"-");
			TSHOW=-T;
		}
		else
		{
			TSHOW=T;
			LCD_ShowString(1,3,"+");
		}
		LCD_ShowNum(1,4,TSHOW,3);
		LCD_ShowChar(1,7,'.');
		LCD_ShowNum(1,8,(unsigned long)(TSHOW*100)%100,2);
		
		if(keynum)
		{
			if(keynum==1)
			{
				if(THIGHT<125){THIGHT++;}
				
			}
			if(keynum==2)
			{
				if(THIGHT>TLOW)THIGHT--;
			}
			if(keynum==3)
			{
				if(THIGHT>TLOW)TLOW++;
				
			}
			if(keynum==4)
			{
				if(TLOW>-55)TLOW--;
				
			}
			LCD_ShowSignedNum(2,4,THIGHT,3);
			LCD_ShowSignedNum(2,12,TLOW,3);
			AT24C02_writebyte(0x01,THIGHT);
			delay_ms(5);
			AT24C02_writebyte(0x02,TLOW);
			delay_ms(5);
		}
		if (T>THIGHT)
		{
			LCD_ShowString(1,13,"OV:H");
		}
		else if (T<TLOW)
		{
			LCD_ShowString(1,13,"OV:L");
		}
		else 
		{
			LCD_ShowString(1,13,"    ");
		}
		
		
	}
	
	
	
}



