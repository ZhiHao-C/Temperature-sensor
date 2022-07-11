#include <REGX52.H>
#define unchar unsigned char
sbit DQ=P3^7;

/*������*/
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

unsigned char onewire_init()//�����߳�ʼ��
{
	unchar ackbit;
	DQ=1;
	DQ=0;                   //��������������
	Delay500us();
	DQ=1;                   //�ͷ�����
	Delay80us();            //��ʱ80us����ڵĴӻ��Ὣ��������
	ackbit=DQ;
	Delay500us();
	return ackbit;
}

void onewire_sentbit(unsigned char Bit)//ͨ�����߷���һλ����
{
	DQ=1;
	Delay5us();	
	DQ=0;                              //��������10us
	Delay10us();
	DQ=Bit;                            //����10us��ӻ�����50us�ڶ�ȡDQ��ƽ�ߵ�ƽΪ1�͵�ƽΪ0
	Delay45us();
	DQ=1;                              //�ͷ�����
}

unsigned char onwire_receivebit()//ͨ�����߽���һλ����
{
	unsigned char Bit;
	DQ=1;
	Delay5us();
	DQ=0;                       //��������
	Delay5us();                 
	DQ=1;                       //�ͷ����ߣ������ӻ���
	Delay5us();
	Bit=DQ;                     
	Delay45us();
	return Bit;
}

void onewire_sentbyte(unsigned char Byte)//�����ֽ�����
{
	unsigned char i;
	for (i=0;i<8;i++)
	{
		onewire_sentbit(Byte&(0x01<<i));
	}
}



unsigned char onewire_receivebyte()     //�����ֽ�����
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