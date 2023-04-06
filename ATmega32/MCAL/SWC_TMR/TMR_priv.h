/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : TMR_priv.h												  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Apr 5, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef TMR_PRIV_H_
#define TMR_PRIV_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

#define TMRx_WGMx0_MASK		0x0u
#define TMRx_WGMx1_MASK		0x1u
#define TMRx_WGMx2_MASK		0x2u
#define TMRx_WGMx3_MASK		0x3u

#define TMR_EXT0_PORT		B
#define TMR_EXT0_PIN		GPIO_TMR_EXT0_IN
#define TMR_EXT1_PORT		B
#define TMR_EXT1_PIN		GPIO_TMR_EXT1_IN

#define TMR_OC0_PORT		B
#define TMR_OC0_PIN			GPIO_TMR_OC0

#define TMR_OC2_PORT		D
#define TMR_OC2_PIN			GPIO_TMR_OC2

#define TMR_OSC1_PORT		C
#define TMR_OSC1_PIN		GPIO_TMR_OSC1
#define TMR_OSC2_PORT		C
#define TMR_OSC2_PIN		GPIO_TMR_OSC2

#define TMR_ICP1_PORT		D
#define TMR_ICP1_PIN		GPIO_TMR_ICP1
#define TMR_OC1A_PORT		D
#define TMR_OC1A_PIN		GPIO_TMR_OC1A
#define TMR_OC1B_PORT		D
#define TMR_OC1B_PIN		GPIO_TMR_OC1B

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

static inline u8   TMR0_u8GetOutputCompare(void){return S_TMR0->m_OCR0;}
static inline u8   TMR0_u8GetCounter(void)      {return S_TMR0->m_TCNT0;}

static inline void TMR0_vidCompareMatch_Enable(void) {S_TIMSK->sBits.m_OCIE0 = LBTY_SET;}
static inline void TMR0_vidCompareMatch_Disable(void){S_TIMSK->sBits.m_OCIE0 = LBTY_RESET;}

static inline void TMR0_vidSetCompareMatch_Flag(void){S_TIFR->sBits.m_OCF0   = LBTY_SET;}
static inline void TMR0_vidClrCompareMatch_Flag(void){S_TIFR->sBits.m_OCF0   = LBTY_RESET;}

static inline void TMR0_vidOverFlow_Enable(void) {S_TIMSK->sBits.m_TOIE0 = LBTY_SET;}
static inline void TMR0_vidOverFlow_Disable(void){S_TIMSK->sBits.m_TOIE0 = LBTY_RESET;}

static inline void TMR0_vidSetOverFlow_Flag(void){S_TIFR->sBits.m_TOV0   = LBTY_SET;}
static inline void TMR0_vidClrOverFlow_Flag(void){S_TIFR->sBits.m_TOV0   = LBTY_RESET;}

/********************************************************************************************************************/

static inline u8   TMR2_u8GetOutputCompare(void){return S_TMR2->m_OCR2;}
static inline u8   TMR2_u8GetCounter(void)      {return S_TMR2->m_TCNT2;}

static inline void TMR2_vidCompareMatch_Enable(void) {S_TIMSK->sBits.m_OCIE2 = LBTY_SET;}
static inline void TMR2_vidCompareMatch_Disable(void){S_TIMSK->sBits.m_OCIE2 = LBTY_RESET;}

static inline void TMR2_vidSetCompareMatch_Flag(void){S_TIFR->sBits.m_OCF2   = LBTY_SET;}
static inline void TMR2_vidClrCompareMatch_Flag(void){S_TIFR->sBits.m_OCF2   = LBTY_RESET;}

static inline void TMR2_vidOverFlow_Enable(void) {S_TIMSK->sBits.m_TOIE2 = LBTY_SET;}
static inline void TMR2_vidOverFlow_Disable(void){S_TIMSK->sBits.m_TOIE2 = LBTY_RESET;}

static inline void TMR2_vidSetOverFlow_Flag(void){S_TIFR->sBits.m_TOV2   = LBTY_SET;}
static inline void TMR2_vidClrOverFlow_Flag(void){S_TIFR->sBits.m_TOV2   = LBTY_RESET;}

/********************************************************************************************************************/

static inline u16  TMR1_u16GetInputCapture(void)   {return S_TMR1->m_ICR1.u16Reg;}
static inline u16  TMR1_u16GetOutputCompare_A(void){return S_TMR1->m_OCR1A.u16Reg;}
static inline u16  TMR1_u16GetOutputCompare_B(void){return S_TMR1->m_OCR1B.u16Reg;}
static inline u16  TMR1_u16GetCounter(void)        {return S_TMR1->m_TCNT1.u16Reg;}

static inline void TMR1_vidInputCapture_Enable(void) {S_TIMSK->sBits.m_TICIE1 = LBTY_SET;}
static inline void TMR1_vidInputCapture_Disable(void){S_TIMSK->sBits.m_TICIE1 = LBTY_RESET;}

static inline void TMR1_vidSetInputCapture_Flag(void){S_TIFR->sBits.m_ICF1   = LBTY_SET;}
static inline void TMR1_vidClrInputCapture_Flag(void){S_TIFR->sBits.m_ICF1   = LBTY_RESET;}

static inline void TMR1_vidCompareMatch_A_Enable(void) {S_TIMSK->sBits.m_OCIE1A = LBTY_SET;}
static inline void TMR1_vidCompareMatch_A_Disable(void){S_TIMSK->sBits.m_OCIE1A = LBTY_RESET;}

static inline void TMR1_vidSetCompareMatch_A_Flag(void){S_TIFR->sBits.m_OCF1A   = LBTY_SET;}
static inline void TMR1_vidClrCompareMatch_A_Flag(void){S_TIFR->sBits.m_OCF1A   = LBTY_RESET;}

static inline void TMR1_vidCompareMatch_B_Enable(void) {S_TIMSK->sBits.m_OCIE1B = LBTY_SET;}
static inline void TMR1_vidCompareMatch_B_Disable(void){S_TIMSK->sBits.m_OCIE1B = LBTY_RESET;}

static inline void TMR1_vidSetCompareMatch_B_Flag(void){S_TIFR->sBits.m_OCF1B   = LBTY_SET;}
static inline void TMR1_vidClrCompareMatch_B_Flag(void){S_TIFR->sBits.m_OCF1B   = LBTY_RESET;}

static inline void TMR1_vidOverFlow_Enable(void) {S_TIMSK->sBits.m_TOIE1 = LBTY_SET;}
static inline void TMR1_vidOverFlow_Disable(void){S_TIMSK->sBits.m_TOIE1 = LBTY_RESET;}

static inline void TMR1_vidSetOverFlow_Flag(void){S_TIFR->sBits.m_TOV1   = LBTY_SET;}
static inline void TMR1_vidClrOverFlow_Flag(void){S_TIFR->sBits.m_TOV1   = LBTY_RESET;}


#endif /* TMR_PRIV_H_ */
/*************************** E N D (TMR_priv.h) ******************************/
