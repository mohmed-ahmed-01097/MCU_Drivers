/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : ADC_prg.c													  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Mar 26, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LBTY_int.h"
#include "LBIT_int.h"
#include "LCTY_int.h"

#include "INTP.h"

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

static u8 au8ChannelValue_LGB [ADC_Num];

static u8 u8ConvDone_GLB = LBTY_SET;
static f32 f32V_REF = ADC_V_REF;

static void (*pvidFunctionCallBack)(void) = INTP_vidCallBack;

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

static void vid_AdcSyncRead(void){
	static u8 u8Channel = LBTY_u8ZERO;

	if (u8Channel < ADC_Num){

		u8ConvDone_GLB = LBTY_RESET;

		au8ChannelValue_LGB[u8Channel++] = (u16)S_ADC->m_ADC;

		while(ADC_u8StartRead(u8Channel));

	}else{

		ADC_u16RefreshADC();
		u8Channel = LBTY_u8ZERO;
		u8ConvDone_GLB = LBTY_SET;
	}
}

/* ************************************************************************** */
/* Description :  	Initialization of the ADC								  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void ADC_vidInit(void){

	for(u8 i = ADC_Num; i-- ; ){
		ADC_u8CofigChannel(kau8ActiveChannel_LGB[i]);
	}

	S_SFIOR->sBits.m_ADTS = ADC_TRIG_SRC;

	S_ADC->m_ADCSRA.sBits.m_ADEN  = LBTY_SET;
	S_ADC->m_ADCSRA.sBits.m_ADSC  = LBTY_RESET;
	S_ADC->m_ADCSRA.sBits.m_ADATE = ADC_AUTO_TRIG;
	S_ADC->m_ADCSRA.sBits.m_ADIE  = ADC_IRQ_STATE;
	S_ADC->m_ADCSRA.sBits.m_ADIF  = LBTY_SET;	/** Clear complete flag by writing logic one **/
	S_ADC->m_ADCSRA.sBits.m_ADPS  = ADC_PRESCALER;
	ADC_vidSetCallBack(vid_AdcSyncRead);

	S_ADC->m_ADMUX.sBits.m_REFS  = ADC_V_REF_SRC;
	S_ADC->m_ADMUX.sBits.m_ADLAR = ADC_ADJUSTMENT;
	S_ADC->m_ADMUX.sBits.m_MUX   = ADC0;

	// first conversion will take 25 ADC clock cycles instead of the normal 13.
	S_ADC->m_ADCSRA.sBits.m_ADSC  = LBTY_SET;
	while(S_ADC->m_ADCSRA.sBits.m_ADSC);

	ADC_vidCalibrate();

	S_ADC->m_ADCSRA.sBits.m_ADEN  = ADC_INIT_STATE;

}

/* ************************************************************************** */
/* Description :  	Configuration of the Channel							  */
/* Input       :	u8Channel												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus ADC_u8CofigChannel(ADC_tenuChannel u8Channel){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	if(IS_CHANNEL(u8Channel)){
		u8RetErrorState = GPIO_u8SetPinDirection(ADC_PORT, u8Channel, PIN_INPUT);
	}else{
		u8RetErrorState = LBTY_NOK;
	}
	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Calibrate ADC Voltage 									  */
/* Input       :	void													  */
/* Return      :	void 													  */
/* ************************************************************************** */
void ADC_vidCalibrate(void){
	ADC_u8SetChannel(VBG_1V22);
	ADC_vidStartConversion();
	ADC_vidWaitConversion();

	f32V_REF = (f32)(ADC_VBG_1V22 * ADC_MAX) / ADC_u16GetData();
	ADC_u8SetChannel(ADC0);
}

/********************************************************************************************************************/

/* ************************************************************************** */
/* Description :  	Enable ADC to be ready for conversion					  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void ADC_vidEnable(void){
	S_ADC->m_ADCSRA.sBits.m_ADEN  = LBTY_SET;
}

/* ************************************************************************** */
/* Description :  	Disable ADC to be wont make further conversions			  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void ADC_vidDisable(void){
	S_ADC->m_ADCSRA.sBits.m_ADEN  = LBTY_RESET;
}

/* ************************************************************************** */
/* Description :  	Enable ADC Auto Trigger									  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void ADC_vidAutoTriggerEnable(void){
	S_ADC->m_ADCSRA.sBits.m_ADATE = LBTY_RESET;
}

/* ************************************************************************** */
/* Description :  	Disable ADC Auto Trigger								  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void ADC_vidAutoTriggerDisable(void){
	S_ADC->m_ADCSRA.sBits.m_ADATE = LBTY_RESET;
}

/* ************************************************************************** */
/* Description :  	Set Auto Trigger Source									  */
/* Input       :	u8Source												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus ADC_u8SetAutoTriggerSource(ADC_tenuTriggerSource u8Source){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	switch(u8Source){
		case ADC_Free_Running_Mode:
		case ADC_Analog_Comparator:
		case ADC_External_INT0:
		case ADC_TMR0_Compare_MatchA:
		case ADC_TMR0_Overflew:
		case ADC_TMR1_Compare_MatchB:
		case ADC_TMR1_Overflew:
		case ADC_TMR1_Capture_Event:
			S_SFIOR->sBits.m_ADTS  = u8Source;
			break;
		default:
			u8RetErrorState = LBTY_NOK;
	}

	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Set ADC Prescaler										  */
/* Input       :	u8Prescaler												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus ADC_u8SetPrescaler(ADC_tenuPrescalerSelection u8Prescaler){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	switch(u8Prescaler){
		case ADC_Division_Factor_2_DEF:
		case ADC_Division_Factor_2:
		case ADC_Division_Factor_4:
		case ADC_Division_Factor_8:
		case ADC_Division_Factor_16:
		case ADC_Division_Factor_32:
		case ADC_Division_Factor_64:
		case ADC_Division_Factor_128:
			S_ADC->m_ADCSRA.sBits.m_ADPS  = u8Prescaler;
			break;
		default:
			u8RetErrorState = LBTY_NOK;
	}

	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Set V_Ref												  */
/* Input       :	u8Vref													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus ADC_u8SetV_REF(ADC_tenuRefSelection u8Vref){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	switch(u8Vref){
		case ADC_AREF:
		case ADC_AVCC:
		case ADC_INTERNAL_Vref:
			S_ADC->m_ADMUX.sBits.m_REFS  = u8Vref;
			break;
		default:
			u8RetErrorState = LBTY_NOK;
	}

	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Set Channel												  */
/* Input       :	u8Channel												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus ADC_u8SetChannel(ADC_tenuChannel u8Channel){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	if((u8)u8Channel < ADC_ChannelMux){
		S_ADC->m_ADMUX.sBits.m_MUX = u8Channel;
	}else{
		u8RetErrorState = LBTY_NOK;
	}

	return u8RetErrorState;
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
	return (f32)((u16)S_ADC->m_ADC * f32V_REF) / ADC_MAX;
}

/********************************************************************************************************************/

/* ************************************************************************** */
/* Description :  	start ADC Read of the channel							  */
/* Input       :	u8Channel												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus ADC_u8StartRead(ADC_tenuChannel u8Channel){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	if((u8)u8Channel < ADC_ChannelMux){
		S_ADC->m_ADMUX.sBits.m_MUX = u8Channel;
	}else{
		u8RetErrorState = LBTY_NOK;
	}

	S_ADC->m_ADCSRA.sBits.m_ADSC = LBTY_SET;

	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Get the ADC Read of the channel							  */
/* Input       :	u8Channel												  */
/* Input/Output:    pu16ADC_Value											  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus ADC_u8ReadChannel(ADC_tenuChannel u8Channel, u16* pu16ADC_Value){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	if(pu16ADC_Value == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else{
		if((u8)u8Channel < ADC_ChannelMux){
			S_ADC->m_ADMUX.sBits.m_MUX = u8Channel;
		}else{
			u8RetErrorState = LBTY_NOK;
		}

		S_ADC->m_ADCSRA.sBits.m_ADSC = LBTY_SET;

		while(S_ADC->m_ADCSRA.sBits.m_ADSC);

		//vidMyDelay_ms(ADC_READ_DELAY);

		//while(!S_ADC->m_ADCSRA.sBits.m_ADIF);		S_ADC->m_ADCSRA.sBits.m_ADIF = LBTY_RESET;

		*pu16ADC_Value = (u16)S_ADC->m_ADC;
	}
	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Get the ADC Read from Conversion Array					  */
/* Input       :	u8Channel												  */
/* Input/Output:    pu16ADC_Value											  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus ADC_u8ReadConvValue(u8 u8Channel, u16* pu16ADC_Value){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	if(pu16ADC_Value == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else{
		for(u8 i = 0 ; i<ADC_Num ; i++){
			if(u8Channel == kau8ActiveChannel_LGB[i]){
				*pu16ADC_Value = au8ChannelValue_LGB[i];
				break;
			}else{
				u8RetErrorState = LBTY_NOK;
			}
		}
	}
	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Start the ADC Interrupt Conversion						  */
/* Input       :	void													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus ADC_u16RefreshADC(void){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	if(u8ConvDone_GLB == LBTY_SET){
		u8ConvDone_GLB = LBTY_RESET;
		S_ADC->m_ADCSRA.sBits.m_ADIE  = LBTY_SET;
		S_ADC->m_ADCSRA.sBits.m_ADIF  = LBTY_SET;	/** Clear complete flag by writing logic one **/
		u8RetErrorState = ADC_u8StartRead(*kau8ActiveChannel_LGB);
	}else{
		u8RetErrorState = LBTY_IN_PROGRESS;
	}
	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Get the ADC Interrupt Conversion						  */
/* Input       :	pu16ADC_Value											  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus ADC_u16GetAll(u16 pu16ADC_Value[]){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	if(u8ConvDone_GLB == LBTY_SET){
		S_ADC->m_ADCSRA.sBits.m_ADIE  = LBTY_RESET;
		S_ADC->m_ADCSRA.sBits.m_ADIF  = LBTY_SET;		/** Clear complete flag by writing logic one **/
		for(u8 i = 0 ; i<ADC_Num ; i++){
			pu16ADC_Value[i] = au8ChannelValue_LGB[i];
		}
	}else{
		u8RetErrorState = LBTY_IN_PROGRESS;
	}
	return u8RetErrorState;
}

/********************************************************************************************************************/

/* ************************************************************************** */
/* Description :  	Enable ADC Interrupt									  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void ADC_vidEnableINT(void){
	S_ADC->m_ADCSRA.sBits.m_ADIE  = LBTY_SET;
}

/* ************************************************************************** */
/* Description :  	Disable ADC Interrupt									  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void ADC_vidDisableINT(void){
	S_ADC->m_ADCSRA.sBits.m_ADIE  = LBTY_RESET;
}

/* ************************************************************************** */
/* Description :  	Clear ADC interrupt Flag								  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void ADC_vidClrFlagINT(void){
	S_ADC->m_ADCSRA.sBits.m_ADIF  = LBTY_SET;		/** Clear complete flag by writing logic one **/
}

/* ************************************************************************** */
/* Description :  	Pass the CallBack function to TMR ISR to execute		  */
/* Input       :	void													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
void ADC_vidSetCallBack(void (*pvidCallBack)(void)){
	pvidFunctionCallBack = pvidCallBack;
}

/* ************************************************************************** */
/* Description :  	ADC Interrupt 											  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
ISR(ADC_vect){
	pvidFunctionCallBack();		//call back function
}

/*************************** E N D (ADC_prg.c) ******************************/
