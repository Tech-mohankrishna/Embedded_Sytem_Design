// RFID card reader for Multi strings without using string.h///
#include<LPC17xx.h>
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
unsigned char a[3][13]={"09008206BE33\0","0900820A5CD0\0","09008206A825\0"};
//unsigned char msg1[]="matched";
//unsigned char msg2[]="not_matched";
char al[12];
unsigned int val,m,n;
unsigned char b=0;
unsigned char i,j;


int main(void)
{
	
	SystemInit(); 
	LPC_GPIO1->FIOMASK3=0xDF;
	LPC_GPIO1->FIODIR3=0x20;
	UART0port_init();
	UART3port_init();
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
								LPC_GPIO1->FIOSET3=0x20;
								break;
							}				
						else
							{
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
