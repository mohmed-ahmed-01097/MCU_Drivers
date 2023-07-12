/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : GPIO_prg.c													  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Mar 23, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LBTY_int.h"
#include "LCTY_int.h"
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
LCTY_INLINE GPIOx_type* pu8GPIO_Port(u8 u8PortNum){
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
void GPIO_vidInit(void){

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

	S_SFIOR->sBits.m_PUD  = PULL_UP_DISABLE;		// PUD: Pull-up disable

	GPIO_u8SetPortDirection(A, GPIOA_DDR_INIT_DEF);
	GPIO_u8SetPortValue	   (A, GPIOA_PORT_INIT_DEF);

	GPIO_u8SetPortDirection(B, GPIOB_DDR_INIT_DEF);
	GPIO_u8SetPortValue	   (B, GPIOB_PORT_INIT_DEF);

	GPIO_u8SetPortDirection(C, GPIOC_DDR_INIT_DEF);
	GPIO_u8SetPortValue	   (C, GPIOC_PORT_INIT_DEF);

	GPIO_u8SetPortDirection(D, GPIOD_DDR_INIT_DEF);
	GPIO_u8SetPortValue	   (D, GPIOD_PORT_INIT_DEF);

}

/* ************************************************************************** */
/* Description :  	Set the pin Initialization								  */
/* Input       :	u8PinConfig												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8PinInit(GPIO_tstrPinConfig u8PinConfig){
	LBTY_tenuErrorStatus u8RetErrorState =
			GPIO_u8SetPinDirection(u8PinConfig.m_Port, u8PinConfig.m_Pin, u8PinConfig.m_Dir);
	if(u8RetErrorState == LBTY_OK){
		if(u8PinConfig.m_Dir == PIN_INPUT){
			u8RetErrorState = GPIO_u8SetPinPullUp(u8PinConfig.m_Port, u8PinConfig.m_Pin, u8PinConfig.m_Res);
		}else if(u8PinConfig.m_Dir == PIN_OUTPUT){
			u8RetErrorState = GPIO_u8SetPinValue(u8PinConfig.m_Port, u8PinConfig.m_Pin, u8PinConfig.m_Value);
		}else{}
	}
	return u8RetErrorState;
}

/********************************************************************************************************************/

/* ************************************************************************** */
/* Description :  	Set the pin direction									  */
/* Input       :	u8PortNum, u8PinNum, u8PinDir							  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8SetPinDirection(GPIO_tenuPortNum u8PortNum,
		GPIO_tenuPinNum u8PinNum, GPIO_tenuDataDirection u8PinDir){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	GPIOx_type * GPIO = pu8GPIO_Port(u8PortNum);

	if(GPIO == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else if((u8)u8PinNum < Pin_MaxNum){
		if(u8PinDir == PIN_OUTPUT){
			SET_BIT(GPIO->m_DDR.u_Reg, u8PinNum);
		}else if(u8PinDir == PIN_INPUT){
			CLR_BIT(GPIO->m_DDR.u_Reg, u8PinNum);
		}else{
			u8RetErrorState = LBTY_NOK;
		}
	}else{
		u8RetErrorState = LBTY_INDEX_OUT_OF_RANGE;
	}

	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Set the pin direction									  */
/* Input       :	u8PortNumm, u8StartPin, u8EndPin, u8PinDir				  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8SetRangeDirection(GPIO_tenuPortNum u8PortNum,
		GPIO_tenuPinNum u8StartPin, GPIO_tenuPinNum u8EndPin, GPIO_tenuDataDirection u8PinDir){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	GPIOx_type * GPIO = pu8GPIO_Port(u8PortNum);

	if(GPIO == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else if(((u8)u8StartPin < Pin_MaxNum) && ((u8)u8EndPin < Pin_MaxNum) && (u8EndPin > u8StartPin)){
		for(u8 i = (u8EndPin - u8StartPin) ; i-- ; u8StartPin++){
			if(u8PinDir == PIN_OUTPUT){
				SET_BIT(GPIO->m_DDR.u_Reg, u8StartPin);
			}else if(u8PinDir == PIN_INPUT){
				CLR_BIT(GPIO->m_DDR.u_Reg, u8StartPin);
			}else{
				u8RetErrorState = LBTY_NOK;
				break;
			}
		}
	}else{
		u8RetErrorState = LBTY_INDEX_OUT_OF_RANGE;
	}

	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Set the pin direction									  */
/* Input       :	u8PortNumm, u8PortMask, u8PortDir						  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8SetMaskDirection(GPIO_tenuPortNum u8PortNum, u8 u8PortMask,
		GPIO_tenuDataDirection u8PortDir){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	GPIOx_type * GPIO = pu8GPIO_Port(u8PortNum);

	if(GPIO == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else if((u8)u8PortMask <= LBTY_u8MAX){
		GPIO->m_DDR.u_Reg &= ~u8PortMask;
		GPIO->m_DDR.u_Reg |= (u8)(u8PortMask & u8PortDir);
	}else{
		u8RetErrorState = LBTY_INDEX_OUT_OF_RANGE;
	}

	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :    Set the port direction 									  */
/* Input       :	u8PortNum, 	u8PortDir									  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8SetPortDirection(GPIO_tenuPortNum u8PortNum,
		GPIO_tenuDataDirection u8PortDir){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	GPIOx_type * GPIO = pu8GPIO_Port(u8PortNum);

	if(GPIO == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else if((u8)u8PortDir <= LBTY_u8MAX){
		GPIO->m_DDR.u_Reg = u8PortDir;
	}else{
		u8RetErrorState = LBTY_INDEX_OUT_OF_RANGE;
	}

	return u8RetErrorState;
}

/********************************************************************************************************************/

/* ************************************************************************** */
/* Description :    Set the pin value										  */
/* Input       :	u8PortNum, u8PinNum, u8PinValue							  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8SetPinValue(GPIO_tenuPortNum u8PortNum,
		GPIO_tenuPinNum u8PinNum, GPIO_tenuDataStatus u8PinValue){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	GPIOx_type * GPIO = pu8GPIO_Port(u8PortNum);

	if(GPIO == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else if((u8)u8PinNum < Pin_MaxNum){
		if(u8PinValue == PIN_High){
			SET_BIT(GPIO->m_PORT.u_Reg, u8PinNum);
		}else if(u8PinValue == PIN_Low){
			CLR_BIT(GPIO->m_PORT.u_Reg, u8PinNum);
		}else{
			u8RetErrorState = LBTY_NOK;
		}
	}else{
		u8RetErrorState = LBTY_INDEX_OUT_OF_RANGE;
	}

	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Set the pin value										  */
/* Input       :	u8PortNumm, u8StartPin, u8EndPin, u8PinValue			  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8SetRangeValue(GPIO_tenuPortNum u8PortNum,
		GPIO_tenuPinNum u8StartPin, GPIO_tenuPinNum u8EndPin, GPIO_tenuDataStatus u8PinValue){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	GPIOx_type * GPIO = pu8GPIO_Port(u8PortNum);

	if(GPIO == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else if(((u8)u8StartPin < Pin_MaxNum) && ((u8)u8EndPin < Pin_MaxNum) && (u8EndPin > u8StartPin)){
		for(u8 i = (u8EndPin - u8StartPin) ; i-- ; u8StartPin++){
			if(u8PinValue == PIN_High){
				SET_BIT(GPIO->m_PORT.u_Reg, u8StartPin);
			}else if(u8PinValue == PIN_Low){
				CLR_BIT(GPIO->m_PORT.u_Reg, u8StartPin);
			}else{
				u8RetErrorState = LBTY_NOK;
				break;
			}
		}
	}else{
		u8RetErrorState = LBTY_INDEX_OUT_OF_RANGE;
	}

	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Set the pin value										  */
/* Input       :	u8PortNumm, u8PortMask, u8PortValue						  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8SetMaskValue(GPIO_tenuPortNum u8PortNum, u8 u8PortMask,
		GPIO_tenuDataStatus u8PortValue){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	GPIOx_type * GPIO = pu8GPIO_Port(u8PortNum);

	if(GPIO == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else if((u8)u8PortMask <= LBTY_u8MAX){
		GPIO->m_PORT.u_Reg &= ~u8PortMask;
		GPIO->m_PORT.u_Reg |= (u8)(u8PortMask & u8PortValue);
	}else{
		u8RetErrorState = LBTY_INDEX_OUT_OF_RANGE;
	}

	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :    Set the port value	 									  */
/* Input       :	u8PortNum, u8PortValue									  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8SetPortValue(GPIO_tenuPortNum u8PortNum,
		GPIO_tenuDataStatus u8PortValue){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	GPIOx_type * GPIO = pu8GPIO_Port(u8PortNum);

	if(GPIO == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else if((u8)u8PortValue <= LBTY_u8MAX){
		GPIO->m_PORT.u_Reg = u8PortValue;
	}else{
		u8RetErrorState = LBTY_INDEX_OUT_OF_RANGE;
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
LBTY_tenuErrorStatus GPIO_u8GetPinValue(GPIO_tenuPortNum u8PortNum,
		GPIO_tenuPinNum u8PinNum, pu8 pu8Value){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	GPIOx_type * GPIO = pu8GPIO_Port(u8PortNum);

	if((GPIO == LBTY_NULL) || (pu8Value == LBTY_NULL)){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else if((u8)u8PinNum < Pin_MaxNum){
		*pu8Value = LBTY_u8ZERO;
		*pu8Value = (u8)GET_BIT(GPIO->m_PIN.u_Reg, u8PinNum);
	}else{
		u8RetErrorState = LBTY_INDEX_OUT_OF_RANGE;
	}

	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :    Get the pin value 										  */
/* Input       :	u8PortNumm, u8StartPin, u8EndPin						  */
/* Input/Output:    pu8Value												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8GetRangeValue(GPIO_tenuPortNum u8PortNum,
		GPIO_tenuPinNum u8StartPin, GPIO_tenuPinNum u8EndPin, pu8 pu8Value){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	GPIOx_type * GPIO = pu8GPIO_Port(u8PortNum);

	if((GPIO == LBTY_NULL) || (pu8Value == LBTY_NULL)){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else if(((u8)u8StartPin < Pin_MaxNum) && ((u8)u8EndPin < Pin_MaxNum) && (u8EndPin > u8StartPin)){
		*pu8Value = LBTY_u8ZERO;
		for(u8 i = (u8EndPin - u8StartPin) ; i-- ; u8StartPin++){
			*pu8Value |= (u8)(GPIO->m_PIN.u_Reg & (1u << u8StartPin));
		}
	}else{
		u8RetErrorState = LBTY_INDEX_OUT_OF_RANGE;
	}

	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :    Get the pin value 										  */
/* Input       :	u8PortNum, u8PortMask									  */
/* Input/Output:    pu8Value												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8GetMaskValue(GPIO_tenuPortNum u8PortNum,
		u8 u8PortMask, pu8 pu8Value){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	if(!(u8RetErrorState = GPIO_u8GetPortValue(u8PortNum, pu8Value))){
		*pu8Value &= u8PortMask;
	}

	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :    Get the port value										  */
/* Input       :	u8PortNum												  */
/* Input/Output:    pu8Value  												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8GetPortValue(GPIO_tenuPortNum u8PortNum, pu8 pu8Value){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	GPIOx_type * GPIO = pu8GPIO_Port(u8PortNum);

	if((GPIO == LBTY_NULL) || (pu8Value == LBTY_NULL)){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else{
		*pu8Value = (u8)GPIO->m_PIN.u_Reg;
	}
	return u8RetErrorState;
}

/********************************************************************************************************************/

/* ************************************************************************** */
/* Description :    Toggle the pin value									  */
/* Input       :	u8PortNum, u8PinNum										  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8TogglePinValue(GPIO_tenuPortNum u8PortNum, GPIO_tenuPinNum u8PinNum){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	GPIOx_type * GPIO = pu8GPIO_Port(u8PortNum);

	if(GPIO == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else if((u8)u8PinNum < Pin_MaxNum){
		TOG_BIT(GPIO->m_PORT.u_Reg, u8PinNum);
	}else{
		u8RetErrorState = LBTY_INDEX_OUT_OF_RANGE;
	}

	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :    Toggle the pin value									  */
/* Input       :	u8PortNumm, u8StartPin, u8EndPin						  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8ToggleRangeValue(GPIO_tenuPortNum u8PortNum,
		GPIO_tenuPinNum u8StartPin, GPIO_tenuPinNum u8EndPin){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	GPIOx_type * GPIO = pu8GPIO_Port(u8PortNum);

	if(GPIO == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else if(((u8)u8StartPin < Pin_MaxNum) && ((u8)u8EndPin < Pin_MaxNum) && (u8EndPin > u8StartPin)){
		for(u8 i = (u8EndPin - u8StartPin) ; i-- ; u8StartPin++){
			TOG_BIT(GPIO->m_PORT.u_Reg, u8StartPin);
		}
	}else{
		u8RetErrorState = LBTY_INDEX_OUT_OF_RANGE;
	}

	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :    Toggle the pin value									  */
/* Input       :	u8PortNum, u8PortMask									  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8ToggleMaskValue(GPIO_tenuPortNum u8PortNum, u8 u8PortMask){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	GPIOx_type * GPIO = pu8GPIO_Port(u8PortNum);

	if(GPIO == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else if((u8)u8PortMask <= LBTY_u8MAX){
		TOG_MASK(GPIO->m_PORT.u_Reg, u8PortMask);
	}else{
		u8RetErrorState = LBTY_INDEX_OUT_OF_RANGE;
	}

	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :    Toggle the pin value									  */
/* Input       :	u8PortNum					 							  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8TogglePortValue(GPIO_tenuPortNum u8PortNum){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	GPIOx_type * GPIO = pu8GPIO_Port(u8PortNum);

	if(GPIO == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else{
		TOG_REG(GPIO->m_PORT.u_Reg);
	}

	return u8RetErrorState;
}

/********************************************************************************************************************/

/* ************************************************************************** */
/* Description :  	Enable the pull up res									  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void GPIO_vidEnablePullUp(void){
	S_SFIOR->sBits.m_PUD  = LBTY_RESET;		// PUD: Pull-up disable
}

/* ************************************************************************** */
/* Description :  	Disable the pull up res									  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void GPIO_vidDisablePullUp(void){
	S_SFIOR->sBits.m_PUD  = LBTY_SET;		// PUD: Pull-up disable
}

/* ************************************************************************** */
/* Description :  	Set the pin pull up res									  */
/* Input       :	u8PortNum, u8PinNum, u8Pullup							  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8SetPinPullUp(GPIO_tenuPortNum u8PortNum,
		GPIO_tenuPinNum u8PinNum, LBTY_tenuFlagStatus u8Pullup){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	GPIOx_type * GPIO = pu8GPIO_Port(u8PortNum);

	if(GPIO == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else if((u8)u8PinNum < Pin_MaxNum){
		if(GET_BIT(GPIO->m_DDR.u_Reg, u8PinNum) == PIN_INPUT){
			if(u8Pullup == PULL_UP){
				SET_BIT(GPIO->m_PORT.u_Reg, u8PinNum);
			}else if(u8Pullup == PULL_DOWN){
				CLR_BIT(GPIO->m_PORT.u_Reg, u8PinNum);
			}else{
				u8RetErrorState = LBTY_NOK;
			}
		}else{
			u8RetErrorState = LBTY_WRITE_ERROR;
		}
	}else{
		u8RetErrorState = LBTY_INDEX_OUT_OF_RANGE;
	}

	return u8RetErrorState;
}

/*************************** E N D (GPIO_prg.c) ******************************/
