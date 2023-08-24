#include<LPC17xx.h>
void uart0_init(void);
void CAN_Init(void);
void CAN_ACC(void);
void looktable(void); 
void delay(unsigned long int z);
void can_tx(unsigned long int id,unsigned char msg);
unsigned char rx=0;
int main()
{
SystemInit ();	
uart0_init();
CAN_Init();
CAN_ACC();
looktable(); 	
	while(1)
	{
	while((LPC_UART0->LSR&0X01)!=0X01) //  UART recive flag
	{}
		rx=LPC_UART0->RBR;
		if(rx=='0')
	{
    can_tx(0x00000021,'0'); //( ascii valyue of character  0 0)

  }		
	else if(rx=='1')	
	{	
	  can_tx(0x00000021,'1');	// ( ascii valyue of character  0 0)
	}
	
}
}
void CAN_Init(void)

{
	LPC_SC->PCONP|=0x00002000; 
	LPC_SC->PCLKSEL0|=0X00000000; // taking default value 18MHz as clock going to peripheral CAN
	LPC_PINCON->PINSEL0|=0X00000005; //......... 0000 0101
	LPC_CAN1->MOD=0x00000001; // make sure MOD[0]: RM;   
														// MOD[3] : Transmit Priority Mode: 0: depends on CAN identifier 
														// bit of mode register should not be zero; CAN controller is opeartional in nature ; if 1; works fine
	LPC_CAN1->CMR=0X00000000;
	LPC_CAN1->GSR=0x00000000; // [0]: RBS : 0 = empty; [2] : TBS : 0 = trasnmitting atlease one byte 
	LPC_CAN1->IER=0x00000001; // 
	LPC_CAN1->BTR=0X001C0007; 
	LPC_CAN1->MOD=0x00000000;	
}

void CAN_ACC(void)
{
	LPC_CANAF->AFMR=0x00000001;
	LPC_CANAF->SFF_sa=0x00000000;
	LPC_CANAF->SFF_GRP_sa=0x00000000;
	LPC_CANAF->EFF_sa=0x00000000;
	LPC_CANAF->EFF_GRP_sa=0x00000008;
	LPC_CANAF->ENDofTable=0x00000008;
	LPC_CANAF->AFMR=0x00000000;	
}

void looktable(void) 
{
	LPC_CANAF->AFMR=0x00000001;
	LPC_CANAF_RAM->mask[0]=0x00000012;
	LPC_CANAF_RAM->mask[1]=0x00000014;
	LPC_CANAF->AFMR=0x00000000;
}

void delay(unsigned long int z)
{unsigned long int x;
for(x=0;x<z;x++);
}

void uart0_init(void)
{ LPC_SC->PCONP|=0X00000000;
  LPC_PINCON->PINSEL0|=0X00000050;
  LPC_SC->PCLKSEL0|=0X00000000;
  LPC_UART0->LCR=0X83;
  LPC_UART0->DLM=0X00;
  LPC_UART0->DLL=0X75;
  LPC_UART0->FDR=0X00000010;
  LPC_UART0->LCR=0X03;
	//LPC_UART0->FCR=0X06;
}
  
  void can_tx(unsigned long int id,unsigned char msg)
	{
	while((LPC_CAN1->SR&0X00000004)!=0X00000004) // to check TBS bit 
	{ // wait here till bu becomes free
	} // checking status register bit no.2 : TBS : ( to check the status of the bus  ) // if 0 it is engaged.
	
	
	LPC_CAN1->TFI1=0X80010000;// (7 - 0)PRIORITY IS 00,(15 - 8) R,(19 - 16) DLC 1 Byte,(19 - 29) R, (30) RTR=0, (31) 29bit identifier
	LPC_CAN1->TID1=id; // 
	LPC_CAN1->TDA1=msg; // becuase only 1 byte of data is used. 
	LPC_CAN1->CMR=0X21; 
	
	}
 
	