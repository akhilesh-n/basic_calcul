#include"header.h"
void main()
{
	u8 data_[50],key,index=0,i;
	f32 out;
	lcd_init();
	lcd_string("demo calcu..");	
	delay_ms(200);
	lcd_cmd(0x01);
	while(1)
	{
		
		key=key_scan();
	
		if(key>=0 && key<=9)
		{
				
			data_[index]=key+48;
			lcd_print(index,data_);
			num_key(key);
			
			
		//	lcd_cmd(0x80+index);
			//lcd_data(key+48);
			index++;
		}
		else
		{
			if(key=='=')
			{
				data_[index]=key;
				out=if_equalto();
				lcd_print(index,data_);
				
				//lcd_data('=');
				lcd_cmd(0xc0);

				lcd_float(out);
		
				i=index;
				while(i)
				{
					data_[i]=0;
					i--;
				}
				data_[0]=0;
				index=0;
				
			                                                  
		
				while(key_scan()!='c');
				lcd_cmd(0x01);
			}				
			else if(key=='c')
			{
				ifcancl();
				lcd_cmd(0x01);
								i=index;
				while(i)
				{
					data_[i]=0;
					i--;
				}
				data_[0]=0;
				index=0;
			}
			else
			{
				data_[index]=key;
			lcd_print(index,data_);
				out=if_operator(key);
		
				//lcd_cmd(0x80+index);
				index++;
				//lcd_data(key);
				lcd_cmd(0xc0);
				lcd_float(out);
					
			}
		
		
		}	
	}
}


	void lcd_print(u8 index,u8 *data_)
{
	u8 d;
	if(index>15)
			{
				d=index-15;
				lcd_cmd(0x80);
				for(d;d<=index;d++)
					lcd_data(data_[d]);
				
			}
			else
			{
				lcd_cmd(0x80);
				for(d=0;d<=index;d++)
					lcd_data(data_[d]);
					
			}	
}
