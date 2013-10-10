#include <16f877a.h>
#device ADC=10
#fuses XT,NOWDT,NOPROTECT,NOLVP,PUT,BROWNOUT
#use fast_io(A)
#use delay(clock=4000000)

float vRead;
void main()
{

   setup_adc(ADC_CLOCK_INTERNAL);   //Modificamos el clock interno del ADC
   setup_adc_ports(RA0_analog);   //Establecemos el puerto RA0 como analogo
   set_adc_channel(0);   //Channel 0 correspondiente a RA0

   setup_CCP1(ccp_pwm);   //establesco el modulo CCP en modo PWM
   setup_timer_2(T2_DIV_BY_4, 249, 1);   // Frecuencia de 1KHz
   
   /**
   Para modificar nuestro setup_timer_2() con lo valores correctos para generar una frecuencia de 1KHz el calculo fue el siguiente:
   
      1/1KHz = [PR2+1]*4*1/Fosc*TMR2Preescaler
         Solucion:
   
      .001 = [PR2+1]*4*1/4MHz*4(Dependiendo de que nuestro resultado sea un entero exacto y va de: 1:1 1:4 1:16)
      1E-3/4E-6 = PR2
      PR2 = 250-1
      PR2 = 249
   
   Calculo de Duty:
   
      Duty = value /[4*(PR2+1)]
      Duty = value /[4*(249+1)]
      _____________
     | 1000 = 100% |
     | 900 = 90%   |
     | 100 = 10%   |

         set_pwm1_duty (anchura de pulso)
         <---------->
                                             
          ----------                     -----------
         |          |                   |           |
         |          |                   |           |
     ----            --------------------            ----------

         <------------------------------>
               setup_Timer_2 (frecuencia)
   **/

   while (TRUE)
   {
      delay_ms(2);  //retardo como tiempo de respuesta a la lectura analoga 
      vRead = read_adc();  //vRead contiene la lectura analoga
      vRead *= (float).488281;
     vRead*=10;
      //set_pwm1_duty(vRead);
     if (vRead<=330)
      {
         //Para trabajar al 10% en base a los calculos
         set_pwm1_duty((long)300);
      }else if(vRead>=500)
         {
            //Para trabajar al 90% en base a los calculos
            set_pwm1_duty(800);
         }
          else
          {
            //Para cuando la variacion es intermedia entre 100 y 900
            set_pwm1_duty(vRead);
          }
   }
   
}
