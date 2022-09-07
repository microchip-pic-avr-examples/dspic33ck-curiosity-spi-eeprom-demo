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
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/system/pins.h"
#include "mcc_generated_files/spi_host/spi1.h"
#include "mcc_generated_files/system/clock.h"
#include "mcc_generated_files/uart/uart1.h"
#define FCY             CLOCK_SystemFrequencyGet()
#include <stdio.h>
#include <string.h>
#include <libpic30.h>

/*     EEPROM COMMANDS      */
#define         EEPROM_READ                 0b00000011
#define         EEPROM_WRITE                0b00000010
#define         EEPROM_WRITEENABLE          0b00000110
#define         EEPROM_WRITEDISABLE         0x04   //write disable
#define         EEPROM_READSTATUS           0x05   //read status
#define         EEPROM_WRITESTATUS          0x01   //write status register
#define         EEPROM_PAGEERASE            0x42   //page erase
#define         EEPROM_SECTORERASE          0xD8   //sector erase
#define         EEPROM_CHIPERASE            0xC7   //chip erase

#define         START_ADDRESS               0x0000    // per page size 128 bytes
#define         BUFFER_SIZE                 20
#define         BUFFER_DATA                 "Microchip Technology"

#define         EEPROM_BYTES_PER_PAGE       128
#define         EEPROM_BYTES_MAX            0xFFFE

/* EEPROM API's*/
void    EEPROM_writeEnable (void);
void    EEPROM_writeDisable (void);
uint8_t EEPROM_readStatusGet(void);
void    EEPROM_byteWrite (unsigned int address, uint8_t databyte);
void    EEPROM_pageWrite (unsigned int address, uint8_t *bufferdata);
uint8_t EEPROM_byteRead (unsigned int address);
void    EEPROM_pageRead(uint16_t address, uint8_t *bufferData);

enum {
    SPI_INIT,
    SPI_STR_WRITE_READ,
    SPI_NUM_WRITE_READ,
    SPI_STOP,
} SPI_STATUS;

/*API's Implementation */

void EEPROM_writeEnable(void)
{
    CS_SetLow();
    __delay_us(1);
    SPI1_Host.ByteExchange(EEPROM_WRITEENABLE);
    CS_SetHigh();
}

void EEPROM_writeDisable(void)
{
    CS_SetLow();
    __delay_us(1);
    SPI1_Host.ByteExchange(EEPROM_WRITEDISABLE);
    CS_SetHigh();
}

uint8_t EEPROM_readStatusGet(void)
{
    uint8_t Status = 0;
    CS_SetLow();
    SPI1_Host.ByteExchange(EEPROM_READSTATUS);
    Status = SPI1_Host.ByteExchange(0);
    CS_SetHigh();
    return (Status); // return the result
}

void EEPROM_byteWrite(unsigned int address, uint8_t databyte)
{
    EEPROM_writeEnable();
    CS_SetLow();
    SPI1_Host.ByteExchange(EEPROM_WRITE);
    SPI1_Host.ByteExchange((address >> 8) & 0xFF); 
    SPI1_Host.ByteExchange(address & 0xFF);   //due to 16 bit address
    SPI1_Host.ByteExchange(databyte);
    CS_SetHigh();
    __delay_us(100);
    while(EEPROM_readStatusGet());
}

void EEPROM_pageWrite(unsigned int address, uint8_t *bufferData)
{
    uint8_t i=0;
    EEPROM_writeEnable();
    CS_SetLow();
    SPI1_Host.ByteExchange(EEPROM_WRITE);
    SPI1_Host.ByteExchange((address >> 8) & 0xFF); 
    SPI1_Host.ByteExchange(address & 0xFF); 
    for (i=0; i<BUFFER_SIZE; i++)
    {
        SPI1_Host.ByteExchange(bufferData[i]);
    }
    CS_SetHigh();
    __delay_us(100);
    while(EEPROM_readStatusGet());
}

uint8_t EEPROM_byteRead (unsigned int address)
{
    CS_SetLow();
    __delay_us(1);
    SPI1_Host.ByteExchange(EEPROM_READ);
    SPI1_Host.ByteExchange((address >> 8) & 0xFF); 
    SPI1_Host.ByteExchange(address & 0xFF);   //due to 24 bit address
    uint8_t byteData = SPI1_Host.ByteExchange(0);
    CS_SetHigh();
    __delay_us(100);
    return byteData;
}

void EEPROM_pageRead(uint16_t address, uint8_t *bufferData)
{
    uint8_t i=0;
    CS_SetLow();
    __delay_us(1);
    SPI1_Host.ByteExchange(EEPROM_READ);
    SPI1_Host.ByteExchange((address >> 8) & 0xFF); 
    SPI1_Host.ByteExchange(address & 0xFF);
    for(i=0; i<BUFFER_SIZE; i++)
    {
        bufferData[i] = SPI1_Host.ByteExchange(0);
    }
    CS_SetHigh();
    __delay_us(100);
}

/*
    Main application
*/

int main(void)
{
    uint8_t state = SPI_INIT, counter = 0, readData = 0;
    uint8_t txBuffer[BUFFER_SIZE] = BUFFER_DATA;
    uint8_t rxBuffer[BUFFER_SIZE] = {0};
    bool readStatus = true;
    
    SYSTEM_Initialize();
    printf("SPI interface with EEPROM demo  \r\n");
    while(1)
    {
        switch(state){
            case SPI_INIT:
                printf("EEPROM initialization .................... \r\n");
                printf("SPI - Opening the port                     \r\n");
                // print all connection information
                SPI1_Open(HOST_CONFIG);
                while(!SPI1_Host.IsTxReady());
                printf("SPI port open - ready to communicate with EEPROM \r\n");
                __delay_ms(1000);
                state = SPI_STR_WRITE_READ;
                break;
                
            case SPI_STR_WRITE_READ: 
                printf(" Write string to EEPROM from txBuffer, then read same string from EEPROM in rxBuffer \r\n");
                printf(" Compare both txBuffer and rxBuffer to validate read/write     \r\n");
                EEPROM_pageWrite(START_ADDRESS, txBuffer);
                __delay_ms(1000);
                
                EEPROM_pageRead(START_ADDRESS, rxBuffer);
                __delay_ms(1000);
                if(strncmp((uint8_t *)txBuffer, (uint8_t *)rxBuffer, BUFFER_SIZE) == 0)
                {
                    printf("EEPROM String write and read successful \r\n");
                    state = SPI_NUM_WRITE_READ;
                }
                else
                {
                    printf("EEPROM String write and read Unsuccessful \r\n");
                    state = SPI_STOP;
                }
                break;
                
            case SPI_NUM_WRITE_READ:
                printf(" Write to memory number from 0 to 127 in second  page \r\n");
                printf(" Read memory from 0 to 127 memory location - compare with number 0 to 127 \r\n");
                for ( counter = START_ADDRESS ; counter < EEPROM_BYTES_PER_PAGE ; counter++ )
                {
                    EEPROM_byteWrite(counter, counter);
                }
                __delay_ms(1000);
                
                for ( counter = START_ADDRESS; counter < EEPROM_BYTES_PER_PAGE; counter++ )
                {
                    readData = EEPROM_byteRead(counter);
                    //printf("Read_data : %d \r\n", readData);
                    if(readData != counter) 
                    {
                        readStatus = false;
                    }
                }
                if (readStatus == true)
                {
                    printf("EEPROM Number write read Successful \r\n");
                }
                else
                {
                    printf("EEPROM Number write read Unsuccessful \r\n");
                }
                __delay_ms(1000);
                printf("Close SPI Port \r\n");
                state = SPI_STOP;
                break;
                
            case SPI_STOP:               
                __delay_ms(1000);
                SPI1_Close();
                break;
                
            default:
                //Do nothing
                break;
        }
        
    }    
}