#include <LPC17xx.H>
#define  RS  0x08 //(01000000000000000000000000000000)
#define  RW  0x10 //(00100000000000000000000000000000)
#define  EN  0x20 //(00010000000000000000000000000000)
void delay(unsigned long int x);
void lcdwrt(unsigned char y);
void lcdgpioinit();

int main(void)
{
	
	unsigned char cmd[]={0X38,0X0E,0X06,0X01,0X80};
	unsigned char msg[]="PES UNIVERSITY",i;
	SystemInit ();
  lcdgpioinit();
	LPC_GPIO2->FIOCLR1=RW;  
	LPC_GPIO2->FIOCLR1=RS;

	for(i=0;i<5;i++)
		{	lcdwrt(cmd[i]);
		}
	
  delay(50000);
		
	LPC_GPIO2->FIOSET1=RS;   // RS=1 – Data Register
		
	for(i=0;msg[i]!='\0';i++)
		{ 
			lcdwrt(msg[i]);
		}
}

void lcdwrt(unsigned char y)
	{	LPC_GPIO0->FIOPINH=y << 5;
		LPC_GPIO2->FIOSET1=EN;
		delay(1000);
		LPC_GPIO2->FIOCLR1=EN;  
		delay(5000);
	}
void lcdgpioinit()
{		LPC_GPIO2->FIOMASK1=0X00;
		LPC_GPIO2->FIODIR1=0XFF;
		LPC_GPIO0->FIOMASKH|=0X0000; // 11111000
		LPC_GPIO0->FIODIRH|=0XFFFF; //00000111
}

void delay (unsigned long int x)
	{	unsigned long int j;
		for(j=0;j<x;j++);
	}
