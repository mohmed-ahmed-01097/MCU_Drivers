/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : SPI_int.h													  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
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

/********************************************************************************************************************/

/** @brief : type define of structure for SPI Configuration                   */
/** <b>Type</b> : struct <b>Unit</b> : None                                   */
typedef struct{
	SPI_tenuMode 			m_Mode;				/*!< SPI Operation Mode */
	SPI_tenuClockRate		m_Prescaler;		/*!< SPI Clock Prescaler */
	SPI_tenuClockPhase		m_Phase;			/*!< SPI Clock Phase */
	SPI_tenuClockPolarity	m_Polarity;			/*!< SPI Clock Polarity */
	SPI_tenuDataOrder		m_Order;			/*!< SPI Data Order */

	LBTY_tenuFlagStatus		m_SPIEN;			/*!< SPI Enable */
	LBTY_tenuFlagStatus		m_SPIIE;			/*!< SPI Interrupt Enable */
}SPI_tstrConfig;

/** @brief : type define of structure for SS Pin Configuration                */
/** <b>Type</b> : struct <b>Unit</b> : None                                   */
typedef struct{
	GPIO_tenuPortNum 		m_Port;				/*!< Port Number */
	GPIO_tenuPinNum			m_Pin;				/*!< Pin Number */
}SPI_tstrSS_Config;

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

extern void SPI_vidSetConfig(SPI_tstrConfig const* const pstrConfig);
extern void SPI_vidSRestConfig(SPI_tstrConfig* const pstrConfig);

extern void SPI_vidInit(void);

extern void SPI_vidEnable(void);
extern void SPI_vidDisable(void);

extern void SPI_vidEnableINT(void);
extern void SPI_vidDisableINT(void);

extern LBTY_tenuErrorStatus SPI_vidSetPrescaler(SPI_tenuClockRate u8Prescaler);
extern LBTY_tenuErrorStatus SPI_vidSetClockPhase(SPI_tenuClockPhase u8Phase);
extern LBTY_tenuErrorStatus SPI_vidSetClockPolarity(SPI_tenuClockPolarity u8Polarity);
extern LBTY_tenuErrorStatus SPI_vidSetDataOrder(SPI_tenuDataOrder u8Order);

/********************************************************************************************************************/

extern LBTY_tenuErrorStatus SPI_u8SetTransmit(u8 u8Char);
extern LBTY_tenuErrorStatus SPI_u8GetTransmit(u8* pu8Char);

extern LBTY_tenuErrorStatus SPI_u8SetChar(u8 u8Char, u8 u8Index);
extern LBTY_tenuErrorStatus SPI_u8GetChar(u8* pu8Char, u8 u8Index);

extern void SPI_vidSetStr(u8* pu8Transmit, u8 u8Index);
extern void SPI_vidGetStr(u8* pu8Receive, u8 u8Index);

/********************************************************************************************************************/

extern void SPI_vidSetCallBack_OverFlow(void (*pCallBack)(void));

#endif /* SPI_INT_H_ */
/*************************** E N D (SPI_int.h) ******************************/
