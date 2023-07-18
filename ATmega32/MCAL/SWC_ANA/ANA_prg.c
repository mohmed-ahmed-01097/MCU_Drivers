/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : ANA_prg.c													  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
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
void (*pvidfunctionCallBack)(void) = INTP_vidCallBack;
/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* Description :  	Initialization of the ANA								  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void ANA_vidInit(void){

	ANA_u8SetPositiveInput(ANA_POS_INPUT);
	ANA_u8SetNegativeInput(ANA_NEG_INPUT);

	S_ADC->m_ACSR.sBits.m_ACD  = LBTY_RESET;	/** Analog Comparator Disable **/

	S_ADC->m_ACSR.sBits.m_ACIC = LBTY_RESET;

	S_ADC->m_ACSR.sBits.m_ACIS = ANA_INTERRUPT_MODE;
	S_ADC->m_ACSR.sBits.m_ACIE = ANA_INTERRUPT_STATE;
	S_ADC->m_ACSR.sBits.m_ACI  = LBTY_RESET;

}

/********************************************************************************************************************/

/* ************************************************************************** */
/* Description :  	Enable ANA to be ready for conversion					  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void ANA_vidEnable(void){
	S_ADC->m_ACSR.sBits.m_ACD  = LBTY_RESET;	/** Analog Comparator Disable **/
}

/* ************************************************************************** */
/* Description :  	Disable ANA to be wont make further conversions			  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void ANA_vidDisable(void){
	S_ADC->m_ACSR.sBits.m_ACD  = LBTY_SET;	/** Analog Comparator Disable **/
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
			S_SFIOR->sBits.m_ACME        = LBTY_SET;
			S_ADC->m_ADCSRA.sBits.m_ADEN = LBTY_RESET;
			S_ADC->m_ADMUX.sBits.m_MUX   = u8Input;

			GPIO_u8SetPinDirection(ADC_PORT, u8Input, PIN_INPUT);
			break;
		case ANA_AIN1:
			S_SFIOR->sBits.m_ACME        = LBTY_SET;
			S_ADC->m_ADCSRA.sBits.m_ADEN = LBTY_SET;

			GPIO_u8SetPinDirection(ANA_PORT, ANA_PIN_AIN1, PIN_INPUT);
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
			GPIO_u8SetPinDirection(ANA_PORT, ANA_PIN_AIN0, PIN_INPUT);
			S_ADC->m_ACSR.sBits.m_ACBG = u8Input;
			break;
		case ANA_BANDGAP:
			//GPIO_u8SetPinDirection(ADC_PORT, u8PosChannel, PIN_INPUT);
			S_ADC->m_ACSR.sBits.m_ACBG = u8Input;
			break;
		default:	u8RetErrorState = LBTY_NOK;
	}
	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Set Interrupt Mode										  */
/* Input       :	u8Mode													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus ANA_u8SetMode(ANA_tenuModeSelect u8Mode){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	switch(u8Mode){
		case ANA_OutputToggle:
		case ANA_OutputFallingEdge:
		case ANA_OutputRisingEdge:
			S_ADC->m_ACSR.sBits.m_ACIS = u8Mode;
			break;
		default:	u8RetErrorState = LBTY_NOK;
	}
	return u8RetErrorState;
}

/********************************************************************************************************************/

/* ************************************************************************** */
/* Description :  	Enable ANA Interrupt									  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void ANA_vidEnableINT(void){
	S_ADC->m_ACSR.sBits.m_ACIE  = LBTY_SET;
}

/* ************************************************************************** */
/* Description :  	Disable ANA Interrupt									  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void ANA_vidDisableINT(void){
	S_ADC->m_ACSR.sBits.m_ACIE = LBTY_RESET;
}

/* ************************************************************************** */
/* Description :  	Clear ANA interrupt Flag								  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void ANA_vidClrFlagINT(void){
	S_ADC->m_ACSR.sBits.m_ACI  = LBTY_RESET;
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
