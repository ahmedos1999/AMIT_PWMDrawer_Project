/***********************************************************************/
/***********************************************************************/
/********************  Author: Ahmed Osama      *************************/
/********************  SWC: DIO                *************************/
/********************  LAYER: MCAL             *************************/
/********************  VERSION: 1.0            *************************/
/********************  DATE:27/1/2024         *************************/
/***********************************************************************/
/***********************************************************************/

/*LIB*/
#include "../../STD_TYPES/STD_TYPES.h"
#include "../../STD_TYPES/BIT_MATH.h"
#include "../../STD_TYPES/Error_State.h"

/*MCAL*/
#include "DIO_config.h"
#include "DIO_private.h"
#include "DIO_interface.h"
#include "DIO_register.h"


/*implementation*/
u8 DIO_u8SetPinDirection(u8 copy_u8Port, u8 copy_u8PinNumber, u8 copy_u8PinDirection)
{
	u8 Local_u8ErrorState = OK;

	if(copy_u8PinNumber >= DIO_PIN0 && copy_u8PinNumber<= DIO_PIN7 )
	{
		if(copy_u8PinDirection == DIO_PIN_OUTPUT)
		{
			switch(copy_u8Port)
			{
				case DIO_PORTA:  SET_BIT(DDRA, copy_u8PinNumber);  break;
				case DIO_PORTB:  SET_BIT(DDRB, copy_u8PinNumber);  break;
				case DIO_PORTC:  SET_BIT(DDRC, copy_u8PinNumber);  break;
				case DIO_PORTD:  SET_BIT(DDRD, copy_u8PinNumber);  break;
				default: Local_u8ErrorState = NOK ;
			}
			
		}
		else if(copy_u8PinDirection == DIO_PIN_INPUT)
		{
			switch(copy_u8Port)
			{
				case DIO_PORTA:  CLR_BIT(DDRA, copy_u8PinNumber);  break;
				case DIO_PORTB:  CLR_BIT(DDRB, copy_u8PinNumber);  break;
				case DIO_PORTC:  CLR_BIT(DDRC, copy_u8PinNumber);  break;
				case DIO_PORTD:  CLR_BIT(DDRD, copy_u8PinNumber);  break;
				default: Local_u8ErrorState = NOK ;
			}
		}
		
		else
		{
			Local_u8ErrorState = NOK;
			return Local_u8ErrorState;
		}
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	
	return Local_u8ErrorState;
}

u8 DIO_u8SetPortDirection(u8 copy_u8Port, u8 copy_u8PortDirection)
{
	u8 Local_u8ErrorState = OK;
	
	if(copy_u8PortDirection == DIO_PORT_OUTPUT)
	{
		switch(copy_u8Port)
		{
			case DIO_PORTA:  DDRA = DIO_PORT_OUTPUT;  break;
			case DIO_PORTB:  DDRB = DIO_PORT_OUTPUT;  break;
			case DIO_PORTC:  DDRC = DIO_PORT_OUTPUT;  break;
			case DIO_PORTD:  DDRD = DIO_PORT_OUTPUT;  break;
			default: Local_u8ErrorState = NOK;
		}
	}
	else if(copy_u8PortDirection == DIO_PORT_INPUT)
	{
		switch(copy_u8Port)
		{
			case DIO_PORTA:  DDRA = DIO_PORT_INPUT;  break;
			case DIO_PORTB:  DDRB = DIO_PORT_INPUT;  break;
			case DIO_PORTC:  DDRC = DIO_PORT_INPUT;  break;
			case DIO_PORTD:  DDRD = DIO_PORT_INPUT;  break;
			default: Local_u8ErrorState = NOK;
		}
	}
	else
	{
		Local_u8ErrorState = NOK;
		return Local_u8ErrorState;
	}
	
	return Local_u8ErrorState;
}

u8 DIO_u8SetPinValue(u8 copy_u8Port, u8 copy_u8PinNumber, u8 copy_u8PinValue)
{
	
	u8 Local_u8ErrorState = OK ;

	if(copy_u8PinNumber >= DIO_PIN0 && copy_u8PinNumber <= DIO_PIN7 )
	{
		if(copy_u8PinValue == DIO_PIN_HIGH)
		{
			switch(copy_u8Port)
			{
				case DIO_PORTA:  SET_BIT(PORTA, copy_u8PinNumber);  break;
				case DIO_PORTB:  SET_BIT(PORTB, copy_u8PinNumber);  break;
				case DIO_PORTC:  SET_BIT(PORTC, copy_u8PinNumber);  break;
				case DIO_PORTD:  SET_BIT(PORTD, copy_u8PinNumber);  break;
				default: Local_u8ErrorState = NOK ;
			}
			
		}
		else if(copy_u8PinValue == DIO_PIN_LOW)
		{
			switch(copy_u8Port)
			{
				case DIO_PORTA:  CLR_BIT(PORTA, copy_u8PinNumber);  break;
				case DIO_PORTB:  CLR_BIT(PORTB, copy_u8PinNumber);  break;
				case DIO_PORTC:  CLR_BIT(PORTC, copy_u8PinNumber);  break;
				case DIO_PORTD:  CLR_BIT(PORTD, copy_u8PinNumber);  break;
				default: Local_u8ErrorState = NOK ;
			}
		}
		
		else
		{
			Local_u8ErrorState = NOK;
			return Local_u8ErrorState;
		}
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	
	return Local_u8ErrorState;
}

u8 DIO_u8SetPortValue(u8 copy_u8Port, u8 copy_u8PortValue)
{
	u8 Local_u8ErrorState = OK;
	
	if(copy_u8PortValue == DIO_PORT_HIGH)
	{
		switch(copy_u8Port)
		{
			case DIO_PORTA:  PORTA = DIO_PORT_HIGH;  break;
			case DIO_PORTB:  PORTB = DIO_PORT_HIGH;  break;
			case DIO_PORTC:  PORTC = DIO_PORT_HIGH;  break;
			case DIO_PORTD:  PORTD = DIO_PORT_HIGH;  break;
			default: Local_u8ErrorState = NOK;
		}
	}
	else if(copy_u8PortValue == DIO_PORT_LOW)
	{
		switch(copy_u8Port)
		{
			case DIO_PORTA:  PORTA = DIO_PORT_LOW;  break;
			case DIO_PORTB:  PORTB = DIO_PORT_LOW;  break;
			case DIO_PORTC:  PORTC = DIO_PORT_LOW;  break;
			case DIO_PORTD:  PORTD = DIO_PORT_LOW;  break;
			default: Local_u8ErrorState = NOK;
		}
	}
	else
	{
		switch(copy_u8Port)
		{
			case DIO_PORTA:  PORTA = copy_u8PortValue;  break;
			case DIO_PORTB:  PORTB = copy_u8PortValue;  break;
			case DIO_PORTC:  PORTC = copy_u8PortValue;  break;
			case DIO_PORTD:  PORTD = copy_u8PortValue;  break;
			default: Local_u8ErrorState = NOK;
		}
	}
	
	return Local_u8ErrorState;
}

u8 DIO_u8TogglePinValue(u8 copy_u8Port, u8 copy_u8PinNumber)
{
	u8 Local_u8ErrorState = OK;
	
	if(copy_u8PinNumber >= DIO_PIN0 && copy_u8PinNumber <= DIO_PIN7 )
	{
		switch(copy_u8Port)
		{
			case DIO_PORTA:  TOG_BIT(PORTA, copy_u8PinNumber);  break;
			case DIO_PORTB:  TOG_BIT(PORTB, copy_u8PinNumber);  break;
			case DIO_PORTC:  TOG_BIT(PORTC, copy_u8PinNumber);  break;
			case DIO_PORTD:  TOG_BIT(PORTD, copy_u8PinNumber);  break;
			default: Local_u8ErrorState = NOK ;
		}
	}
	else
	{
		Local_u8ErrorState = NOK;
		return Local_u8ErrorState;
	}
	
	return Local_u8ErrorState;
}

u8 DIO_u8TogglePortValue(u8 copy_u8Port)
{
	u8 Local_u8ErrorState = OK;
	
	switch(copy_u8Port)
	{
		case DIO_PORTA:  TOG_REG(PORTA);  break;
		case DIO_PORTB:  TOG_REG(PORTB);  break;
		case DIO_PORTC:  TOG_REG(PORTC);  break;
		case DIO_PORTD:  TOG_REG(PORTD);  break;
		default: Local_u8ErrorState = NOK;
	}
	
	return Local_u8ErrorState;
}

u8 DIO_u8GetPinValue(u8 copy_u8Port, u8 copy_u8PinNumber, u8 *copy_pu8ReturnPinValue)
{
	
	u8 Local_u8ErrorState = OK ;

	if(copy_u8PinNumber >= DIO_PIN0 && copy_u8PinNumber<= DIO_PIN7 )
	{
		switch(copy_u8Port)
		{
			case DIO_PORTA:  *copy_pu8ReturnPinValue = GET_BIT(PINA, copy_u8PinNumber);  break;
			case DIO_PORTB:  *copy_pu8ReturnPinValue = GET_BIT(PINB, copy_u8PinNumber);  break;
			case DIO_PORTC:  *copy_pu8ReturnPinValue = GET_BIT(PINC, copy_u8PinNumber);  break;
			case DIO_PORTD:  *copy_pu8ReturnPinValue = GET_BIT(PIND, copy_u8PinNumber);  break;
			default: Local_u8ErrorState = NOK;
		}
	}
	else
	{
		Local_u8ErrorState = NOK;
	}

	return Local_u8ErrorState;
}

u8 DIO_u8GetPortValue(u8 copy_u8Port, u8 *copy_pu8ReturnPortValue)
{
	u8 Local_u8ErrorState = OK ;

		switch(copy_u8Port)
		{
			case DIO_PORTA:  *copy_pu8ReturnPortValue = PINA;  break;
			case DIO_PORTB:  *copy_pu8ReturnPortValue = PINB;  break;
			case DIO_PORTC:  *copy_pu8ReturnPortValue = PINC;  break;
			case DIO_PORTD:  *copy_pu8ReturnPortValue = PIND;  break;		
			default: Local_u8ErrorState = NOK;
		}

	return Local_u8ErrorState;	
}