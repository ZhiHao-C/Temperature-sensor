#include <REGX52.H>
#include "delay.h"
sbit SCL=P2^1;                     //���������ܽ�
sbit SDA=P2^0;                     


void I2C_start()                   //I2C��ʼ��־ΪSCL�ߵ�ƽʱSDA��һ���½���
{
	SCL=1;
	SDA=1;
	SDA=0;
	delay_ms(2);
	SCL=0;
}

void I2C_stop()                   //I2C������־ΪSCL�ߵ�ƽʱSDA����һ���½���
{
	SDA=0;
////	SCL=0;
	SCL=1;
	delay_ms(2);
	SDA=1;
}

void I2C_sentdata(unsigned char byte)//ͨ��I2C��������
{
	unsigned char i;
	for(i=0;i<8;i++)                 //��Ҫ���͵�byte�ֽڴӸ�λ��ʼ����
	{
		SDA=byte&(0x80>>i);
		SCL=1;                       //SCLΪ1��ʱ�򽫶�ȡSDA
		SCL=0;                       //����Ϊ�´���׼��
	}
//	for(i=0;i<8;i++)
//	{
//		SDA=(byte<<i);
//		SCL=1;
//		SCL=0;
//	}
}

unsigned char I2C_receivedata()//ͨ��I2C��������
{
	unsigned char Data=0X00;
	unsigned char i;
	SDA=1;                     //�ͷ�SDA����SDA����Ȩ���ӻ���
	delay_ms(5);
	for(i=0;i<8;i++)           //����һ��Date����SDA�������������Ƚ������λ
	{
		SCL=1;                 //SCL�͵�ƽ�ڼ�ӻ������ݸ���SDA����SCLΪ�ߵ�ƽʱ��ȡһλ
		if(SDA==1){Data=Data|(0x80>>i);}
		SCL=0;
	}
	return Data;
}

void I2C_sentACK(unsigned char ACK)//����Ӧ���������յ��ӻ��������ݺ�Ҫ����Ӧ��ACKΪ0ʱ��ʾӦ��
{
	SDA=ACK;                       //SDA
	SCL=1;                         //�ߵ�ƽ��ȡ
	delay_ms(1);
	SCL=0;
}

unsigned char I2C_receiveACK()//����Ӧ��
{
	unsigned char ACKbit;
	SDA=1;
	delay_ms(1);
	ACKbit=SDA;
	SCL=1;
	delay_ms(1);
	SCL=0;
	return ACKbit;
}