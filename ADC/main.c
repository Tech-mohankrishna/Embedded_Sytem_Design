#include <LPC17xx.H>
void delay(unsigned long int dk);
unsigned long int di=0;
unsigned short int adc=0;
int main()
{
SystemInit();
	

/*Configuration of ADC */
	
LPC_SC->PCONP|=0X00001000; //initializing the System Control register values.
LPC_GPIO1->FIOMASK3=0XEF; //masking 
LPC_GPIO1->FIODIR3=0X10; //making it as output
LPC_PINCON->PINSEL3=0XC0000000;// initilizing pinselect register as AD0.5 ( alternating function 3 )( 31st and 30th bit )
LPC_ADC->ADCR=0X00210320;//initializing ADC Control Register  [7:0] = 20 : 0010 0000 : enabling AD05 : ......... [16] : BURST bit
LPC_SC->PCLKSEL0=0x00000000; // default peripheral clock for ADC PINCLK frequency is 18MHz factor of 4.
	
/* Conversion takes places
Totally it takes 12 clock cycles, 

Generate signal for end of conversion as DONE bit.( 5th bit of AD0STAT register )	
	
	if conversion is completed it gives the value: 0x00000020
	
	*/	
	
	
	
	
	// checking whether conversion is complete or not.
	
while(1) 		
{                         
while((LPC_ADC->ADSTAT&0X00000020)!=0X00000020) // hence as state above, checking the 5th bit so check for the done status.
{ // waiting here till the conversion completes.
}

adc=(((LPC_ADC->ADDR5 )& 0x0000fff0)>>4);  // ADDR5 storing the converted value in (15:4 ), hence first mask those value using fff0 and 
																						//and shifter by 4 

if (adc > 0x7ff) // Comparing MV with RV
	{
		LPC_GPIO1->FIOSET3=0X10;  
	}
else 
	{
		LPC_GPIO1->FIOCLR3=0X10; 
	}
}			
}
