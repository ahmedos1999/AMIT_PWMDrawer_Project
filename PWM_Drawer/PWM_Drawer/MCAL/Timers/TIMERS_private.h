/***********************************************************************/
/***********************************************************************/
/********************  Author: Ahmed Osama     *************************/
/********************  SWC: TIMERS             *************************/
/********************  LAYER: MCAL             *************************/
/********************  VERSION: 1.0            *************************/
/********************  DATE:2/3/2024           *************************/
/***********************************************************************/
/***********************************************************************/




#ifndef TIMERS_PRIVATE_H_
#define TIMERS_PRIVATE_H_

	/********** TCCR0 **********/
	#define TCCR0_FOC0						7	// Force Output Compare	(Forces an immediate compare match on the Wave Gen. Unit)
	
	/* Wave Gen. Mode Selection */
	#define TCCR0_WGM00						6
	#define TCCR0_WGM01						3
	
	#define TIMER0_WGM_FAST_PWM				0
	#define TIMER0_WGM_PHASE_CORRECT_PWM	1
	#define TIMER0_WGM_NORMAL				2
	#define TIMER0_WGM_CTC					3
	
	/* Compare Match Output on OC0 */
	#define TCCR0_COM01						5
	#define TCCR0_COM00						4
	
	/* Clock Selection Bits & Pre-Scaler */
	#define TCCR0_CS02						2
	#define TCCR0_CS01						1
	#define TCCR0_CS00						0
				 
	#define TIMER0_PRESCALER_NOCLKSRC		0
	#define TIMER0_PRESCALER_1				1
	#define TIMER0_PRESCALER_8				2
	#define TIMER0_PRESCALER_64				3
	#define TIMER0_PRESCALER_256			4
	#define TIMER0_PRESCALER_1024			5
	#define TIMER0_EXT_CLK_FALLING_EDGE		6		// External Clock on T0 Pin
	#define TIMER0_EXT_CLK_RISING_EDGE		7		// External Clock on T0 Pin
	
	/********** TCCR2 **********/
	#define TCCR2_FOC2						7	// Force Output Compare	(Forces an immediate compare match on the Wave Gen. Unit)
	
	/* Wave Gen. Mode Selection */
	#define TCCR2_WGM20						6
	#define TCCR2_WGM21						3
	
	#define TIMER2_WGM_FAST_PWM				0
	#define TIMER2_WGM_PHASE_CORRECT_PWM	1
	#define TIMER2_WGM_NORMAL				2
	#define TIMER2_WGM_CTC					3
	
	/* Compare Match Output on OC0 */
	#define TCCR2_COM21						5
	#define TCCR2_COM20						4
	
	#define TIMER2_COMPARE_MATCH_OUTPUT_MODE	MODE0
	
	/* Clock Selection Bits & Pre-Scaler */
	#define TCCR2_CS22						2
	#define TCCR2_CS21						1
	#define TCCR2_CS20						0
	
	#define TIMER2_PRESCALER_NOCLKSRC		0x0
	#define TIMER2_PRESCALER_1				1
	#define TIMER2_PRESCALER_8				2
	#define TIMER2_PRESCALER_32				3
	#define TIMER2_PRESCALER_64				4
	#define TIMER2_PRESCALER_128			5
	#define TIMER2_PRESCALER_256			6
	#define TIMER2_PRESCALER_1024			7
	
	/********** TCCR1A **********/
	/* Compare Output Mode for Compare unit A */
	#define TCCR1A_COM1A1					7
	#define TCCR1A_COM1A0					6
	
	/* Compare Output Mode for Compare unit B */
	#define TCCR1A_COM1B1					5
	#define TCCR1A_COM1B0					4
	
	#define TCCR1A_FOC1A					3	// Force Output Compare	(Force Output Compare for Compare unit A)
	#define TCCR1A_FOC1B					2	// Force Output Compare	(Force Output Compare for Compare unit B)
	
	/* Wave Gen. Mode Selection */
	#define TCCR1A_WGM11					1
	#define TCCR1A_WGM10					0
	
	/********** TCCR1B **********/
	/* ICU Mode Edge Select and Noise Cancel */
	#define TCCR1B_ICNC1					7	// Input Capture Noise Canceler
	#define TCCR1B_ICES1					6	// Input Capture Edge Select, 0 = Falling Edge Trigger, 1 = Rising Edge Trigger
	/* ICU Modes */
	#define TIMER1_ICU_FALLING				0
	#define TIMER1_ICU_RISING				1
	
	
	// Bit 5 : Reserved
	
	/* Wave Gen. Mode Selection */
	#define TCCR1B_WGM13					4
	#define TCCR1B_WGM12					3
	
	#define TIMER1_NORMAL								0
	#define TIMER1_PWM_PHASE_CORRECT_8					1
	#define TIMER1_PWM_PHASE_CORRECT_9					2
	#define TIMER1_PWM_PHASE_CORRECT_10					3
	#define TIMER1_CTC									4
	#define TIMER1_FAST_PWM_8							5
	#define TIMER1_FAST_PWM_9							6
	#define TIMER1_FAST_PWM_10							7
	#define TIMER1_PWM_PHASE_FREQ_CORRECT_ICR1			8
	#define TIMER1_PWM_PHASE_FREQ_CORRECT_OCR1A			9
	#define TIMER1_PWM_PHASE_CORRECT_ICR1				10
	#define TIMER1_PWM_PHASE_CORRECT_OCR1A				11
	#define TIMER1_CTC_ICR1								12
	// Number 13 is Reserved
	#define TIMER1_FAST_PWM_ICR1						14
	#define TIMER1_FAST_PWM_OCR1A						15
	
	/* Clock Selection Bits & Pre-Scaler */
	#define TCCR1B_CS12						2
	#define TCCR1B_CS11						1
	#define TCCR1B_CS10						0
	
	#define TIMER1_PRESCALER_NoClockSRC		0
	#define TIMER1_PRESCALER_1				1
	#define TIMER1_PRESCALER_8				2
	#define TIMER1_PRESCALER_64				3
	#define TIMER1_PRESCALER_256			4
	#define TIMER1_PRESCALER_1024			5
	#define TIMER1_EXT_CLK_FALLING_EDGE		6		// External Clock on T1 Pin
	#define TIMER1_EXT_CLK_RISING_EDGE		7		// External Clock on T1 Pin
	
	/********** TIMSK **********/
	#define TIMSK_OCIE2						7	// Timer/Counter2 Output Compare Match Interrupt Enable
	#define TIMSK_TOIE2						6	// Timer/Counter2 Overflow Interrupt Enable
	#define TIMSK_TICIE1					5	// Timer/Counter1, Input Capture Interrupt Enable
	#define TIMSK_OCIE1A					4	// Timer/Counter1, Output Compare 'A' Match Interrupt Enable
	#define TIMSK_OCIE1B					3	// Timer/Counter1, Output Compare 'B' Match Interrupt Enable
	#define TIMSK_TOIE1						2	// Timer/Counter1, Overflow Interrupt Enable
	#define TIMSK_OCIE0						1	// Timer/Counter0 Output Compare Match Interrupt Enable	
	#define TIMSK_TOIE0						0	// Timer/Counter0 Overflow Interrupt Enable
	
	/********** TIFR **********/
	#define TIFR_OCF2						7	// Timer/Counter2 Output Compare Flag
	#define TIFR_TOV2						6	// Timer/Counter2 Overflow Flag
	#define TIFR_ICF1						5	// Timer/Counter1, Input Capture Flag
	#define TIFR_OCF1A						4	// Timer/Counter1, Output Compare A Match Flag
	#define	TIFR_OCF1B						3	// Timer/Counter1, Output Compare B Match Flag
	#define	TIFR_TOV1						2	// Timer/Counter1, Overflow Flag
	#define TIFR_OCF0						1	// Timer/Counter0 Output Compare Flag
	#define	TIFR_TOV0						0	// Timer/Counter0 Overflow Flag
	
	/********** SFIOR **********/
	#define SFIOR_PSR10						0	// When Set to 1, Pre-Scaler of Timer/Counter1 & Timer/Counter0 are Reset
	#define SFIOR_PSR2						1	// When Set to 1, Pre-Scaler of Timer/Counter2 will Reset
	
	/**** Compare OutPut Mode Select ****/
	#define MODE0							0
	#define MODE1							1
	#define MODE2							2
	#define MODE3							3
	
	#define TIMER0_MAX						256
	#define TIMER1_MAX						65536
	#define TIMER2_MAX						256

#endif