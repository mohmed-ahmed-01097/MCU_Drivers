/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : ADC_priv.h												  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Mar 27, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef ADC_PRIV_H_
#define ADC_PRIV_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

typedef enum{
    ADC_Division_Factor_2_DEF = (u8)0u,
    ADC_Division_Factor_2,
    ADC_Division_Factor_4,
    ADC_Division_Factor_8,
    ADC_Division_Factor_16,
    ADC_Division_Factor_32,
    ADC_Division_Factor_64,
    ADC_Division_Factor_128
}ADC_tenuPrescalerSelection;      // ADC Prescaler Selections

typedef enum{
    ADC_Free_Running_Mode = (u8)0u,
	ADC_Analog_Comparator,
	ADC_External_INT0,
	ADC_TMR0_Compare_MatchA,
	ADC_TMR0_Overflew,
	ADC_TMR1_Compare_MatchB,
	ADC_TMR1_Overflew,
	ADC_TMR1_Capture_Event
}ADC_tenuTriggerSource;      // ADC Auto Trigger Source

typedef enum{
    ADC_AREF = (u8)0u,		/* Internal Vref turned off */
	ADC_AVCC,				/* external capacitor at AREF pin */
	RESERVED,
	ADC_INTERNAL_Vref		/* 2.56v with external capacitor at AREF pin */
}ADC_tenuRefSelection;      // ADC Voltage Reference Selections


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


#endif /* ADC_PRIV_H_ */
/*************************** E N D (ADC_priv.h) ******************************/
