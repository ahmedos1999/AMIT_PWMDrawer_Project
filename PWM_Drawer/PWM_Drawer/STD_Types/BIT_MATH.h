/***********************************************************************/
/***********************************************************************/
/********************  Author: Ahmed Osama     *************************/
/********************  SWC: Bit Wise OP        *************************/
/********************  LAYER: LIB             * ************************/
/********************  VERSION: 1.0            *************************/
/********************  DATE:14/05/2024         *************************/
/***********************************************************************/
/***********************************************************************/

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

	#define SET_BIT(REG,BIT_NUM)			(REG |= (1 << BIT_NUM))
	#define CLR_BIT(REG,BIT_NUM)			(REG &= (~(1 << BIT_NUM)))
	#define TOG_BIT(REG,BIT_NUM)			(REG ^= (1 << BIT_NUM))
	#define TOG_REG(REG)					(REG ^= 1)
	#define GET_BIT(REG,BIT_NUM)			( (REG >> BIT_NUM) & 1)
	#define AssignNum(REG,BIT_NUM,VALUE)	(REG = ((CLR_BIT(REG,BIT_NUM)) | ((VALUE) << (BIT_NUM))))
	#define AssignReg(REG1,BIT1,REG2,BIT2)	(REG1 = ((CLR_BIT(REG1,BIT1) | (GET_BIT(REG2,BIT2) << (BIT1)))))

#endif