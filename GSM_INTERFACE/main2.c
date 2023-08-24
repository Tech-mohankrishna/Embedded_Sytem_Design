// #include<LPC17xx.h>

// void gsmsend();
// void fire_sensor();
// void 


// int main ()
// {   
//     int sensor,flag;
//     // pins to detect fire sensor 
//     sensor=LPC_GPIO0->FIOMASK3 >>>3
//     SystemInit();
//     flag=0;
//     while(1){

//         if(sensor&(flag!=1)){   
//             //send message

//             flag=1;
//         }

//     }

// }

// void 

// void fire_sensor(){
//     LPC_GPIO0->FIOMASK3= 0xFD;// 1111_1011
//     LPC_GPIO0->FIODIR3=0x03; // 0000_0100

// } 

// void gsmsend(){

// }


// //GSM AND SMS USING SENSOR

#include<LPC17xx.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int flag = 0;


void delay(unsigned long int x)
{
	unsigned long int i;
	for(i=0;i<x;i++){};
}

void cmdsend(unsigned char k)
{
	unsigned char m;
	LPC_UART0->THR=m;
	while((LPC_UART0->LSR & 0X20)!=0X20)
	{
	}
}


void gsm_init(void)
{
	unsigned char cmd_at[]="AT\r\n";
	unsigned char cmd_creg[]="AT+CREG?\r\n";
	unsigned char cmd_cmgf[]="AT+CMGF=1\r\n";
	unsigned short int i=0;
	
	for(i=0;cmd_at[i]!='\0';i++)
	{
		cmdsend(cmd_at[i]);
	}
	
	delay(0x500000);
	for(i=0;cmd_creg[i]!='\0';i++)
	{
		cmdsend(cmd_creg[i]);
	}
	
	delay(0x500000);
	
	for(i=0;cmd_cmgf[i]!='\0';i++)
	{
		cmdsend(cmd_cmgf[i]);
	}
	
	delay(0x500000);
	
}

void uart0_init(void)
{
	LPC_SC -> PCONP|=0X03001000; //0000 0011 0000 ... 0000
	
    LPC_PINCON -> PINSEL0 = 0X00000050; //P0.2 and P0.3 must do first alternate function
    LPC_UART0 -> LCR = 0X83;
    LPC_UART0 -> DLM = 0X00;
    LPC_UART0 -> DLL = 0X75;
    LPC_UART0 -> FDR = 0X00000010; //LSB 4 bits are for divided value and MSB 4 bits are for mul value
    LPC_UART0 -> LCR = 0X03;
}


void gsm_msgsend(void)
{
	//int flag=0;
	unsigned short int i=0;
	unsigned char cmd_cmgs[]="AT+CMGS=\"8095820000\"\r\n";
	unsigned char msg[]="Aagh lagh gayi hai bhaago!!";
	
	for(i=0;cmd_cmgs[i]!='\0';i++)
	{
		cmdsend(cmd_cmgs[i]);
	}
	
	delay(0x500000);
	
	
	for(i=0;msg[i]!='\0';i++)
	{
		cmdsend(msg[i]);
	}
	
	cmdsend(0X1A);
	delay(0x500000);
	flag=1;  //to send the sms only once
}

int main()
{
	unsigned char sensor;
	//int flag=0;
	SystemInit();
	uart0_init();
	LPC_GPIO0->FIOMASK3=0XF7;
	LPC_GPIO0->FIODIR3=0X00; //P0.27 AS INPUT
	LPC_GPIO1->FIOMASK3=0XDF; // 1101 1111
	LPC_GPIO1->FIODIR3=0X20; //P0.29 AS OUTPUT 0010 0000 
	
	gsm_init();
	
	while(1)
	{
		if(flag==0)
		{
			sensor=(LPC_GPIO0->FIOPIN3>>3);
			if(sensor==0X01)
			{
			LPC_GPIO1->FIOSET3=0X20;
			gsm_msgsend();
		}
		
		else
		{
			LPC_GPIO1->FIOCLR3=0X20;
		}
	}
		
	}
	
}
