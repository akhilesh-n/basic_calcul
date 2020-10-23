#ifndef __headr__
#define __headr__
typedef unsigned int u16;
typedef unsigned char u8;
typedef unsigned long int u32;
typedef signed int s16;
typedef signed char s8;
typedef signed long int s32;
typedef float f32;


sfr LED=0x90;


extern void convergence();
extern void divergence();
extern void running_led();
extern bit led_read(u8,u8);
extern void io_write(u8,u8,u8);
extern void io_byte_write(u8,u8);


static u8 flag;


#define PORT0 0
#define PORT1 1
#define PORT2 2
#define PORT3 3

#define SET 1
#define CLR 0

#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7


sfr LCD_PORT=0x080;

extern void delay_ms(u16);
extern void lcd_init(void);
extern void lcd_data(u8);
extern void lcd_cmd(u8);
extern void lcd_string(u8*);


extern void lcd_int(s16);
extern void lcd_float(f32);
extern void cgram_init();
extern u8 strlenc(u8 *);


extern u8 key_scan(void);
extern u8 compare(u8 *);

extern void hex_print(u8);
extern void timer(void);
extern u8 pick_rand(void);

extern f32 calcu(s16,s16,u8);
extern void num_key(u8);
extern f32 if_equalto();
extern void ifcancl();
extern f32 if_operator(u8);
void lcd_print(u8,u8 *);

extern void uart_init(u16 baud);
extern void uart_tx(u8 byte);
extern void uart_string(s8 *ptr);
extern u8 uart_rx(void);
sbit SW1=0x90;
sbit SW2=0x91;
sbit SW3=0x92;

#endif