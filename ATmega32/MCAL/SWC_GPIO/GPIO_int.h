/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : GPIO_int.h													  */
/* Author      : MAAM														  */
/* Version     : v00														  */
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
	A = (u8)0,
	B,
	C,
	D
}GPIO_PortNum_type;

typedef enum{
    PIN_INPUT = (u8)0u,
	PIN_OUTPUT = (u8)1u,
	PORT_INPUT = (u8)0x00U,
	PORT_OUTPUT = (u8)0xFFU
}GPIO_DataDirection_type;

typedef enum{
    PIN_Low = (u8)0u,
	PIN_High = (u8)1u,
	PORT_Low = (u8)0x00U,
	PORT_High = (u8)0xFFU
}GPIO_DataStatus_type;

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
/* Description :  	Set the pin direction									  */
/* Input       :	u8PortNumm, u8PinNum, u8PinDir							  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8SetPinDirection(GPIO_PortNum_type u8PortNum,
											u8 u8PinNum,
											GPIO_DataDirection_type u8PinDir);

/* ************************************************************************** */
/* Description :    Set the pin value										  */
/* Input       :	u8PortNum, u8PinNum, u8PinValue							  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8SetPinValue(GPIO_PortNum_type u8PortNum,
										u8 u8PinNum,
										GPIO_DataStatus_type u8PinVlaue);

/* ************************************************************************** */
/* Description :    Toggle the pin value									  */
/* Input       :	u8PortNum, u8PinNum, u8PinValue							  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8TogglePinValue(GPIO_PortNum_type u8PortNum, u8 u8PinNum);

/* ************************************************************************** */
/* Description :    Get the pin value 										  */
/* Input       :	u8PortNum, u8PinNum										  */
/* Input/Output:    pu8Value												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8GetPinValue(GPIO_PortNum_type u8PortNum,
										u8 u8PinNum, pu8 pu8Value);

/* ************************************************************************** */
/* Description :    Set the port direction 									  */
/* Input       :	u8PortNum, 	u8PortDir									  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8SetPortDirection(GPIO_PortNum_type u8PortNum,
											 GPIO_DataDirection_type u8PortDir);

/* ************************************************************************** */
/* Description :    Set the port direction 									  */
/* Input       :	u8PortNum, u8PortValue									  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8SetPortValue(GPIO_PortNum_type u8PortNum,
										 GPIO_DataStatus_type u8PortValue);

/* ************************************************************************** */
/* Description :    Get the port value										  */
/* Input       :	u8PortNum												  */
/* Input/Output:    pu8Value  												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus GPIO_u8GetPortValue(GPIO_PortNum_type u8PortNum, pu8 pu8Value);

#endif /* SWC_GPIO_GPIO_INT_H_ */
/*************************** E N D (GPIO_int.h) ******************************/
