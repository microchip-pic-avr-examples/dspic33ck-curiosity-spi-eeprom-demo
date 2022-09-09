/*
� [2022] Microchip Technology Inc. and its subsidiaries.

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
#include "eeprom_25AA512.h"
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/uart/uart1.h"
#include <stdio.h>
#include <string.h>

/* User Configurable settings */
#define         EEPROM_DATA_START_ADDRESS       0x0000    // per page size 128 bytes
#define         EEPROM_DATA_BUFFER_SIZE         20
#define         EEPROM_DATA_BUFFER              "Microchip Technology"

/* execution sequence */
enum {
    INIT,
    STR_WRITE_READ,
    NUM_WRITE_READ,
    STOP,
} SPI_STATUS;

/*
    Main application
*/

int main(void)
{
    uint8_t txBuffer[EEPROM_DATA_BUFFER_SIZE] = EEPROM_DATA_BUFFER;
    uint8_t rxBuffer[EEPROM_DATA_BUFFER_SIZE] = {0};
    uint8_t state = INIT; 
    uint8_t counter = 0; 
    uint8_t readData = 0;
    bool readStatus = true;
    bool isExit = false;
    
    SYSTEM_Initialize();
    printf("\r\n");
    printf("****************************************************************************\r\n");
    printf("dsPIC33CK256MP508 Curiosity SPI EEPROM Demo\r\n");
    printf("****************************************************************************\r\n");
    printf("\r\n");
    while(!isExit)
    {
        switch(state){
            case INIT:
                printf("SPI - Opening the port \r\n");
                SPI_Host->Open(EEPROM_25AA512);
                while(!SPI_Host->IsTxReady());
                printf("SPI port open - ready to communicate with EEPROM \r\n");
                EEPROM_ChipErase(); //User can erase entire chip before write
                state = STR_WRITE_READ;
                break;
                
            case STR_WRITE_READ: 
                printf("\r\n");
                printf("Write string to EEPROM from txBuffer, then read same string from EEPROM in rxBuffer \r\n");
                printf("Compare both txBuffer and rxBuffer to validate read/write     \r\n");
                printf("\r\n");
                EEPROM_PageWrite(EEPROM_DATA_START_ADDRESS, txBuffer, 20);               
                EEPROM_PageRead(EEPROM_DATA_START_ADDRESS, rxBuffer, 20);
                if(strncmp((char *)txBuffer, (char *)rxBuffer, EEPROM_DATA_BUFFER_SIZE) == 0)
                {
                    printf("EEPROM String write and read Successful \r\n");
                    state = NUM_WRITE_READ;
                }
                else
                {
                    printf("EEPROM String write and read Unsuccessful \r\n");
                    state = NUM_WRITE_READ;
                }
                break;
                
            case NUM_WRITE_READ:
                printf("\r\n");
                printf("Write to memory number from 0 to 127 to EEPROM \r\n");
                printf("Read memory from 0 to 127 from EEPROM - compare to validate read/write \r\n");
                printf("\r\n");
                for ( counter = EEPROM_DATA_START_ADDRESS ; counter < EEPROM_MAX_BYTES_PER_PAGE ; counter++ )
                {
                    EEPROM_ByteWrite(counter, counter);
                }
                
                for ( counter = EEPROM_DATA_START_ADDRESS; counter < EEPROM_MAX_BYTES_PER_PAGE; counter++ )
                {
                    readData = EEPROM_ByteRead(counter);
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
                printf("Close SPI Port \r\n");
                printf("****************************************************************************\r\n");
                state = STOP;
                break;
                
            case STOP:               
                SPI_Host->Close();
                isExit = true;
                break;
                
            default:
                //Do nothing
                break;
        }
    }
    
    while(1)
    {
        
    }
}