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
#use delay(clock = 100Mhz, crystal = 8Mhz)
#use spi(SLAVE, SPI2, BITS = 16, MODE = 0, ENABLE = PIN_G9, stream = SPI_2)

#define GREEN_LED  PIN_A6
#define RED_LED  PIN_A7

int8 i, Error;
   
#bank_dma 
    unsigned int16  TxBuffer[2];
#bank_dma 
    unsigned int16  RxBuffer[2]; 

void main()
{    
    
   
   //output_float(PIN_G9); // SS as an input


   for(i = 0; i <= 3; i++)
       TxBuffer[i] = i * 10;
   
   setup_dma(2, DMA_OUT_SPI2, DMA_WORD);  
   setup_dma(0, DMA_IN_SPI2, DMA_WORD);

   spi_prewrite(TxBuffer[0]);
   dma_start(0, DMA_CONTINOUS ,&RxBuffer[0],1);  
   dma_start(2, DMA_CONTINOUS ,&TxBuffer[0],1);
   
   while(1)
   {
       output_high(GREEN_LED);
       delay_ms(500);
       output_low(GREEN_LED);
       delay_ms(500);
       
       for(i = 0; i <= 1; i++)
            TxBuffer[i] = RxBuffer[i];
       
   }
  
}   
