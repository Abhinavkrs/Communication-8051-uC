#include<reg51.h>  
#include<stdio.h>

#define lcd_data P2
sbit RS = P1^0;
sbit E  = P1^1;
sbit op = P1^3;
sbit led2 = P1^5;
sbit def = P1^2;

unsigned char val1;
unsigned char t1 = 0;
unsigned int t2 = 0;
int voteamt[3],j;

void cct_init(void);
void delay(int);
void lcdinit(void);
void writecmd(int);
void writedata(char);
void ReturnHome(void);
void votedata(unsigned int);


void uart_init()  
{
 TMOD=0x20;
 TH1=0XE8;
 SCON=0X50;
 TCON=0x40;
 IE=0X90;
 RI=0;
 TI=0;
 TR1 = 1;
}

void receive_data(void) interrupt 4
{	
	
		//return SBUF;
		val1 = SBUF;
		led2 = 1;
		RI = 0;
	
	if(val1 == '0')
	{
		def = 1;
		t1++;
		
	}
	else if(val1 == '1')
	{
		op = 1;
		t2++;
	}
	else
	{
	;
	}
//	switch(val1)
//	{
//		case '1': led2 = 0; break;
//		case '0': led1 = 1; break;
//		default: def = 1; break;
//	}
}






void main()
{	
	uart_init();
	cct_init();
	lcdinit();                                      

			
	while(1)
	{
			
		
		writecmd(0x80);
		writedata('T');                                 
		writedata('1');
		writecmd(0x84);
		writedata('T');                                 
		writedata('2');   
		writecmd(0xc0);
		votedata(t1);
		writecmd(0xc4);
		votedata(t2);
	}
}


void cct_init(void)
{
P0 = 0x00;   
P1 = 0x00;    
P2 = 0x00;	 
P3 = 0x03;
}

void delay(int a)
{
   int i;
   for(i=0;i<a;i++);   
}

void writedata(char t)
{
	RS = 1;             
  P2 = t;             
  E  = 1;             
  delay(150);
  E  = 0;             
  delay(150);
  
}


void writecmd(int z)
{
   RS = 0;             
   P2 = z;             
   E  = 1;             
   delay(150);
   E  = 0;             
   delay(150);
}

void lcdinit(void)
{
  
     delay(15000);
   writecmd(0x30);
     delay(4500);
   writecmd(0x30);
     delay(300);
   writecmd(0x30);
     delay(650);
  
   writecmd(0x38);    
   writecmd(0x0c);   
   writecmd(0x01);    
   writecmd(0x06);   
   
}
void votedata(unsigned int vote)
{
	char digit;
	int p;
	for(j=2;j>=0;j--)
	{
		voteamt[j] = vote%10;
		vote = vote/10;
	}
	
	for(p=0;p<=2;p++)
	{
	digit = voteamt[p]+48;
	 RS = 1;            
    P2 = digit;             
    E  = 1;             
    delay(150);
    E  = 0;             
    delay(150);
	}
}
