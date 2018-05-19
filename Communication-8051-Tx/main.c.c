#include<reg51.h>

sbit SW1 = P1^7;
sbit SW2 = P1^6;

void delay_ms(unsigned int itime)
{
unsigned int i,j;
for (i=0;i<itime;i++) 
{
for (j=0;j<1275;j++);
}
}

void serial(unsigned char x)
{
SBUF=x;
while(TI==0);
TI=0;
}

void uart_init()  
{
 TMOD=0x20;
 TH1=-3;
 SCON=0X50;
 TCON=0x40;
 IE=0X90;
 RI=0;
 TI=0;
}

void tx_data(char *aaa)
{
unsigned int i;
for(i=0;aaa[i]!=0;i++)
{
serial(aaa[0]); //For sending only a single character
}
}
void main(void)
{

	uart_init();
	while(1==1)
	{
		if(SW1 == 0)
		{	
			tx_data("A");
			delay_ms(50);

		}
		else if(SW2 == 0)
		{
			tx_data("B");
			delay_ms(50);
		}

	}
}
