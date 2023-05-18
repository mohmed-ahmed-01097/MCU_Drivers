/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : SPI_int.h													  */
/* Author      : MAAM														  */
/* Version     : v01														  */
/* date        : Apr 12, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef SPI_INT_H_
#define SPI_INT_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

typedef enum{
	SPI_Slave = (u8)0u,
	SPI_Master,
}SPI_tenuMode;

typedef enum{
	SPI_Speed_x1 = (u8)0u,
	SPI_Speed_x2,
}SPI_tenuSpeed;

typedef enum{
	SPI_Prescaler_4 = (u8)0u,
	SPI_Prescaler_16,
	SPI_Prescaler_64,
	SPI_Prescaler_128,
	SPI_Prescaler_2,
	SPI_Prescaler_8,
	SPI_Prescaler_32
}SPI_tenuClockRate;

typedef enum{
	SPI_Leading_Rising = (u8)0u,
	SPI_Leading_Falling,
	SPI_Tralling_Falling = (u8)0u,
	SPI_Tralling_Rising
}SPI_tenuClockPolarity;

typedef enum{
	SPI_Leading_Sample = (u8)0u,
	SPI_Leading_Setup,
	SPI_Tralling_Setup = (u8)0u,
	SPI_Tralling_Sample
}SPI_tenuClockPhase;

typedef enum{
	SPI_MSB_Frist = (u8)0u,
	SPI_LSB_Frist
}SPI_tenuDataOrder;

typedef struct{
//	SPI_tenuMode 			m_Mode;
//	SPI_tenuSpeed			m_Speed;
	SPI_tenuClockRate		m_Prescaler;
	SPI_tenuClockPhase		m_Phase;
	SPI_tenuClockPolarity	m_Polarity;
	SPI_tenuDataOrder		m_Order;

	LBTY_tenuFlagStatus		m_SPIEN;
	LBTY_tenuFlagStatus		m_SPIIE;
}SPI_tstrConfig;

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

void SPI_vidSetConfig(SPI_tstrConfig const* const pstrConfig);
void SPI_vidSRestConfig(SPI_tstrConfig* const pstrConfig);

void SPI_vidInit(void);

void SPI_vidEnable(void);
void SPI_vidDisable(void);

void SPI_vidEnableINT(void);
void SPI_vidDisableINT(void);

LBTY_tenuErrorStatus SPI_vidSetPrescaler(SPI_tenuClockRate u8Prescaler);
LBTY_tenuErrorStatus SPI_vidSetClockPhase(SPI_tenuClockPhase u8Phase);
LBTY_tenuErrorStatus SPI_vidSetClockPolarity(SPI_tenuClockPolarity u8Polarity);
LBTY_tenuErrorStatus SPI_vidSetDataOrder(SPI_tenuDataOrder u8Order);

/********************************************************************************************************************/

LBTY_tenuErrorStatus SPI_u8SetChar(u8 u8Char);
LBTY_tenuErrorStatus SPI_u8GetChar(u8* pu8Char);

void SPI_vidSetStr(u8* pu8Transmit);
void SPI_vidGetStr(u8* pu8Receive);

/********************************************************************************************************************/

void SPI_vidSetCallBack_OverFlow(void (*pCallBack)(void));

#endif /* SPI_INT_H_ */
/*************************** E N D (SPI_int.h) ******************************/
