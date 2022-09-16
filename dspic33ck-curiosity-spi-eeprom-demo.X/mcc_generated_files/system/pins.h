/**
 * PINS Generated Driver Header File 
 * 
 * @file      pins.h
 *            
 * @defgroup  pinsdriver Pins Driver
 *            
 * @brief     The Pin Driver directs the operation and function of 
 *            the selected device pins using dsPIC MCUs.
 *            
 * @version   Driver Version 1.0.0
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

#ifndef PINS_H
#define PINS_H
// Section: Includes
#include <xc.h>

// Section: Device Pin Macros

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RE10 GPIO Pin which has a custom name of CS to High
 * @pre      The RE10 must be set as Output Pin             
 * @return   none  
 */
#define CS_SetHigh()          (_LATE10 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RE10 GPIO Pin which has a custom name of CS to Low
 * @pre      The RE10 must be set as Output Pin
 * @return   none  
 */
#define CS_SetLow()           (_LATE10 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RE10 GPIO Pin which has a custom name of CS
 * @pre      The RE10 must be set as Output Pin
 * @return   none  
 */
#define CS_Toggle()           (_LATE10 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RE10 GPIO Pin which has a custom name of CS
 * @return   none  
 */
#define CS_GetValue()         _RE10

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RE10 GPIO Pin which has a custom name of CS as Input
 * @return   none  
 */
#define CS_SetDigitalInput()  (_TRISE10 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RE10 GPIO Pin which has a custom name of CS as Output
 * @return   none  
 */
#define CS_SetDigitalOutput() (_TRISE10 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Initializes the PINS module
 * @return   none  
 */
void PINS_Initialize(void);



#endif
