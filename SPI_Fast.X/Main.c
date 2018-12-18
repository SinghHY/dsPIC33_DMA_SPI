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
#use spi(SLAVE, SPI2, BITS = 8, MODE = 1, ENABLE = PIN_G9, stream = SPI_2)



void main()
{    
   output_float(PIN_G9); // SS as an input
   setup_adc_ports(sAN0 | sAN2 | sAN3| sAN4, VSS_VDD);
   setup_adc(ADC_CLOCK_INTERNAL);
   
   #BANK_DMA 
   unsigned char SPI2Buff[32]; 
   unsigned char SPI2OBuff[32];

   setup_dma(6,DMA_OUT_SPI2,DMA_BYTE); 
   dma_start(6, DMA_CONTINOUS ,&SPI2OBuff[0],32);
   
   setup_dma(7, DMA_IN_SPI2, DMA_BYTE);      //use DMA channel 7 for SPI2 DATA IN (dummy) 
   dma_start(7, DMA_CONTINOUS ,&SPI2Buff[0],32);   //setup dummy receive to avoid SPI2 overrun 


  
}   