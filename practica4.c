#include <16f877a.h>
#fuses XT, NOWDT, NOPROTECT, PUT,NOLVP,NOBROWNOUT
int8 a,x1,x2,x3,ciclo;
#int_timer0

void_isr()
{
 a += 1;
}
void main()
{
set_tris_B(0x00);
set_tris_C(0x00);
set_tris_D(0x00);
output_b(0);
output_c(0);
output_d(0);

x1=0;
x2=0;
x3=0;

ciclo=0;
setup_timer_0(rtcc_div_64|rtcc_internal);
enable_interrupts(int_timer0);
enable_interrupts(global);


while (true)
{
   if (a==61)
   {
      a=0;
      ciclo+=1;
     if (ciclo>6)
       {
         ciclo=1;

       }
   x1+=1;
   output_B(x1);
   
   
     if ((ciclo==2) || (ciclo==4) || (ciclo==6) )
      {
         x2+=1;
         output_C(x2);
      }
     if ((ciclo==3) || (ciclo==6) )
      {
         x3+=1;
         output_D(x3);
      }

   }
 }

}
