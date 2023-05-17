/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : GPIO_int.h													  */
/* Author      : MAAM														  */
/* Version     : v01.1														  */
/* date        : Mar 23, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef SWC_GPIO_GPIO_INT_H_
#define SWC_GPIO_GPIO_INT_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

typedef enum {
	Pin_0 = (u8)0,
	Pin_1,
	Pin_2,
	Pin_3,
	Pin_4,
	Pin_5,
	Pin_6,
	Pin_7,
	Pin_MaxNum
}GPIO_tenuPinNum;

typedef enum {
	A = (u8)0,
	B,
	C,
	D,
	Port_Num
}GPIO_tenuPortNum;

typedef enum{
    PIN_INPUT = (u8)0u,
	PIN_OUTPUT = (u8)1u,
	PORT_INPUT = (u8)0x00U,
	PORT_OUTPUT = (u8)0xFFU
}GPIO_tenuDataDirection;

typedef enum{
    PIN_Low = (u8)0u,
	PIN_High = (u8)1u,
	PORT_Low = (u8)0x00U,
	PORT_High = (u8)0xFFU
}GPIO_tenuDataStatus;

typedef enum{
	PULL_DOWN = (u8)0u,
    PULL_UP = (u8)1u,
	PULL_None
}GPIO_tenuInputRes;

/********************************************************************************************************************/

typedef struct{
	GPIO_tenuPortNum 		m_Port;
	GPIO_tenuPinNum			m_Pin;
	GPIO_tenuDataDirection	m_Dir;
	GPIO_tenuDataStatus		m_Value;
	GPIO_tenuInputRes		m_Res;
}GPIO_tstrPinConfig;

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

/* ************************************************************************** */
/* Description : Initialize the pins direction and value					  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void GPIO_voidInit(void);

/* ************************************************************************** */
/* Description :  	Set the pin Initialization								  */
/* Input       :	u8PinConfig												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8PinInit(GPIO_tstrPinConfig u8PinConfig);

/********************************************************************************************************************/

/* ************************************************************************** */
/* Description :  	Set the pin direction									  */
/* Input       :	u8PortNum, u8PinNum, u8PinDir							  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8SetPinDirection(GPIO_tenuPortNum u8PortNum,
		GPIO_tenuPinNum u8PinNum, GPIO_tenuDataDirection u8PinDir);

/* ************************************************************************** */
/* Description :  	Set the pin direction									  */
/* Input       :	u8PortNumm, u8StartPin, u8EndPin, u8PinDir				  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8SetRangeDirection(GPIO_tenuPortNum u8PortNum,
		GPIO_tenuPinNum u8StartPin, GPIO_tenuPinNum u8EndPin, GPIO_tenuDataDirection u8PinDir);

/* ************************************************************************** */
/* Description :  	Set the pin direction									  */
/* Input       :	u8PortNumm, u8PortMask, u8PortDir						  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8SetMaskDirection(GPIO_tenuPortNum u8PortNum, u8 u8PortMask,
											GPIO_tenuDataDirection u8PortDir);

/* ************************************************************************** */
/* Description :    Set the port direction 									  */
/* Input       :	u8PortNum, 	u8PortDir									  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8SetPortDirection(GPIO_tenuPortNum u8PortNum,
											 GPIO_tenuDataDirection u8PortDir);

/********************************************************************************************************************/

/* ************************************************************************** */
/* Description :    Set the pin value										  */
/* Input       :	u8PortNum, u8PinNum, u8PinValue							  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8SetPinValue(GPIO_tenuPortNum u8PortNum,
		GPIO_tenuPinNum u8PinNum, GPIO_tenuDataStatus u8PinVlaue);

/* ************************************************************************** */
/* Description :  	Set the pin direction									  */
/* Input       :	u8PortNumm, u8StartPin, u8EndPin, u8PinValue			  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8SetRangeValue(GPIO_tenuPortNum u8PortNum,
		GPIO_tenuPinNum u8StartPin, GPIO_tenuPinNum u8EndPin, GPIO_tenuDataDirection u8PinValue);

/* ************************************************************************** */
/* Description :  	Set the pin direction									  */
/* Input       :	u8PortNumm, u8PortMask, u8PortValue						  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8SetMaskValue(GPIO_tenuPortNum u8PortNum, u8 u8PortMask,
											GPIO_tenuDataDirection u8PortValue);

/* ************************************************************************** */
/* Description :    Set the port direction 									  */
/* Input       :	u8PortNum, u8PortValue									  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8SetPortValue(GPIO_tenuPortNum u8PortNum,
										 GPIO_tenuDataStatus u8PortValue);

/********************************************************************************************************************/

/* ************************************************************************** */
/* Description :    Get the pin value 										  */
/* Input       :	u8PortNum, u8PinNum										  */
/* Input/Output:    pu8Value												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8GetPinValue(GPIO_tenuPortNum u8PortNum,
		GPIO_tenuPinNum u8PinNum, pu8 pu8Value);

/* ************************************************************************** */
/* Description :    Get the pin value 										  */
/* Input       :	u8PortNumm, u8StartPin, u8EndPin						  */
/* Input/Output:    pu8Value												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8GetRangeValue(GPIO_tenuPortNum u8PortNum,
		GPIO_tenuPinNum u8StartPin, GPIO_tenuPinNum u8EndPin, pu8 pu8Value);

/* ************************************************************************** */
/* Description :    Get the pin value 										  */
/* Input       :	u8PortNum, u8PortMask									  */
/* Input/Output:    pu8Value												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8GetMaskValue(GPIO_tenuPortNum u8PortNum,
										u8 u8PortMask, pu8 pu8Value);

/* ************************************************************************** */
/* Description :    Get the port value										  */
/* Input       :	u8PortNum												  */
/* Input/Output:    pu8Value  												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8GetPortValue(GPIO_tenuPortNum u8PortNum, pu8 pu8Value);

/********************************************************************************************************************/

/* ************************************************************************** */
/* Description :    Toggle the pin value									  */
/* Input       :	u8PortNum, u8PinNum										  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8TogglePinValue(GPIO_tenuPortNum u8PortNum, GPIO_tenuPinNum u8PinNum);

/* ************************************************************************** */
/* Description :    Toggle the pin value									  */
/* Input       :	u8PortNumm, u8StartPin, u8EndPin						  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8ToggleRangeValue(GPIO_tenuPortNum u8PortNum,
		GPIO_tenuPinNum u8StartPin, GPIO_tenuPinNum u8EndPin);

/* ************************************************************************** */
/* Description :    Toggle the pin value									  */
/* Input       :	u8PortNum, u8PortMask									  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8ToggleMaskValue(GPIO_tenuPortNum u8PortNum, u8 u8PortMask);

/* ************************************************************************** */
/* Description :    Toggle the pin value									  */
/* Input       :	u8PortNum					 							  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8TogglePortValue(GPIO_tenuPortNum u8PortNum);

/********************************************************************************************************************/

/* ************************************************************************** */
/* Description :  	Enable the pull up res									  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void GPIO_vidEnablePullUp(void);

/* ************************************************************************** */
/* Description :  	Disable the pull up res									  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void GPIO_vidDisablePullUp(void);

/* ************************************************************************** */
/* Description :  	Set the pin pull up res									  */
/* Input       :	u8PortNum, u8PinNum, u8Pullup							  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8SetPinPullUp(GPIO_tenuPortNum u8PortNum,
		GPIO_tenuPinNum u8PinNum, LBTY_tenuFlagStatus u8Pullup);

#endif /* SWC_GPIO_GPIO_INT_H_ */
/*************************** E N D (GPIO_int.h) ******************************/
