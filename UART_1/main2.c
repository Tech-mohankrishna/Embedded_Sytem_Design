#include<LPC17XX.H>
void uart0_init(void);
void delay(unsigned long int x);
int main()
	{
	unsigned long int imm;
	unsigned char str1[]="ARM Cortex M3",i; // tx from Mc to PC.
	SystemInit();
	LPC_SC->PCONP|= 0x03001000; // 0000 0000 0000 ...... byte 4, 24th, 25th bit as 1. power supply for UART 0 & UART 3 and along to ADC
	LPC_PINCON->PINSEL0|=0X00000050; // initializing 4,5,6,7 bit of PINCON high to act in 1st alternate mode P0.2 and P0.3
	uart0_init(); // UART initialization to generate 9600 baud rate ( 9615)


	for(i=0;str1[i]!='\0';i++)
		
	while(1)
	{
		while (LPC_UART0->LSR&0x01==0X01); // Receive FLAG: check bit 0 of LSR register ( RDR Flag is checked ) and data is available in RBR
		{
		}
		
			
		imm = LPC_UART0->RBR; // recived string to RBR Register
		
		LPC_UART0->THR = imm; // transmitting the string
		

		while (LPC_UART0->LSR&0xFF==0X20); // waiting till string is transmitted. chrcks 5th bit of LSR, 5th flag bit = 1: complete 																	// can also be written as while (LPC_UART0->LSR&0x20!=0X20);
		}
	}
	

//********************************************************
void uart0_init(void)
	{
	LPC_UART0->LCR = 0x83;// DLL DLM  FDR: generating 9600 baud rate
	LPC_UART0->DLM=0X00;
	LPC_UART0->DLL=0X75;
	LPC_UART0->FDR=0X00000010; // FDR[3:0] = 0000 ( Divaddval ) /// FDR[7:4] = 0001(Mulval) 
	LPC_UART0->LCR=0X03; // disabling MSB bit as 0.
	}
	
	
//********************************************************
void delay(unsigned long int x)
	{	
	unsigned long int j;
	for(j=0;j<x;j++)
        {}
	}

//**********************************************************


