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
#include "eeprom_25AA512.h"
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/uart/uart1.h"
#include <stdio.h>
#include <string.h>

/* User Configurable settings */
#define         EEPROM_DATA_START_ADDRESS       0x0000    // per page size 128 bytes
#define         EEPROM_DATA_BUFFER_SIZE         20
#define         EEPROM_DATA_BUFFER              "Microchip Technology"

/* SPI EEPROM state */
enum  SPI_EEPROM_STATE {
    SPI_EEPROM_OPEN,
    SPI_EEPROM_WRITE_READ,
    SPI_EEPROM_CLOSE,
    SPI_EEPROM_IDLE,
};

/*
    Main application
*/

int main(void)
{
    uint8_t txBuffer[EEPROM_DATA_BUFFER_SIZE] = EEPROM_DATA_BUFFER;
    uint8_t rxBuffer[EEPROM_DATA_BUFFER_SIZE] = {0};
    uint8_t state = SPI_EEPROM_OPEN; 
    
    SYSTEM_Initialize();
    printf("\r\n************************************************************\r\n");
    printf(" dsPIC33CK256MP508 Curiosity SPI EEPROM Demo\r\n");
    printf("************************************************************\r\n");
    while(1)
    {
        switch(state){
            case SPI_EEPROM_OPEN:
                SPI_Host->Open(EEPROM_25AA512);
                if(1U == SPI_Host->IsTxReady())  
                {
                    printf("\r\n SPI port open - ready to communicate with EEPROM \r\n");
                    EEPROM_ChipErase(); //User can erase entire chip before write 
                    state = SPI_EEPROM_WRITE_READ;
                }                               
                break;
                
            case SPI_EEPROM_WRITE_READ:  
                printf("\r\n Write string to EEPROM from txBuffer \r\n");
                EEPROM_PageWrite(EEPROM_DATA_START_ADDRESS, txBuffer, 20);  
                
                printf("\r\n Read string from EEPROM in rxBuffer \r\n");
                EEPROM_PageRead(EEPROM_DATA_START_ADDRESS, rxBuffer, 20);
                
                printf("\r\n Compare both txBuffer and rxBuffer to validate write/read     \r\n");
                if(strncmp((char *)txBuffer, (char *)rxBuffer, EEPROM_DATA_BUFFER_SIZE) == 0)
                {
                    printf("\r\n EEPROM write and read successful \r\n");
                }
                else
                {
                    printf("\r\n EEPROM write and read unsuccessful \r\n");                  
                }
                state = SPI_EEPROM_CLOSE;
                break;
                                
            case SPI_EEPROM_CLOSE:     
                printf("\r\n Close SPI port \r\n");
                SPI_Host->Close();              
                printf("************************************************************\r\n");
                state = SPI_EEPROM_IDLE;
                break;
                
            case SPI_EEPROM_IDLE:
                //Do nothing
                break;
                
            default:
                //Do nothing
                break;
        }
    }
    
}