#include<16F877A.h>
#device adc=10
#include<math.h>
#use delay (clock = 4000000)
#fuses XT,NOWDT,PUT,NOLVP,NOBROWNOUT
#use fast_io(b)


 int8 d1,d2,d3,d4,itr=0,con=0;
 int8 num[10]={63,6,91,79,102,109,125,7,127,111};
 float cif=0,aux=0,dec=0;

#INT_RTCC
void_isr(void)
   {
   itr += 1;
   if (itr==1){
output_b(num[d1]);
output_c(0);
output_c(1);
}
if (itr==2){
output_b(num[d2]);
output_c(0);
output_c(2);
}
if (itr==3){
output_b(num[d3]);
output_c(0);
output_c(4);
}
if (itr==4){
output_b(num[d4]);
output_c(0);
output_c(8);
itr=0;
con+=1;
}
   
   }


void main ()
{

set_tris_a(0xff);
set_tris_c(0x00);
set_tris_b(0x00);

output_c(0x00);
output_b(0x00);

setup_adc_ports(RA0_ANALOG);
set_adc_channel(0);
setup_adc(ADC_CLOCK_DIV_32);

enable_interrupts(int_rtcc);
enable_interrupts(GLOBAL);
set_timer0(0);
setup_timer_0(RTCC_INTERNAL|RTCC_DIV_16);


while (true)
{
if(con==9){
cif = read_adc();
cif *= .488281;   //por que Vref / 1024 = 0.004882  x 100

aux=floor(cif); //floor me regresa el entero de cif en aux
dec=cif-aux;

d1=floor(aux/10);
aux-=d1*10;

d2=floor(aux);
d3=floor(dec/0.1);
d4=(floor(dec/0.01))-(d3*10);
con=0;
}

}

}

