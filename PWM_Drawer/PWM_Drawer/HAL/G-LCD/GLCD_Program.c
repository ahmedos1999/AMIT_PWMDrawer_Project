/***********************************************************************/
/***********************************************************************/
/********************  Author: Ahmed Osama     *************************/
/********************  SWC: GLCD               *************************/
/********************  LAYER: HAL              *************************/
/********************  VERSION: 1.0            *************************/
/********************  DATE:14/05/2024         *************************/
/***********************************************************************/
/***********************************************************************/

/* Standard Types */
#include "../../STD_TYPES/STD_TYPES.h"
#include "../../STD_TYPES/BIT_MATH.h"
#include "../../STD_TYPES/Error_State.h"

/* MCAL */
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/Timers/TIMERS_interface.h"

/* GLCD.h */
#include "GLCD_Config.h"
#include "GLCD_Interface.h"
#include "GLCD_Private.h"


u8 global_u8CurrXAddress = 0;
u8 global_u8CurrYAddress = 0;
u8 global_u8CurrPage = 0;

/***********  Private Functions ***********/
static void static_GLCD_VoidSendEnablePulse(void)
{
	DIO_u8SetPinValue(GLCD_CTRL_PORT, GLCD_CTRL_E, DIO_PIN_HIGH);
	#if GLCD_TIMER_USED_FOR_DELAY == GLCD_TIMER0_DLEAY_MS
		TIMER0_VoidDelayms(1);
	#elif GLCD_TIMER_USED_FOR_DELAY == GLCD_TIMER2_DLEAY_MS
		TIMER2_VoidDelayms(1);
	#endif
	
	DIO_u8SetPinValue(GLCD_CTRL_PORT, GLCD_CTRL_E, DIO_PIN_LOW);
}

/***********  Initialization Function ***********/
void GLCD_VoidInit(void)
{
	/* Initializing Control and Data Ports */
	/* Control Pins */
	DIO_u8SetPinDirection(GLCD_CTRL_PORT, GLCD_CTRL_RESET,	DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(GLCD_CTRL_PORT, GLCD_CTRL_E,		DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(GLCD_CTRL_PORT, GLCD_CTRL_RS,		DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(GLCD_CTRL_PORT, GLCD_CTRL_RW,		DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(GLCD_CTRL_PORT, GLCD_CTRL_CS_1,	DIO_PIN_OUTPUT);
	DIO_u8SetPinDirection(GLCD_CTRL_PORT, GLCD_CTRL_CS_2,	DIO_PIN_OUTPUT);
	
	/* Data Pins */
	DIO_u8SetPortDirection(GLCD_DATA_PORT, DIO_PORT_OUTPUT);
	
	/* Keep Reset Pin High (Inactive) */
	DIO_u8SetPinValue(GLCD_CTRL_PORT, GLCD_CTRL_RESET,	DIO_PIN_HIGH);
	
	/* Initialization */
	GLCD_u8SelectPage(GLCD_BOTH_PAGES);
	GLCD_u8SendCommand(GLCD_DISPLAY_OFF);
	GLCD_u8SendCommand(GLCD_SET_X_ADDRESS_PREFIX + 0);		/* Line = 0 */
	GLCD_u8SendCommand(GLCD_SET_Y_ADDRESS_PREFIX + 0);		/* Column = 0 */
	GLCD_u8SendCommand(GLCD_SET_Z_ADDRESS_PREFIX + 0);		/* Start Line = 0 */
	GLCD_u8SendCommand(GLCD_DISPLAY_ON);
	GLCD_u8SelectPage(GLCD_PAGE_0);
	
}


/***********  Control Functions ***********/
void GLCD_u8SendCommand(u8 copy_u8Command)
{
	/* Register Select (RS) */
	/*
	GLCD_IR = Instruction Register (Command)
	GLCD_DR = Data Register (Data)
	*/
	DIO_u8SetPinValue(GLCD_CTRL_PORT, GLCD_CTRL_RS, GLCD_IR);	/* Instruction Register */

	/* Read / Write Operation (R/W) */
	/*
	GLCD_WRITE_MODE = Write Operation (Data / Instruction)
	GLCD_READ_MODE = Read Operation (Data / Busy Flag & Address Counter)
	*/
	DIO_u8SetPinValue(GLCD_CTRL_PORT, GLCD_CTRL_RW, GLCD_WRITE_MODE);	/* Write Operation */

	/* Send Instruction */
	DIO_u8SetPortValue(GLCD_DATA_PORT, copy_u8Command);
	static_GLCD_VoidSendEnablePulse();
}

u8 GLCD_u8SelectPage(u8 copy_u8PageNum)
{
	u8 local_u8ErrorState = OK;
	
	switch (copy_u8PageNum)
	{
		case GLCD_NO_PAGE_SELECTED:
			DIO_u8SetPinValue(GLCD_CTRL_PORT, GLCD_CTRL_CS_1, DIO_PIN_LOW); 
			DIO_u8SetPinValue(GLCD_CTRL_PORT, GLCD_CTRL_CS_2, DIO_PIN_LOW);
			break;
		case GLCD_PAGE_0:
			DIO_u8SetPinValue(GLCD_CTRL_PORT, GLCD_CTRL_CS_1, DIO_PIN_HIGH);
			DIO_u8SetPinValue(GLCD_CTRL_PORT, GLCD_CTRL_CS_2, DIO_PIN_LOW);
			break;						
		case GLCD_PAGE_1:
			DIO_u8SetPinValue(GLCD_CTRL_PORT, GLCD_CTRL_CS_1, DIO_PIN_LOW);
			DIO_u8SetPinValue(GLCD_CTRL_PORT, GLCD_CTRL_CS_2, DIO_PIN_HIGH);
			break;						
		case GLCD_BOTH_PAGES:
			DIO_u8SetPinValue(GLCD_CTRL_PORT, GLCD_CTRL_CS_1, DIO_PIN_HIGH);
			DIO_u8SetPinValue(GLCD_CTRL_PORT, GLCD_CTRL_CS_2, DIO_PIN_HIGH);
			break;
		default: local_u8ErrorState = NOK;
	}
	return(local_u8ErrorState);
}

void GLCD_VoidSendData(u8 copy_u8Data)
{
/* Register Select (RS) */
	/*
	GLCD_IR = Instruction Register (Command)
	GLCD_DR = Data Register (Data)
	*/
	DIO_u8SetPinValue(GLCD_CTRL_PORT, GLCD_CTRL_RS, GLCD_DR);	/* Data Register */

	/* Read / Write Operation (R/W) */
	/*
	GLCD_WRITE_MODE = Write Operation (Data / Instruction)
	GLCD_READ_MODE = Read Operation (Data / Busy Flag & Address Counter)
	*/
	DIO_u8SetPinValue(GLCD_CTRL_PORT, GLCD_CTRL_RW, GLCD_WRITE_MODE);		/* Write Operation */

	/* Send Instruction */
	DIO_u8SetPortValue(GLCD_DATA_PORT, copy_u8Data);
	static_GLCD_VoidSendEnablePulse();
}



void GLCD_VoidReset(void)
{
	DIO_u8SetPinValue(GLCD_CTRL_PORT, GLCD_CTRL_RESET, DIO_PIN_LOW);
	TIMER0_VoidDelayms(2);
	DIO_u8SetPinValue(GLCD_CTRL_PORT, GLCD_CTRL_RESET, DIO_PIN_HIGH);
}

void GLCD_VoidGoToPos(u8 copy_u8XPos, u8 copy_u8YPos)
{
	if (copy_u8XPos < GLCD_MAX_LINES)
	{
		GLCD_u8SelectPage(GLCD_PAGE_0);
		global_u8CurrXAddress = copy_u8XPos;
		GLCD_u8SendCommand(GLCD_SET_X_ADDRESS_PREFIX + global_u8CurrXAddress);
		global_u8CurrYAddress = copy_u8YPos;
		GLCD_u8SendCommand(GLCD_SET_Y_ADDRESS_PREFIX + global_u8CurrYAddress);
	}
}

void GLCD_VoidClearDisplay(void)
{
	for (u8 Line = 0; Line < GLCD_MAX_LINES; Line++)
	{
		GLCD_VoidGoToPos(Line, 0);
		GLCD_u8SelectPage(GLCD_BOTH_PAGES);
		for (u8 i = 0; i < GLCD_MAX_PAGE_PIXEL_WIDTH; i++)
		{
			GLCD_u8SendCommand(GLCD_SET_Y_ADDRESS_PREFIX + i);
			GLCD_VoidSendData(0);
		}
	}
	GLCD_VoidReset();
	GLCD_u8SelectPage(GLCD_PAGE_0);
	global_u8CurrPage = 0;
	GLCD_VoidGoToPos(0, 0);
}


/***********  Display Functions ***********/
void GLCD_VoidDisplayFloatingPoint(f32 copy_f32FloatingNumber)
{
	/* Will display only 3 Decimal Places */
	u16 local_u16IntegerPart = (u16)copy_f32FloatingNumber;
	u8 local_u8Counter = 0;
	
	GLCD_VoidWriteNumber(local_u16IntegerPart);			/* Displaying Integer Part of the Number */
	GLCD_VoidPrintCharacter('.');
	f32 local_f32DecimalPart = (copy_f32FloatingNumber - local_u16IntegerPart);
	u8 local_u8Digit = 0;
	
	for (local_u8Counter = 0; local_u8Counter < 3; local_u8Counter++)		/* Displaying 3 Decimals of the Number */
	{
		local_u8Digit = (u8)(local_f32DecimalPart * 10.0);
		GLCD_VoidPrintCharacter((char)(48 + local_u8Digit));
		local_f32DecimalPart = ((local_f32DecimalPart * 10.0) - local_u8Digit);
	}
}

void GLCD_VoidDisplaySpecialPattern(u64 Pattern)
{
	for(u8 i = 0; i < 5; i++) {
		GLCD_u8SendCommand(GLCD_SET_X_ADDRESS_PREFIX + global_u8CurrXAddress);
		GLCD_u8SendCommand(GLCD_SET_Y_ADDRESS_PREFIX + global_u8CurrYAddress);
		GLCD_VoidSendData((Pattern >> (i * 8)) & 0x00000000FFUL);
		global_u8CurrYAddress++;
		if ((global_u8CurrYAddress >= GLCD_MAX_PAGE_PIXEL_WIDTH) && (global_u8CurrPage == 0))
		{
			GLCD_u8SelectPage(GLCD_PAGE_1);
			global_u8CurrYAddress = 0;
		}
	}
}

void GLCD_VoidPrintCharacter(u8 copy_u8Data)
{
	if ((global_u8CurrPage == 0) | (global_u8CurrYAddress < (GLCD_MAX_PAGE_PIXEL_WIDTH - 7U)))
	{
		/* Enough space to write character */
		switch (copy_u8Data)
		{
			case 'A': case 'a': GLCD_VoidDisplaySpecialPattern(GLCD_CHAR_A); break;
			case 'F': case 'f': GLCD_VoidDisplaySpecialPattern(GLCD_CHAR_F); break;
			case 'R': case 'r': GLCD_VoidDisplaySpecialPattern(GLCD_CHAR_R); break;
			case 'E': case 'e': GLCD_VoidDisplaySpecialPattern(GLCD_CHAR_E); break;
			case 'Q': case 'q': GLCD_VoidDisplaySpecialPattern(GLCD_CHAR_Q); break;
			case 'U': case 'u': GLCD_VoidDisplaySpecialPattern(GLCD_CHAR_U); break;
			case 'N': case 'n': GLCD_VoidDisplaySpecialPattern(GLCD_CHAR_N); break;
			case 'C': case 'c': GLCD_VoidDisplaySpecialPattern(GLCD_CHAR_C); break;
			case 'Y': case 'y': GLCD_VoidDisplaySpecialPattern(GLCD_CHAR_Y); break;
			case 'D': case 'd': GLCD_VoidDisplaySpecialPattern(GLCD_CHAR_D); break;
			case 'T': case 't': GLCD_VoidDisplaySpecialPattern(GLCD_CHAR_T); break;
			case 'K': case 'k': GLCD_VoidDisplaySpecialPattern(GLCD_CHAR_K); break;
			case 'H': case 'h': GLCD_VoidDisplaySpecialPattern(GLCD_CHAR_H); break;
			case 'Z': case 'z': GLCD_VoidDisplaySpecialPattern(GLCD_CHAR_Z); break;
			case 'M': case 'm': GLCD_VoidDisplaySpecialPattern(GLCD_CHAR_M); break;
			case 'S': case 's': GLCD_VoidDisplaySpecialPattern(GLCD_CHAR_S); break;
			case 'I': case 'i': GLCD_VoidDisplaySpecialPattern(GLCD_CHAR_I); break;
			case '%': GLCD_VoidDisplaySpecialPattern(GLCD_CHAR_PERCENT); break;
			case '=': GLCD_VoidDisplaySpecialPattern(GLCD_CHAR_EQUAL); break;
			case '.': GLCD_VoidDisplaySpecialPattern(GLCD_CHAR_POINT); break;
			case ' ': GLCD_VoidDisplaySpecialPattern(GLCD_CHAR_SPACE); break;
			case '-': GLCD_VoidDisplaySpecialPattern(GLCD_CHAR_NEGATIVE); break;
			case '0': GLCD_VoidDisplaySpecialPattern(GLCD_CHAR_0); break;
			case '1': GLCD_VoidDisplaySpecialPattern(GLCD_CHAR_1); break;
			case '2': GLCD_VoidDisplaySpecialPattern(GLCD_CHAR_2); break;
			case '3': GLCD_VoidDisplaySpecialPattern(GLCD_CHAR_3); break;
			case '4': GLCD_VoidDisplaySpecialPattern(GLCD_CHAR_4); break;
			case '5': GLCD_VoidDisplaySpecialPattern(GLCD_CHAR_5); break;
			case '6': GLCD_VoidDisplaySpecialPattern(GLCD_CHAR_6); break;
			case '7': GLCD_VoidDisplaySpecialPattern(GLCD_CHAR_7); break;
			case '8': GLCD_VoidDisplaySpecialPattern(GLCD_CHAR_8); break;
			case '9': GLCD_VoidDisplaySpecialPattern(GLCD_CHAR_9); break;
			default: break;
		}
		GLCD_u8SendCommand(GLCD_SET_X_ADDRESS_PREFIX + global_u8CurrXAddress);
		GLCD_u8SendCommand(GLCD_SET_Y_ADDRESS_PREFIX + global_u8CurrYAddress);
		GLCD_VoidSendData(0);
		global_u8CurrYAddress++;
		if (global_u8CurrYAddress >= GLCD_MAX_PAGE_PIXEL_WIDTH && global_u8CurrPage == 0)
		{
			GLCD_u8SelectPage(GLCD_PAGE_1);
			global_u8CurrYAddress = 0;
		}
	}
}

u8 GLCD_u8PrintString(const char *copy_u8String)
{
	u8 local_u8ErrorState = OK;
	u8 local_u8StringIndex = 0;
	
	if(copy_u8String != NULL)
	{
		while(copy_u8String[local_u8StringIndex] != '\0' )
		{
			GLCD_VoidPrintCharacter(copy_u8String[local_u8StringIndex]);
			local_u8StringIndex ++;
		}
	}
	else
	{
		local_u8ErrorState = NOK;
	}
	return local_u8ErrorState;
}

void GLCD_VoidWriteNumber(u32 copy_u32Number)
{
	u32 local_reversed = 1;

	if(copy_u32Number == 0)
	{
		GLCD_VoidPrintCharacter('0');
	}
	else
	{
		/* Reverse Number */
		while (copy_u32Number != 0)
		{
			local_reversed = local_reversed * 10 + (copy_u32Number % 10);
			copy_u32Number /= 10;
		}
		do
		{
			GLCD_VoidPrintCharacter((local_reversed % 10) + '0');
			local_reversed /= 10;
		}
		while(local_reversed != 1);
	}
}