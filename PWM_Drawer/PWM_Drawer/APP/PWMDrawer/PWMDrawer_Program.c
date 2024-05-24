/***********************************************************************/
/***********************************************************************/
/********************  Author: Ahmed Osama     *************************/
/********************  SWC: PWM Drawer         *************************/
/********************  LAYER: APP              *************************/
/********************  VERSION: 1.0            *************************/
/********************  DATE:21/05/2024         *************************/
/***********************************************************************/
/***********************************************************************/

/* LIB */
#include "../../STD_TYPES/STD_TYPES.h"
#include "../../STD_TYPES/BIT_MATH.h"
#include "../../STD_TYPES/Error_State.h"

/* HAL */
#include "../../HAL/G-LCD/GLCD_interface.h"

/* MCAL */
/*
None
*/

/* PWM_Drawer.h */
#include "PWMDrawer_Private.h"
#include "PWMDrawer_Interface.h"


 void PWMDrawer_VoidDrawSignal(f32 copy_f32Duty, f32 copy_f32Frequency, f32 copy_f32Periodic_Time, f32 copy_f32High_Time, f32 copy_f32Low_Time)
 {	
 	/* Display Signal Data (Frequency and Duty) Values */
 	GLCD_VoidGoToPos(0, 0);
 	char txt1[15] = "Freq.=";
 	GLCD_u8PrintString(txt1);
 	GLCD_VoidDisplayFloatingPoint(copy_f32Frequency);
 	char txt2[5] = "kHz";
 	GLCD_u8PrintString(txt2);
 
 	GLCD_VoidGoToPos(1, 0);
 	char txt3[15] = "Duty=";
 	GLCD_u8PrintString(txt3);
 	GLCD_VoidWriteNumber(copy_f32Duty);
 	char txt4[5] = "%";
 	GLCD_u8PrintString(txt4);
 
 	/* Display Signal Shape */
 	GLCD_VoidGoToPos(6, 0);
 	u8 pixel_width_count = 0;
 	u8 i;
 	while (pixel_width_count < (128U - 8U))
	 {
 		GLCD_VoidDisplaySpecialPattern(PWM_DRAWER_GLCD_RISING_EDGE); pixel_width_count += 5;
		 
 		for (i = 0; i < ((u16)(copy_f32High_Time*(f32)10)); i++)
		{
 			GLCD_VoidDisplaySpecialPattern(PWM_DRAWER_GLCD_HIGH_LINE); pixel_width_count += 5;
 		}
		 
 		GLCD_VoidDisplaySpecialPattern(PWM_DRAWER_GLCD_FALLING_EDGE); pixel_width_count += 5;
		 
 		for (i = 0; i < ((u16)(copy_f32Low_Time*(f32)10)); i++)
		{
 			GLCD_VoidDisplaySpecialPattern(PWM_DRAWER_GLCD_LOW_LINE); pixel_width_count += 5;
		}
 	}
 
 	/* Display Arrow for Time Period */
 	GLCD_VoidGoToPos(5, 0);
 	GLCD_VoidDisplaySpecialPattern(PWM_DRAWER_GLCD_LEFT_ARROW_HEAD);
	 
 	for (i = 0; i < ((u16)(copy_f32High_Time*(f32)10)); i++)
	{
 		GLCD_VoidDisplaySpecialPattern(PWM_DRAWER_GLCD_ARROW_MIDDLE_BODY);
 	}
	 
 	GLCD_VoidDisplaySpecialPattern(PWM_DRAWER_GLCD_ARROW_MIDDLE_BODY);
	 
 	for (i = 0; i < ((u16)(copy_f32Low_Time*(f32)10)); i++)
	{
 		GLCD_VoidDisplaySpecialPattern(PWM_DRAWER_GLCD_ARROW_MIDDLE_BODY);
 	}
	 
	GLCD_VoidDisplaySpecialPattern(PWM_DRAWER_GLCD_RIGHT_ARROW_HEAD);
 
 	/* Display Time Period Value */
 	GLCD_VoidGoToPos(4, 0);
 	char txt5[15] = "Time=";
 	GLCD_u8PrintString(txt5);
 	GLCD_VoidDisplayFloatingPoint(copy_f32Periodic_Time*(f32)1000);
 	char txt6[5] = "ms";
 	GLCD_u8PrintString(txt6);
 }
