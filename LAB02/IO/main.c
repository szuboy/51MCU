/*
* @time: 2019-10-9 
* @author: Jeremy.Zhang, George
* @function: IO Parallel Control
*/

#include "STC12C5A60S2.h"


/* content: which one is 1(实验内容: 相应的实验内容置为1) */
#define IO_EXP1  0      //按下KEY1, 第一位数码管从0~9依次显示
#define IO_EXP2  1      //按下KEY2, 切换模式，按下KEY1数码管从0~9依次显示，并伴随有蜂鸣器的蜂鸣


/* redefine data type(重定义数据类型别名) */
typedef unsigned char u8;


/* define all pins and variable(定义所有引脚和变量) */
unsigned char NUMS[11] = {0x03, 0x9F, 0x25, 0x0D, 0x99, 0x49, 0x41, 0x1F, 0x01, 0x09, 0xff};    //数字列表(最后一位清空)
sbit KEY1 = P3^2;      //KEY1引脚
sbit KEY2 = P3^4;	   //KEY2引脚
sbit BEEP = P1^0;      //蜂鸣器引脚(低电平有效) 


/* define Eight-Segment pins, Low-Level works(定义八段数码管引脚, 低电平有效)*/
sbit SM_G1 = P2^0;  
sbit SM_G2 = P2^1;
sbit SM_G3 = P2^2;
sbit SM_G4 = P2^3;


/*
* @function: choose_SM, 控制哪一个数码管显示
* @args: index: 数码管序号; status: 低电平有效
* @return: None
*/
void choose_SM(u8 index, u8 status)
{
	switch (index)
	{
		case 1:
			SM_G1 = status;
			break;
		case 2:
			SM_G2 = status;
			break;
		case 3:
			SM_G3 = status;
			break;
		case 4:
			SM_G4 = status;
			break;
		default:
			break;
	}
}


/*
* @function: delay_by_2ms, 延时函数, 2ms的基
* @args: time: 时间
* @return: None
*/
void delay_by_2ms(unsigned long int time)
{
	unsigned long int i;
	for (i = 0; i < time * 100; i++);
}



#if IO_EXP1

void main()
{
	/* define nums index variable(定义数字索引变量) */
	u8 n_index;
	while (1)
	{
		if (0 == KEY1)
		{
			choose_SM(1, 0);
			for (n_index = 0; n_index <= 9; n_index++)
			{
				/* display nums and delay 1s(显示数字, 并延时1秒) */
				P0 = NUMS[n_index];
				delay_by_2ms(500);
			}
			/* clear diaplay nums(清空显示数字) */
			P0 = NUMS[n_index];
		}
	}		
}

#endif


#if IO_EXP2

void main()
{
	/* define nums index and Eight-Segment index variable(定义数字和数码管索引变量) */
	u8 n_index = 0, s_index = 1;

	/* config Beeper Mode and default choose Eight-Segment 1(配置蜂鸣器为推挽输出模式, 默认选择数码管1) */
	P1M0 = 0x01;
	choose_SM(1, 0);	

	while (1)
	{
		if (0 == KEY2)
		{
			/* request to limit range 1-4, setting Eight-Segment mode(限制范围到1-4, 循环选择, 同时设置显示的上一个和当前的数码管的模式, ) */
			s_index++;
			if (s_index < 5)
			{
				choose_SM(s_index - 1, 1);
				choose_SM(s_index, 0);
			}
			else
			{
				s_index = 1;
				choose_SM(1, 0);
				choose_SM(4, 1);
			}
		}

		if (0 == KEY1)
		{
			for (n_index = 0; n_index <= 9; n_index++)
			{
				/* display nums and delay 1s with beeper(显示数字, 并延时1秒, 同时伴随蜂鸣器工作) */
				P0 = NUMS[n_index];
				BEEP = 0;
				delay_by_2ms(250);
				BEEP = 1;
				delay_by_2ms(250);
			}
			/* clear diaplay nums(清空显示数字) */
			P0 = NUMS[n_index];	
		}
	}
}

#endif
