/***********************************************************************/
/***********************************************************************/
/********************  Author: Ahmed Osama      *************************/
/********************  SWC: DIO                *************************/
/********************  LAYER: MCAL             *************************/
/********************  VERSION: 1.0            *************************/
/********************  DATE:27/1/2024         *************************/
/***********************************************************************/
/***********************************************************************/


#ifndef DIO_INTEFACE_H_
#define DIO_INTEFACE_H_
 
 /*
***** DIO Ports *****
DIO_PORTA
DIO_PORTB
DIO_PORTC
DIO_PORTD
*/
 
/*
***** DIO Port Direction *****
DIO_PORT_OUTPUT
DIO_PORT_INPUT
*/

/*
***** DIO Port Value *****
DIO_PORT_HIGH
DIO_PORT_LOW

*/
 
/*
***** DIO Pins *****
DIO_PIN0
DIO_PIN1
DIO_PIN2
DIO_PIN3
DIO_PIN4
DIO_PIN5
DIO_PIN6
DIO_PIN7
*/

/*
***** DIO Pin Direction *****
DIO_PIN_OUTPUT
DIO_PIN_INPUT
*/

/*
***** DIO Pin Value *****
DIO_PIN_HIGH
DIO_PIN_LOW
*/

/* DIO Ports */
#define DIO_PORTA 0
#define DIO_PORTB 1
#define DIO_PORTC 2
#define DIO_PORTD 3

/* DIO Pins */
#define DIO_PIN0   0
#define DIO_PIN1   1
#define DIO_PIN2   2
#define DIO_PIN3   3
#define DIO_PIN4   4
#define DIO_PIN5   5
#define DIO_PIN6   6
#define DIO_PIN7   7

/* DIO Pin Direction */
#define DIO_PIN_OUTPUT 1
#define DIO_PIN_INPUT  0

/* DIO Pin Value */
#define DIO_PIN_HIGH 1
#define DIO_PIN_LOW  0

/* DIO Port Direction */
#define DIO_PORT_OUTPUT 0XFF
#define DIO_PORT_INPUT  0X00

/* DIO Port Vlaue */
#define DIO_PORT_HIGH 0XFF
#define DIO_PORT_LOW  0X00


u8 DIO_u8SetPinDirection(u8 copy_u8Port, u8 copy_u8PinNumber, u8 copy_u8PinDirection);
u8 DIO_u8SetPortDirection(u8 copy_u8Port, u8 copy_u8PortDirection);

u8 DIO_u8SetPinValue(u8 copy_u8Port, u8 copy_u8PinNumber, u8 copy_u8PinValue);
u8 DIO_u8SetPortValue(u8 copy_u8Port, u8 copy_u8PortValue);

u8 DIO_u8TogglePinValue(u8 copy_u8Port, u8 copy_u8PinNumber);
u8 DIO_u8TogglePortValue(u8 copy_u8Port);

u8 DIO_u8GetPinValue(u8 copy_u8Port, u8 copy_u8PinNumber, u8 *copy_pu8ReturnPinValue);
u8 DIO_u8GetPortValue(u8 copy_u8Port, u8 *copy_pu8ReturnPortValue);


#endif