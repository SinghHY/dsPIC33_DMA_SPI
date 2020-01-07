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
#use delay(crystal = 40Mhz)
//#use spi(SLAVE, SPI2, BITS = 16, MODE = 0, ENABLE = PIN_G9, stream = SPI_2)

        
#define GREEN_LED  PIN_A6
#define RED_LED  PIN_A7

int8 i, Error;
   
#bank_dma 
    unsigned int16  TxBuffer[4];
#bank_dma 
    unsigned int16  RxBuffer[4]; 
#INT_DMA0
void dma0_isr(void)
{
   dma_start(0, DMA_ONE_SHOT ,&RxBuffer[0],4);
   dma_start(2, DMA_ONE_SHOT ,&TxBuffer[0],4);
   clear_interrupt(INT_DMA0);
   clear_interrupt(INT_DMA2);
}

void main()
{    
    
   
   //output_float(PIN_G9); // SS as an input
    setup_spi2(SPI_SLAVE | SPI_SCK_IDLE_LOW | SPI_XMIT_L_TO_H | SPI_MODE_16B | SPI_SAMPLE_AT_END | SPI_SS_ENABLED);

  
       TxBuffer[0] = 1;
       TxBuffer[1] = 3;
       TxBuffer[2] = 2;
       TxBuffer[3] = 1;

   enable_interrupts(INT_DMA0);

   setup_dma(2, DMA_OUT_SPI2, DMA_WORD);  
   setup_dma(0, DMA_IN_SPI2, DMA_WORD);

 
   dma_start(0, DMA_ONE_SHOT ,&RxBuffer[0],4);  
   dma_start(2, DMA_ONE_SHOT ,&TxBuffer[0],4);
   enable_interrupts(INT_DMA0);
  
   while(1)
   {

             
            for (i=0; i<=3; i++)
                TxBuffer[i] = RxBuffer[i];

 
   }
  
}   
