#include <LPC17xx.H>

#define  RS  0x01 //(01000000000000000000000000000000)
#define  RW  0x02 //(00100000000000000000000000000000)
#define  EN  0x04 //(00010000000000000000000000000000)

unsigned long int di=0;
unsigned short int adc=0;
unsigned short int temp=0;


int arraySize = 4;  // Size of the array to store ASCII characters


void delay(unsigned long int x);
void lcdwrt(unsigned char y);
void hexatoascii(unsigned int	 hex, unsigned char *ascii);
void lcdgpioinit();

int main()
{
	unsigned char cmd[]={0X38,0X0E,0X06,0X01,0X80};
	unsigned char msg[]="TEMP IS=",i;
	unsigned char ascii_result[4];  // Buffer to store ASCII result
	//unsigned char asciiResult[arraySize];
//	unsigned char ascii[] = "" ;

	SystemInit ();
	lcdgpioinit();
	LPC_GPIO1->FIOCLR1=RW;  
	LPC_GPIO1->FIOCLR1=RS;
/*Configuration of ADC */
	
	LPC_SC->PCONP|=0X00001000; //initializing the System Control register values.
	LPC_GPIO1->FIOMASK3=0XEF; //masking 
	LPC_GPIO1->FIODIR3=0X10; //making it as output
	LPC_PINCON->PINSEL3=0X30000000;// initilizing pinselect register as AD0.5 ( alternating function 3 )( 31st and 30th bit )
	LPC_ADC->ADCR=0X00210310;//initializing ADC Control Register  [7:0] = 20 : 0010 0000 : enabling AD05 : ......... [16] : BURST bit
	LPC_SC->PCLKSEL0=0x00000000; // default peripheral clock for ADC PINCLK frequency is 18MHz factor of 4.
	
	for(i=0;i<5;i++)
		{	lcdwrt(cmd[i]);
		}

	delay(5000000);
		
	LPC_GPIO1->FIOSET1=RS;   // RS=1 – Data Register
		
	for(i=0;i<4;i++)
		{ 
			lcdwrt(msg[i]);
		}	
		
	delay(0x5000000);

/* Conversion takes places
Totally it takes 12 clock cycles, 

Generate signal for end of conversion as DONE bit.( 5th bit of AD0STAT register )	
	
	if conversion is completed it gives the value: 0x00000020
	
	*/	
	
	
	
	
	// checking whether conversion is complete or not.
	
while(1) 		
{                         
	while((LPC_ADC->ADSTAT&0X00000010)!=0X00000010) // hence as state above, checking the 5th bit so check for the done status.
	{ // waiting here till the conversion completes.
	}

	adc=(((LPC_ADC->ADDR4 )& 0x0000fff0)>>4);  // ADDR5 storing the converted value in (15:4 ), hence first mask those value using fff0 and shifter by 4 
	temp = adc / 0xc ;

	/*PC_GPIO1->FIOCLR1=RS;
	lcdwrt(0x87);
	delay(5000000);*/


	hexatoascii(temp,ascii_result);
	
	delay(50000);
	LPC_GPIO1->FIOCLR1=RS;
	lcdwrt(0x88);
	delay(5000000);


	LPC_GPIO1->FIOSET1=RS;
	
/*	for(i=0;ascii_result[i]!='\0' | cmd[i]!='\0' ;i++)
			{ 
				
				lcdwrt(ascii_result[i]);
	
			}*/



	for(i=0; i<4 ;i++)
			{ 
				
				lcdwrt(ascii_result[i]);
	
			}
		}
	}
		




//*********************************************

void hexatoascii(unsigned int	 hex, unsigned char *ascii) {
    unsigned char d0, d1, d2, d3;
    d0 = hex % 0x0A;
    hex = hex / 0x0A;
    d1 = hex % 0x0A;
    hex = hex / 0x0A;
    d2 = hex % 0x0A;
    d3 = hex / 0x0A;
    d0 = d0 + 0x30;
    d1 = d1 + 0x30;
    d2 = d2 + 0x30;
    d3 = d3 + 0x30;

    ascii[0] = d3;
    ascii[1] = d2;
    ascii[2] = d1;
    ascii[3] = d0;
}



//********************************************

void lcdgpioinit()
{		LPC_GPIO2->FIOMASK0|=0X00;
		LPC_GPIO2->FIODIR0|=0XFF;
		LPC_GPIO1->FIOMASK1|=0XF8;
		LPC_GPIO1->FIODIR1|=0X07;
}

//*********************************************

void delay (unsigned long int x)
	{	unsigned long int j;
		for(j=0;j<x;j++);
	}

//*********************************************
	

void lcdwrt(unsigned char y)
	{	LPC_GPIO2->FIOPIN0=y;
		LPC_GPIO1->FIOSET1=EN;
		delay(1000);
		LPC_GPIO1->FIOCLR1=EN;  
		delay(5000);
	}
	
//*********************************************
	




