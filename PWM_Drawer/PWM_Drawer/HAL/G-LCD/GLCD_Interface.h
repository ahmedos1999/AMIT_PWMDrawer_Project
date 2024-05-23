/***********************************************************************/
/***********************************************************************/
/********************  Author: Ahmed Osama     *************************/
/********************  SWC: GLCD               *************************/
/********************  LAYER: HAL              *************************/
/********************  VERSION: 1.0            *************************/
/********************  DATE:14/05/2024         *************************/
/***********************************************************************/
/***********************************************************************/

#ifndef GLCD_INTERFACE_H_
#define GLCD_INTERFACE_H_

	/* GLCD Definitions */
	#define GLCD_DISPLAY_ON				(0x3F)
	#define GLCD_DISPLAY_OFF			(0x3E)
	#define	GLCD_SET_Y_ADDRESS_PREFIX	(0x40)
	#define	GLCD_SET_X_ADDRESS_PREFIX	(0xB8)
	#define	GLCD_SET_Z_ADDRESS_PREFIX	(0xC0)

	/***********  Initialization Function ***********/	
	void GLCD_VoidInit(void);
	
	/***********  Control Functions ***********/
	void GLCD_u8SendCommand(u8 copy_u8Command);
	u8 GLCD_u8SelectPage(u8 copy_u8PageNum);
	void GLCD_VoidSendData(u8 copy_u8Data);
	void GLCD_VoidReset(void);
	void GLCD_VoidGoToPos(u8 copy_u8XPos, u8 copy_u8YPos);
	void GLCD_VoidClearDisplay(void);

	
	/***********  Display Functions ***********/
	void GLCD_VoidWriteNumber(u32 copy_u32Number);
	void GLCD_VoidDisplayFloatingPoint(f32 copy_f32FloatingNumber);
	void GLCD_VoidDisplaySpecialPattern(u64 Pattern);
	void GLCD_VoidPrintCharacter(u8 copy_u8Data);
	u8 GLCD_u8PrintString(const char * copy_u8String);


#endif /* GLCD_INTERFACE_H_ */