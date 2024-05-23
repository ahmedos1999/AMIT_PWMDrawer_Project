/***********************************************************************/
/***********************************************************************/
/********************  Author: Ahmed Osama     *************************/
/********************  SWC: ICU                *************************/
/********************  LAYER: MCAL             *************************/
/********************  VERSION: 1.0            *************************/
/********************  DATE:17/05/2024         *************************/
/***********************************************************************/
/***********************************************************************/

#define F_CPU	16000000UL

/* ICU.h */
#include "ICU_Config.h"
#include "ICU_Private.h"
#include "ICU_Interface.h"

/* Global Static Counter Initialization */
static u32 OVF_Counter = 0;
static u64 ICU_OnCounter = 0;
static u64 ICU_TotalCounter = 0;
static u8 Ints = 0;
static u8 Done = 0;


void ICU_VoidTimer1Init(void)
{
	#if TIMER1_WAVE_GEN_MODE == TIMER1_PWM_PHASE_FREQ_CORRECT_ICR1
		#error " Can_Not_Use_ICU_Mode_with_ICR1"
	#elif TIMER1_WAVE_GEN_MODE == TIMER1_PWM_PHASE_CORRECT_ICR1
		#error " Can_Not_Use_ICU_Mode_with_ICR1"
	#elif TIMER1_WAVE_GEN_MODE == TIMER1_CTC_ICR1
		#error " Can_Not_Use_ICU_Mode_with_ICR1"
	#elif TIMER1_WAVE_GEN_MODE == TIMER1_FAST_PWM_ICR1
		#error " Can_Not_Use_ICU_Mode_with_ICR1"
	#else
		/* Set Trigger Edge Select Bit (ICES1) */
		/*
		TIMER1_ICU_FALLING
		TIMER1_ICU_RISING
		*/
		#if TIMER1_ICU_MODE == TIMER1_ICU_FALLING
			CLR_BIT(TIMERS_TCCR1B, TCCR1B_ICES1);
		#elif TIMER1_ICU_MODE == TIMER1_ICU_RISING
			SET_BIT(TIMERS_TCCR1B, TCCR1B_ICES1);
		#endif
	#endif
	
	/* Enable ICU Interrupt */
	SET_BIT(TIMERS_TIMSK, TIMSK_TICIE1);
	
	/* Clear Flag of pending Interrupts*/
	SET_BIT(TIMERS_TIFR, TIFR_ICF1);
	
	/* Clearing Both Timer(TCNT1) and Input Capture (ICR1) Registers  */
	TIMERS_TCNT1DATA = 0x00U;			
}

void ICU_VoidTimer1SignalCapture(f32* copy_Ptrf32Duty, f32* copy_Ptrf32Frequency, f32* copy_Ptrf32Periodic_Time, f32* copy_Ptrf32High_Time, f32* copy_Ptrf32Low_Time)
{
	#if TIMER1_PRESCALER == TIMER1_PRESCALER_1
		u16 local_u16PS = 1;
	#elif TIMER1_PRESCALER == TIMER1_PRESCALER_8
		u16 local_u16PS = 8;
	#elif TIMER1_PRESCALER == TIMER1_PRESCALER_64
		u16 local_u16PS = 64;
	#elif TIMER1_PRESCALER == TIMER1_PRESCALER_256
		u16 local_u16PS = 256;	
	#elif TIMER1_PRESCALER == TIMER1_PRESCALER_1024
		u16 local_u16PS = 1024;
	#endif
	
	/* Calculated Parameters */
	/*
	Duty Percent
	Frequency
	Periodic Time
	High Time
	Low Time
	*/
	DIO_u8SetPinDirection(DIO_PORTD, DIO_PIN6, DIO_PIN_INPUT);		/* ICP1 Pin as Input */
	SET_BIT(TIMERS_TCCR1B, TCCR1B_ICES1);							/* Set Detection to Rising Edge */
	
	TIMERS_u8CallBackFunction(ICU_VoidTimer1ICUInterrupt, ICU1);
	TIMERS_u8CallBackFunction(ICU_VoidTimer1OVFInterrupt, OVF1);
	
	if (Done == 1)
	{
		*copy_Ptrf32Duty = ( ((f32)ICU_OnCounter / (f32)ICU_TotalCounter )) * 100;
		*copy_Ptrf32Periodic_Time = (((f32)ICU_TotalCounter) * ((f32)local_u16PS/(f32)F_CPU));
		*copy_Ptrf32Frequency =  ((f32)1 / *copy_Ptrf32Periodic_Time);
		*copy_Ptrf32High_Time = (f32)ICU_OnCounter * (f32)(local_u16PS/16000000);
		*copy_Ptrf32Low_Time = ((f32)ICU_TotalCounter - (f32)ICU_OnCounter) * (f32)(local_u16PS/F_CPU);
		Done = 0;
		Ints = 0;
	}
}

void ICU_VoidTimer1ICUInterrupt(void)
{
	if (Ints == 0)
	{
		OVF_Counter = 0;
		TIMERS_TCNT1DATA = 0x00U;
		CLR_BIT(TIMERS_TCCR1B, TCCR1B_ICES1);	// falling edge
		Ints++;
	}
	else if (Ints == 1)
	{
		ICU_OnCounter = TIMERS_ICR1DATA + (OVF_Counter * 65536U);
		SET_BIT(TIMERS_TCCR1B, TCCR1B_ICES1);	// Rising Edge
		Ints++;
	}
	else if (Ints == 2)
	{
		ICU_TotalCounter = TIMERS_ICR1DATA + (OVF_Counter * 65536U);
		Ints = 0;
		Done = 1;
	}
}
void ICU_VoidTimer1OVFInterrupt(void)
{
	OVF_Counter++;
}