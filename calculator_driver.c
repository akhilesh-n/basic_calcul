#include<reg51.h>
#include"header.h"
sbit RS=P3^4;
sbit RW=P3^5;
sbit EN=P3^6;

void lcd_init()
{
	lcd_cmd(0x2);//compulsory in hw curser set to home not clr
	lcd_cmd(0x28);//init into 8 bit mode
	lcd_cmd(0xe);//cursor on
	lcd_cmd(0x1);//clr scr n set cursor to home
}
void lcd_data(u8 ch)
{
	P0=ch>>4;
	RS=1;
	RW=0;
	EN=1;
	delay_ms(2);
	EN=0;
	
	P0=ch&0x0f;
	RS=1;
	RW=0;
	EN=1;
	delay_ms(2);
	EN=0;
}
void lcd_cmd(u8 cmd)
{
	P0=cmd>>4;
	RS=0;
	RW=0;
	EN=1;
	delay_ms(2);
	EN=0;
	P0=cmd&0x0f;
	RS=0;
	RW=0;
	EN=1;
	delay_ms(2);
	EN=0;
}


void lcd_string(u8 *str)
{
	while(*str)
	{
		lcd_data(*str);
		str++;	
		delay_ms(50);		
	}
}
void lcd_int(s16 num)
{
	u8 buff[6];
	s8 i=0;
	if(num==0)
		{
			lcd_data('0');
			return;
		}
			if(num<0)
		{
			lcd_data('-');
			num=-num;
		}
	while(num)
	{
		buff[i]=(num%10)+48;
		num=num/10;
		i++;
	}
	for(--i;i>=0;i--)
	{
		lcd_data(buff[i]);
	}
	
}
	void lcd_float(f32 f)
{
	s16 n=f;
	lcd_int(n);
	lcd_data('.');
	n=(f-n)*10000;
	if(n<10)
		lcd_data('0');
	lcd_int(n);
}

sbit R0=P2^0;
sbit R1=P2^1;
sbit R2=P2^2;
sbit R3=P2^3;
sbit C0=P2^4;
sbit C1=P2^5;
sbit C2=P2^6;
sbit C3=P2^7;
code u8 lookup_tbl[4][4]={1,2,3,'/',
													4,5,6,'*',
													7,8,9,'-',
													'c',0,'=','+'};
u8 key_scan(void)
{
	u8 row,col;
	R0=R1=R2=R3=0;
	C0=C1=C2=C3=1;
	while((C0&C1&C2&C3)==1); // checking any sw is pressed or not !
	R0=0;
	R1=1;
	R2=1;
	R3=1;
	if((C1&C2&C0&C3)==0)
	{
		row=0;
		goto colcheck;

	}
	R0=1;
	R1=0;
	R2=1;
	R3=1;
	if((C1&C2&C0&C3)==0)
	{
		row=1;
		goto colcheck;
	}
	R0=1;
	R1=1;
	R2=0;
	R3=1;
	if((C1&C2&C0&C3)==0)
	{
		row=2;
		goto colcheck;
	}
	R0=1;
	R1=1;
	R2=1;
	R3=0;
	if((C1&C2&C0&C3)==0)
	{
		row=3;
		goto colcheck;
	}
	
	colcheck:
	if(C0==0)
		col=0;
	if(C1==0)
		col=1;
	if(C2==0)
		col=2;	
	if(C3==0)
		col=3;
	while((C0&C1&C2&C3)==0);
	return lookup_tbl[row][col];
}
f32 calcu(s16 prev,s16 temp,u8 op)
{
	f32 result;
	switch(op)
	{
		case '+': if(prev=='x')
								result=(f32)temp;
							else
								result=(f32)prev+(f32)temp;
							break;
		case '-': if(prev=='x')
								result=(f32)temp;
							else
								result=(f32)prev-(f32)temp;
							break;
		case '*': if(prev=='x')
								result=(f32)temp;
							else
								result=(f32)prev*(f32)temp;
							break;
		case '/': if(prev=='x')
								result=(f32)temp;
							else
								result=(f32)prev/(f32)temp;
							break;
		default : result=temp;
	}
							return result;
}
//23 oct

s16 prev_val='x';
	u8 op,prev_op=0;
	f32 result,temp=0;

void num_key(u8 key)
{
	temp=temp*10+key;
}

f32 if_equalto()
{
	result=calcu(prev_val,temp,prev_op);
	prev_val='x';
	temp=0;
	return result;
}

void ifcancl()
{
	prev_val='x';
	temp=0;
}

f32 if_operator(u8 key)
{
	
				op=key;
				if(prev_op)
					result=calcu(prev_val,temp,prev_op);
				else
					result=calcu(prev_val,temp,op);
				prev_op=key;
				prev_val=result;
				temp=0;
				return result;
	
}
	
