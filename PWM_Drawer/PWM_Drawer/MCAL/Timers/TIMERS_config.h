/***********************************************************************/
/***********************************************************************/
/********************  Author: Ahmed Osama     *************************/
/********************  SWC: TIMERS             *************************/
/********************  LAYER: MCAL             *************************/
/********************  VERSION: 1.0            *************************/
/********************  DATE:2/3/2024           *************************/
/***********************************************************************/
/***********************************************************************/


#ifndef TIMERS_CONFIG_H_
#define TIMERS_CONFIG_H_

	/********** TIMER 0 CONFIG **********/
	/* Pre-Scaler Timer0 */
	/*
	TIMER0_PRESCALER_NOCLKSRC
	TIMER0_PRESCALER_1
	TIMER0_PRESCALER_8
	TIMER0_PRESCALER_64
	TIMER0_PRESCALER_256
	TIMER0_PRESCALER_1024
	TIMER0_EXT_CLK_FALLING_EDGE
	TIMER0_EXT_CLK_RISING_EDGE
	*/
	#define TIMER0_PRESCALER    TIMER0_PRESCALER_1024
	
	/* WaveGeneration mode Timer0*/
	/*
	TIMER0_WGM_FAST_PWM
	TIMER0_WGM_CORRECT_PWM
	TIMER0_WGM_NORMAL
	TIMER0_WGM_CTC
	*/
	#define TIMER0_WAVE_GEN_MODE    TIMER0_WGM_FAST_PWM
	
	/* Compare Match HardWare Action COM - Bits*/
	/*
	MODE0	- Hardware Disconnected
	
	MODE1	- OvF/CTC : Toggle
	- PWM : Reserved
	
	MODE2	- OvF/CTC : Clear on compare
	- Fast PWM : Non-Inverting (Clear on Compare, Set at BOTTOM)
	- Phase Correct PWM : Clear on Compare Up-Count, Set on Compare Down-Count
	
	MODE3	- OvF/CTC : Set on compare
	- Fast PWM : Inverting (Set on Compare, Clear at BOTTOM)
	- Phase Correct PWM : Set on Compare Up-Count, Clear on Compare Down-Count
	*/
	#define TIMER0_COMPARE_MATCH_OUTPUT_MODE	MODE2
	
	#define TIMER0_COMPARE_VALUE	200		/* Value put in OCR0 to Compare */
	
	
	/********** TIMER 1 CONFIG **********/
	/* Pre-Scaler Timer1 */
	/*
	TIMER1_PRESCALER_NOCLKSRC
	TIMER1_PRESCALER_1
	TIMER1_PRESCALER_8
	TIMER1_PRESCALER_64
	TIMER1_PRESCALER_256
	TIMER1_PRESCALER_1024
	TIMER1_EXT_CLK_FALLING_EDGE
	TIMER1_EXT_CLK_RISING_EDGE
	*/
	#define TIMER1_PRESCALER    TIMER1_PRESCALER_1
	
	/* WaveGeneration Mode Timer1*/
	/*
	TIMER1_NORMAL
	TIMER1_PWM_PHASE_CORRECT_8
	TIMER1_PWM_PHASE_CORRECT_9
	TIMER1_PWM_PHASE_CORRECT_10
	TIMER1_CTC
	TIMER1_FAST_PWM_8
	TIMER1_FAST_PWM_9
	TIMER1_FAST_PWM_10
	TIMER1_PWM_PHASE_FREQ_CORRECT_ICR1
	TIMER1_PWM_PHASE_FREQ_CORRECT_OCR1A
	TIMER1_PWM_PHASE_CORRECT_ICR1
	TIMER1_PWM_PHASE_CORRECT_OCR1A
	TIMER1_CTC_ICR1
	TIMER1_FAST_PWM_ICR1
	TIMER1_FAST_PWM_OCR1A
	*/
	#define TIMER1_WAVE_GEN_MODE   TIMER1_NORMAL
	
	
	/* Compare Match HardWare Action COM - Bits*/
	/*
	MODE0	-
	MODE1	-
	MODE2	-
	MODE3	-
	*/
	#define TIMER1A_COMPARE_MATCH_OUTPUT_MODE	MODE0
	#define TIMER1B_COMPARE_MATCH_OUTPUT_MODE	MODE0
	
	#define TIMER1A_COMPARE_VALUE 2000			/* Value put in OCR1A to Compare */
	#define TIMER1B_COMPARE_VALUE 2000			/* Value put in OCR1B to Compare */
	
	#define TIMER1_TOP	40000					/* TOP Value Equals MAX = 2^res or Value Put in ICR1 */
	
	/* ICU Mode Configurations */
	/*
	TIMER1_ICU_FALLING
	TIMER1_ICU_RISING
	*/
	#define TIMER1_ICU_MODE		TIMER1_ICU_RISING
	
	
	/********** TIMER 2 CONFIG **********/
	/*Pre-Scaler Timer2*/
	/*
	TIMER2_PRESCALER_NOCLKSRC
	TIMER2_PRESCALER_1
	TIMER2_PRESCALER_8
	TIMER2_PRESCALER_32
	TIMER2_PRESCALER_64
	TIMER2_PRESCALER_128
	TIMER2_PRESCALER_256
	TIMER2_PRESCALER_1024
	*/
	#define TIMER2_PRESCALER    TIMER2_PRESCALER_64
	
	/* WaveGeneration mode Timer0*/
	/*
	TIMER2_WGM_Fast_PWM
	TIMER2_WGM_CORRECT_PWM
	TIMER2_WGM_NORMAL
	TIMER2_WGM_CTC
	*/
	#define TIMER2_WAVE_GEN_MODE   TIMER2_WGM_CTC
	
	/* Compare Match HardWare Action COM - Bits*/
	/*
	MODE0	-
	MODE1	-
	MODE2	-
	MODE3	-
	*/
	#define TIMER2_COMPARE_MATCH_OUTPUT_MODE	MODE0
	
	#define TIMER2_COMPARE_VALUE 250					/* Value put in OCR2 to Compare */
	
#endif
