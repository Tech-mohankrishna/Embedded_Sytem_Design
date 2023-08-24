#include<LPC17XX.H>
#include<stdio.h>
#include<string.h>

void uart0_init(void);
void delay(unsigned long int x);
void pin_init();
void uart0_init();
void uart3_init();
int main()
	{ 
		
	  unsigned char str1[13]= "09008206C944" , i,j;
		unsigned char str2[64];
		unsigned int count;
	  SystemInit();
	  uart0_init();
	  uart3_init();
	  pin_init();	 
    LPC_GPIO1 -> FIOSET3 = 0X20;		
	  while(1)
	  {
		  
		  for(i=0;i<12;i++)
		  {
				
			while((LPC_UART0->LSR&0x01)!=0x01)
			{
			}
			  str2[i] = LPC_UART0->RBR;
//			  LPC_UART0->THR = str2[i];
		  }
			str2[12]='\0';
			
			count =0;
			
			for(j=0;j<12;j++)
		  {
			  if(str1[j] == str2[j])
				{
					count++;
				}
				else
				{
					count = 0;
				}
		  }
			
		  if (count!=0)
		  {
			  LPC_GPIO1 -> FIOSET3 = 0X20;
				delay(0x500000);
				LPC_GPIO1 -> FIOCLR3 = 0X20;
		  }
		  else
		  {
			  
		  }
	  }
		
	
}

void pin_init()
{
	 LPC_GPIO1->FIOMASK3 = 0XDF;
	  LPC_GPIO1 -> FIODIR3 = 0x20;
}

void uart0_init()
{
	LPC_SC ->PCONP |= 0x03001000; // 24th and 25th bit make UART 2,3 both enable 
	  LPC_PINCON->PINSEL0|=0X00000050;//
	  //Initialze Baud Rate , before that define LCR reg
	  LPC_UART0->LCR = 0x83;
	  LPC_UART0->DLM=0X00;
	  LPC_UART0->DLL=0X75;
	  LPC_UART0->FDR=0X00000010;
	  LPC_UART0->LCR=0X03;
}

void uart3_init()
{
	LPC_SC ->PCONP |= 0x20000000; // 24th and 25th bit make URAT 2,3 both enable 
	  LPC_PINCON->PINSEL0|=0X0F000000;//
	  //Initialze Baud Rate , before that define LCR reg
	  LPC_UART3->LCR = 0x83;
	  LPC_UART3->DLM=0X00;
	  LPC_UART3->DLL=0X75;
	  LPC_UART3->FDR=0X00000010;
	  LPC_UART3->LCR=0X03;
}

void delay(unsigned long int x)
{ unsigned long int m;
	for(m=0;m<x;m++);

}
