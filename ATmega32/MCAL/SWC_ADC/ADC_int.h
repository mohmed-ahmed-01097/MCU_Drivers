/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : ADC_int.h													  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Mar 27, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef ADC_INT_H_
#define ADC_INT_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

typedef enum{
/** Analog Channels **/
    ADC0 = (u8)0u,
    ADC1,
    ADC2,
    ADC3,
    ADC4,
    ADC5,
    ADC6,
    ADC7,
/** Analog Amplifier **/
	ADC0_ADC0_10X,
	ADC1_ADC0_10X,
	ADC0_ADC0_200X,
	ADC1_ADC0_200X,
	ADC2_ADC2_10X,
	ADC3_ADC2_10X,
	ADC2_ADC2_200X,
	ADC3_ADC2_200X,
/** Analog Comparator with ADC1 **/
	ADC0_ADC1_1X,
	ADC1_ADC1_1X,
	ADC2_ADC1_1X,
	ADC3_ADC1_1X,
	ADC4_ADC1_1X,
	ADC5_ADC1_1X,
	ADC6_ADC1_1X,
	ADC7_ADC1_1X,
/** Analog Comparator with ADC1 **/
	ADC0_ADC2_1X,
	ADC1_ADC2_1X,
	ADC2_ADC2_1X,
	ADC3_ADC2_1X,
	ADC4_ADC2_1X,
	ADC5_ADC2_1X,
/** Constant Voltage **/
	VBG_1V22,
	GND,
	ADC_ChannelMux
}ADC_tenuChannel;      // ADC Channel Selection

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
    ADC_AREF = (u8)0u,		/*!< Internal Vref turned off */
	ADC_AVCC,				/*!< external capacitor at AREF pin */
	RESERVED,
	ADC_INTERNAL_Vref		/*!< 2.56v with external capacitor at AREF pin */
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

/* ************************************************************************** */
/* Description :  	Initialization of the ADC								  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
extern void ADC_vidInit(void);

/* ************************************************************************** */
/* Description :  	Configuration of the Channel							  */
/* Input       :	u8Channel												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
extern LBTY_tenuErrorStatus ADC_u8CofigChannel(ADC_tenuChannel u8Channel);

/* ************************************************************************** */
/* Description :  	Calibrate ADC Voltage 									  */
/* Input       :	void													  */
/* Return      :	void 													  */
/* ************************************************************************** */
extern void ADC_vidCalibrate(void);

/* ************************************************************************** */
/* Description :  	Enable ADC to be ready for conversion					  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
extern void ADC_vidEnable(void);

/* ************************************************************************** */
/* Description :  	Disable ADC to be wont make further conversions			  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
extern void ADC_vidDisable(void);

/* ************************************************************************** */
/* Description :  	Enable ADC Auto Trigger									  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
extern void ADC_vidAutoTriggerEnable(void);

/* ************************************************************************** */
/* Description :  	Disable ADC Auto Trigger								  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
extern void ADC_vidAutoTriggerDisable(void);

/* ************************************************************************** */
/* Description :  	Set Auto Trigger Source									  */
/* Input       :	u8Source												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
extern LBTY_tenuErrorStatus ADC_u8SetAutoTriggerSource(ADC_tenuTriggerSource u8Source);

/* ************************************************************************** */
/* Description :  	Set ADC Prescaler										  */
/* Input       :	u8Prescaler												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
extern LBTY_tenuErrorStatus ADC_u8SetPrescaler(ADC_tenuPrescalerSelection u8Prescaler);

/* ************************************************************************** */
/* Description :  	Set V_Ref												  */
/* Input       :	u8Vref													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
extern LBTY_tenuErrorStatus ADC_u8SetV_REF(ADC_tenuRefSelection u8Vref);

/* ************************************************************************** */
/* Description :  	Set Channel												  */
/* Input       :	u8Channel												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
extern LBTY_tenuErrorStatus ADC_u8SetChannel(ADC_tenuChannel u8Channel);

/* ************************************************************************** */
/* Description :  	Start conversion										  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
extern void ADC_vidStartConversion(void);

/* ************************************************************************** */
/* Description :  	wait conversion	done									  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
extern void ADC_vidWaitConversion(void);

/* ************************************************************************** */
/* Description :  	Get ADC Read											  */
/* Input       :	void													  */
/* Return      :	u16														  */
/* ************************************************************************** */
extern u16 ADC_u16GetData(void);

/* ************************************************************************** */
/* Description :  	Get ADC Read V											  */
/* Input       :	void													  */
/* Return      :	f32														  */
/* ************************************************************************** */
extern f32 ADC_f32GetVoltage(void);

/* ************************************************************************** */
/* Description :  	start ADC Read of the channel							  */
/* Input       :	u8Channel												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
extern LBTY_tenuErrorStatus ADC_u8StartRead(ADC_tenuChannel u8Channel);

/* ************************************************************************** */
/* Description :  	Get the ADC Read of the channel							  */
/* Input       :	u8Channel												  */
/* Input/Output:    pu16ADC_Value											  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
extern LBTY_tenuErrorStatus ADC_u8ReadChannel(ADC_tenuChannel u8Channel, u16* pu16ADC_Value);

/* ************************************************************************** */
/* Description :  	Get the ADC Read from Conversion Array					  */
/* Input       :	u8Channel												  */
/* Input/Output:    pu16ADC_Value											  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
extern LBTY_tenuErrorStatus ADC_u8ReadConvValue(u8 u8Channel, u16* pu16ADC_Value);

/* ************************************************************************** */
/* Description :  	Start the ADC Interrupt Conversion						  */
/* Input       :	void													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
extern LBTY_tenuErrorStatus ADC_u16RefreshADC(void);

/* ************************************************************************** */
/* Description :  	Get the ADC Interrupt Conversion						  */
/* Input       :	pu16ADC_Value											  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
extern LBTY_tenuErrorStatus ADC_u16GetAll(u16 pu16ADC_Value[]);

/********************************************************************************************************************/

/* ************************************************************************** */
/* Description :  	Enable ADC Interrupt									  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
extern void ADC_vidEnableINT(void);

/* ************************************************************************** */
/* Description :  	Disable ADC Interrupt									  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
extern void ADC_vidDisableINT(void);

/* ************************************************************************** */
/* Description :  	Clear ADC interrupt Flag								  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
extern void ADC_vidClrFlagINT(void);

/* ************************************************************************** */
/* Description :  	Pass the CallBack function to TMR ISR to execute		  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
extern void ADC_vidSetCallBack(void (*pvidCallBack)(void));


#endif /* ADC_INT_H_ */
/*************************** E N D (ADC_int.h) ******************************/
