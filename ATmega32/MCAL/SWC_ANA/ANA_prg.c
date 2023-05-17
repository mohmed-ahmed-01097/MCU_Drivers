/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : ANA_prg.c													  */
/* Author      : MAAM														  */
/* Version     : v01														  */
/* date        : Apr 30, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LBTY_int.h"
#include "LCTY_int.h"

#include "INTP.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"

#include "ANA_int.h"
#include "ANA_cfg.h"
#include "ANA_priv.h"

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
void (*pvidfunctionCallBack)(void);
/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* Description :  	Initialization of the ANA								  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void ANA_vidInit(void){

	GPIO_u8SetPinDirection(ANA_PORT, ANA_PIN_AIN0, PIN_INPUT);
	GPIO_u8SetPinDirection(ANA_PORT, ANA_PIN_AIN1, PIN_INPUT);

	S_SFIOR->sBits.m_ACME        = LBTY_RESET;
	S_ADC->m_ADCSRA.sBits.m_ADEN = LBTY_RESET;

	S_ADC->m_ACSR.sBits.m_ACD  = LBTY_RESET;	/** Analog Comparator Disable **/
	S_ADC->m_ACSR.sBits.m_ACBG = LBTY_RESET;

	S_ADC->m_ACSR.sBits.m_ACIC = LBTY_SET;

	S_ADC->m_ACSR.sBits.m_ACIS = ANA_INTERRUPT_MODE;
	S_ADC->m_ACSR.sBits.m_ACIE = ANA_INTERRUPT_STATE;
	S_ADC->m_ACSR.sBits.m_ACI  = LBTY_RESET;

	ANA_u8SetNegativeInput(ANA_NEG_INPUT);
	ANA_u8SetPositiveInput(ANA_POS_INPUT);
	S_ADC->m_ACSR.sBits.m_ACO;
}

/* ************************************************************************** */
/* Description :  	Get the Output of Comparator							  */
/* Input       :	pu8Output												  */
/* Return      :	void													  */
/* ************************************************************************** */
void ANA_vidGetOutput(u8* pu8Output){
	*pu8Output = S_ADC->m_ACSR.sBits.m_ACO;
}

/* ************************************************************************** */
/* Description :  	Set negative Input										  */
/* Input       :	u8Input													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus ANA_u8SetNegativeInput(ANA_tenuNegativeInput u8Input){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	switch(u8Input){
		case ANA_ADC0:
		case ANA_ADC1:
		case ANA_ADC2:
		case ANA_ADC3:
		case ANA_ADC4:
		case ANA_ADC5:
		case ANA_ADC6:
		case ANA_ADC7:
			S_SFIOR->sBits.m_ACME = LBTY_SET;
			S_ADC->m_ADCSRA.sBits.m_ADEN = LBTY_RESET;
			S_ADC->m_ACSR.sBits.m_ACIS   = u8Input;
			break;
		case ANA_AIN1:
			S_SFIOR->sBits.m_ACME = LBTY_RESET;
			S_ADC->m_ADCSRA.sBits.m_ADEN = LBTY_RESET;
			break;
		default:	u8RetErrorState = LBTY_NOK;
	}
	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Set positive Input										  */
/* Input       :	u8Input													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus ANA_u8SetPositiveInput(ANA_tenuPositiveInput u8Input){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	switch(u8Input){
		case ANA_AIN0:
			S_ADC->m_ACSR.sBits.m_ACBG = u8Input;
			break;
		case ANA_BANDGAP:
			S_ADC->m_ACSR.sBits.m_ACBG = u8Input;
			break;
		default:	u8RetErrorState = LBTY_NOK;
	}
	return u8RetErrorState;
}


/* ************************************************************************** */
/* Description :  	Pass the CallBack function to ANA ISR to execute		  */
/* Input       :	void													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
void ANA_vidSetCallBack(void (*pvidCallBack)(void)){
	pvidfunctionCallBack = pvidCallBack;
}

/* ************************************************************************** */
/* Description :  	ANA Interrupt 											  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
ISR(ANA_COMP_vect){
	pvidfunctionCallBack();
}

/*************************** E N D (ANA_prg.c) ******************************/
