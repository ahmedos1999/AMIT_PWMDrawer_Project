/***********************************************************************/
/***********************************************************************/
/********************  Author: Ahmed Osama     *************************/
/********************  SWC: GLCD               *************************/
/********************  LAYER: HAL              *************************/
/********************  VERSION: 1.0            *************************/
/********************  DATE:14/05/2024         *************************/
/***********************************************************************/
/***********************************************************************/


#ifndef GLCD_CONFIG_H_
#define GLCD_CONFIG_H_


	/* GLCD Control Port & Data Port Selection */
	/*
	1 - DIO_PORTA
	2 - DIO_PORTB
	3 - DIO_PORTC
	4 - DIO_PORTD
	*/
	#define GLCD_CTRL_PORT  DIO_PORTB
	#define GLCD_DATA_PORT  DIO_PORTA
	
	
	/* GLCD Control Pins */
	/*
	1 - DIO_PIN0
	2 - DIO_PIN1
	3 - DIO_PIN2
	4 - DIO_PIN3
	5 - DIO_PIN4
	6 - DIO_PIN5
	7 - DIO_PIN6
	8 - DIO_PIN7
	*/
	#define GLCD_CTRL_RESET		DIO_PIN4
	#define GLCD_CTRL_E			DIO_PIN2
	#define GLCD_CTRL_RW		DIO_PIN1
	#define GLCD_CTRL_RS		DIO_PIN0	// RS = DI
	#define GLCD_CTRL_CS_1		DIO_PIN6
	#define GLCD_CTRL_CS_2		DIO_PIN7
	
	
	/* Timer Used for Delay */
	/*
	GLCD_TIMER0_DLEAY_MS
	GLCD_TIMER2_DLEAY_MS
	*/
	#define GLCD_TIMER_USED_FOR_DELAY	GLCD_TIMER2_DLEAY_MS
	
	/* GLCD Charactaristics */
	#define GLCD_MAX_LINES							(8U)
	#define GLCD_MAX_LINE_PIXEL_WIDTH				(128U)
	#define GLCD_MAX_PAGE_PIXEL_WIDTH				(64U)
	
#endif /* GLCD_CONFIG_H_ */