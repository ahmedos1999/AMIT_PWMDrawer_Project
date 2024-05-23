/***********************************************************************/
/***********************************************************************/
/********************  Author: Ahmed Osama     *************************/
/********************  SWC: PWM Drawer         *************************/
/********************  LAYER: APP              *************************/
/********************  VERSION: 1.0            *************************/
/********************  DATE:21/05/2024         *************************/
/***********************************************************************/
/***********************************************************************/

#ifndef PWMDRAWER_PRIVATE_H_
#define PWMDRAWER_PRIVATE_H_

/************************************************************************/
/*				Signal Patterns Characters (Font = 5 x 8)               */
/************************************************************************/
#define PWM_DRAWER_GLCD_HIGH_LINE					(0x0202020202UL)
#define PWM_DRAWER_GLCD_LOW_LINE					(0x4040404040UL)
#define PWM_DRAWER_GLCD_RISING_EDGE					(0x02027E4040UL)
#define PWM_DRAWER_GLCD_FALLING_EDGE				(0x40407E0202UL)
#define PWM_DRAWER_GLCD_RIGHT_ARROW_HEAD			(0x003E081C2AUL)
#define PWM_DRAWER_GLCD_LEFT_ARROW_HEAD				(0x2A1C083E00UL)
#define PWM_DRAWER_GLCD_ARROW_MIDDLE_BODY			(0x0808080808UL)



#endif /* PWMDRAWER_PRIVATE_H_ */