#ifndef __ONEWIRE_H__
#define __ONEWIRE_H__

unsigned char onewire_init();
void onewire_sentbit(unsigned char Bit);
unsigned char onwire_receivebit();
void onewire_sentbyte(unsigned char byte);
unsigned char onewire_receivebyte();
#endif