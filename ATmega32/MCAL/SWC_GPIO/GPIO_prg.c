/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : GPIO_prg.c													  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Mar 23, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */
#include "ATMega32.h"

#include "LBTY_int.h"
#include "LBIT_int.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"
#include "GPIO_priv.h"

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */
static inline GPIOx_type* pu8GPIO_Port(u8 u8PortNum){
	GPIOx_type * GPIO = LBTY_NULL;
	switch(u8PortNum){
		case A:
			GPIO = S_GPIOA;
			break;
		case B:
			GPIO = S_GPIOB;
			break;
		case C:
			GPIO = S_GPIOC;
			break;
		case D:
			GPIO = S_GPIOD;
			break;
		default:
			GPIO = (GPIOx_type *)LBTY_NULL;
	}
	return GPIO;
}
/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* Description : Initialize the pins direction and value					  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void GPIO_voidInit(void){

#if(~(GPIOA_DDR_INIT_DEF | (~GPIOA_PORT_INIT_DEF)))
	#warning "there is some pin's in Port A direction is input so it will need to be set to the default value!"
#endif
#if(~(GPIOB_DDR_INIT_DEF | ~GPIOB_PORT_INIT_DEF))
	#warning "there is some pin's in Port B direction is input so it will need to be set to the default value!"
#endif
#if(~(GPIOC_DDR_INIT_DEF | ~GPIOC_PORT_INIT_DEF))
	#warning "there is some pin's in Port C direction is input so it will need to be set to the default value!"
#endif
#if(~(GPIOD_DDR_INIT_DEF | ~GPIOD_PORT_INIT_DEF))
	#warning "there is some pin's in Port D direction is input so it will need to be set to the default value!"
#endif

#if PULL_UP
	S_SFIOR->sBits.m_PUD  = LBTY_SET;
#endif

	GPIO_u8SetPortDirection(A, GPIOA_DDR_INIT_DEF);
	GPIO_u8SetPortValue	   (A, GPIOA_PORT_INIT_DEF);

	GPIO_u8SetPortDirection(B, GPIOB_DDR_INIT_DEF);
	GPIO_u8SetPortValue	   (B, GPIOB_PORT_INIT_DEF);

	GPIO_u8SetPortDirection(C, GPIOC_DDR_INIT_DEF);
	GPIO_u8SetPortValue	   (C, GPIOC_PORT_INIT_DEF);

	GPIO_u8SetPortDirection(D, GPIOD_DDR_INIT_DEF);
	GPIO_u8SetPortValue	   (D, GPIOD_PORT_INIT_DEF);

}

/********************************************************************************************************************/

/* ************************************************************************** */
/* Description :  	Set the pin direction									  */
/* Input       :	u8PortNum, u8PinNum, u8PinDir							  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8SetPinDirection(GPIO_PortNum_type u8PortNum, u8 u8PinNum,
											GPIO_DataDirection_type u8PinDir){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_NOK;
	GPIOx_type * GPIO = pu8GPIO_Port(u8PortNum);

	if(GPIO == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else{
		if(u8PinDir == PIN_OUTPUT){
			SET_BIT(GPIO->m_DDR.u_Reg, u8PinNum);
		}else{
			CLR_BIT(GPIO->m_DDR.u_Reg, u8PinNum);
		}
		u8RetErrorState = LBTY_OK;
	}

	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Set the pin direction									  */
/* Input       :	u8PortNumm, u8StartPin, u8EndPin, u8PinDir				  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8SetRangeDirection(GPIO_PortNum_type u8PortNum,
											u8 u8StartPin, u8 u8EndPin,
											GPIO_DataDirection_type u8PinDir){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_NOK;
	GPIOx_type * GPIO = pu8GPIO_Port(u8PortNum);

	if(GPIO == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else{
		for(u8 i = (u8EndPin - u8StartPin) ; --i ; u8StartPin++){
			if(u8PinDir == PIN_OUTPUT){
				SET_BIT(GPIO->m_DDR.u_Reg, u8StartPin);
			}else{
				CLR_BIT(GPIO->m_DDR.u_Reg, u8StartPin);
			}
		}
		u8RetErrorState = LBTY_OK;
	}

	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Set the pin direction									  */
/* Input       :	u8PortNumm, u8PortMask, u8PortDir						  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8SetMaskDirection(GPIO_PortNum_type u8PortNum, u8 u8PortMask,
											GPIO_DataDirection_type u8PortDir){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_NOK;
	GPIOx_type * GPIO = pu8GPIO_Port(u8PortNum);

	if(GPIO == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else{
		GPIO->m_DDR.u_Reg &= ~u8PortMask;
		GPIO->m_DDR.u_Reg |= (u8)(u8PortMask & u8PortDir);
		u8RetErrorState = LBTY_OK;
	}

	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :    Set the port direction 									  */
/* Input       :	u8PortNum, 	u8PortDir									  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8SetPortDirection(GPIO_PortNum_type u8PortNum,
											 GPIO_DataDirection_type u8PortDir){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_NOK;
	GPIOx_type * GPIO = pu8GPIO_Port(u8PortNum);

	if(GPIO == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else{
		GPIO->m_DDR.u_Reg = u8PortDir;
		u8RetErrorState = LBTY_OK;
	}

	return u8RetErrorState;
}

/********************************************************************************************************************/

/* ************************************************************************** */
/* Description :    Set the pin value										  */
/* Input       :	u8PortNum, u8PinNum, u8PinValue							  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8SetPinValue(GPIO_PortNum_type u8PortNum, u8 u8PinNum,
										GPIO_DataStatus_type u8PinValue){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_NOK;
	GPIOx_type * GPIO = pu8GPIO_Port(u8PortNum);

	if(GPIO == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else{
		if(u8PinValue == PIN_High){
			SET_BIT(GPIO->m_PORT.u_Reg, u8PinNum);
		}else{
			CLR_BIT(GPIO->m_PORT.u_Reg, u8PinNum);
		}
		u8RetErrorState = LBTY_OK;
	}

	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Set the pin direction									  */
/* Input       :	u8PortNumm, u8StartPin, u8EndPin, u8PinValue			  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8SetRangeValue(GPIO_PortNum_type u8PortNum,
											u8 u8StartPin, u8 u8EndPin,
											GPIO_DataDirection_type u8PinValue){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_NOK;
	GPIOx_type * GPIO = pu8GPIO_Port(u8PortNum);

	if(GPIO == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else{
		for(u8 i = (u8EndPin - u8StartPin) ; --i ; u8StartPin++){;
			if(u8PinValue == PIN_High){
				SET_BIT(GPIO->m_PORT.u_Reg, u8StartPin);
			}else{
				CLR_BIT(GPIO->m_PORT.u_Reg, u8StartPin);
			}
		}
		u8RetErrorState = LBTY_OK;
	}

	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Set the pin direction									  */
/* Input       :	u8PortNumm, u8PortMask, u8PortValue						  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8SetMaskValue(GPIO_PortNum_type u8PortNum, u8 u8PortMask,
											GPIO_DataDirection_type u8PortValue){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_NOK;
	GPIOx_type * GPIO = pu8GPIO_Port(u8PortNum);

	if(GPIO == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else{
		GPIO->m_PORT.u_Reg &= ~u8PortMask;
		GPIO->m_PORT.u_Reg |= (u8)(u8PortMask & u8PortValue);
		u8RetErrorState = LBTY_OK;
	}

	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :    Set the port direction 									  */
/* Input       :	u8PortNum, u8PortValue									  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8SetPortValue(GPIO_PortNum_type u8PortNum,
										 GPIO_DataStatus_type u8PortValue){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_NOK;
	GPIOx_type * GPIO = pu8GPIO_Port(u8PortNum);

	if(GPIO == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else{
		GPIO->m_PORT.u_Reg = u8PortValue;
		u8RetErrorState = LBTY_OK;
	}

	return u8RetErrorState;
}

/********************************************************************************************************************/

/* ************************************************************************** */
/* Description :    Get the pin value 										  */
/* Input       :	u8PortNum, u8PinNum										  */
/* Input/Output:    pu8Value												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8GetPinValue(GPIO_PortNum_type u8PortNum,
										u8 u8PinNum, pu8 pu8Value){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_NOK;
	GPIOx_type * GPIO = pu8GPIO_Port(u8PortNum);

	if(GPIO == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else{
		*pu8Value = LBTY_u8ZERO;
		*pu8Value = (u8)GET_BIT(GPIO->m_PIN.u_Reg, u8PinNum);
		u8RetErrorState = LBTY_OK;
	}

	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :    Get the pin value 										  */
/* Input       :	u8PortNumm, u8StartPin, u8EndPin						  */
/* Input/Output:    pu8Value												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8GetRangeValue(GPIO_PortNum_type u8PortNum,
		 	 	 	 	 	 	 	 	 u8 u8StartPin, u8 u8EndPin, pu8 pu8Value){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_NOK;
	GPIOx_type * GPIO = pu8GPIO_Port(u8PortNum);

	if(GPIO == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else{
		*pu8Value = LBTY_u8ZERO;
		for(u8 i = (u8EndPin - u8StartPin) ; --i ; u8StartPin++){
			*pu8Value |= (u8)(GPIO->m_PIN.u_Reg & (1u << u8StartPin));
		}
		u8RetErrorState = LBTY_OK;
	}

	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :    Get the pin value 										  */
/* Input       :	u8PortNum, u8PortMask									  */
/* Input/Output:    pu8Value												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8GetMaskValue(GPIO_PortNum_type u8PortNum,
										u8 u8PortMask, pu8 pu8Value){

	LBTY_tenuErrorStatus u8RetErrorState = GPIO_u8GetPortValue(u8PortNum, pu8Value);
	*pu8Value &= u8PortMask;

	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :    Get the port value										  */
/* Input       :	u8PortNum												  */
/* Input/Output:    pu8Value  												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8GetPortValue(GPIO_PortNum_type u8PortNum, pu8 pu8Value){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_NOK;
	GPIOx_type * GPIO = pu8GPIO_Port(u8PortNum);
	if(GPIO == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else{
		*pu8Value = (u8)GPIO->m_PIN.u_Reg;
		u8RetErrorState = LBTY_OK;
	}
	return u8RetErrorState;
}

/********************************************************************************************************************/

/* ************************************************************************** */
/* Description :    Toggle the pin value									  */
/* Input       :	u8PortNum, u8PinNum										  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8TogglePinValue(GPIO_PortNum_type u8PortNum, u8 u8PinNum){

	LBTY_tenuErrorStatus u8RetErrorState = LBTY_NOK;
	GPIOx_type * GPIO = pu8GPIO_Port(u8PortNum);

	if(GPIO == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else{
		TOG_BIT(GPIO->m_PORT.u_Reg, u8PinNum);
		u8RetErrorState = LBTY_OK;
	}

	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :    Toggle the pin value									  */
/* Input       :	u8PortNumm, u8StartPin, u8EndPin						  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8ToggleRangeValue(GPIO_PortNum_type u8PortNum,
 	 	 	 	 	 	 	 	 	 	 	 u8 u8StartPin, u8 u8EndPin){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_NOK;
	GPIOx_type * GPIO = pu8GPIO_Port(u8PortNum);

	if(GPIO == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else{
		for(u8 i = (u8EndPin - u8StartPin) ; --i ; u8StartPin++){
			TOG_BIT(GPIO->m_PORT.u_Reg, u8StartPin);
		}
		u8RetErrorState = LBTY_OK;
	}

	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :    Toggle the pin value									  */
/* Input       :	u8PortNum, u8PortMask									  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8ToggleMaskValue(GPIO_PortNum_type u8PortNum, u8 u8PortMask){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_NOK;
	GPIOx_type * GPIO = pu8GPIO_Port(u8PortNum);

	if(GPIO == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else{
		TOG_MASK(GPIO->m_PORT.u_Reg, u8PortMask);
		u8RetErrorState = LBTY_OK;
	}

	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :    Toggle the pin value									  */
/* Input       :	u8PortNum					 							  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8TogglePortValue(GPIO_PortNum_type u8PortNum){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_NOK;
	GPIOx_type * GPIO = pu8GPIO_Port(u8PortNum);

	if(GPIO == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else{
		TOG_REG(GPIO->m_PORT.u_Reg);
		u8RetErrorState = LBTY_OK;
	}

	return u8RetErrorState;
}

/*************************** E N D (GPIO_prg.c) ******************************/
