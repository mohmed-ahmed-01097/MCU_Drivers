/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : ADC_prg.c												  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Mar 26, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */
#define ADC_ADJUSTMENT	(0u)
#include "ATMega32.h"

#include "LBTY_int.h"
#include "LBIT_int.h"

#include "GPIO_int.h"

#include "ADC_int.h"
#include "ADC_cfg.h"
#include "ADC_priv.h"

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

extern u8 pu8ActiveChannel_LGB[ADC_CHANNELS_NUM];
static u8 pu8ChannelValue_LGB [ADC_CHANNELS_NUM];

u8 u8ConvDone_GLB = LBTY_SET;

static void (*pvidFunctionCallBack)(void);

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* Description :  	Initialization of the ADC								  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void ADC_vidInit(void){

	S_SFIOR->sBits.m_ADTS = ADC_TRIG_SRC;

	S_ADC->m_ADCSRA.sBits.m_ADEN  = LBTY_SET;
	S_ADC->m_ADCSRA.sBits.m_ADSC  = LBTY_RESET;
	S_ADC->m_ADCSRA.sBits.m_ADATE = ADC_AUTO_TRIG;
	S_ADC->m_ADCSRA.sBits.m_ADIE  = LBTY_RESET;
	S_ADC->m_ADCSRA.sBits.m_ADIF  = LBTY_RESET;
	S_ADC->m_ADCSRA.sBits.m_ADPS  = ADC_PRESCALER;

	S_ADC->m_ADMUX.sBits.m_REFS  = ADC_V_REF_SRC;
	S_ADC->m_ADMUX.sBits.m_ADLAR = ADC_ADJUSTMENT;
	S_ADC->m_ADMUX.sBits.m_MUX   = ADC0;

	// first conversion will take 25 ADC clock cycles instead of the normal 13.
	S_ADC->m_ADCSRA.sBits.m_ADSC  = LBTY_SET;
	while(S_ADC->m_ADCSRA.sBits.m_ADSC);
	S_ADC->m_ADCSRA.sBits.m_ADEN  = ADC_INIT_STATE;

}

/* ************************************************************************** */
/* Description :  	Configuration of the Channel							  */
/* Input       :	u8Channel												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus ADC_vidCofigChannel(u8 u8Channel){
	LBTY_tenuErrorStatus u8RetValue = LBTY_OK;

	switch(u8Channel){
		case ADC0:	u8RetValue = GPIO_u8SetPinDirection(ADC_PORT, ADC0, PIN_INPUT);	break;
		case ADC1:	u8RetValue = GPIO_u8SetPinDirection(ADC_PORT, ADC1, PIN_INPUT);	break;
		case ADC2:	u8RetValue = GPIO_u8SetPinDirection(ADC_PORT, ADC2, PIN_INPUT);	break;
		case ADC3:	u8RetValue = GPIO_u8SetPinDirection(ADC_PORT, ADC3, PIN_INPUT);	break;
		case ADC4:	u8RetValue = GPIO_u8SetPinDirection(ADC_PORT, ADC4, PIN_INPUT);	break;
		case ADC5:	u8RetValue = GPIO_u8SetPinDirection(ADC_PORT, ADC5, PIN_INPUT);	break;
		case ADC6:	u8RetValue = GPIO_u8SetPinDirection(ADC_PORT, ADC6, PIN_INPUT);	break;
		case ADC7:	u8RetValue = GPIO_u8SetPinDirection(ADC_PORT, ADC7, PIN_INPUT);	break;
		default  :	u8RetValue = LBTY_NOK;
	}
	return u8RetValue;
}

/* ************************************************************************** */
/* Description :  	Enable ADC to be ready for conversion					  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void ADC_voidEnable(void){
	S_ADC->m_ADCSRA.sBits.m_ADEN  = LBTY_SET;
}

/* ************************************************************************** */
/* Description :  	Disable ADC to be wont make further conversions			  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void ADC_voidDisable(void){
	S_ADC->m_ADCSRA.sBits.m_ADEN  = LBTY_RESET;
}

/* ************************************************************************** */
/* Description :  	Set Channel												  */
/* Input       :	u8Channel												  */
/* Return      :	void													  */
/* ************************************************************************** */
void ADC_vidSetChannel(u8 u8Channel){
	S_ADC->m_ADMUX.sBits.m_MUX = u8Channel;
}

/* ************************************************************************** */
/* Description :  	Start conversion										  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void ADC_vidStartConversion(void){
	S_ADC->m_ADCSRA.sBits.m_ADSC = LBTY_SET;
}

/* ************************************************************************** */
/* Description :  	wait conversion	done									  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void ADC_vidWaitConversion(void){
	while(S_ADC->m_ADCSRA.sBits.m_ADSC);
}

/* ************************************************************************** */
/* Description :  	Get ADC Read											  */
/* Input       :	void													  */
/* Return      :	u16														  */
/* ************************************************************************** */
u16 ADC_u16GetData(void){
	return (u16)S_ADC->m_ADC;
}

/* ************************************************************************** */
/* Description :  	Get ADC Read V											  */
/* Input       :	void													  */
/* Return      :	f32														  */
/* ************************************************************************** */
f32 ADC_f32GetVoltage(void){
	return (f32)ADC_u16GetData() * ADC_V_FACTOR;
}

/* ************************************************************************** */
/* Description :  	start ADC Read of the channel							  */
/* Input       :	u8Channel												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus ADC_u8StartRead(u8 u8Channel){
	LBTY_tenuErrorStatus u8RetValue = LBTY_OK;

	switch(u8Channel){
		case ADC0:	S_ADC->m_ADMUX.sBits.m_MUX = ADC0;		break;
		case ADC1:	S_ADC->m_ADMUX.sBits.m_MUX = ADC1;		break;
		case ADC2:	S_ADC->m_ADMUX.sBits.m_MUX = ADC2;		break;
		case ADC3:	S_ADC->m_ADMUX.sBits.m_MUX = ADC3;		break;
		case ADC4:	S_ADC->m_ADMUX.sBits.m_MUX = ADC4;		break;
		case ADC5:	S_ADC->m_ADMUX.sBits.m_MUX = ADC5;		break;
		case ADC6:	S_ADC->m_ADMUX.sBits.m_MUX = ADC6;		break;
		case ADC7:	S_ADC->m_ADMUX.sBits.m_MUX = ADC7;		break;
		default  :	S_ADC->m_ADMUX.sBits.m_MUX = ADC0;		u8RetValue = LBTY_NOK;
	}
	S_ADC->m_ADCSRA.sBits.m_ADSC = LBTY_SET;

	return u8RetValue;
}

/* ************************************************************************** */
/* Description :  	Get the ADC Read of the channel							  */
/* Input       :	u8Channel												  */
/* Input/Output:    pu16ADC_Value											  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus ADC_u8ReadChannel(u8 u8Channel, u16* pu16ADC_Value){
	LBTY_tenuErrorStatus u8RetValue = ADC_u8StartRead(u8Channel);

	while(S_ADC->m_ADCSRA.sBits.m_ADSC);

	//vidMyDelay_ms(ADC_READ_DELAY);

	//while(!S_ADC->m_ADCSRA.sBits.m_ADIF);		S_ADC->m_ADCSRA.sBits.m_ADIF = LBTY_RESET;

	*pu16ADC_Value = (u16)S_ADC->m_ADC;
	return u8RetValue;
}


/* ************************************************************************** */
/* Description :  	Get the ADC Read from Conversion Array					  */
/* Input       :	u8Channel												  */
/* Input/Output:    pu16ADC_Value											  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus ADC_u8ReadConvValue(u8 u8Channel, u16* pu16ADC_Value){
	LBTY_tenuErrorStatus u8RetValue = LBTY_OK;

	for(u8 i = 0 ; i<ADC_CHANNELS_NUM ; i++){
		if(u8Channel == pu8ActiveChannel_LGB[i]){
			*pu16ADC_Value = pu8ChannelValue_LGB[i];
			u8RetValue = LBTY_OK;
			break;
		}else{
			u8RetValue = LBTY_NOK;
		}
	}
	return u8RetValue;
}

/* ************************************************************************** */
/* Description :  	Start the ADC Interrupt Conversion						  */
/* Input       :	void													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus ADC_u16RefreshADC(void){
	LBTY_tenuErrorStatus u8RetValue = LBTY_OK;

	if(u8ConvDone_GLB == LBTY_SET){
		u8ConvDone_GLB = LBTY_RESET;
		S_ADC->m_ADCSRA.sBits.m_ADIE  = LBTY_SET;
		S_ADC->m_ADCSRA.sBits.m_ADIF  = LBTY_RESET;
		u8RetValue = ADC_u8StartRead(*pu8ActiveChannel_LGB);
	}else{
		u8RetValue = LBTY_NOK;
	}
	return u8RetValue;
}

/* ************************************************************************** */
/* Description :  	Get the ADC Interrupt Conversion						  */
/* Input       :	pu16ADC_Value											  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus ADC_u16GetADC(u16 pu16ADC_Value[ADC_CHANNELS_NUM]){
	LBTY_tenuErrorStatus u8RetValue = LBTY_OK;

	if(u8ConvDone_GLB == LBTY_SET){
		for(u8 i = 0 ; i<ADC_CHANNELS_NUM ; i++){
			pu16ADC_Value[i] = pu8ChannelValue_LGB[i];
		}
		S_ADC->m_ADCSRA.sBits.m_ADIE  = LBTY_RESET;
		S_ADC->m_ADCSRA.sBits.m_ADIF  = LBTY_RESET;
	}else{
		u8RetValue = LBTY_NOK;
	}
	return u8RetValue;
}

/* ************************************************************************** */
/* Description :  	Pass the CallBack function to TMR ISR to execute		  */
/* Input       :	void													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
void Timer_vidSetCallBack(void (*pvidCallBack)(void)){
	pvidFunctionCallBack = pvidCallBack;
}

/* ************************************************************************** */
/* Description :  	ADC Interrupt 											  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void __vector_16 (void) __attribute__((signal));
void __vector_16 (void){
	static u8 u8Channel = LBTY_u8ZERO;

	if (u8Channel < ADC_CHANNELS_NUM){

		u8ConvDone_GLB = LBTY_RESET;

		pu8ChannelValue_LGB[u8Channel++] = (u16)S_ADC->m_ADC;

		while(ADC_u8StartRead(u8Channel) != LBTY_OK);

	}else{

		pvidFunctionCallBack();		//call back function

		u8Channel = LBTY_u8ZERO;
		u8ConvDone_GLB = LBTY_SET;
	}
}

/*************************** E N D (ADC_prg.c) ******************************/
