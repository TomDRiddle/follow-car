#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char
//左右电机控制位
sbit LEFT_IN1=P2^0;
sbit LEFT_IN2=P2^1;
sbit RIGHT_IN1=P2^2;
sbit RIGHT_IN2=P2^3;
//四位红外检测位
sbit R1=P1^3;
sbit R2=P1^2;
sbit L1=P1^0;
sbit L2=P1^1;

/*void delay(uint ms)
{

}*/
uchar i=0,j=0;
uchar PWM_LEFT=70,PWM_RIGHT=70;
void turn_left()
{
	PWM_LEFT=30;
	PWM_RIGHT=90;
}


void turn_right()
{
	PWM_LEFT=90;
	PWM_RIGHT=30;
}

void straight()
{
	PWM_LEFT=80;
	PWM_RIGHT=80;
}

void right_fix()
{
	PWM_LEFT=90;
	PWM_RIGHT=10;
}

void left_fix()
{
	PWM_LEFT=10;
	PWM_RIGHT=90;
}
void follow()
{
	if(R1==R2==L1==L2==1)
		straight();
	else if(R1==0)
		turn_right();
	else if(L1==0)
		turn_left();
	else if(R2==0)
		right_fix();
	else if(L2==0)
		left_fix();
}
void init()
{
	 TMOD=0x01;   
	 TH0=(65536-100)/256; 
	 TL0=(65536-100)%256;
	 EA=1;	   
	 ET0=1;	   
	 TR0=1;	   
}

void time_0() interrupt 1  
{
	 i++;
	 j++;
	 TH0=(65536-100)/256; 
	 TL0=(65536-100)%256;

	 if(i<=PWM_LEFT)
	 	LEFT_IN1=1;
	 else 
	    LEFT_IN1=0;
	 if(i>=100)
	    LEFT_IN1=0;

	 if(j<=PWM_RIGHT)
	 	RIGHT_IN1=1;
	 else 
	    RIGHT_IN1=0;
	 if(j>=100)
	    RIGHT_IN1=0;
}

void main()
{
	 init();
	 while(1)
	 {
	 	follow();
	 }
}
