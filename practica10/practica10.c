#include<16F877A.h>
#device adc=10
#use delay (clock = 4000000)
#include <lcd.c> // driver para usar la lcd
#include <math.h>
#include <stdlib.h> //libreia para funciones como read_adc y otras
#fuses XT,NOWDT,PUT,NOLVP,NOBROWNOUT
float cif=0,aux=0,cif2=0,aux2=0;

void main ()
{

set_tris_a(0xff);
set_tris_d(0x00);

setup_adc_ports(ALL_ANALOG);
setup_adc(ADC_CLOCK_DIV_32);

lcd_init();
while (true)
{
delay_ms(500);
set_adc_channel(0);
delay_us(10);
cif = read_adc();
cif *= (float).488281;    
lcd_gotoxy(1,1);
printf(lcd_putc,"temp 1: %2.2f",cif);

set_adc_channel(1);
delay_us(10);
cif2 = read_adc();
cif2 *= (float).488281; 
lcd_gotoxy(1,2);
printf(lcd_putc,"temp 2: %2.2f",cif2);




}

}

