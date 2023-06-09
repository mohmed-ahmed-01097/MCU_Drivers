/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : SPI_int.h												  */
/* Author      : MAAM														  */
/* Version     : v00														  */
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

void SPI_vidInit(void);

void SPI_vidEnable(void);
void SPI_vidDisable(void);

void SPI_vidEnableINT(void);
void SPI_vidDisableINT(void);

void SPI_vidMasterSend(u8 u8Char);
void SPI_vidMasterReceive(u8* pu8Char);

#endif /* SPI_INT_H_ */
/*************************** E N D (SPI_int.h) ******************************/
