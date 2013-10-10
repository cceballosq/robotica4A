#include<16F877A.h>
#device adc=10
#include<math.h>
#use delay (clock = 4000000)
#fuses XT,NOWDT,PUT,NOLVP,NOBROWNOUT


 int8 d1,d2,d3;
 int8 num[10]={63,6,91,79,102,109,125,7,127,111};
 float cif=0,aux=0,dec=0,tem=0;



void main ()
{

set_tris_a(0xff);
set_tris_b(0x00);
set_tris_c(0x00);
set_tris_d(0x00);

setup_adc_ports( RA0_ANALOG);
set_adc_channel(0);
setup_adc(ADC_CLOCK_DIV_32);



output_b(0x00);
output_c(0x00);
output_d(0x00);

while (true){
  tem = read_adc();
  //por que Vref / 1024 = 0.004882  x 1000
  cif = tem * .488281;

aux=floor(cif);
dec=cif-aux;

d1=floor(aux/10);
aux-=d1*10;

d2=floor(aux);
d3=floor(dec/0.1);


output_c(num[d1]);
output_d(num[d2]);
output_b(num[d3]);

}

}
