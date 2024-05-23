/***********************************************************************/
/***********************************************************************/
/********************  Author: Ahmed Osama     *************************/
/********************  SWC: TIMERS             *************************/
/********************  LAYER: MCAL             *************************/
/********************  VERSION: 1.0            *************************/
/********************  DATE:2/3/2024           *************************/
/***********************************************************************/
/***********************************************************************/



/*LIB*/
#include "../../STD_TYPES/STD_TYPES.h"
#include "../../STD_TYPES/BIT_MATH.h"
#include "../../STD_TYPES/Error_State.h"

/* Timers.h */
#include "TIMERS_config.h"
#include "TIMERS_private.h"
#include "TIMERS_interface.h"
#include "TIMERS_register.h"

/* Timer/Counter0 Compare Match */
void(*TIMER0_CTC_ptrFunction)(void) = NULL;
/* Timer/Counter0 Overflow */
void(*TIMER0_OVF_ptrFunction)(void) = NULL;

/* Timer/Counter1 Capture Event */
void(*TIMER1_ICU_ptrFunction)(void) = NULL;
/* Timer/Counter1 Compare Match A */
void(*TIMER1A_CTC_ptrFunction)(void) = NULL;
/* Timer/Counter1 Compare Match B */
void(*TIMER1B_CTC_ptrFunction)(void) = NULL;
/* Timer/Counter1 Overflow */
void(*TIMER1_OVF_ptrFunction)(void) = NULL;

/*/ Timer/Counter2 Compare Match */
void(*TIMER2_CTC_ptrFunction)(void) = NULL;
/* Timer/Counter2 Overflow */
void(*TIMER2_OVF_ptrFunction)(void) = NULL;

/********** Initialization Functions **********/
void TIMER0_VoidInit(void)
{
	/***** Wave Generation Section *****/
	#if TIMER0_WAVE_GEN_MODE == TIMER0_WGM_NORMAL
	/* WGM : Normal Overflow Mode */
	CLR_BIT(TIMERS_TCCR0, TCCR0_WGM00);
	CLR_BIT(TIMERS_TCCR0, TCCR0_WGM01);
	
	SET_BIT(TIMERS_TIMSK, TIMSK_TOIE0);		// Overflow Interrupt Enable
	
	#elif TIMER0_WAVE_GEN_MODE == TIMER0_WGM_CTC
	/* WGM : Clear Time on Compare Mode */
	CLR_BIT(TIMERS_TCCR0, TCCR0_WGM00);
	SET_BIT(TIMERS_TCCR0, TCCR0_WGM01);
	
	TIMERS_OCR0 |= TIMER0_COMPARE_VALUE;	// Assignment of Compare Match Value
	SET_BIT(TIMERS_TIMSK, TIMSK_OCIE0);		// Compare Interrupt Enable
	
	#elif TIMER0_WAVE_GEN_MODE == TIMER0_WGM_FAST_PWM
	/* WGM : Fast PWM Mode */
	SET_BIT(TIMERS_TCCR0, TCCR0_WGM00);
	SET_BIT(TIMERS_TCCR0, TCCR0_WGM01);
	
	TIMERS_OCR0 = TIMER0_COMPARE_VALUE;		// Assignment of Compare Match Value
	SET_BIT(TIMERS_TIMSK, TIMSK_OCIE0);		// Compare Interrupt Enable
	SET_BIT(TIMERS_TIMSK, TIMSK_TOIE0);		// Overflow Interrupt Enable
	
	#elif TIMER0_WAVE_GEN_MODE == TIMER0_WGM_PHASE_CORRECT_PWM
	/* WGM : Phase Correct PWM Mode */
	SET_BIT(TIMERS_TCCR0, TCCR0_WGM00);
	CLR_BIT(TIMERS_TCCR0, TCCR0_WGM01);
	
	TIMERS_OCR0 = TIMER0_COMPARE_VALUE;		// Assignment of Compare Match Value
	SET_BIT(TIMERS_TIMSK, TIMSK_OCIE0);		// Compare Interrupt Enable
	SET_BIT(TIMERS_TIMSK, TIMSK_TOIE0);		// Overflow Interrupt Enable
	
	#else
		#error "WGM_TIMER0_CONFIG_FILE"
	#endif
	
	/***** Hardware Action Section *****/
	#if TIMER0_COMPARE_MATCH_OUTPUT_MODE == MODE0
	/* Hardware Disconnected */
	CLR_BIT(TIMERS_TCCR0, TCCR0_COM00);
	CLR_BIT(TIMERS_TCCR0, TCCR0_COM01);
	
	#elif TIMER0_COMPARE_MATCH_OUTPUT_MODE == MODE1
		#if TIMER0_WAVE_GEN_MODE == TIMER0_WGM_FAST_PWM
			#error "MODE1_RESERVED_CONFIG_FILE"
		#elif TIMER0_WAVE_GEN_MODE == TIMER0_WGM_PHASE_CORRECT_PWM
			#error "MODE1_RESERVED_CONFIG_FILE"
		#else
		/* Mode1 */
		/*
		- OvF/CTC : Toggle
		- PWM : Reserved 
		*/
		SET_BIT(TIMERS_TCCR0, TCCR0_COM00);
		CLR_BIT(TIMERS_TCCR0, TCCR0_COM01);
		
		#endif
	#elif TIMER0_COMPARE_MATCH_OUTPUT_MODE == MODE2
	/* Mode2 */
	/*
	- OvF/CTC : Clear on compare
	- Fast PWM : Non-Inverting (Clear on Compare, Set at BOTTOM)
	- Phase Correct PWM : Clear on Compare Up-Count, Set on Compare Down-Count
	*/
	CLR_BIT(TIMERS_TCCR0, TCCR0_COM00);
	SET_BIT(TIMERS_TCCR0, TCCR0_COM01);
	
	#elif TIMER0_COMPARE_MATCH_OUTPUT_MODE == MODE3
	/* Mode3 */
	/*
	- OvF/CTC : Set on compare
	- Fast PWM : Inverting (Set on Compare, Clear at BOTTOM)
	- Phase Correct PWM : Set on Compare Up-Count, Clear on Compare Down-Count
	*/
	SET_BIT(TIMERS_TCCR0, TCCR0_COM00);
	SET_BIT(TIMERS_TCCR0, TCCR0_COM01);
	
	#else
		#error "TIMER0_WRONG_MODE_CONFIG_FILE"
	#endif
	
	/* Pre-Scaler */
	TIMERS_TCCR0 &= 0b11111000;
	TIMERS_TCCR0 |= TIMER0_PRESCALER;
}

void TIMER1_VoidInit(void)
{
	/***** Wave Generation Section *****/
	#if TIMER1_WAVE_GEN_MODE == TIMER1_NORMAL
	/* WGM : Normal Mode */
	CLR_BIT(TIMERS_TCCR1A, TCCR1A_WGM10);
	CLR_BIT(TIMERS_TCCR1A, TCCR1A_WGM11);
	CLR_BIT(TIMERS_TCCR1B, TCCR1B_WGM12);
	CLR_BIT(TIMERS_TCCR1B, TCCR1B_WGM13);
	
	SET_BIT(TIMERS_TIMSK, TIMSK_TOIE1);		// Enables Overflow Interrupt
	
	#elif TIMER1_WAVE_GEN_MODE == TIMER1_PWM_PHASE_CORRECT_8
	/* WGM : PHASE CORRECT 8-BIT*/
	SET_BIT(TIMERS_TCCR1A, TCCR1A_WGM10);
	CLR_BIT(TIMERS_TCCR1A, TCCR1A_WGM11);
	CLR_BIT(TIMERS_TCCR1B, TCCR1B_WGM12);
	CLR_BIT(TIMERS_TCCR1B, TCCR1B_WGM13);
	
	TIMERS_OCR1ADATA = TIMER1A_COMPARE_VALUE;		// Assignment of Compare Match Value on A
	TIMERS_OCR1BDATA = TIMER1B_COMPARE_VALUE;		// Assignment of Compare Match Value on B
	
	SET_BIT(TIMERS_TIMSK, TIMSK_TOIE1);		// Enables Overflow Interrupt
	SET_BIT(TIMERS_TIMSK, TIMSK_OCIE1A);	// Enables Compare Match on A
	SET_BIT(TIMERS_TIMSK, TIMSK_OCIE1B);	// Enables Compare Match on B
	
	#elif TIMER1_WAVE_GEN_MODE == TIMER1_PWM_PHASE_CORRECT_9
	/* WGM : PHASE CORRECT PWM 9-BIT*/
	CLR_BIT(TIMERS_TCCR1A, TCCR1A_WGM10);
	SET_BIT(TIMERS_TCCR1A, TCCR1A_WGM11);
	CLR_BIT(TIMERS_TCCR1B, TCCR1B_WGM12);
	CLR_BIT(TIMERS_TCCR1B, TCCR1B_WGM13);
	
	TIMERS_OCR1ADATA = TIMER1A_COMPARE_VALUE;		// Assignment of Compare Match Value on A
	TIMERS_OCR1BDATA = TIMER1B_COMPARE_VALUE;		// Assignment of Compare Match Value on B
	
	SET_BIT(TIMERS_TIMSK, TIMSK_TOIE1);		// Enables Overflow Interrupt
	SET_BIT(TIMERS_TIMSK, TIMSK_OCIE1A);	// Enables Compare Match on A
	SET_BIT(TIMERS_TIMSK, TIMSK_OCIE1B);	// Enables Compare Match on B
	
	#elif TIMER1_WAVE_GEN_MODE == TIMER1_PWM_PHASE_CORRECT_10
	/* WGM : PHASE CORRECT PWM 10-BIT*/
	SET_BIT(TIMERS_TCCR1A, TCCR1A_WGM10);
	SET_BIT(TIMERS_TCCR1A, TCCR1A_WGM11);
	CLR_BIT(TIMERS_TCCR1B, TCCR1B_WGM12);
	CLR_BIT(TIMERS_TCCR1B, TCCR1B_WGM13);

	TIMERS_OCR1ADATA = TIMER1A_COMPARE_VALUE;		// Assignment of Compare Match Value on A
	TIMERS_OCR1BDATA = TIMER1B_COMPARE_VALUE;		// Assignment of Compare Match Value on B
	
	SET_BIT(TIMERS_TIMSK, TIMSK_TOIE1);		// Enables Overflow Interrupt
	SET_BIT(TIMERS_TIMSK, TIMSK_OCIE1A);	// Enables Compare Match on A
	SET_BIT(TIMERS_TIMSK, TIMSK_OCIE1B);	// Enables Compare Match on B
	
	#elif TIMER1_WAVE_GEN_MODE == TIMER1_CTC
	/* WGM : CTC */
	CLR_BIT(TIMERS_TCCR1A, TCCR1A_WGM10);
	CLR_BIT(TIMERS_TCCR1A, TCCR1A_WGM11);
	SET_BIT(TIMERS_TCCR1B, TCCR1B_WGM12);
	CLR_BIT(TIMERS_TCCR1B, TCCR1B_WGM13);
	
	TIMERS_OCR1ADATA = TIMER1A_COMPARE_VALUE;		// Assignment of Compare Match Value on A
	TIMERS_OCR1BDATA = TIMER1B_COMPARE_VALUE;		// Assignment of Compare Match Value on B
	
	SET_BIT(TIMERS_TIMSK, TIMSK_OCIE1A);	// Enables Compare Match on A
	SET_BIT(TIMERS_TIMSK, TIMSK_OCIE1B);	// Enables Compare Match on B
	
	#elif TIMER1_WAVE_GEN_MODE == TIMER1_FAST_PWM_8
	/* WGM : FAST PWM 8-BIT*/
	SET_BIT(TIMERS_TCCR1A, TCCR1A_WGM10);
	CLR_BIT(TIMERS_TCCR1A, TCCR1A_WGM11);
	SET_BIT(TIMERS_TCCR1B, TCCR1B_WGM12);
	CLR_BIT(TIMERS_TCCR1B, TCCR1B_WGM13);
	
	TIMERS_OCR1ADATA = TIMER1A_COMPARE_VALUE;		// Assignment of Compare Match Value on A
	TIMERS_OCR1BDATA = TIMER1B_COMPARE_VALUE;		// Assignment of Compare Match Value on B
	
	SET_BIT(TIMERS_TIMSK, TIMSK_TOIE1);		// Enables Overflow Interrupt
	SET_BIT(TIMERS_TIMSK, TIMSK_OCIE1A);	// Enables Compare Match on A
	SET_BIT(TIMERS_TIMSK, TIMSK_OCIE1B);	// Enables Compare Match on B
	
	#elif TIMER1_WAVE_GEN_MODE == TIMER1_FAST_PWM_9
	/* WGM : FAST PWM 9-BIT*/
	CLR_BIT(TIMERS_TCCR1A, TCCR1A_WGM10);
	SET_BIT(TIMERS_TCCR1A, TCCR1A_WGM11);
	SET_BIT(TIMERS_TCCR1B, TCCR1B_WGM12);
	CLR_BIT(TIMERS_TCCR1B, TCCR1B_WGM13);
	
	TIMERS_OCR1ADATA = TIMER1A_COMPARE_VALUE;		// Assignment of Compare Match Value on A
	TIMERS_OCR1BDATA = TIMER1B_COMPARE_VALUE;		// Assignment of Compare Match Value on B
	
	SET_BIT(TIMERS_TIMSK, TIMSK_TOIE1);		// Enables Overflow Interrupt
	SET_BIT(TIMERS_TIMSK, TIMSK_OCIE1A);	// Enables Compare Match on A
	SET_BIT(TIMERS_TIMSK, TIMSK_OCIE1B);	// Enables Compare Match on B
	
	#elif TIMER1_WAVE_GEN_MODE == TIMER1_FAST_PWM_10	
	/* WGM : FAST PWM 10-BIT*/
	SET_BIT(TIMERS_TCCR1A, TCCR1A_WGM10);
	SET_BIT(TIMERS_TCCR1A, TCCR1A_WGM11);
	SET_BIT(TIMERS_TCCR1B, TCCR1B_WGM12);
	CLR_BIT(TIMERS_TCCR1B, TCCR1B_WGM13);
	
	TIMERS_OCR1ADATA = TIMER1A_COMPARE_VALUE;		// Assignment of Compare Match Value on A
	TIMERS_OCR1BDATA = TIMER1B_COMPARE_VALUE;		// Assignment of Compare Match Value on B
	
	SET_BIT(TIMERS_TIMSK, TIMSK_TOIE1);		// Enables Overflow Interrupt
	SET_BIT(TIMERS_TIMSK, TIMSK_OCIE1A);	// Enables Compare Match on A
	SET_BIT(TIMERS_TIMSK, TIMSK_OCIE1B);	// Enables Compare Match on B
	
	#elif TIMER1_WAVE_GEN_MODE == TIMER1_PWM_PHASE_FREQ_CORRECT_ICR1
	/* WGM : PHASE CORRECT PWM FREQUENCY ICR1*/
	CLR_BIT(TIMERS_TCCR1A, TCCR1A_WGM10);
	CLR_BIT(TIMERS_TCCR1A, TCCR1A_WGM11);
	CLR_BIT(TIMERS_TCCR1B, TCCR1B_WGM12);
	SET_BIT(TIMERS_TCCR1B, TCCR1B_WGM13);
	
	TIMERS_OCR1ADATA = TIMER1A_COMPARE_VALUE;		// Assignment of Compare Match Value on A
	TIMERS_OCR1BDATA = TIMER1B_COMPARE_VALUE;		// Assignment of Compare Match Value on B
	TIMERS_ICR1DATA = TIMER1_TOP;					// Assignment of Timer1 TOP Value to ICR Register
	
	SET_BIT(TIMERS_TIMSK, TIMSK_TOIE1);		// Enables Overflow Interrupt
	SET_BIT(TIMERS_TIMSK, TIMSK_OCIE1A);	// Enables Compare Match on A
	SET_BIT(TIMERS_TIMSK, TIMSK_OCIE1B);	// Enables Compare Match on B
	
	#elif TIMER1_WAVE_GEN_MODE == TIMER1_PWM_PHASE_FREQ_CORRECT_OCR1A
	/* WGM : PHASE CORRECT PWM FREQUENCY OCR1A*/
	SET_BIT(TIMERS_TCCR1A, TCCR1A_WGM10);
	CLR_BIT(TIMERS_TCCR1A, TCCR1A_WGM11);
	CLR_BIT(TIMERS_TCCR1B, TCCR1B_WGM12);
	SET_BIT(TIMERS_TCCR1B, TCCR1B_WGM13);
	
	TIMERS_OCR1ADATA = TIMER1A_COMPARE_VALUE;		// Assignment of Compare Match Value on A
	
	SET_BIT(TIMERS_TIMSK, TIMSK_TOIE1);		// Enables Overflow Interrupt
	SET_BIT(TIMERS_TIMSK, TIMSK_OCIE1A);	// Enables Compare Match on A
	
	#elif TIMER1_WAVE_GEN_MODE == TIMER1_PWM_PHASE_CORRECT_ICR1
	/* WGM : PHASE CORRECT PWM ICR1*/
	CLR_BIT(TIMERS_TCCR1A, TCCR1A_WGM10);
	SET_BIT(TIMERS_TCCR1A, TCCR1A_WGM11);
	CLR_BIT(TIMERS_TCCR1B, TCCR1B_WGM12);
	SET_BIT(TIMERS_TCCR1B, TCCR1B_WGM13);
	
	TIMERS_OCR1ADATA = TIMER1A_COMPARE_VALUE;		// Assignment of Compare Match Value on A
	TIMERS_OCR1BDATA = TIMER1B_COMPARE_VALUE;		// Assignment of Compare Match Value on B
	TIMERS_ICR1DATA = TIMER1_TOP;					// Assignment of Timer1 TOP Value to ICR Register
	
	SET_BIT(TIMERS_TIMSK, TIMSK_TOIE1);		// Enables Overflow Interrupt
	SET_BIT(TIMERS_TIMSK, TIMSK_OCIE1A);	// Enables Compare Match on A
	SET_BIT(TIMERS_TIMSK, TIMSK_OCIE1B);	// Enables Compare Match on B
	
	TIMERS_ICR1DATA = TIMER1_TOP;			// Set the TOP Value
	
	#elif TIMER1_WAVE_GEN_MODE == TIMER1_PWM_PHASE_CORRECT_OCR1A
	/* WGM : PHASE CORRECT PWM OCR1A*/
	SET_BIT(TIMERS_TCCR1A, TCCR1A_WGM10);
	SET_BIT(TIMERS_TCCR1A, TCCR1A_WGM11);
	CLR_BIT(TIMERS_TCCR1B, TCCR1B_WGM12);
	SET_BIT(TIMERS_TCCR1B, TCCR1B_WGM13);
	
	TIMERS_OCR1ADATA = TIMER1A_COMPARE_VALUE;		// Assignment of Compare Match Value on A
	
	SET_BIT(TIMERS_TIMSK, TIMSK_TOIE1);		// Enables Overflow Interrupt
	SET_BIT(TIMERS_TIMSK, TIMSK_OCIE1A);	// Enables Compare Match on A
	
	#elif TIMER1_WAVE_GEN_MODE == TIMER1_CTC_ICR1	
	/* WGM : CTC ICR1*/
	CLR_BIT(TIMERS_TCCR1A, TCCR1A_WGM10);
	CLR_BIT(TIMERS_TCCR1A, TCCR1A_WGM11);
	SET_BIT(TIMERS_TCCR1B, TCCR1B_WGM12);
	SET_BIT(TIMERS_TCCR1B, TCCR1B_WGM13);
	
	TIMERS_OCR1ADATA = TIMER1A_COMPARE_VALUE;		// Assignment of Compare Match Value on A
	TIMERS_OCR1BDATA = TIMER1B_COMPARE_VALUE;		// Assignment of Compare Match Value on B
	TIMERS_ICR1DATA = TIMER1_TOP;					// Assignment of Timer1 TOP Value to ICR Register
	
	//SET_BIT(TIMERS_TIMSK, TIMSK_TICIE1);	// Enables Input Capture
	SET_BIT(TIMERS_TIMSK, TIMSK_OCIE1A);	// Enables Compare Match Interrupt on A
	SET_BIT(TIMERS_TIMSK, TIMSK_OCIE1B);	// Enables Compare Match Interrupt on B
	
	#elif TIMER1_WAVE_GEN_MODE == TIMER1_FAST_PWM_ICR1
	/* WGM : FAST PWM ICR1*/
	CLR_BIT(TIMERS_TCCR1A, TCCR1A_WGM10);
	SET_BIT(TIMERS_TCCR1A, TCCR1A_WGM11);
	SET_BIT(TIMERS_TCCR1B, TCCR1B_WGM12);
	SET_BIT(TIMERS_TCCR1B, TCCR1B_WGM13);

	TIMERS_OCR1ADATA = TIMER1A_COMPARE_VALUE;		// Assignment of Compare Match Value on A
	TIMERS_OCR1BDATA = TIMER1B_COMPARE_VALUE;		// Assignment of Compare Match Value on B
	TIMERS_ICR1DATA = TIMER1_TOP;					// Assignment of Timer1 TOP Value to ICR Register
	
	//SET_BIT(TIMERS_TIMSK, TIMSK_TICIE1);	// Enables Input Capture
	SET_BIT(TIMERS_TIMSK, TIMSK_TOIE1);		// Enables Overflow Interrupt
	SET_BIT(TIMERS_TIMSK, TIMSK_OCIE1A);	// Enables Compare Match Interrupt on A
	SET_BIT(TIMERS_TIMSK, TIMSK_OCIE1B);	// Enables Compare Match Interrupt on B
	
	#elif TIMER1_WAVE_GEN_MODE == TIMER1_FAST_PWM_OCR1A
	/* WGM : FAST PWM OCR1A */
	SET_BIT(TIMERS_TCCR1A, TCCR1A_WGM10);
	SET_BIT(TIMERS_TCCR1A, TCCR1A_WGM11);
	SET_BIT(TIMERS_TCCR1B, TCCR1B_WGM12);
	SET_BIT(TIMERS_TCCR1B, TCCR1B_WGM13);
	
	TIMERS_OCR1ADATA = TIMER1A_COMPARE_VALUE;		// Assignment of Compare Match Value on A
	TIMERS_OCR1BDATA = TIMER1B_COMPARE_VALUE;		// Assignment of Compare Match Value on B
	
	SET_BIT(TIMERS_TIMSK, TIMSK_TOIE1);		// Enables Overflow Interrupt
	SET_BIT(TIMERS_TIMSK, TIMSK_OCIE1A);	// Enables Compare Match on A
	
	#else
	#error "WGM_TIMER1_CONFIG_FILE"
	
	#endif
	
	/***** Hardware Action Section *****/
	/* OC1A */
	#if TIMER1A_COMPARE_MATCH_OUTPUT_MODE == MODE0
	CLR_BIT(TIMERS_TCCR1A, TCCR1A_COM1A0);
	CLR_BIT(TIMERS_TCCR1A, TCCR1A_COM1A1);
	
	#elif TIMER1A_COMPARE_MATCH_OUTPUT_MODE == MODE1
	SET_BIT(TIMERS_TCCR1A, TCCR1A_COM1A0);
	CLR_BIT(TIMERS_TCCR1A, TCCR1A_COM1A1);
	
	#elif TIMER1A_COMPARE_MATCH_OUTPUT_MODE == MODE2
	CLR_BIT(TIMERS_TCCR1A, TCCR1A_COM1A0);
	SET_BIT(TIMERS_TCCR1A, TCCR1A_COM1A1);
	
	#elif TIMER1A_COMPARE_MATCH_OUTPUT_MODE == MODE3
	SET_BIT(TIMERS_TCCR1A, TCCR1A_COM1A0);
	SET_BIT(TIMERS_TCCR1A, TCCR1A_COM1A1);
	
	#else
		#error "TIMER1A_WRONG_MODE_CONFIG_FILE"
	#endif
	/* OC1B */
	#if TIMER1B_COMPARE_MATCH_OUTPUT_MODE == MODE0
	CLR_BIT(TIMERS_TCCR1A, TCCR1A_COM1B0);
	CLR_BIT(TIMERS_TCCR1A, TCCR1A_COM1B1);
	
	#elif TIMER1B_COMPARE_MATCH_OUTPUT_MODE == MODE1
	SET_BIT(TIMERS_TCCR1A, TCCR1A_COM1B0);
	CLR_BIT(TIMERS_TCCR1A, TCCR1A_COM1B1);
	
	#elif TIMER1B_COMPARE_MATCH_OUTPUT_MODE == MODE2
	CLR_BIT(TIMERS_TCCR1A, TCCR1A_COM1B0);
	SET_BIT(TIMERS_TCCR1A, TCCR1A_COM1B1);
	
	#elif TIMER1B_COMPARE_MATCH_OUTPUT_MODE == MODE3
	SET_BIT(TIMERS_TCCR1A, TCCR1A_COM1B0);
	SET_BIT(TIMERS_TCCR1A, TCCR1A_COM1B1);
	
	#else
		#error "TIMER1B_WRONG_MODE_CONFIG_FILE"

	#endif

	/* Pre-Scaler */
	TIMERS_TCCR1B &= 0b11111000;		// Clearing Pre-Scaler Bits
	TIMERS_TCCR1B |= TIMER1_PRESCALER;
}



void TIMER2_VoidInit(void)
{
	/***** Wave Generation Section *****/
	#if TIMER2_WAVE_GEN_MODE == TIMER2_WGM_NORMAL
	/* WGM */
	CLR_BIT(TIMERS_TCCR2, TCCR2_WGM20);
	CLR_BIT(TIMERS_TCCR2, TCCR2_WGM21);
	SET_BIT(TIMERS_TIMSK, TIMSK_TOIE2);		// Overflow enable
	
	#elif TIMER2_WAVE_GEN_MODE == TIMER2_WGM_CTC
	/* WGM */
	CLR_BIT(TIMERS_TCCR2, TCCR2_WGM20);
	SET_BIT(TIMERS_TCCR2, TCCR2_WGM21);
	
	TIMERS_OCR2 = TIMER2_COMPARE_VALUE;		// Compare Match Value
	SET_BIT(TIMERS_TIMSK, TIMSK_OCIE2);		// Compare Enable
	
	#elif TIMER2_WAVE_GEN_MODE == TIMER2_WGM_FAST_PWM
	/* WGM */
	SET_BIT(TIMERS_TCCR2, TCCR2_WGM20);
	SET_BIT(TIMERS_TCCR2, TCCR2_WGM21);
	
	TIMERS_OCR2 = TIMER2_COMPARE_VALUE;		// Compare Match Value
	SET_BIT(TIMERS_TIMSK, TIMSK_OCIE2);		// Compare Enable
	SET_BIT(TIMERS_TIMSK, TIMSK_TOIE2);		// Overflow enable
	
	#elif TIMER2_WAVE_GEN_MODE == TIMER2_WGM_PHASE_CORRECT_PWM
	/* WGM */
	SET_BIT(TIMERS_TCCR2, TCCR2_WGM20);
	CLR_BIT(TIMERS_TCCR2, TCCR2_WGM21);
	
	#else
	#error "WGM_CONFIG_FILE_TIMER2"
	
	#endif
	
	/***** Hardware Action Section *****/
	#if TIMER2_COMPARE_MATCH_OUTPUT_MODE == MODE0
	/* Hardware Disconnected */
	CLR_BIT(TIMERS_TCCR2, TCCR2_COM20);
	CLR_BIT(TIMERS_TCCR2, TCCR2_COM21);
	
	#elif TIMER0_COMPARE_MATCH_OUTPUT_MODE == MODE1
		#if TIMER2_WAVE_GEN_MODE == TIMER2_WGM_FAST_PWM
			#error "MODE1_RESERVED_CONFIG_FILE"
		#elif TIMER2_WAVE_GEN_MODE == TIMER2_WGM_PHASE_CORRECT_PWM
			#error "MODE1_RESERVED_CONFIG_FILE"
		#else
		/* Mode1 */
		/*
		- OvF/CTC : Toggle
		- PWM : Reserved 
		*/
		SET_BIT(TIMERS_TCCR2, TCCR2_COM20);
		CLR_BIT(TIMERS_TCCR2, TCCR2_COM21);
		
		#endif
	#elif TIMER2_COMPARE_MATCH_OUTPUT_MODE == MODE2
	/* Mode2 */
	/*
	- OvF/CTC : Clear on compare
	- Fast PWM : Non-Inverting (Clear on Compare, Set at BOTTOM)
	- Phase Correct PWM : Clear on Compare Up-Count, Set on Compare Down-Count
	*/
	CLR_BIT(TIMERS_TCCR2, TCCR2_COM20);
	SET_BIT(TIMERS_TCCR2, TCCR2_COM21);
	
	#elif TIMER2_COMPARE_MATCH_OUTPUT_MODE == MODE3
	/* Mode3 */
	/*
	- OvF/CTC : Set on compare
	- Fast PWM : Inverting (Set on Compare, Clear at BOTTOM)
	- Phase Correct PWM : Set on Compare Up-Count, Clear on Compare Down-Count
	*/
	SET_BIT(TIMERS_TCCR2, TCCR2_COM20);
	SET_BIT(TIMERS_TCCR2, TCCR2_COM21);
	
	#else
		#error "TIMER2_WRONG_MODE_CONFIG_FILE"
	#endif
	
	/* Pre-Scaler */
	TIMERS_TCCR2 &= 0b11111000;
	TIMERS_TCCR2 |= TIMER2_PRESCALER;
}

/********** Compare Value Update Functions **********/
void TIMER0_voidUpdateCompareValue(u8 copy_u8Value)
{
	TIMERS_OCR0 = copy_u8Value;
}

u8 TIMER1_voidUpdateCompareValue(u8 copy_u8Value, u8 copy_u8RegSelect)
{
	u8 local_ErrorState= OK;
	if (copy_u8RegSelect == A)
	{
		TIMERS_OCR1ADATA = copy_u8Value;
		return OK;	
	}
	else if (copy_u8RegSelect == B)
	{
		TIMERS_OCR1BDATA = copy_u8Value;
		return OK;
	}
	else
	{
		local_ErrorState = NOK;
	}
	return (local_ErrorState);
}

void TIMER2_voidUpdateCompareValue(u8 copy_u8Value)
{
	TIMERS_OCR2 = copy_u8Value;
}

/********** Delay Functions **********/
void TIMER0_VoidDelayms(u16 copy_u16DelayTime)
{
	u16 local_Counter = 0;

	TIMERS_TCCR0 |= TIMER0_PRESCALER_64;	// Every 250 Ticks = 1 ms at P.S.64
	CLR_BIT(TIMERS_TIMSK, TIMSK_OCIE0);		// Disable CTC Interrupt
	for (local_Counter = 0; local_Counter < copy_u16DelayTime; local_Counter++)
	{
		TIMERS_TCNT0 = 0x00;
		while((GET_BIT(TIMERS_TIFR, TIFR_OCF0)) == 0);		// Polling for Interrupt Flag
		SET_BIT(TIMERS_TIFR, TIFR_OCF0);					// Writing one to Flag to Clear it
	}
	TIMERS_TCCR0 &= 0b11111000;
	TIMERS_TCCR0 |= TIMER0_PRESCALER;
	SET_BIT(TIMERS_TIMSK, TIMSK_OCIE0);		// Re-Enable CTC Interrupt
}

void TIMER2_VoidDelayms(u16 copy_u16DelayTime)
{
	u16 local_Counter = 0;

	TIMERS_TCCR2 |= TIMER2_PRESCALER_64;	// Every 250 Ticks = 1 ms at P.S.64
	CLR_BIT(TIMERS_TIMSK, TIMSK_OCIE2);		// Disable CTC Interrupt
	for (local_Counter = 0; local_Counter < copy_u16DelayTime; local_Counter++)
	{
		TIMERS_TCNT0 = 0x00;
		while((GET_BIT(TIMERS_TIFR, TIFR_OCF2)) == 0);		// Polling for Interrupt Flag
		SET_BIT(TIMERS_TIFR, TIFR_OCF2);					// Writing one to Flag to Clear it
	}
	TIMERS_TCCR2 &= 0b11111000;
	TIMERS_TCCR2 |= TIMER2_PRESCALER;
	SET_BIT(TIMERS_TIMSK, TIMSK_OCIE2);		// Re-Enable CTC Interrupt
}

/********** Call-Back Function **********/
u8 TIMERS_u8CallBackFunction(void(*copy_ptrFunction)(void), u8 copy_ptrNum)
{
	/* Call Back Function Pointer Number */
	/*
	CTC2	- Clear Timer2 on Compare
	OVF2	- Overflow on Timer2
	ICU1	- Input Capture Unit on Timer1
	CTC1A	- Clear Timer1A on Compare
	CTC1B	- Clear Timer1B on Compare
	OVF1	- Overflow on Timer1
	CTC0	- Clear Timer0 on Compare
	OVF0	- Overflow on Timer0
	*/
	
	u8 Error_u8State = OK;
	
	/* Pointer Type Switch */
	switch(copy_ptrNum)
	{
		case CTC2 :	TIMER2_CTC_ptrFunction = copy_ptrFunction;		break;
		case OVF2 : TIMER2_OVF_ptrFunction = copy_ptrFunction;		break;
		case ICU1 : TIMER1_ICU_ptrFunction = copy_ptrFunction;		break;
		case CTC1A: TIMER1A_CTC_ptrFunction = copy_ptrFunction;		break;
		case CTC1B: TIMER1B_CTC_ptrFunction = copy_ptrFunction;		break;
		case OVF1 : TIMER1_OVF_ptrFunction = copy_ptrFunction;		break;
		case CTC0 : TIMER0_CTC_ptrFunction = copy_ptrFunction;		break;
		case OVF0 : TIMER0_OVF_ptrFunction = copy_ptrFunction;		break;
		default:	Error_u8State = NOK;	break;
	}
	return Error_u8State;
}


/********** Duty Cycle Functions **********/
u8 TIMER0_u8PWMDutyCycle(u8 copy_u8DutyPercent)
{
	u8 local_u8ErrorState = OK;
	
	if ((copy_u8DutyPercent >= 0) &(copy_u8DutyPercent <= 100))
	{
		TIMER0_voidUpdateCompareValue((copy_u8DutyPercent/100) * TIMER0_MAX);
	}
	else
	{
		local_u8ErrorState = NOK;
	}
	return (local_u8ErrorState);
}

u8 TIMER1_u8PWMDutyCycle(u8 copy_u8DutyPercent)
{
	u8 local_u8ErrorState = OK;
	
	if ((copy_u8DutyPercent >= 0) &(copy_u8DutyPercent <= 100))
	{
		#if TIMER1_WAVE_GEN_MODE == TIMER1_PWM_PHASE_FREQ_CORRECT_ICR1
			TIMER1_voidUpdateCompareValue((copy_u8DutyPercent/100) * TIMERS_ICR1DATA, A);
			TIMER1_voidUpdateCompareValue((copy_u8DutyPercent/100) * TIMERS_ICR1DATA, B);
		
		#elif TIMER1_WAVE_GEN_MODE == TIMER1_PWM_PHASE_CORRECT_ICR1
			TIMER1_voidUpdateCompareValue((copy_u8DutyPercent/100) * TIMERS_ICR1DATA, A);
			TIMER1_voidUpdateCompareValue((copy_u8DutyPercent/100) * TIMERS_ICR1DATA, B);
			
		#elif TIMER1_WAVE_GEN_MODE == TIMER1_CTC_ICR1
			TIMER1_voidUpdateCompareValue((copy_u8DutyPercent/100) * TIMERS_ICR1DATA, A);
			TIMER1_voidUpdateCompareValue((copy_u8DutyPercent/100) * TIMERS_ICR1DATA, B);
			
		#elif TIMER1_WAVE_GEN_MODE == TIMER1_FAST_PWM_ICR1
			TIMER1_voidUpdateCompareValue((copy_u8DutyPercent/100) * TIMERS_ICR1DATA, A);
			TIMER1_voidUpdateCompareValue((copy_u8DutyPercent/100) * TIMERS_ICR1DATA, B);
		
		#else
			TIMER1_voidUpdateCompareValue((copy_u8DutyPercent/100) * TIMER1_MAX, A);
			TIMER1_voidUpdateCompareValue((copy_u8DutyPercent/100) * TIMER1_MAX, B);
			
		#endif
	}
	else
	{
		local_u8ErrorState = NOK;
	}
	return (local_u8ErrorState);
}

u8 TIMER2_u8PWMDutyCycle(u8 copy_u8DutyPercent)
{
	u8 local_u8ErrorState = OK;
	
	if ((copy_u8DutyPercent >= 0) &(copy_u8DutyPercent <= 100))
	{
		TIMER2_voidUpdateCompareValue((copy_u8DutyPercent/100) * TIMER2_MAX);
	}
	else
	{
		local_u8ErrorState = NOK;
	}
	return (local_u8ErrorState);
}




/********** Interrupt Vector Functions **********/
void __vector_4(void) __attribute__((signal));
void __vector_4(void)	// Timer/Counter2 Compare Match
{
	if(TIMER2_CTC_ptrFunction != NULL)
	{
		TIMER2_CTC_ptrFunction();
	}
	else
	{}
}

void __vector_5(void) __attribute__((signal));
void __vector_5(void)	// Timer/Counter2 Overflow
{
	if(TIMER2_OVF_ptrFunction != NULL)
	{
		TIMER2_OVF_ptrFunction();
	}
	else
	{}
}

void __vector_6(void) __attribute__((signal));
void __vector_6(void)	// Timer/Counter1 Capture Event
{
	if(TIMER1_ICU_ptrFunction != NULL)
	{
		TIMER1_ICU_ptrFunction();
	}
	else
	{}
}

void __vector_7(void) __attribute__((signal));
void __vector_7(void)	// Timer/Counter1 Compare Match A
{
	if(TIMER1A_CTC_ptrFunction != NULL)
	{
		TIMER1A_CTC_ptrFunction();
	}
	else
	{}
}

void __vector_8(void) __attribute__((signal));
void __vector_8(void)	// Timer/Counter1 Compare Match B
{
	if(TIMER1B_CTC_ptrFunction != NULL)
	{
		TIMER1B_CTC_ptrFunction();
	}
	else
	{}
}

void __vector_9(void) __attribute__((signal));
void __vector_9(void)	// Timer/Counter1 Overflow
{
	if(TIMER1_OVF_ptrFunction != NULL)
	{
		TIMER1_OVF_ptrFunction();
	}
	else
	{}
}

void __vector_10(void) __attribute__((signal));
void __vector_10(void)	// Timer/Counter0 Compare Match
{
	if(TIMER0_CTC_ptrFunction != NULL)
	{
		TIMER0_CTC_ptrFunction();
	}
	else
	{}
}

void __vector_11(void) __attribute__((signal));
void __vector_11(void)	// Timer/Counter0 Overflow
{
	if(TIMER0_OVF_ptrFunction != NULL)
	{
		TIMER0_OVF_ptrFunction();
	}
	else
	{}
}