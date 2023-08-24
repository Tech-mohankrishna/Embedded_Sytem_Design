#include<LPC17xx.h>
#define PRESCALE (25-1)
#define TRIG1 (1<<21) //P0.21 
#define ECHO1 (1<<22) //P0.22
void delay(unsigned long int x);

void initTimer0(void) //PCLK must be = 25Mhz! 
  { 
		LPC_TIM0->CTCR = 0x0; 
  	LPC_TIM0->PR = PRESCALE; //Increment TC at every 24999+1 clock cycles 
  	LPC_TIM0->TCR = 0x02; //Reset Timer 
  } 
  
 
  void startTimer0(void) 
  { 
  	LPC_TIM0->TCR = 0x02; //Reset Timer 
  	LPC_TIM0->TCR = 0x01; //Enable timer 
  } 
  
 
  unsigned int stopTimer0(void) 
  { 
  	LPC_TIM0->TCR = 0x00; //Disable timer 
  	return LPC_TIM0->TC; 
  } 
  
 
  void delayUS(unsigned int microseconds) //Using Timer0 
  { 
  	LPC_TIM0->TCR = 0x02; //Reset Timer 
  	LPC_TIM0->TCR = 0x01; //Enable timer 
  	while(LPC_TIM0->TC < microseconds); //wait until timer counter reaches the desired delay 
  	LPC_TIM0->TCR = 0x00; //Disable timer 
  } 
  
 
  void delayMS(unsigned int milliseconds) //Using Timer0 
  { 
  	delayUS(milliseconds * 1000); 
  } 

unsigned char rx=0;
int main()
{
		int echoTime1=0; 
  	float distance11=0; 
		unsigned int distance1,i;
  	initTimer0(); //Init Timer for delay functions - defined in ocf_lpc176x_lib.c 
  	
  
    LPC_GPIO0->FIOMASK3=0x00;
  	LPC_GPIO0->FIODIR |= TRIG1;    //Set P0.21(TRIG) as output 
  	LPC_GPIO0->FIODIR &= ~(ECHO1); //Set P0.22(ECHO) as input (explicitly) 
  	LPC_GPIO0->FIOCLR |= TRIG1;    //Set P0.21 LOW initially 
	//------P1.29 as output (LED)
	  LPC_GPIO1->FIOMASK3=0XDF;  // 1101 1111 
 		LPC_GPIO1->FIODIR3=0X20;	 // 0010 0000
		SystemInit ();	
		
	while(1)
	{
			distance11=0;
		
  		//Output 10us HIGH on TRIG pin 
  		LPC_GPIO0->FIOPIN |= TRIG1; 
  		delayUS(10); 
  		LPC_GPIO0->FIOCLR |= TRIG1; 
		
		  
  		while(!(LPC_GPIO0->FIOPIN & ECHO1)); //Wait for a HIGH on ECHO pin 
  		startTimer0(); //Start counting 
  		while(LPC_GPIO0->FIOPIN & ECHO1); //Wait for a LOW on ECHO pin 
  		echoTime1 = stopTimer0(); //Stop counting and save value(us) in echoTime 
   
		  
  		distance11 = (0.0343 * echoTime1)/2.0; //Find the distance 
			distance1=(int)(distance11*100);
		  if(distance1<20)
			{ 
				for(i=0;i<20;i++)
				{
				LPC_GPIO1->FIOSET3=0X20;	
   			delay(0x50000);	
   			LPC_GPIO1->FIOCLR3=0X20;	
   			delay(0x50000);
				}
			}
			else 
			{
			}
  }
}

void delay(unsigned long int z)
{unsigned long int x;
for(x=0;x<z;x++);
}

