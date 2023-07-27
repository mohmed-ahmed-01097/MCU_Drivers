/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : SPI_prg.c													  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Apr 12, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LBTY_int.h"
#include "LBIT_int.h"
#include "LCTY_int.h"

#include "INTP.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"

#include "SPI_int.h"
#include "SPI_cfg.h"
#include "SPI_priv.h"

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

static volatile u8 SPI_u8Flag_GLB;

static void (*pFuncCallBack_SPI)(void) = INTP_vidCallBack;

static SPI_tstrConfig strSPI_Config_GLB = {
		.m_Mode 		= SPI_MODE,
		.m_Prescaler	= SPI_CLOCK_PRESCALER,
		.m_Phase		= SPI_CLOCK_PHASE,
		.m_Polarity		= SPI_CLOCK_POLARITY,
		.m_Order 		= SPI_DATA_ORDER,

		.m_SPIEN 		= SPI_INIT,
		.m_SPIIE 		= SPI_INT,
};

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

void SPI_vidSetConfig(SPI_tstrConfig const* const pstrConfig){
	if(pstrConfig != LBTY_NULL){
		strSPI_Config_GLB = *pstrConfig;
	}
	SPI_vidInit();
}

void SPI_vidSRestConfig(SPI_tstrConfig* const pstrConfig){
	strSPI_Config_GLB.m_Mode 		= SPI_MODE;
	strSPI_Config_GLB.m_Prescaler	= SPI_CLOCK_PRESCALER;
	strSPI_Config_GLB.m_Phase		= SPI_CLOCK_PHASE;
	strSPI_Config_GLB.m_Polarity	= SPI_CLOCK_POLARITY;
	strSPI_Config_GLB.m_Order 		= SPI_DATA_ORDER;
	strSPI_Config_GLB.m_SPIEN 		= SPI_INIT;
	strSPI_Config_GLB.m_SPIIE 		= SPI_INT;

	if(pstrConfig != LBTY_NULL){
		*pstrConfig = strSPI_Config_GLB;
	}
	SPI_vidInit();
}

void SPI_vidInit(void){

	S_SPI->m_SPCR.sBits.m_MSTR = strSPI_Config_GLB.m_Mode;
	if(strSPI_Config_GLB.m_Mode == SPI_Master){
		GPIO_u8SetMaskDirection(SPI_PORT, SPI_MODE_MASK, PORT_OUTPUT);
		GPIO_u8SetPinDirection (SPI_PORT, SPI_MISO_PIN , PIN_INPUT  );
		for(u8 i = SPI_SS_NUM ; i-- ; ){
			GPIO_u8SetPinDirection(kastrSSConfiguration_GLB[i].m_Port, kastrSSConfiguration_GLB[i].m_Pin, PIN_OUTPUT);
			GPIO_u8SetPinValue    (kastrSSConfiguration_GLB[i].m_Port, kastrSSConfiguration_GLB[i].m_Pin, SPI_SS_DISABLE);
		}
	}else if(strSPI_Config_GLB.m_Mode == SPI_Slave){
		GPIO_u8SetMaskDirection(SPI_PORT, SPI_MODE_MASK, PORT_INPUT);
		GPIO_u8SetPinDirection (SPI_PORT, SPI_MISO_PIN , PIN_OUTPUT);
	}

	//SPI_vidSetPrescaler(strSPI_Config_GLB.m_Prescaler);
	S_SPI->m_SPSR.sBits.m_SPI2X= GET_BIT(strSPI_Config_GLB.m_Prescaler, SPI_SPI2X_BIT);
	S_SPI->m_SPCR.sBits.m_SPR  = GET_MASK(strSPI_Config_GLB.m_Prescaler, SPI_SPR_MASK);
	//SPI_vidSetClockPhase(strSPI_Config_GLB.m_Phase);
	S_SPI->m_SPCR.sBits.m_CPHA = strSPI_Config_GLB.m_Phase;
	//SPI_vidSetClockPolarity(strSPI_Config_GLB.m_Polarity);
	S_SPI->m_SPCR.sBits.m_CPOL = strSPI_Config_GLB.m_Polarity;
	//SPI_vidSetDataOrder(strSPI_Config_GLB.m_Order);
	S_SPI->m_SPCR.sBits.m_DORD = strSPI_Config_GLB.m_Order;

	S_SPI->m_SPCR.sBits.m_SPIE = strSPI_Config_GLB.m_SPIIE;
	S_SPI->m_SPCR.sBits.m_SPE  = strSPI_Config_GLB.m_SPIEN;
}

void SPI_vidEnable(void){
	S_SPI->m_SPCR.sBits.m_SPE  = strSPI_Config_GLB.m_SPIEN = LBTY_SET;
}
void SPI_vidDisable(void){
	S_SPI->m_SPCR.sBits.m_SPE  = strSPI_Config_GLB.m_SPIEN = LBTY_RESET;
}

void SPI_vidEnableINT(void){
	S_SPI->m_SPCR.sBits.m_SPIE  = strSPI_Config_GLB.m_SPIIE = LBTY_SET;
}
void SPI_vidDisableINT(void){
	S_SPI->m_SPCR.sBits.m_SPIE  = strSPI_Config_GLB.m_SPIIE = LBTY_RESET;
}

LBTY_tenuErrorStatus SPI_vidSetPrescaler(SPI_tenuClockRate u8Prescaler){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	switch(u8Prescaler){
		case SPI_Prescaler_4:
		case SPI_Prescaler_16:
		case SPI_Prescaler_64:
		case SPI_Prescaler_128:
		case SPI_Prescaler_2:
		case SPI_Prescaler_8:
		case SPI_Prescaler_32:
			S_SPI->m_SPSR.sBits.m_SPI2X= GET_BIT(u8Prescaler, SPI_SPI2X_BIT);
			S_SPI->m_SPCR.sBits.m_SPR  = GET_MASK(u8Prescaler, SPI_SPR_MASK);
			strSPI_Config_GLB.m_Prescaler = u8Prescaler;
			break;
		default:
			u8RetErrorState = LBTY_NOK;
	}

	return u8RetErrorState;
}

LBTY_tenuErrorStatus SPI_vidSetClockPhase(SPI_tenuClockPhase u8Phase){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	switch(u8Phase){
		case SPI_Leading_Sample:
		case SPI_Leading_Setup:
			S_SPI->m_SPCR.sBits.m_CPHA = strSPI_Config_GLB.m_Phase = u8Phase;
			break;
		default:
			u8RetErrorState = LBTY_NOK;
	}

	return u8RetErrorState;
}

LBTY_tenuErrorStatus SPI_vidSetClockPolarity(SPI_tenuClockPolarity u8Polarity){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	switch(u8Polarity){
		case SPI_Leading_Rising:
		case SPI_Leading_Falling:
			S_SPI->m_SPCR.sBits.m_CPOL = strSPI_Config_GLB.m_Polarity = u8Polarity;
			break;
		default:
			u8RetErrorState = LBTY_NOK;
	}

	return u8RetErrorState;
}

LBTY_tenuErrorStatus SPI_vidSetDataOrder(SPI_tenuDataOrder u8Order){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	switch(u8Order){
		case SPI_MSB_Frist:
		case SPI_LSB_Frist:
			S_SPI->m_SPCR.sBits.m_DORD = strSPI_Config_GLB.m_Order = u8Order;
			break;
		default:
			u8RetErrorState = LBTY_NOK;
	}

	return u8RetErrorState;
}

/********************************************************************************************************************/

LBTY_tenuErrorStatus SPI_u8SetTransmit(u8 u8Char){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	if(!(S_SPI->m_SPSR.sBits.m_WCOL)){
		S_SPI->m_SPDR = u8Char;
		while((!S_SPI->m_SPSR.sBits.m_SPIF) && (!SPI_u8Flag_GLB));
		SPI_u8Flag_GLB = LBTY_RESET;
	}else{
		u8RetErrorState = LBTY_NOK;
	}

	return u8RetErrorState;
}
LBTY_tenuErrorStatus SPI_u8GetTransmit(u8* pu8Char){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	if(!(S_SPI->m_SPSR.sBits.m_WCOL)){
		while((!S_SPI->m_SPSR.sBits.m_SPIF) && (!SPI_u8Flag_GLB));
		SPI_u8Flag_GLB = LBTY_RESET;
		*pu8Char = S_SPI->m_SPDR;
	}else{
		u8RetErrorState = LBTY_NOK;
	}

	return u8RetErrorState;
}

LBTY_tenuErrorStatus SPI_u8SetChar(u8 u8Char, u8 u8Index){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	if(strSPI_Config_GLB.m_Mode == SPI_Master){

		GPIO_u8SetPinValue(kastrSSConfiguration_GLB[u8Index].m_Port, kastrSSConfiguration_GLB[u8Index].m_Pin,  SPI_SS_ENABLE);
		u8RetErrorState = SPI_u8SetTransmit(u8Char);
		GPIO_u8SetPinValue(kastrSSConfiguration_GLB[u8Index].m_Port, kastrSSConfiguration_GLB[u8Index].m_Pin, SPI_SS_DISABLE);

	}else if(strSPI_Config_GLB.m_Mode == SPI_Slave){

		u8 u8State = SPI_SS_DISABLE;
		GPIO_u8GetPinValue(SPI_PORT, SPI_SS_PIN, &u8State);

		if(u8State == SPI_SS_ENABLE){
			u8RetErrorState = SPI_u8SetTransmit(u8Char);
		}

	}else{
		while(1);
	}

	return u8RetErrorState;
}
LBTY_tenuErrorStatus SPI_u8GetChar(u8* pu8Char, u8 u8Index){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	if(strSPI_Config_GLB.m_Mode == SPI_Master){

		GPIO_u8SetPinValue(kastrSSConfiguration_GLB[u8Index].m_Port, kastrSSConfiguration_GLB[u8Index].m_Pin,  SPI_SS_ENABLE);
		u8RetErrorState = SPI_u8GetTransmit(pu8Char);
		GPIO_u8SetPinValue(kastrSSConfiguration_GLB[u8Index].m_Port, kastrSSConfiguration_GLB[u8Index].m_Pin, SPI_SS_DISABLE);

	}else if(strSPI_Config_GLB.m_Mode == SPI_Slave){

		u8 u8State = SPI_SS_DISABLE;
		GPIO_u8GetPinValue(SPI_PORT, SPI_SS_PIN, &u8State);

		if(u8State == SPI_SS_ENABLE){
			u8RetErrorState = SPI_u8GetTransmit(pu8Char);
		}

	}else{
		while(1);
	}

	return u8RetErrorState;
}

void SPI_vidSetStr(u8* pu8Transmit, u8 u8Index){
	while(*pu8Transmit){
		if(SPI_u8SetChar(*(pu8Transmit++), u8Index)){
			break;
		}
	}
}
void SPI_vidGetStr(u8* pu8Receive, u8 u8Index){
	do{
		if(SPI_u8GetChar(pu8Receive, u8Index)){
			break;
		}
	}while(*(pu8Receive++) != '\0');
}

/********************************************************************************************************************/

void SPI_vidSetCallBack_OverFlow(void (*pCallBack)(void)){
	pFuncCallBack_SPI = pCallBack;
}

ISR(SPI_STC_vect){
	pFuncCallBack_SPI();
	SPI_u8Flag_GLB = LBTY_SET;
}

/*************************** E N D (SPI_prg.c) ******************************/
