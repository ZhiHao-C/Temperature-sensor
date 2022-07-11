#include <REGX52.H>
#define unchar unsigned char
sbit DQ=P3^7;

/*单总线*/
void Delay45us()		//@11.0592MHz
{
	unsigned char i;

	i = 18;
	while (--i);
}

void Delay5us()		//@11.0592MHz
{
}
void Delay10us()		//@11.0592MHz
{
	unsigned char i;

	i = 2;
	while (--i);
}

void Delay500us()		//@11.0592MHz
{
	unsigned char i;
	i = 227;
	while (--i);
}

void Delay80us()		//@11.0592MHz
{
	unsigned char i;
	i = 34;
	while (--i);
}

unsigned char onewire_init()//单总线初始化
{
	unchar ackbit;
	DQ=1;
	DQ=0;                   //主机把总线拉低
	Delay500us();
	DQ=1;                   //释放总线
	Delay80us();            //延时80us后存在的从机会将总线拉低
	ackbit=DQ;
	Delay500us();
	return ackbit;
}

void onewire_sentbit(unsigned char Bit)//通过总线发送一位数据
{
	DQ=1;
	Delay5us();	
	DQ=0;                              //拉低总线10us
	Delay10us();
	DQ=Bit;                            //拉低10us后从机会在50us内读取DQ电平高电平为1低电平为0
	Delay45us();
	DQ=1;                              //释放总线
}

unsigned char onwire_receivebit()//通过总线接收一位数据
{
	unsigned char Bit;
	DQ=1;
	Delay5us();
	DQ=0;                       //拉低总线
	Delay5us();                 
	DQ=1;                       //释放总线（交给从机）
	Delay5us();
	Bit=DQ;                     
	Delay45us();
	return Bit;
}

void onewire_sentbyte(unsigned char Byte)//发送字节数据
{
	unsigned char i;
	for (i=0;i<8;i++)
	{
		onewire_sentbit(Byte&(0x01<<i));
	}
}



unsigned char onewire_receivebyte()     //接收字节数据
{

	unchar i;
	unchar byte=0x00;
	for (i=0;i<8;i++)
	{
		if(onwire_receivebit())
		{
			byte=(byte|(0x01<<i));
		}
	}
	return byte;
}