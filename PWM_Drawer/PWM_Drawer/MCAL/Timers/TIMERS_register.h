/***********************************************************************/
/***********************************************************************/
/********************  Author: Ahmed Osama     *************************/
/********************  SWC: TIMERS             *************************/
/********************  LAYER: MCAL             *************************/
/********************  VERSION: 1.0            *************************/
/********************  DATE:2/3/2024           *************************/
/***********************************************************************/
/***********************************************************************/




#ifndef TIMERS_REGISTER_H_
#define TIMERS_REGISTER_H_
 
			/* TIMER0 Registers */
	#define TIMERS_TCCR0        (*(( volatile u8 *)0X53))
	#define TIMERS_TCNT0        (*(( volatile u8 *)0X52))	// Timer/Counter0 Register
	#define TIMERS_OCR0         (*(( volatile u8 *)0X5C))	// Holds the Compare Value of Timer0
	
			/* TIMER1 Registers */
	#define TIMERS_TCCR1A		(*(( volatile u8 *)0X4F))
	#define TIMERS_TCCR1B		(*(( volatile u8 *)0X4E))
	
	#define TIMERS_TCNT1DATA	(*(( volatile u16*)0X4C))	// Timer/Counter1 Register
	#define TIMERS_TCNT1H		(*(( volatile u8 *)0X4D))
	#define TIMERS_TCNT1L		(*(( volatile u8 *)0X4C))
	
	#define TIMERS_OCR1ADATA	(*(( volatile u16*)0X4A))	// Holds the Compare Value of Timer1 (OC1A / D5)
	#define TIMERS_OCR1AH		(*(( volatile u8 *)0X4B))
	#define TIMERS_OCR1AL		(*(( volatile u8 *)0X4A))
	
	#define TIMERS_OCR1BDATA	(*(( volatile u16*)0X48))	// Holds the Compare Value of Timer1 (OC1B / D4)
	#define TIMERS_OCR1BH		(*(( volatile u8 *)0X49))
	#define TIMERS_OCR1BL		(*(( volatile u8 *)0X48))
	
	#define TIMERS_ICR1DATA		(*(( volatile u16*)0X46))	// Used to Define the TOP Value / Stores ICU Value from TCNT1
	#define TIMERS_ICR1H		(*(( volatile u8 *)0X47))
	#define TIMERS_ICR1L		(*(( volatile u8 *)0X46))
			
			/* TIMER2 Registers */
	#define TIMERS_TCCR2		(*(( volatile u8 *)0X45))
	#define TIMERS_TCNT2		(*(( volatile u8 *)0X44))	// Time/Counter2 Register
	#define TIMERS_OCR2			(*(( volatile u8 *)0X43))	// Holds the Compare Value of Timer2
	#define TIMERS_ASSR			(*(( volatile u8 *)0X42))
	
			/* General Timer Registers */
	#define TIMERS_TIMSK        (*(( volatile u8 *)0X59))	// Interrupt Mask Register (Enable/Disable)
	#define TIMERS_TIFR         (*(( volatile u8 *)0X58))	// Interrupt Flag Register
	#define TIMERS_SFIOR        (*(( volatile u8 *)0X50))	// Bit 0 & 1 for Pre-Scaler Reset

#endif