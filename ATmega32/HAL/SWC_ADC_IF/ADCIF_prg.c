/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : ADCIF_prg.c												  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Jul 19, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LBTY_int.h"

#include "ADC_int.h"
#include "ADC_cfg.h"

#include "ADCIF_int.h"
#include "ADCIF_cfg.h"
#include "ADCIF_priv.h"

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

/* ************************************************************************** */
/* Description :  	Initialization of the Sensors 							  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void SENSOR_vidInit(void){
	ADC_vidInit();
}

/* ************************************************************************** */
/* Description :  	Get Sensors Read										  */
/* Input/Output:    paf32Read												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus SENSOR_u8GetData(f32* paf32Read){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	for(u8 i = SENSOR_NUM ; i-- && (u8RetErrorState == LBTY_OK) ; ){
		u8RetErrorState = SENSOR_u8GetChannel(i, paf32Read + i);
	}
	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Get Sensor Read 										  */
/* Input/Output:    pf32Read												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus SENSOR_u8GetChannel(u8 u8Num, f32* pf32Read){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	const SENSOR_tstrConfig* pstrSensor = (const SENSOR_tstrConfig*)&katstrSensorConfig_GLB[u8Num];
	u8RetErrorState = ADC_u8StartRead(pstrSensor->m_Channel);
	if(u8RetErrorState == LBTY_OK){
		ADC_vidWaitConversion();
		*pf32Read = (f32)(ADC_f32GetVoltage()
				* (pstrSensor->m_MaxValue - pstrSensor->m_MinValue) / (f32)ADC_V_REF) + pstrSensor->m_MinValue;
	}
	return u8RetErrorState;
}


/*************************** E N D (ADCIF_prg.c) ******************************/
