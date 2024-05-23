/***********************************************************************/
/***********************************************************************/
/********************  Author: Ahmed Osama     *************************/
/********************  SWC: TIMERS             *************************/
/********************  LAYER: MCAL             *************************/
/********************  VERSION: 1.0            *************************/
/********************  DATE:2/3/2024           *************************/
/***********************************************************************/
/***********************************************************************/



#ifndef TIMERS_INTEFACE_H_
#define TIMERS_INTEFACE_H_

	/* Call Back Fun. Numbers */
	#define CTC2		10
	#define OVF2		20
	#define ICU1		30
	#define CTC1A		40
	#define CTC1B		50
	#define OVF1		60
	#define CTC0		70
	#define OVF0		80
	
	/* Timer1 A or B*/
	#define A	'A'
	#define B	'B'
	
	
	void TIMER0_VoidInit(void);
	void TIMER1_VoidInit(void);
	void TIMER2_VoidInit(void);
	

	
	/* CTC Value Update */
	void TIMER0_VoidUpdateCompareValue(u8 copy_u8Value);
	u8 TIMER1_VoidUpdateCompareValue(u8 copy_u8Value, u8 copy_u8RegSelect);
	void TIMER2_VoidUpdateCompareValue(u8 copy_u8Value);
	
	/* Delay Functions */
	void TIMER0_VoidDelayms(u16 copy_u16DelayTime);
	void TIMER2_VoidDelayms(u16 copy_u16DelayTime);
	
	/* Call Back Function for All Timers */
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
	u8 TIMERS_u8CallBackFunction(void(*copy_ptrFunction)(void), u8 copy_ptrNum);

#endif
