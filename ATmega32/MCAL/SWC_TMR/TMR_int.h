/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : TMR_int.h													  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Apr 5, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef TMR_INT_H_
#define TMR_INT_H_

#if !defined(TMR0) && !defined(PWM0)
#define TMR0
#endif
#if !defined(TMR2) && !defined(PWM2)
#define TMR2
#endif
#if !defined(TMR1) && !defined(PWM1)
#define TMR1
#endif

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

typedef enum{
	TMR0_NoClockSource_Disable = (u8)0u,
	TMR0_Fosc_Prescaler_1,
	TMR0_Fosc_Prescaler_8,
	TMR0_Fosc_Prescaler_64,
	TMR0_Fosc_Prescaler_256,
	TMR0_Fosc_Prescaler_1024,
	TMR0_ExternalClock_FallingEdge,
	TMR0_ExternalClock_RisinfEdge
}TMR0_tenuClockSource;

typedef enum{
	TMR1_NoClockSource_Disable = (u8)0u,
	TMR1_Fosc_Prescaler_1,
	TMR1_Fosc_Prescaler_8,
	TMR1_Fosc_Prescaler_64,
	TMR1_Fosc_Prescaler_256,
	TMR1_Fosc_Prescaler_1024,
	TMR1_ExternalClock_FallingEdge,
	TMR1_ExternalClock_RisinfEdge
}TMR1_tenuClockSource;

typedef enum{
	TMR2_NoClockSource_Disable = (u8)0u,
	TMR2_Fosc_Prescaler_1,
	TMR2_Fosc_Prescaler_8,
	TMR2_Fosc_Prescaler_32,
	TMR2_Fosc_Prescaler_64,
	TMR2_Fosc_Prescaler_128,
	TMR2_Fosc_Prescaler_256,
	TMR2_Fosc_Prescaler_1024
}TMR2_tenuClockSource;

typedef enum{
	TMRx_u8_Normal_Mode = (u8)0u,
	TMRx_u8_PWM_PhaseCorrect_Mode,
	TMRx_u8_CTC_Mode_Mode,			//Clear Timer on Compare Match
	TMRx_u8_PWM_Fase_Mode
}TMRx_u8_tenuWaveGenerationMode;

typedef enum{
	TMR1_Normal_Mode = (u8)0u,
	TMR1_PWM_PhaseCorrect_Mode_8bit,
	TMR1_PWM_PhaseCorrect_Mode_9bit,
	TMR1_PWM_PhaseCorrect_Mode_10bit,
	TMR1_CTC_Mode_Mode_ICR1,			//Clear Timer on Compare Match
	TMR1_PWM_Fase_Mode_8bit,
	TMR1_PWM_Fase_Mode_9bit,
	TMR1_PWM_Fase_Mode_10bit,
	TMR1_PWM_Phase_Freq_Correct_Mode_ICR1,
	TMR1_PWM_Phase_Freq_Correct_Mode_ICR1A,
	TMR1_PWM_Phase_Correct_Mode_ICR1,
	TMR1_PWM_Phase_Correct_Mode_ICR1A,
	TMR1_CTC_Mode_Mode_ICR1A,			//Clear Timer on Compare Match
	TMR1_Reserved,
	TMR1_PWM_Fase_Mode_ICR1,
	TMR1_PWM_Fase_Mode_ICR1A,
}TMR1_tenuWaveGenerationMode;

typedef enum{
/** Non PWM Mode **/
	TMRx_u8_COM_Disconnected = (u8)0u,
	TMRx_u8_COM_Toggle_on_Match,
	TMRx_u8_COM_Clear_on_Match,
	TMRx_u8_COM_Set_on_Match,

/** Fast PWM Mode **/
	TMRx_u8_FastPWM_Clear_on_Match = (u8)2u,	// Non Inverting Mode
	TMRx_u8_FastPWM_Set_on_Match,				// Inverting Mode

/** Phase PWM Mode **/
	TMRx_u8_PhasePWM_Clear_on_Match = (u8)2u,	// Low Pulse
	TMRx_u8_PhasePWM_Set_on_Match,				// High Pulse

}TMRx_u8_tenuCompareOutputMode;

typedef enum{
	TMR2_IO_Clock = (u8)0u,
	TMR2_TOSC_Clock
}TMR2_tenuInputCaptureEdgeSelect;

typedef enum{
/** Non PWM Mode **/
	TMR1_COM_Disconnected = (u8)0u,
	TMR1_COM_Toggle_on_Match,
	TMR1_COM_Clear_on_Match,
	TMR1_COM_Set_on_Match,

/** Fast PWM Mode **/
	TMR1_FastPWM_ToggleA_on_Match_Mode15 = (u8)1u,
	TMR1_FastPWM_Clear_on_Match = (u8)2u,	// Non Inverting Mode
	TMR1_FastPWM_Set_on_Match,				// Inverting Mode

/** Phase PWM Mode **/
	TMR1_PhasePWM_ToggleA_on_Match_Mode15 = (u8)1u,
	TMR1_PhasePWM_Clear_on_Match = (u8)2u,	// Low Pulse
	TMR1_PhasePWM_Set_on_Match,				// High Pulse

}TMR1_tenuCompareOutputMode;

typedef enum{
	TMR1_Capture_Falling_Edge = (u8)0u,
	TMR1_Capture_Rising_Edge,
	TMR1_Capture_Off
}TMR1_tenuInputCaptureEdgeSelect;

/********************************************************************************************************************/
#if defined(TMR0) || defined(PWM0)
typedef struct{
#if defined(PWM0)
	u32								m_TMR_Freq;
	u16								m_TMR_Duty;
#endif
	u8 								m_TMR_Reload;
	u8 								m_TMR_Compare;
	TMR0_tenuClockSource 			m_TMR_Prescalar;
	TMRx_u8_tenuWaveGenerationMode	m_TMR_Mode;
	TMRx_u8_tenuCompareOutputMode	m_TMR_OutputMode;
	LBTY_tenuFlagStatus				m_TMR_FOC;
	LBTY_tenuFlagStatus				m_TMR_OVIE;
	LBTY_tenuFlagStatus				m_TMR_OCIE;
}TMR0_tstrConfig;
#endif
#if defined(TMR2) || defined(PWM2)
typedef struct{
#if defined(PWM2)
	u32								m_TMR_Freq;
	u16								m_TMR_Duty;
#endif
	u8 								m_TMR_Reload;
	u8 								m_TMR_Compare;
	TMR2_tenuClockSource 			m_TMR_Prescalar;
	TMRx_u8_tenuWaveGenerationMode	m_TMR_Mode;
	TMRx_u8_tenuCompareOutputMode	m_TMR_OutputMode;
	LBTY_tenuFlagStatus				m_TMR_FOC;
	LBTY_tenuFlagStatus				m_TMR_OVIE;
	LBTY_tenuFlagStatus				m_TMR_OCIE;
	TMR2_tenuInputCaptureEdgeSelect m_TMR_AsyClock;
}TMR2_tstrConfig;
#endif
#if defined(TMR1) || defined(PWM1)
typedef struct{
#if defined(PWM1)
	u32								m_TMR_Freq;
	u16								m_TMR_Duty_A;
	u16								m_TMR_Duty_B;
#endif
	u16								m_TMR_Reload;
	u16								m_TMR_Input;
	u16								m_TMR_CompareA;
	u16								m_TMR_CompareB;
	TMR1_tenuClockSource 			m_TMR_Prescalar;
	TMR1_tenuWaveGenerationMode		m_TMR_Mode;
	TMR1_tenuCompareOutputMode		m_TMR_OutputModeA;
	TMR1_tenuCompareOutputMode		m_TMR_OutputModeB;
	LBTY_tenuFlagStatus				m_TMR_FOCA;
	LBTY_tenuFlagStatus				m_TMR_FOCB;
	LBTY_tenuFlagStatus				m_TMR_TICIE;
	LBTY_tenuFlagStatus				m_TMR_OCIEA;
	LBTY_tenuFlagStatus				m_TMR_OCIEB;
	LBTY_tenuFlagStatus				m_TMR_TOIE;
	LBTY_tenuFlagStatus				m_TMR_InputNoise;
	TMR1_tenuInputCaptureEdgeSelect m_TMR_InputEdge;
}TMR1_tstrConfig;
#endif
/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

#define TMR_TICK_US			(1.0f/(F_CPU/1000000))

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

extern void TMR0_vidSetConfig(TMR0_tstrConfig const* const pstrConfig);
extern void TMR0_vidSRestConfig(TMR0_tstrConfig* const pstrConfig);

extern void TMR0_vidInit(void);

extern void TMR0_vidEnable(void);
extern void TMR0_vidDisable(void);

extern void TMR0_vidSetForceOutputCompare(void);
extern void TMR0_vidResetForceOutputCompare(void);

extern LBTY_tenuErrorStatus TMR2_u8Async(TMR2_tenuInputCaptureEdgeSelect u8Async);
extern LBTY_tenuErrorStatus TMR0_u8SetMode(TMRx_u8_tenuWaveGenerationMode u8Mode);
extern LBTY_tenuErrorStatus TMR0_u8SetOutputMode(TMRx_u8_tenuCompareOutputMode u8OutMode);

extern LBTY_tenuErrorStatus TMR0_u8SetOutputCompare(u8 u8Reload);
extern LBTY_tenuErrorStatus TMR0_u8SetCounter(u8 u8Reload);

extern LBTY_tenuErrorStatus TMR0_u8GetOutputCompare(u8* pu8Reload);
extern LBTY_tenuErrorStatus TMR0_u8GetCounter(u8* pu8Reload);

#if defined(PWM0)
extern LBTY_tenuErrorStatus PWM_u8SetFreq_OC0(u32 u32Freq);
extern LBTY_tenuErrorStatus PWM_u8SetDuty_OC0(u16 u16Duty);

static inline void PWM_vidEnable_OC0(void) {TMR0_vidEnable(); }
static inline void PWM_vidDisable_OC0(void){TMR0_vidDisable();}
#endif

extern void TMR0_vidSetCompareNum(u16 u16Num);
extern void TMR0_vidGetCompareNum(u16* pu16Num);

extern void TMR0_vidSetOverflowNum(u16 u16Num);
extern void TMR0_vidGetOverflowNum(u16* pu16Num);
extern void TMR0_vidGetTicks(u32* pu32Tick);

extern void TMR0_vidCompareMatch_Enable(void);
extern void TMR0_vidCompareMatch_Disable(void);

extern void TMR0_vidSetCompareMatch_Flag(void);
extern void TMR0_vidClrCompareMatch_Flag(void);

extern void TMR0_vidOverFlow_Enable(void);
extern void TMR0_vidOverFlow_Disable(void);

extern void TMR0_vidSetOverFlow_Flag(void);
extern void TMR0_vidClrOverFlow_Flag(void);

extern void TMR0_vidSetCallBack_CompareMatch(void (*pCallBack)(void));
extern void TMR0_vidSetCallBack_OverFlow(void (*pCallBack)(void));

/********************************************************************************************************************/

extern void TMR2_vidSetConfig(TMR2_tstrConfig const* const pstrConfig);
extern void TMR2_vidSRestConfig(TMR2_tstrConfig* const pstrConfig);

extern void TMR2_vidInit(void);

extern void TMR2_vidEnable(void);
extern void TMR2_vidDisable(void);

extern void TMR2_vidSetForceOutputCompare(void);
extern void TMR2_vidResetForceOutputCompare(void);

extern LBTY_tenuErrorStatus TMR2_u8SetMode(TMRx_u8_tenuWaveGenerationMode u8Mode);
extern LBTY_tenuErrorStatus TMR2_u8SetOutputMode(TMRx_u8_tenuCompareOutputMode u8OutMode);

extern LBTY_tenuErrorStatus TMR2_u8SetOutputCompare(u8 u8Reload);
extern LBTY_tenuErrorStatus TMR2_u8SetCounter(u8 u8Reload);

extern LBTY_tenuErrorStatus TMR2_u8GetOutputCompare(u8* pu8Reload);
extern LBTY_tenuErrorStatus TMR2_u8GetCounter(u8* pu8Reload);

#if defined(PWM2)
extern LBTY_tenuErrorStatus PWM_u8SetFreq_OC2(u32 u32Freq);
extern LBTY_tenuErrorStatus PWM_u8SetDuty_OC2(u16 u16Duty);

static inline void PWM_vidEnable_OC2(void) {TMR2_vidEnable(); }
static inline void PWM_vidDisable_OC2(void){TMR2_vidDisable();}
#endif

extern void TMR2_vidSetCompareNum(u16 u16Num);
extern void TMR2_vidGetCompareNum(u16* pu16Num);

extern void TMR2_vidSetOverflowNum(u16 u16Num);
extern void TMR2_vidGetOverflowNum(u16* pu16Num);
extern void TMR2_vidGetTicks(u32* pu32Tick);

extern void TMR2_vidCompareMatch_Enable(void);
extern void TMR2_vidCompareMatch_Disable(void);

extern void TMR2_vidSetCompareMatch_Flag(void);
extern void TMR2_vidClrCompareMatch_Flag(void);

extern void TMR2_vidOverFlow_Enable(void);
extern void TMR2_vidOverFlow_Disable(void);

extern void TMR2_vidSetOverFlow_Flag(void);
extern void TMR2_vidClrOverFlow_Flag(void);

extern void TMR2_vidSetCallBack_CompareMatch(void (*pCallBack)(void));
extern void TMR2_vidSetCallBack_OverFlow(void (*pCallBack)(void));

/********************************************************************************************************************/

void TMR1_vidSetConfig(TMR1_tstrConfig const* const pstrConfig);
void TMR1_vidSRestConfig(TMR1_tstrConfig* const pstrConfig);

void TMR1_vidInit(void);

void TMR1_vidEnable(void);
void TMR1_vidDisable(void);
void TMR1_vidInitInputCapture(void);

void TMR1_vidSetForceOutputCompareA(void);
void TMR1_vidResetForceOutputCompareA(void);
void TMR1_vidSetForceOutputCompareB(void);
void TMR1_vidResetForceOutputCompareB(void);

LBTY_tenuErrorStatus TMR1_u8SetMode(TMR1_tenuWaveGenerationMode u8Mode);
LBTY_tenuErrorStatus TMR1_u8SetOutputModeA(TMR1_tenuCompareOutputMode u8OutMode);
LBTY_tenuErrorStatus TMR1_u8SetOutputModeB(TMR1_tenuCompareOutputMode u8OutMode);

LBTY_tenuErrorStatus TMR1_u8SetInputCapture(u16 u16Reload);
LBTY_tenuErrorStatus TMR1_u8SetOutputCompare_A(u16 u16Reload);
LBTY_tenuErrorStatus TMR1_u8SetOutputCompare_B(u16 u16Reload);
LBTY_tenuErrorStatus TMR1_u8SetCounter(u16 u16Reload);

LBTY_tenuErrorStatus TMR1_u8GetInputCapture(u16* pu16Reload);
LBTY_tenuErrorStatus TMR1_u8GetOutputCompare_A(u16* pu16Reload);
LBTY_tenuErrorStatus TMR1_u8GetOutputCompare_B(u16* pu16Reload);
LBTY_tenuErrorStatus TMR1_u8GetCounter(u16* pu16Reload);

#if defined(PWM1)
LBTY_tenuErrorStatus PWM_u8SetFreq_OC1x(u32 u32Freq);
LBTY_tenuErrorStatus PWM_u8SetDuty_OC1A(u16 u16Duty);
LBTY_tenuErrorStatus PWM_u8SetDuty_OC1B(u16 u16Duty);

static inline void PWM_vidEnable_OC1x(void) {TMR1_vidEnable(); }
static inline void PWM_vidDisable_OC1x(void){TMR1_vidDisable();}
#endif

void TMR1_vidSetOverflowNum(u16 u16Num);
void TMR1_vidGetOverflowNum(u16* pu16Num);
void TMR1_vidGetTicks(u32* pu32Tick);

void TMR1_vidInputCapture_Enable(void);
void TMR1_vidInputCapture_Disable(void);

void TMR1_vidSetInputCapture_Flag(void);
void TMR1_vidClrInputCapture_Flag(void);

void TMR1_vidCompareMatch_A_Enable(void);
void TMR1_vidCompareMatch_A_Disable(void);

void TMR1_vidSetCompareMatch_A_Flag(void);
void TMR1_vidClrCompareMatch_A_Flag(void);

void TMR1_vidCompareMatch_B_Enable(void);
void TMR1_vidCompareMatch_B_Disable(void);

void TMR1_vidSetCompareMatch_B_Flag(void);
void TMR1_vidClrCompareMatch_B_Flag(void);

void TMR1_vidOverFlow_Enable(void);
void TMR1_vidOverFlow_Disable(void);

void TMR1_vidSetOverFlow_Flag(void);
void TMR1_vidClrOverFlow_Flag(void);

void TMR1_vidSetCallBack_CaptureEvent(void (*pCallBack)(void));
void TMR1_vidSetCallBack_CompareMatch_A(void (*pCallBack)(void));
void TMR1_vidSetCallBack_CompareMatch_B(void (*pCallBack)(void));
void TMR1_vidSetCallBack_OverFlow(void (*pCallBack)(void));

#endif /* TMR_INT_H_ */
/*************************** E N D (TMR_int.h) ******************************/
