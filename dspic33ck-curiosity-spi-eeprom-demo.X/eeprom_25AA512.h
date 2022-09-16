/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "mcc_generated_files/spi_host/spi_host_interface.h"
#include "mcc_generated_files/spi_host/spi1.h"
#include "mcc_generated_files/system/pins.h"
#include "mcc_generated_files/system/clock.h"

#define  FCY             CLOCK_SystemFrequencyGet()
#include <libpic30.h>

/*     EEPROM COMMANDS      */
#define         EEPROM_CMD_READ                 0x03
#define         EEPROM_CMD_WRITE                0x02
#define         EEPROM_CMD_WRITEENABLE          0x06
#define         EEPROM_CMD_WRITEDISABLE         0x04   //write disable
#define         EEPROM_CMD_READSTATUS           0x05   //read status
#define         EEPROM_CMD_WRITESTATUS          0x01   //write status register
#define         EEPROM_CMD_PAGEERASE            0x42   //page erase
#define         EEPROM_CMD_SECTORERASE          0xD8   //sector erase
#define         EEPROM_CMD_CHIPERASE            0xC7   //chip erase

#define         EEPROM_MAX_BYTES_PER_PAGE       128
#define         EEPROM_MAX_BYTE_SIZE            0xFFFE
    
extern const struct SPI_HOST_INTERFACE *SPI_Host;
    /* EEPROM API's*/
void    EEPROM_WriteEnable (void);
void    EEPROM_WriteDisable (void);
void    EEPROM_ChipErase (void);
uint8_t EEPROM_IsWriteInProgress (void);
void    EEPROM_ByteWrite (unsigned int address, uint8_t databyte);
void    EEPROM_PageWrite (unsigned int address, uint8_t *bufferdata, uint8_t bufferSize);
uint8_t EEPROM_ByteRead (unsigned int address);
void    EEPROM_PageRead (uint16_t address, uint8_t *bufferData, uint8_t bufferSize);

#endif	/* XC_HEADER_TEMPLATE_H */

