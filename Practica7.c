#include <16F877a.H>
#device ADC=10
#include <stdlib.h>
#fuses XT, NOWDT, NOPROTECT, BROWNOUT, PUT, NOLVP
#use delay(clock=4000000)
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7, bits=8, parity=N)
int opc;
char str[10];
int ban,ban2=0,bancs=0;

#int_rda
void rda_isr()
{
   while(kbhit()){//espera a la llegada de los 8 bits
             delay_us(10);
      if(kbhit()){
         if (bancs==0){/*off set*/
            opc=getc();/*recibe comando*/
            if ((opc>96) && (opc < 107) )
               opc=opc - 32;
            ban=1;
            }
         else{
            gets(str);//obtener cadena
            ban2=1;
         }
      }
      }
}

void index()
{
   printf("\f         #### Menu Principal ###");
   printf("\r (A)Lecturas de temperatura  \n(B)Configuracion ");
}

void mconf()
{
   printf("\f### Configuracion ###");
   printf("\r>(C)Offset + -2°C  \r>(D)Cadencia de actualizacion ");
   printf("\r>(E)Resolucion del sensor \r>(F)Version de Firmware");
   printf("\r>(G)Volver al menu principal\r");
}

void main()
{
   //Lineas para conversor ADC
   float decimal;
   int16 valor=0;//lectura ADC
   int cadencia=1;//tiempo de lectura
   int aux=0;
   float offset=0;//rangos de variacion
   int resol=0;//margen de error
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc_ports(RA0_analog);
   set_adc_channel(0);
   //Lineas para interrupcion RDA RS232
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   //LLamada a menu principal
   index();
   //Inicializacion de variables
   opc=0;
   ban=0;
   while(true)
   {
      if (ban==1){
         ban=0;
         switch (opc){
            case 65:{
               printf("\r### Lecturas ###\r");
               printf("\r Para regresar al menu principal precionar m\r\r");
               printf("La temperatura es:        ");
               ban=1;
               aux=cadencia-1;
               while (ban==1){
                  delay_ms(1000);
                  aux+=1;
                  if (aux==cadencia){
                     valor=read_adc();
                     valor=(valor>>resol);
                     
                     if (resol==0){
                     decimal=(float)valor/2.048;}                     
                     if (resol==1){
                     decimal=(float)valor/1.024;}                     
                     if (resol==2){
                     decimal=(float)valor/.512;}
                                          
                     decimal=decimal + offset;
                     
                     printf("\r%f°c",decimal);
                     aux=0;
                  }
                  if ((opc==109)||(opc==77)){
                     ban=0;                     
                     printf("\rRegresando a menu principal\r");
                     delay_ms(1000);
                     index();
                  }
               }
               break;
            }
            case 66: {
               printf("\rConfiguracion \n");
               delay_ms(1000);
               mconf();
               break;
            }
            case 67:{
                  bancs=1;
                  printf("\r---- OFFSET ----");
                  printf("\rIntroduce un valor en el rango de [-2,2] ");
                  while (bancs==1){
                     if (ban2==1){
                        offset=atof(str);
                        ban2=0;
                        bancs=0;
                        mconf();
                     }
                  }
                  break;
            }
            case 68:{
               printf("\r---- Cadencia ----\r");
               printf("\rElige un valor entre 1 y 10 segundos");
               printf(" (para diez presionar CERO)");
               ban=1;
               while (ban==1){
                  if ((opc>47) && (opc<58)){
                     cadencia=opc-47;
                     ban=0;
                     mconf();
                  }
               }
               break;
            }
            Case 69:{
                  printf("\r ---- Opciones de Resolucion ----");
                  printf("\r>(H)8 bits  \r>(I)9 bits \r>(J)10 bits");
                  ban=1;
                  while (ban==1){
                     if (opc != 69){
                        switch (opc){
                           case 72:{
                              resol=2;
                              ban=0;
                              mconf();
                              break;
                           }
                           case 73:{
                              resol=1;
                              ban=0;
                              mconf();
                              break;
                           }
                           case 74:{
                              resol=0;
                              ban=0;
                              mconf();
                              break;
                           }
                           default:{
                              printf("\nNo valido   \n");
                              ban=0;
                              mconf();
                              break;
                           }
                        }
                     }
                  }
               break;
            }
            case 70:{
               printf("\f------------------------");
               printf("\r| Version 0.00000000001 |");
               printf("\r------------------------");
               printf("\r\r\r\r\rRegresar con m");               
               break;
            }
            case 71:{
               index();
               break;
            }
            default :{
               printf("\r\rCaracter invalido %d ",opc);
               delay_ms(1000);
               index();
               break;
            }
         }
      }
   }
}


