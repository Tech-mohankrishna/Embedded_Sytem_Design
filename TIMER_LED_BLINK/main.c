#include <LPC17xx.h>

void initTimer0(void);
void delayUs(unsigned int microseconds);



int main ()
{
	SystemInit();
	LPC_GPIO1->FIOMASK3 = 0xDF; // 1101 1111
	LPC_GPIO1->FIODIR3 = 0x20; //  0010 0000
	initTimer0();
	
	while(1)
	{
		LPC_GPIO1->FIOSET3 = 0x20;
		delayUs(100000);
		LPC_GPIO1->FIOCLR3 = 0x20;
		delayUs(100000);
	}
}

void initTimer0 (void)
{
	LPC_TIM0->CTCR = 0X00;
	LPC_TIM0->PR = 17;
	LPC_TIM0->TCR = 0X02;
}

void delayUs(unsigned int microseconds)
{
	LPC_TIM0->TCR = 0X02;
	LPC_TIM0->TCR = 0X01;
	while( LPC_TIM0->TC < microseconds )
	{
	}
	LPC_TIM0->TCR = 0X00;
}


