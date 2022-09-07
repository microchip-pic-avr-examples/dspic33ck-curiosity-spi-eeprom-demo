/**
 * DMA Generated Driver Source File
 * 
 * @file      dma.c
 * 
 * @ingroup   dmadriver
 * 
 * @brief     This is the generated driver source file for DMA driver
 *
 * @version   Driver Version 1.1.0
 *
 * @skipline  Device : dsPIC33CK256MP508
*/

/*
© [2022] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

// Section: Included Files
#include <xc.h>
#include "../dma.h"

// Section: Driver Interface Function Definitions

void DMA_Initialize (void)
{ 
    // DMAEN disabled; PRSSEL Fixed priority; 
    DMACON = (0x0 | 0x01) & 0x7FFF; //The module is disabled, till other settings are configured.
    // LADDR 0; 
    DMAL= 0x0;
    // HADDR 0; 
    DMAH= 0x0;

    // CHEN0 disabled; DAMODE0 Unchanged; TRMODE0 One-Shot; CHREQ0 disabled; RELOAD0 disabled; SIZE0 16 bit; NULLW0 disabled; SAMODE0 Unchanged; 
    DMACH0 = 0x0 & 0xFFFE; //The channel is disabled, till other settings are configured.
    // HALFIF disabled; LOWIF disabled; HALFEN disabled; DONEIF disabled; OVRUNIF disabled; CHSEL0 ; HIGHIF disabled; 
    DMAINT0= 0x0;
    // SADDR0 0; 
    DMASRC0= 0x0;
    // DADDR0 0; 
    DMADST0= 0x0;
    // CNT0 0; 
    DMACNT0= 0x0;
    // Clearing Channel 0 Interrupt Flag;
    IFS0bits.DMA0IF = 0;

    // CHEN1 disabled; SAMODE1 Unchanged; SIZE1 16 bit; DAMODE1 Unchanged; CHREQ1 disabled; RELOAD1 disabled; TRMODE1 One-Shot; NULLW1 disabled; 
    DMACH1 = 0x0 & 0xFFFE; //The channel is disabled, till other settings are configured.
    // HALFIF disabled; LOWIF disabled; HALFEN disabled; DONEIF disabled; OVRUNIF disabled; HIGHIF disabled; CHSEL1 ; 
    DMAINT1= 0x0;
    // SADDR1 0; 
    DMASRC1= 0x0;
    // DADDR1 0; 
    DMADST1= 0x0;
    // CNT1 0; 
    DMACNT1= 0x0;
    // Clearing Channel 1 Interrupt Flag;
    IFS0bits.DMA1IF = 0;

    // SAMODE2 Unchanged; CHEN2 disabled; SIZE2 16 bit; DAMODE2 Unchanged; CHREQ2 disabled; RELOAD2 disabled; NULLW2 disabled; TRMODE2 One-Shot; 
    DMACH2 = 0x0 & 0xFFFE; //The channel is disabled, till other settings are configured.
    // HALFIF disabled; LOWIF disabled; HALFEN disabled; DONEIF disabled; OVRUNIF disabled; HIGHIF disabled; CHSEL2 ; 
    DMAINT2= 0x0;
    // SADDR2 0; 
    DMASRC2= 0x0;
    // DADDR2 0; 
    DMADST2= 0x0;
    // CNT2 0; 
    DMACNT2= 0x0;
    // Clearing Channel 2 Interrupt Flag;
    IFS1bits.DMA2IF = 0;

    // SAMODE3 Unchanged; CHEN3 disabled; SIZE3 16 bit; DAMODE3 Unchanged; TRMODE3 One-Shot; NULLW3 disabled; CHREQ3 disabled; RELOAD3 disabled; 
    DMACH3 = 0x0 & 0xFFFE; //The channel is disabled, till other settings are configured.
    // HALFIF disabled; LOWIF disabled; HALFEN disabled; DONEIF disabled; OVRUNIF disabled; CHSEL3 ; HIGHIF disabled; 
    DMAINT3= 0x0;
    // SADDR3 0; 
    DMASRC3= 0x0;
    // DADDR3 0; 
    DMADST3= 0x0;
    // CNT3 0; 
    DMACNT3= 0x0;
    // Clearing Channel 3 Interrupt Flag;
    IFS1bits.DMA3IF = 0;
    
    //Enable DMA
    DMACONbits.DMAEN = 1; 
    
}


