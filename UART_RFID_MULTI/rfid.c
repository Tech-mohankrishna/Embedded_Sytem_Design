// RFID card reader for Multi strings without using string.h///
#include<LPC17xx.h>
#define  RS  0x08 //(01000000000000000000000000000000)
#define  RW  0x10 //(00100000000000000000000000000000)
#define  EN  0x20 //(00010000000000000000000000000000)

typedef unsigned char u8;
typedef unsigned int u32;
void UART0port_init(void);
void UART3port_init(void);
int call(void);
//char call(char *data);
void rec(void);
//void cmp(void);
void send(void);
void delay(u32 x);
void delay1(unsigned long int x);
void lcdwrt(unsigned char y);
void lcdgpioinit();

unsigned char cmd[]={0X38,0X0E,0X06,0X01,0X80};
unsigned char msg[]="RFID Authentication",i;
unsigned char msg1[]="Matched    ",i;
unsigned char a[3][13]={"0900820A5CDD\0","09008207109C\0","090082070589\0"};
//unsigned char msg1[]="matched";
unsigned char msg2[]="not_matched";
char al[12];
unsigned int val,m,n;
unsigned char b=0;
unsigned char i,j;


int main(void)
{
	
	SystemInit(); 
	lcdgpioinit();
	LPC_GPIO1->FIOMASK3=0xDF;
	LPC_GPIO1->FIODIR3=0x20;
	LPC_GPIO0->FIOMASK0= 0x00;
	LPC_GPIO0->FIODIR0= 0x03; // 00000011
	UART0port_init();
	UART3port_init();
	for(i=0;i<5;i++)
		{	lcdwrt(cmd[i]);
		}
	
  delay(50000);
		
	LPC_GPIO2->FIOSET1=RS;   // RS=1 – Data Register
		
	for(i=0;msg[i]!='\0';i++)
		{ 
			lcdwrt(msg[i]);
		}
		LPC_GPIO0->FIOCLR0= 0x03;
	while(1)
		{
				rec();
				for(j=0;j<3;j++)
					{
						n=0;
						for(i=0;i<12;i++)
						{
								if(a[j][i] == al[i])
									{
										n++;
									}
						}		
						if(n==12)
							{
								LPC_GPIO2->FIOCLR1=RS; // making RS as 0   
								lcdwrt(0xc0);
								LPC_GPIO2->FIOSET1=RS;   // RS=1 – Data Register
								for(i=0;msg1[i]!='\0';i++)
									{ 
										lcdwrt(msg1[i]);
									}
								
								LPC_GPIO1->FIOSET3=0x20; //00100000 
								LPC_GPIO0->FIOSET0= 0x03;// 00000011 (P0.0 P0.1)
								delay(0X1FFFFFF);
								LPC_GPIO1->FIOCLR3=0x20;
								LPC_GPIO0->FIOCLR0= 0x03;
								break;
							}				
						else
							{
								LPC_GPIO2->FIOCLR1=RS; // making RS as 0   
								lcdwrt(0xc0);
								LPC_GPIO2->FIOSET1=RS;   // RS=1 – Data Register
								for(i=0;msg2[i]!='\0';i++)
									{ 
										lcdwrt(msg2[i]);
									}
								
								LPC_GPIO1->FIOCLR3=0x20;
							//	break;
							}
					
          }
				}
			}
	
 
void rec(void)
{

	char emp=0;
  for(i=0;i<12;i++)
		{	
				while(( LPC_UART3->LSR & 0X01)!= 0X01)
					{
					}
			emp=LPC_UART3->RBR;
		  al[i]=emp;
	  }
		
		
		for(i=0;i<=12;i++)
		{	
			LPC_UART0->THR=al[i];	
			while(( LPC_UART0->LSR & 0X20)!= 0X20)
					{
					}
			
	  }
 

} 	


void UART0port_init(void)
{ 
	LPC_SC->PCONP|=0x00400008;
  LPC_PINCON->PINSEL0=0X00000050;
  LPC_UART0->LCR=0X83;
  LPC_UART0->DLL=0X75;
  LPC_UART0->DLM=0X00;
  LPC_UART0->FDR=0X10;
	LPC_UART0->FCR=0X07;
  LPC_UART0->LCR=0X03;
  
}
void UART3port_init(void)
{ 
	LPC_SC->PCONP|=0X02000000;
  LPC_PINCON->PINSEL9=0X0F000000;
  LPC_UART3->LCR=0X83;
  LPC_UART3->DLL=0X75;
  LPC_UART3->DLM=0X00;
  LPC_UART3->FDR=0X10;
	LPC_UART3->FCR=0X07;
  LPC_UART3->LCR=0X03;
}

void delay(u32 x)
{
  int i=0;
  for(i=0;i<x;i++)
  {
  }
}



void lcdwrt(unsigned char y)
	{	
		LPC_GPIO0->FIOPINH=y << 5;
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

void delay1 (unsigned long int x)
	{	unsigned long int j;
		for(j=0;j<x;j++)
		{
	}
}
