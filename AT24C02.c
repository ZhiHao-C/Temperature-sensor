#include <REGX52.H>
#include "I2C.h"
#define AT24C02_address 0xa0             //д��ַ������ַ��1


void AT24C02_writebyte(unsigned char address,Data)//��24c02��ַΪaddress �ĵط�д������Data
{
	
	I2C_start();
	I2C_sentdata(AT24C02_address);// ͨ��I2Cд�ӻ���ַ��AT24C02Ĭ�ϵ�ַ����������
	I2C_receiveACK();
	I2C_sentdata(address);        //��д��Ҫд�����ݵĵ�ַ������24c02Ҫд�����ݵĵ�ַ��
	I2C_receiveACK();
	I2C_sentdata(Data);           //д������
	I2C_receiveACK();
	I2C_stop();
	
}

unsigned char AT24C02_readbyte(unsigned char address)
{
	unsigned char Data;
	I2C_start();
	I2C_sentdata(AT24C02_address);//ͨ��I2Cд�ӻ���ַ
	I2C_receiveACK();
	I2C_sentdata(address);        //��д��Ҫ��ȡ���ݵĵ�ַ������24c02Ҫд�����ݵĵ�ַ��
	I2C_receiveACK();
	I2C_start();
	I2C_sentdata(AT24C02_address+1);//ͨ��I2Cд�ӻ���ַ������
	I2C_receiveACK();
	Data=I2C_receivedata();
	I2C_sentACK(1);
	I2C_stop();
	return Data;
}