/*
* @time: 2019-10-9 
* @author: Jeremy.Zhang
* @function: LED and Beeper blink(LED闪烁和蜂鸣器响)
*/

#include "STC12C5A60S2.h"

/* define all pins(定义所有引脚) */
sbit LED1 = P2^4;    //high(1) works(高电平点亮)   
sbit LED2 = P2^5;    //high(1) works(高电平点亮) 
sbit LED3 = P2^6;	 //high(1) works(高电平点亮) 
sbit LED4 = P2^7;  	 //high(1) works(高电平点亮) 
sbit BEEP = P1^0;    //low(0)  works(低电平响声)


void main()
{	
	/* define delay variable(定义延时变量) */
	unsigned long int i;
	
	/* config Beeper Mode(配置蜂鸣器为推挽输出模式) */
	P1M0 = 0x01;	

	while(1)
	{
		for(i=0;i<50000;i++);
		BEEP = 0;
		LED1 = 0;
		LED2 = 1;
		LED3 = 1;
		LED4 = 1;

		for(i=0;i<50000;i++);
		BEEP = 1;
		LED1 = 0;
		LED2 = 0;
		LED3 = 1;
		LED4 = 1;

		for(i=0;i<50000;i++);
		BEEP = 0;
		LED1 = 0;
		LED2 = 0;
		LED3 = 0;
		LED4 = 1;

		for(i=0;i<50000;i++);
		BEEP = 1;
		LED1 = 0;
		LED2 = 0;
		LED3 = 0;
		LED4 = 0;
	}	
}
