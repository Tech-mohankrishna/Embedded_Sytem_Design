#define CR 0x0D
#include <LPC21xx.H>
#include <stdio.h>

void getstring(unsigned char *);
int getchar (void) /* Read character from Serial Port */
void status_ok(void);
void Serial_Init(void);
void delay(unsigned int n);


void main(void)
{
	unsigned int
	cnt=0x80,m; char xx;
	Serial_Init();
	delay(50);
	while(1)
	{
		printf("AT\r"); // AT COMMAND FOR INITIALING status_ok();
		printf("AT+IPR=9600\r"); // AT COMMAND FOR BAUD RATE status_ok();
		printf("AT+CMGR=2\r"); // Reading the message detail // at Index 1 with phone number, data and time status_ok();
		delay(250); 
		printf("ATD9790550124;\r");//ATCOMMAND FOR CALL DIALING 
		delay(250); 
		status_ok();
		delay(500);
		 delay(500);
		delay(500);
		delay(500);
		delay(500);
		delay(500);
		printf("ATH\r"); // AT COMMAND FOR CALL DISCONNECTING delay(250);
		status_ok();
		delay(500);
		delay(500);
		printf("ATDL\r"); // AT COMMAND FOR REDIALING delay(250); 
		status_ok();
		delay(500);
		delay(500);
		printf("ATH\r"); // AT COMMAND FOR ANSWERING THE CALL delay(250);
		status_ok();
		delay(500);
		delay(500);
	}
}


void getstring(unsigned char *array)
{
	unsigned char temp=0, i=0;
	do { temp = getchar();
	*array++ = temp;}
	while((temp != '\r') && (temp != '\n'));
	*array = '\0';
}

int getchar (void) /* Read character from Serial Port */
{
	while (!(U0LSR & 0x01));
	return (U0RBR);
}


void status_ok(void)
{
	getstring(y);
	while(!(strstr(y,"OK")))
		getstring(y);
		pointr = strstr(y,"OK");
		lcd_cmd(0xc0);
		lcd_data(*pointr++);
		lcd_data(*pointr);
		delay(500);
		lcd_cmd(0x01);
}


void Serial_Init(void)
{
	PINSEL0 |= 0X00000005; //Enable Txd0 and Rxd0
	U0LCR = 0x00000083; //8-bit data, no parity, 1-stop bit
	U0DLL = 0x00000061; //for Baud rate=9600,DLL=82
	U0LCR = 0x00000003; //DLAB = 0;
}

void delay(unsigned int n)
{
	unsigned int i,j;
	for(i=0;i<n;i++)
	{
	for(j=0;j<12000;j++)
		{
		}
	}
}

