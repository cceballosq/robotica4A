#include <16f877a.h>
#fuses XT,NOWDT,NOPROTECT,PUT,NOLVP,NOBROWNOUT
#use delay( clock = 4000000 )
#use fast_io(B)
int8 var,var1,var2;
int16 var3;
#int_rb
void int_portb(){
var2=(input_b()>>4);
}
  void main(){
      set_tris_A(0x00);
      set_tris_B(0xF0);
      set_tris_C(0xFF);
      set_tris_D(0xFF);
      var2=0x0D;
      var3=0x00;  
      input_b();
      enable_interrupts(int_rb);
      input_b();
      enable_interrupts(GLOBAL);
   while(TRUE){
   
      var =input_c();
      var1=input_d();
      if(var2==0x0D){
         var3=(int16)var + (int16)var1;
         var2= 0xFF;
        }
     if(var2==0x0E){
         var3=var - var1;
         var2 = 0xFF;
        }
      if(var2==0x0B){
         var3=(int16)var * (int16)var1;
         var2 = 0xFF;
        }
      if(var2==0x07){
         var3=var / var1;
         var2 = 0xFF;
        }
      if (var2==0xFF){
      output_A(var3);
      output_B(var3>>6);
      var2=0x00;
        }
   }
}
