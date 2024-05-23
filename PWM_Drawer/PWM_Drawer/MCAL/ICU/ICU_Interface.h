/***********************************************************************/
/***********************************************************************/
/********************  Author: Ahmed Osama     *************************/
/********************  SWC: ICU                *************************/
/********************  LAYER: MCAL             *************************/
/********************  VERSION: 1.0            *************************/
/********************  DATE:17/05/2024         *************************/
/***********************************************************************/
/***********************************************************************/



#ifndef ICU_INTERFACE_H_
#define ICU_INTERFACE_H_

/* LIB */
#include "../../STD_TYPES/STD_TYPES.h"
#include "../../STD_TYPES/BIT_MATH.h"
#include "../../STD_TYPES/Error_State.h"

/* Timers.h*/
#include "../Timers/TIMERS_config.h"
#include "../Timers/TIMERS_private.h"
#include "../Timers/TIMERS_interface.h"
#include "../Timers/TIMERS_register.h"

/*DIO.h*/
#include "../DIO/DIO_interface.h"

/* Initialization for ICU */
void ICU_VoidTimer1Init(void);

/* Timer1 ICU with Interrupt Functions */
void ICU_VoidTimer1SignalCapture(f32* copy_Ptrf32Duty, f32* copy_Ptrf32Frequency, f32* copy_Ptrf32Periodic_Time, f32* copy_Ptrf32High_Time, f32* copy_Ptrf32Low_Time);


#endif /* ICU_INTERFACE_H_ */