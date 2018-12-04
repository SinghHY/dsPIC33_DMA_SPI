/**********************************************************************
* Filament Control.
* © Harpreet Singh, 2017
* FileName:        main.c
* Dependencies:    Header (.h) files if applicable, see below* 
* Processor:dsPIC33FJ256GP710A
* Compiler:        MPLAB® CCS v5.074
************************************************************************/
#include <33FJ256GP710A.h>
#fuses XT,NOWDT,NOPROTECT
#device ADC = 12 
#use delay(crystal = 8Mhz)




void main()
{    
   output_float(PIN_G9); // SS as an input
   setup_adc_ports(sAN0 | sAN2 | sAN3| sAN4, VSS_VDD);
   setup_adc(ADC_CLOCK_INTERNAL);


  
}   