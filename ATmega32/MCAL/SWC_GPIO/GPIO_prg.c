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
#include "SEV_SEG.h"

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */


void main(void){
    GPIO_voidInit();
    /** Buzzer **/
    GPIO_u8SetPinDirection(D, AMIT_BUZZER, PIN_OUTPUT);
    GPIO_u8SetPinValue(D, AMIT_BUZZER, PIN_Low);

    GPIO_u8SetPinDirection(D, AMIT_LED0, PIN_OUTPUT);
    GPIO_u8SetPinValue(D, AMIT_LED0, PIN_Low);

    SEG_vidInit();
   	u8 u8Value = 0;

   	while(1){
//
//        GPIO_u8SetPinValue(D, AMIT_BUZZER, PIN_Low);
//        vidMyDelay_ms(500);
//        GPIO_u8SetPinValue(D, AMIT_BUZZER, PIN_High);
//        vidMyDelay_ms(500);

    	for(u8 i = 50 ; --i ; ){
    		SEG_vidSetValue(u8Value);
    	}
    	u8Value++;
    	GPIO_u8TogglePinValue(D, AMIT_LED0);


    }
}

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

	S_SFIOR->sBits.m_PUD  = LBTY_SET;

	S_GPIOA->m_DDR.u_Reg  = GPIOA_DDR_INIT_DEF;
	S_GPIOA->m_PORT.u_Reg = GPIOA_PORT_INIT_DEF;

	S_GPIOB->m_DDR.u_Reg  = GPIOB_DDR_INIT_DEF;
	S_GPIOB->m_PORT.u_Reg = GPIOB_PORT_INIT_DEF;

	S_GPIOC->m_DDR.u_Reg  = GPIOC_DDR_INIT_DEF;
	S_GPIOC->m_PORT.u_Reg = GPIOC_PORT_INIT_DEF;

	S_GPIOD->m_DDR.u_Reg  = GPIOD_DDR_INIT_DEF;
	S_GPIOD->m_PORT.u_Reg = GPIOD_PORT_INIT_DEF;

}

/* ************************************************************************** */
/* Description :  	Set the pin direction									  */
/* Input       :	u8PortNum, u8PinNum, u8PinDir							  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8SetPinDirection(GPIO_PortNum_type u8PortNum,
											u8 u8PinNum,
											GPIO_DataDirection_type u8PinDir){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_NOK;
	switch(u8PortNum){
		case A:
//			S_GPIOA->m_DDR.u_Reg &= ~(1U<< u8PinNum);
//			S_GPIOA->m_DDR.u_Reg |= ((u8PinDir & 1U) << u8PinNum);
			ASSIGN_BIT(S_GPIOA->m_DDR.u_Reg, u8PinNum, u8PinDir);
			u8RetErrorState = LBTY_OK;
			break;
		case B:
//			S_GPIOB->m_DDR.u_Reg &= ~(1U<< u8PinNum);
//			S_GPIOB->m_DDR.u_Reg |= ((u8PinDir & 1U) << u8PinNum);
			ASSIGN_BIT(S_GPIOB->m_DDR.u_Reg, u8PinNum, u8PinDir);
			u8RetErrorState = LBTY_OK;
			break;
		case C:
//			S_GPIOC->m_DDR.u_Reg &= ~(1U<< u8PinNum);
//			S_GPIOC->m_DDR.u_Reg |= ((u8PinDir & 1U) << u8PinNum);
			ASSIGN_BIT(S_GPIOC->m_DDR.u_Reg, u8PinNum, u8PinDir);
			u8RetErrorState = LBTY_OK;
			break;
		case D:
//			S_GPIOD->m_DDR.u_Reg &= ~(1U<< u8PinNum);
//			S_GPIOD->m_DDR.u_Reg |= ((u8PinDir & 1U) << u8PinNum);
			ASSIGN_BIT(S_GPIOD->m_DDR.u_Reg, u8PinNum, u8PinDir);
			u8RetErrorState = LBTY_OK;
			break;
		default:
			u8RetErrorState = LBTY_NOK;
	}
	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :    Set the pin value										  */
/* Input       :	u8PortNum, u8PinNum, u8PinValue							  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8SetPinValue(GPIO_PortNum_type u8PortNum,
										u8 u8PinNum,
										GPIO_DataStatus_type u8PinValue){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_NOK;
	switch(u8PortNum){
		case A:
//			S_GPIOA->m_PORT.u_Reg &= ~(1U<< u8PinNum);
//			S_GPIOA->m_PORT.u_Reg |= ((u8PinValue & 1U) << u8PinNum);
			ASSIGN_BIT(S_GPIOA->m_PORT.u_Reg, u8PinNum, u8PinValue);
			u8RetErrorState = LBTY_OK;
			break;
		case B:
//			S_GPIOB->m_PORT.u_Reg &= ~(1U<< u8PinNum);
//			S_GPIOB->m_PORT.u_Reg |= ((u8PinValue & 1U) << u8PinNum);
			ASSIGN_BIT(S_GPIOB->m_PORT.u_Reg, u8PinNum, u8PinValue);
			u8RetErrorState = LBTY_OK;
			break;
		case C:
//			S_GPIOC->m_PORT.u_Reg &= ~(1U<< u8PinNum);
//			S_GPIOC->m_PORT.u_Reg |= ((u8PinValue & 1U) << u8PinNum);
			ASSIGN_BIT(S_GPIOC->m_PORT.u_Reg, u8PinNum, u8PinValue);
			u8RetErrorState = LBTY_OK;
			break;
		case D:
//			S_GPIOD->m_PORT.u_Reg &= ~(1U<< u8PinNum);
//			S_GPIOD->m_PORT.u_Reg |= ((u8PinValue & 1U) << u8PinNum);
			ASSIGN_BIT(S_GPIOD->m_PORT.u_Reg, u8PinNum, u8PinValue);
			u8RetErrorState = LBTY_OK;
			break;
		default:
			u8RetErrorState = LBTY_NOK;
	}
	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :    Toggle the pin value									  */
/* Input       :	u8PortNum, u8PinNum, u8PinValue							  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8TogglePinValue(GPIO_PortNum_type u8PortNum, u8 u8PinNum){

	LBTY_tenuErrorStatus u8RetErrorState = LBTY_NOK;
	switch(u8PortNum){
		case A:
//			S_GPIOA->m_PORT.u_Reg ^= (1U << u8PinNum);
			TOG_BIT(S_GPIOA->m_PORT.u_Reg, u8PinNum);
			u8RetErrorState = LBTY_OK;
			break;
		case B:
//			S_GPIOB->m_PORT.u_Reg ^= (1U<< u8PinNum);
			TOG_BIT(S_GPIOB->m_PORT.u_Reg, u8PinNum);
			u8RetErrorState = LBTY_OK;
			break;
		case C:
//			S_GPIOC->m_PORT.u_Reg ^= (1U<< u8PinNum);
			TOG_BIT(S_GPIOC->m_PORT.u_Reg, u8PinNum);
			u8RetErrorState = LBTY_OK;
			break;
		case D:
//			S_GPIOD->m_PORT.u_Reg ^= (1U<< u8PinNum);
			TOG_BIT(S_GPIOD->m_PORT.u_Reg, u8PinNum);
			u8RetErrorState = LBTY_OK;
			break;
		default:
			u8RetErrorState = LBTY_NOK;
	}
	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :    Get the pin value 										  */
/* Input       :	u8PortNum, u8PinNum										  */
/* Input/Output:    pu8Value												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8GetPinValue(GPIO_PortNum_type u8PortNum,
										u8 u8PinNum, pu8 pu8Value){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_NOK;
	switch(u8PinNum){
		case A:
			*pu8Value = GET_BIT(S_GPIOA->m_PIN.u_Reg, u8PinNum);
			u8RetErrorState = LBTY_OK;
			break;
		case B:
			*pu8Value = GET_BIT(S_GPIOB->m_PIN.u_Reg, u8PinNum);
			u8RetErrorState = LBTY_OK;
			break;
		case C:
			*pu8Value = GET_BIT(S_GPIOC->m_PIN.u_Reg, u8PinNum);
			u8RetErrorState = LBTY_OK;
			break;
		case D:
			*pu8Value = GET_BIT(S_GPIOD->m_PIN.u_Reg, u8PinNum);
			u8RetErrorState = LBTY_OK;
			break;
		default:
			u8RetErrorState = LBTY_NOK;
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
	switch(u8PortNum){
		case A:
//			S_GPIOA->m_DDR.u_Reg &= ~(0u);
//			S_GPIOA->m_DDR.u_Reg |= u8PortDir;
			ASSIGN_BYTE(S_GPIOA->m_DDR.u_Reg, u8PortDir);
			u8RetErrorState = LBTY_OK;
			break;
		case B:
//			S_GPIOB->m_DDR.u_Reg &= ~(0u);
//			S_GPIOB->m_DDR.u_Reg |= u8PortDir;
			ASSIGN_BYTE(S_GPIOB->m_DDR.u_Reg, u8PortDir);
			u8RetErrorState = LBTY_OK;
			break;
		case C:
//			S_GPIOC->m_DDR.u_Reg &= ~(0u);
//			S_GPIOC->m_DDR.u_Reg |= u8PortDir;
			ASSIGN_BYTE(S_GPIOC->m_DDR.u_Reg, u8PortDir);
			u8RetErrorState = LBTY_OK;
			break;
		case D:
//			S_GPIOD->m_DDR.u_Reg &= ~(0u);
//			S_GPIOD->m_DDR.u_Reg |= u8PortDir;
			ASSIGN_BYTE(S_GPIOD->m_DDR.u_Reg, u8PortDir);
			u8RetErrorState = LBTY_OK;
			break;
		default:
			u8RetErrorState = LBTY_NOK;
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
	switch(u8PortNum){
		case A:
//			S_GPIOA->m_PORT.u_Reg &= (0u);
//			S_GPIOA->m_PORT.u_Reg |= u8PortValue;
			ASSIGN_BYTE(S_GPIOA->m_PORT.u_Reg, u8PortValue);
			u8RetErrorState = LBTY_OK;
			break;
		case B:
//			S_GPIOB->m_PORT.u_Reg &= (0u);
//			S_GPIOB->m_PORT.u_Reg |= u8PortValue;
			ASSIGN_BYTE(S_GPIOB->m_PORT.u_Reg, u8PortValue);
			u8RetErrorState = LBTY_OK;
			break;
		case C:
//			S_GPIOC->m_PORT.u_Reg &= (0u);
//			S_GPIOC->m_PORT.u_Reg |= u8PortValue;
			ASSIGN_BYTE(S_GPIOC->m_PORT.u_Reg, u8PortValue);
			u8RetErrorState = LBTY_OK;
			break;
		case D:
//			S_GPIOD->m_PORT.u_Reg &= (0u);
//			S_GPIOD->m_PORT.u_Reg |= u8PortValue;
			ASSIGN_BYTE(S_GPIOD->m_PORT.u_Reg, u8PortValue);
			u8RetErrorState = LBTY_OK;
			break;
		default:
			u8RetErrorState = LBTY_NOK;
	}
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
	switch(u8PortNum){
		case A:
			*pu8Value = S_GPIOA->m_PIN.u_Reg;
			u8RetErrorState = LBTY_OK;
			break;
		case B:
			*pu8Value = S_GPIOB->m_PIN.u_Reg;
			u8RetErrorState = LBTY_OK;
			break;
		case C:
			*pu8Value = S_GPIOC->m_PIN.u_Reg;
			u8RetErrorState = LBTY_OK;
			break;
		case D:
			*pu8Value = S_GPIOD->m_PIN.u_Reg;
			u8RetErrorState = LBTY_OK;
			break;
		default:
			u8RetErrorState = LBTY_NOK;
	}
	return u8RetErrorState;

}


/*************************** E N D (GPIO_prg.c) ******************************/
