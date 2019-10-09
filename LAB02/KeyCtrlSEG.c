#include <STC12C5A60S2.h>

//目录，看哪个实验把0改成1
#define Test1  0       //按下KEY1,第一位数码管从0~9依次显示
#define Test2  0       //按下KEY2，切换模式，按下KEY1数码管从0~9依次显示，并伴随有蜂鸣器的蜂鸣

typedef unsigned char u8;

sbit BEEP = P1 ^ 0;     //置0则响

sbit SM_G1 = P2 ^ 0;
sbit SM_G2 = P2 ^ 1;
sbit SM_G3 = P2 ^ 2;
sbit SM_G4 = P2 ^ 3;

sbit SM_A = P0 ^ 7;
sbit SM_B = P0 ^ 6;
sbit SM_C = P0 ^ 5;
sbit SM_D = P0 ^ 4;
sbit SM_E = P0 ^ 3;
sbit SM_F = P0 ^ 2;
sbit SM_G = P0 ^ 1;
sbit SM_DP = P0 ^ 0;

sbit KEY1 = P3 ^ 2;
sbit KEY2 = P3 ^ 4;

void SM_Ctrl(u8 index, u8 status) //0则开启
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

void DispNum(u8 num, u8 hasdip) //0点亮dip
{
	switch (num)
	{
		case 0:
			P0 = 0x03;
			break;
		case 1:
			P0 = 0x9F;
			break;
		case 2:
			P0 = 0x25;
			break;
		case 3:
			P0 = 0x0D;
			break;
		case 4:
			P0 = 0x99;
			break;
		case 5:
			P0 = 0x49;
			break;
		case 6:
			P0 = 0x41;
			break;
		case 7:
			P0 = 0x1F;
			break;
		case 8:
			P0 = 0x01;
			break;
		case 9:
			P0 = 0x09;
			break;
	}
	SM_DP = hasdip;
}

void Clear(void)
{
	P0 = 0xFF;
}

void delay_2ms(unsigned long int time) //2ms的基
{
	unsigned long int i;
	for (i = 0; i < time * 100; i++);
}


#if Test1

void main()
{
	u8 num;

	while (1)
	{
		if (KEY1 == 0)
		{
			SM_Ctrl(1, 0);
			for (num = 0; num <= 9; num++)
			{
				Clear();
				DispNum(num, 1);
				delay_2ms(500);
			}
			Clear();
		}
	}
}

#endif


#if Test2

void main()
{
	u8 index = 1;
	u8 num = 0;

	BEEP = 0;
	SM_Ctrl(1, 0);
	DispNum(0, 1);

	while (1)
	{
		if (KEY2 == 0)
		{
			delay_2ms(100);
			index++;
			if (index < 5)
			{
				SM_Ctrl(index - 1, 1);
				SM_Ctrl(index, 0);
				//DispNum(0,1);
			}
			else
			{
				index = 1;
				SM_Ctrl(1, 0);
				SM_Ctrl(4, 1);
				//DispNum(0, 1);
			}
		}

		if (KEY1 == 0)
		{
			for (num = 0; num <= 9; num++)
			{
				DispNum(num, 1);
				BEEP = 1;
				delay_2ms(20);
				BEEP = 0;
				delay_2ms(300);
			}
			DispNum(0, 1);
		}


	}
}

#endif

