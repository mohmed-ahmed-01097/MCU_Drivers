/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : SPI_prg.c												  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Apr 12, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */
#include "ATMega32.h"

#include "LBTY_int.h"
#include "LBIT_int.h"

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

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

void SPI_vidInit(void){
	S_SPI->m_SPSR.sBits.m_SPI2X= GET_BIT(SPI_CLOCK_RATE, SPI_SPI2X_BIT);
	S_SPI->m_SPCR.sBits.m_SPR  = GET_MASK(SPI_CLOCK_RATE, SPI_SPR_MASK);
	S_SPI->m_SPCR.sBits.m_CPHA = SPI_CLOCK_PHASE;
	S_SPI->m_SPCR.sBits.m_CPOL = SPI_CLOCK_POLARITY;
	S_SPI->m_SPCR.sBits.m_DORD = SPI_DATA_ORDER;

#ifdef SPI_MASTER
	S_SPI->m_SPCR.sBits.m_MSTR = LBTY_SET;
#else
#ifdef SPI_SLAVE
	S_SPI->m_SPCR.sBits.m_MSTR = LBTY_RESET;
#endif
#endif

	GPIO_u8SetPinDirection(SPI_PORT, SPI_MOSI_PIN, SPI_MOSI_CONFIG);
	GPIO_u8SetPinDirection(SPI_PORT, SPI_MISO_PIN, SPI_MISO_CONFIG);
	GPIO_u8SetPinDirection(SPI_PORT, SPI_SCK_PIN , SPI_SCK_CONFIG );
	GPIO_u8SetPinDirection(SPI_PORT, SPI_SS_PIN  , SPI_SS_CONFIG  );

	S_SPI->m_SPCR.sBits.m_SPIE = SPI_INTI_STATE;
	S_SPI->m_SPCR.sBits.m_SPE  = LBTY_SET;
}

void SPI_vidEnable(void){
	S_SPI->m_SPCR.sBits.m_SPE  = LBTY_SET;
}
void SPI_vidDisable(void){
	S_SPI->m_SPCR.sBits.m_SPE  = LBTY_RESET;
}

void SPI_vidEnableINT(void){
	S_SPI->m_SPCR.sBits.m_SPIE  = LBTY_SET;
}
void SPI_vidDisableINT(void){
	S_SPI->m_SPCR.sBits.m_SPIE  = LBTY_RESET;
}

void SPI_vidMasterSend(u8 u8Char){
	GPIO_u8SetPinValue(SPI_PORT, SPI_SS_PIN, PIN_High);
	S_SPI->m_SPDR = u8Char;
	while(!S_SPI->m_SPSR.sBits.m_SPIF);
	GPIO_u8SetPinValue(SPI_PORT, SPI_SS_PIN, PIN_Low);
}

void SPI_vidMasterReceive(u8* pu8Char){
	GPIO_u8SetPinValue(SPI_PORT, SPI_SS_PIN, PIN_High);
	while(!S_SPI->m_SPSR.sBits.m_SPIF);
	*pu8Char = S_SPI->m_SPDR;
	GPIO_u8SetPinValue(SPI_PORT, SPI_SS_PIN, PIN_Low);
}

void SPI_vidSetChar(u8 u8Char){
	S_SPI->m_SPDR = u8Char;
	while(!S_SPI->m_SPSR.sBits.m_WCOL);
}

void SPI_vidGetChar(u8* pu8Char){
	while(!S_SPI->m_SPSR.sBits.m_SPIF);
	*pu8Char = S_SPI->m_SPDR;
}

/*************************** E N D (SPI_prg.c) ******************************/
