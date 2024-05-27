/***********************************************************************/
/***********************************************************************/
/********************  Author: Ahmed Osama     *************************/
/********************  LAYER: Main             *************************/
/********************  DATE:21/05/2024         *************************/
/***********************************************************************/
/***********************************************************************/

#define F_CPU	16000000UL

/* LIB */
#include "STD_TYPES/STD_TYPES.h"
#include "STD_TYPES/BIT_MATH.h"
#include "STD_TYPES/Error_State.h"

/* MCAL */
#include "MCAL/Timers/TIMERS_interface.h"
#include "MCAL/DIO/DIO_interface.h"
#include "MCAL/GIE/GIE_interface.h"
#include "MCAL/ICU/ICU_Interface.h"

/* HAL */
#include "HAL/G-LCD/GLCD_interface.h"

/* APP */
#include "APP/PWMDrawer/PWMDrawer_Interface.h"


int main(void)
{	
	/* Variable Initializations */
	f32 f32Duty = 0;
	f32 f32Freq = 0;
	f32 f32Periodic_Time = 0;
	f32 f32HighTime = 0;
	f32 f32Low_time = 0;
	
	/* Peripherals Initializations */
	TIMER0_VoidInit();			/* Timer0 Initialization */
	TIMER1_VoidInit();			/* Timer1 Initialization */
	ICU_VoidTimer1Init();		/* ICU Initialization Using Timer1 */
	TIMER2_VoidInit();			/* Timer2 Initialization */
	GIE_Enable();				/* Global Interrupt Enable */
	GLCD_VoidInit();			/* Graphical LCD Initialization */
	
	/* I/O Pins Initialization */
	DIO_u8SetPinDirection(DIO_PORTB, DIO_PIN3, DIO_PIN_OUTPUT);		/* Timer0 PWM OC0 */
	DIO_u8SetPinDirection(DIO_PORTD, DIO_PIN6, DIO_PIN_INPUT);		/* ICP1 Pin as Input */
	
	
	TIMER0_u8PWMDutyCycle(80);
    /* Replace with your application code */
    while (1) 
    {
		ICU_VoidTimer1SignalCapture(&f32Duty, &f32Freq, &f32Periodic_Time, &f32HighTime, &f32Low_time);		/* Parameter Calculation */
		PWMDrawer_VoidDrawSignal(f32Duty, f32Freq, f32Periodic_Time, f32HighTime, f32Low_time);				/* PWM & Parameters Display */
	}
}

