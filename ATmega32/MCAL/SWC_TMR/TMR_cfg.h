/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : TMR_cfg.h												  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Apr 5, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef TMR_CFG_H_
#define TMR_CFG_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

#if TMR0

#define TMR0_CLOCK_SOURCE						TMRx_Fosc_Prescaler_8
#define TMR0_MODE_INIT							TMRx_u8_Normal_Mode
#define TMR0_COMPARE_OUTPUT_MODE				TMRx_u8_COM_Disconnected

#define TMR0_COMPARE_MATCH_INTERRUPT_INIT_STATE	LBTY_RESET
#define TMR0_OVERFLOW_INTERRUPT_INIT_STATE		LBTY_SET

#define TMR0_COUNTER_INIT						0x00u
#define TMR0_OUTPUT_COMPARE_INIT				0x7Fu

#elif PWM0

#define TMR0_CLOCK_SOURCE						TMRx_Fosc_Prescaler_64
#define TMR0_MODE_INIT							TMRx_u8_PWM_Fase_Mode
#define TMR0_COMPARE_OUTPUT_MODE				TMRx_u8_FastPWM_Clear_on_Match

#define TMR0_COMPARE_MATCH_INTERRUPT_INIT_STATE	LBTY_RESET
#define TMR0_OVERFLOW_INTERRUPT_INIT_STATE		LBTY_SET

// Resolution_PWM = log(Top + 1) / log(2)
// F_P_PWM = F_clk / (Prescaler *  2 * Top )
// F_F_PWM = F_clk / (Prescaler * (1 + Top))
// counts  = top - F_CPU / (Freq * Prescaler)
#define PWM0_FREQ_INIT							1000u
#define PWM0_DUTY_INIT							50u

#define TMR0_COUNTER_INIT						0x00u
#define TMR0_OUTPUT_COMPARE_INIT				0xFFu

#endif

/********************************************************************************************************************/

#if TMR2

#define TMR2_ASYNCHRONOUS_CLOCK					TMR2_TOSC_Clock
#define TMR2_CLOCK_SOURCE						TMRx_Fosc_Prescaler_1
#define TMR2_MODE_INIT							TMRx_u8_Normal_Mode
#define TMR2_COMPARE_OUTPUT_MODE				TMRx_u8_COM_Disconnected

#define TMR2_COMPARE_MATCH_INTERRUPT_INIT_STATE	LBTY_RESET
#define TMR2_OVERFLOW_INTERRUPT_INIT_STATE		LBTY_RESET

#define TMR2_COUNTER_INIT						0x00u
#define TMR2_OUTPUT_COMPARE_INIT				0xFFu

#elif PWM2

#define TMR2_ASYNCHRONOUS_CLOCK					TMR2_IO_Clock
#define TMR2_CLOCK_SOURCE						TMRx_Fosc_Prescaler_8
#define TMR2_MODE_INIT							TMRx_u8_PWM_Fase_Mode
#define TMR2_COMPARE_OUTPUT_MODE				TMRx_u8_FastPWM_Clear_on_Match

#define TMR2_COMPARE_MATCH_INTERRUPT_INIT_STATE	LBTY_RESET
#define TMR2_OVERFLOW_INTERRUPT_INIT_STATE		LBTY_SET

// Resolution_PWM = log(Top + 1) / log(2)
// F_P_PWM = F_clk / (Prescaler *  2 * Top )
// F_F_PWM = F_clk / (Prescaler * (1 + Top))
// counts  = top - F_CPU / (Freq * Prescaler)
#define PWM2_FREQ_INIT							10000u
#define PWM2_DUTY_INIT							50u

#define TMR2_COUNTER_INIT						0x00u
#define TMR2_OUTPUT_COMPARE_INIT				0xFFu

#endif

/********************************************************************************************************************/

#define TMR1_CLOCK_SOURCE						TMRx_Fosc_Prescaler_1

#define TMR1_MODE_INIT							TMR1_Normal_Mode
#define TMR1_COMPARE_OUTPUT_A_MODE				TMR1_COM_Disconnected
#define TMR1_COMPARE_OUTPUT_B_MODE				TMR1_COM_Disconnected

#define TMR1_COUNTER_INIT						0x00u
#define TMR1_INPUT_CAPTURE_INIT					0x00u
#define TMR1_OUTPUT_COMPARE_A_INIT				0xFFu
#define TMR1_OUTPUT_COMPARE_B_INIT				0xFFu

#define TMR1_INPUT_CAPTURE_INTERRUPT_STATE		LBTY_RESET
#define TMR1_OVERFLOW_INTERRUPT_STATE			LBTY_RESET
#define TMR1_COMPARE_A_MATCH_INTERRUPT_STATE	LBTY_RESET
#define TMR1_COMPARE_B_MATCH_INTERRUPT_STATE	LBTY_RESET

#define TMR1_INPUT_CAPTURE_NOISE_CANCELER		LBTY_SET
#define TMR1_INPUT_CAPTURE_EDGE_SELECT			TMR1_Capture_Rising_Edge

/********************************************************************************************************************/

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


#endif /* TMR_CFG_H_ */
/*************************** E N D (TMR_cfg.h) ******************************/
