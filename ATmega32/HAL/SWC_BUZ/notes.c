/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : notes.c													  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Sep 3, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LBTY_int.h"
#include "LCTY_int.h"
#include "DELAY.h"
#include "notes.h"
#include "TMR_int.h"

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */
#define TMRx_INIT		TMR1_vidInit
//#define TMR_MAX			(LBTY_u16MAX + 1u)
//#define TMR_PRESCALER	TMR1_u8GetPrescaler()
/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

void Music_Init(void){
	TMRx_INIT();
//  PWM_vidEnable_OC1x();
//	PWM_u8SetFreq_OC1x(Note_C_0);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_C_1);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_C_2);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_C_3);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_C_4);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_C_5);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_C_6);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_C_7);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_C_8);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//
//	PWM_u8SetFreq_OC1x(Note_C_x_0);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_C_x_1);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_C_x_2);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_C_x_3);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_C_x_4);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_C_x_5);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_C_x_6);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_C_x_7);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_C_x_8);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//
//	PWM_u8SetFreq_OC1x(Note_D_0);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_D_1);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_D_2);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_D_3);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_D_4);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_D_5);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_D_6);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_D_7);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_D_8);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//
//	PWM_u8SetFreq_OC1x(Note_D_x_0);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_D_x_1);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_D_x_2);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_D_x_3);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_D_x_4);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_D_x_5);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_D_x_6);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_D_x_7);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_D_x_8);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//
//	PWM_u8SetFreq_OC1x(Note_E_0);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_E_1);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_E_2);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_E_3);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_E_4);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_E_5);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_E_6);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_E_7);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_E_8);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//
//	PWM_u8SetFreq_OC1x(Note_F_0);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_F_1);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_F_2);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_F_3);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_F_4);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_F_5);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_F_6);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_F_7);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_F_8);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//
//	PWM_u8SetFreq_OC1x(Note_F_x_0);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_F_x_1);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_F_x_2);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_F_x_3);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_F_x_4);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_F_x_5);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_F_x_6);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_F_x_7);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_F_x_8);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//
//	PWM_u8SetFreq_OC1x(Note_G_0);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_G_1);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_G_2);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_G_3);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_G_4);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_G_5);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_G_6);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_G_7);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_G_8);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//
//	PWM_u8SetFreq_OC1x(Note_G_x_0);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_G_x_1);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_G_x_2);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_G_x_3);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_G_x_4);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_G_x_5);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_G_x_6);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_G_x_7);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_G_x_8);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//
//	PWM_u8SetFreq_OC1x(Note_A_0);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_A_1);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_A_2);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_A_3);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_A_4);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_A_5);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_A_6);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_A_7);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_A_8);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//
//	PWM_u8SetFreq_OC1x(Note_A_x_0);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_A_x_1);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_A_x_2);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_A_x_3);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_A_x_4);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_A_x_5);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_A_x_6);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_A_x_7);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_A_x_8);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//
//	PWM_u8SetFreq_OC1x(Note_B_0);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_B_1);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_B_2);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_B_3);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_B_4);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_B_5);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_B_6);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_B_7);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);
//	PWM_u8SetFreq_OC1x(Note_B_8);
//	PWM_u8SetDuty_OC1B(50); vidMyDelay_ms(1000);

}

void Music_Run(const u16* pMusicNotes, u8 u8Tempo){
	//turn on any sound
    PWM_vidEnable_OC1x();
	while(*pMusicNotes){
		int note = *pMusicNotes++;
		if( p == note ){
			//pause, do not generate any sound
			PWM_u8SetDuty_OC1B(0);
		}else{
			//set frequency
			PWM_u8SetFreq_OC1x(note);
			//not a pause, generate tone
			PWM_u8SetDuty_OC1B(4000);
		}
		//wait duration
		vidMyDelay_ms(u8Tempo * (32-*pMusicNotes++));
	}
	//turn off any sound
	PWM_u8SetDuty_OC1B(0);
    PWM_vidDisable_OC1x();
}

/*************************** E N D (notes.c) ******************************/
