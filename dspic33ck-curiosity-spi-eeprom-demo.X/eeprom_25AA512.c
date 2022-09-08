/*
 * File:   eeprom_25AA512.c
 * Author: I69791
 *
 * Created on September 8, 2022, 4:17 PM
 */


#include "eeprom_25AA512.h"

/*API's Implementation */

const struct SPI_HOST_INTERFACE *SPI_Host = &SPI1_Host;

void EEPROM_WriteEnable(void)
{
    CS_SetLow();
    __delay_us(1);
    SPI_Host->ByteExchange(EEPROM_CMD_WRITEENABLE);
    CS_SetHigh();
}

void EEPROM_WriteDisable(void)
{
    CS_SetLow();
    __delay_us(1);
    SPI_Host->ByteExchange(EEPROM_CMD_WRITEDISABLE);
    CS_SetHigh();
}

void EEPROM_ChipErase(void)
{
    CS_SetLow();
    __delay_us(1);
    SPI_Host->ByteExchange(EEPROM_CMD_CHIPERASE);
    CS_SetHigh();
}

uint8_t EEPROM_IsWriteInProgress(void)
{
    uint8_t Status = 0;
    CS_SetLow();
    SPI_Host->ByteExchange(EEPROM_CMD_READSTATUS);
    Status = SPI_Host->ByteExchange(0);
    CS_SetHigh();
    return (Status); // return the result
}

void EEPROM_ByteWrite(uint16_t address, uint8_t databyte)
{
    EEPROM_WriteEnable();
    CS_SetLow();
    SPI_Host->ByteExchange(EEPROM_CMD_WRITE);
    SPI_Host->ByteExchange((address >> 8) & 0xFF); 
    SPI_Host->ByteExchange(address & 0xFF);   //due to 16 bit address
    SPI_Host->ByteExchange(databyte);
    CS_SetHigh();
    __delay_us(100);
    while(EEPROM_IsWriteInProgress());
}

void EEPROM_PageWrite(uint16_t address, uint8_t *bufferData, uint8_t bufferSize)
{
    uint8_t addrIndex = 0;
    EEPROM_WriteEnable();
    CS_SetLow();
    SPI_Host->ByteExchange(EEPROM_CMD_WRITE);
    SPI_Host->ByteExchange((address >> 8) & 0xFF); 
    SPI_Host->ByteExchange(address & 0xFF); 
    for (addrIndex=0; addrIndex<bufferSize; addrIndex++)
    {
        SPI_Host->ByteExchange(bufferData[addrIndex]);
    }
    CS_SetHigh();
    __delay_us(100);
    while(EEPROM_IsWriteInProgress());
}

uint8_t EEPROM_ByteRead (uint16_t address)
{
    CS_SetLow();
    __delay_us(1);
    SPI_Host->ByteExchange(EEPROM_CMD_READ);
    SPI_Host->ByteExchange((address >> 8) & 0xFF); 
    SPI_Host->ByteExchange(address & 0xFF);   //due to 24 bit address
    uint8_t byteData = SPI_Host->ByteExchange(0);
    CS_SetHigh();
    __delay_us(100);
    return byteData;
}

void EEPROM_PageRead(uint16_t address, uint8_t *bufferData, uint8_t bufferSize)
{
    uint8_t addrIndex = 0;
    CS_SetLow();
    __delay_us(1);
    SPI_Host->ByteExchange(EEPROM_CMD_READ);
    SPI_Host->ByteExchange((address >> 8) & 0xFF); 
    SPI_Host->ByteExchange(address & 0xFF);
    for(addrIndex=0; addrIndex<bufferSize; addrIndex++)
    {
        bufferData[addrIndex] = SPI_Host->ByteExchange(0);
    }
    CS_SetHigh();
    __delay_us(100);
}

