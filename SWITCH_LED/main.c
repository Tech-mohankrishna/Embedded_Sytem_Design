#include <lpc17xx.h>

void delay(void);

int main()
{
	LPC_GPIO1->FIODIR3 = 0x10; // Configure pins 0 to 3 on Port 0 as Output
	
	while(1)
	{
		LPC_GPIO1->FIOSET3 = 0x10; // Output HIGH
		delay();
		LPC_GPIO1->FIOCLR3 = 0x10; // Output LOW
		delay();
	}
	//return 0; // normally this wont execute
}	

void delay() //Hardcoded delay function
{
	int count,i=0;
	for(count=0; count < 1000; count++) // You can edit this as per your needs
	{
		i++; // something needs to be here else compiler will remove the for loop!
	}
}
