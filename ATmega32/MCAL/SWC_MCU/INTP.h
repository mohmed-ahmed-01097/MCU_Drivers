/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : INT.h														  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Apr 26, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef INTP_H_
#define INTP_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/** @brief : Type define of Union bit field of "General INT Control Register" */
/** <b>Type</b> : Union <b>Unit</b> : None                                    */
typedef union{
	u8 u_Reg;
	struct {
		__IO u8 m_C : 1;			/*!< Carry Flag */
		__IO u8 m_Z : 1;			/*!< Zero Flag */
		__IO u8 m_N : 1;			/*!< Negative Flag */
		__IO u8 m_V : 1;			/*!< Two’s Complement Overflow Flag */
		__IO u8 m_S : 1;			/*!< Sign Bit */
		__IO u8 m_H : 1;			/*!< Half Carry Flag */
		__IO u8 m_T : 1;			/*!< Bit Copy Storage */
		__IO u8 m_I : 1;			/*!< Global Interrupt Enable */
	}sBits;
}SREG_type;

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/** Status Register **/
#define S_SREG          ((SREG_type* const)0x5FU)
#define SREG            (*(volatile u8* const)0x5FU)

/* ************************************************************************** */

# define nop()						__asm__ __volatile__ ("NOP")
# define wdr()						__asm__ __volatile__ ("wdr")
# define sei()  					__asm__ __volatile__ ("sei" ::)
# define cli()  					__asm__ __volatile__ ("cli" ::)
# define reti()  					__asm__ __volatile__ ("reti" ::)

#ifndef _VECTOR
#define _VECTOR(N) 					__vector_ ## N
#endif

#define ISR_BLOCK
#define ISR_NOBLOCK    				__attribute__((interrupt))
#define ISR_NAKED      				__attribute__((naked))
#define ISR_ALIASOF(v) 				__attribute__((alias(__STRINGIFY(v))))

#define ISR(vector, ...)           	\
		void vector(void) __attribute__((signal)) __VA_ARGS__; \
		void vector(void)
/*
#define ISR(vector, ...)           	\
	void vector(void) __attribute__ ((signal,used,externally_visible)) __VA_ARGS__;\
	void vector(void)
 */
/** Interrupt Vectors **/
/***************************************************************************/
/*
Address 	Labels 	Code 						Comments
$000 				jmp RESET 			 ; Reset Handler
$002 				jmp EXT_INT0 		 ; IRQ0 Handler
$004 				jmp EXT_INT1 		 ; IRQ1 Handler
$006 				jmp EXT_INT2 		 ; IRQ2 Handler
$008 				jmp TIM2_COMP 		 ; Timer2 Compare Handler
$00A 				jmp TIM2_OVF 		 ; Timer2 Overflow Handler
$00C 				jmp TIM1_CAPT 		 ; Timer1 Capture Handler
$00E 				jmp TIM1_COMPA 		 ; Timer1 CompareA Handler
$010 				jmp TIM1_COMPB 		 ; Timer1 CompareB Handler
$012 				jmp TIM1_OVF 		 ; Timer1 Overflow Handler
$014 				jmp TIM0_COMP 		 ; Timer0 Compare Handler
$016 				jmp TIM0_OVF 		 ; Timer0 Overflow Handler
$018 				jmp SPI_STC 		 ; SPI Transfer Complete Handler
$01A 				jmp USART_RXC 		 ; USART RX Complete Handler
$01C 				jmp USART_UDRE 		 ; UDR Empty Handler
$01E 				jmp USART_TXC 		 ; USART TX Complete Handler
$020 				jmp ADC 			 ; ADC Conversion Complete Handler
$022 				jmp EE_RDY 			 ; EEPROM Ready Handler
$024 				jmp ANA_COMP 		 ; Analog Comparator Handler
$026 				jmp TWI 			 ; Two-wire Serial Interface Handler
$028 				jmp SPM_RDY 		 ; Store Program Memory Ready Handler
;
$02A 		RESET: 	ldi r16,high(RAMEND) ; Main program start
$02B 				out SPH,r16 		 ; Set Stack Pointer to top of RAM
$02C 				ldi r16,low(RAMEND)
$02D 				out SPL,r16
$02E 				sei 				 ; Enable interrupts
$02F 				<instr> xxx
... ... ...
 */

#define EXT_INT0_vect				_VECTOR(1)	/* External Interrupt Request 0 */
#define EXT_INT1_vect				_VECTOR(2)	/* External Interrupt Request 1 */
#define EXT_INT2_vect				_VECTOR(3)	/* External Interrupt Request 2 */
#define TIMER2_COMP_vect			_VECTOR(4)	/* Timer/Counter2 Compare Match */
#define TIMER2_OVF_vect				_VECTOR(5)	/* Timer/Counter2 Overflow */
#define TIMER1_CAPT_vect			_VECTOR(6)	/* Timer/Counter1 Capture Event */
#define TIMER1_COMPA_vect			_VECTOR(7)	/* Timer/Counter1 Compare Match A */
#define TIMER1_COMPB_vect			_VECTOR(8)	/* Timer/Counter1 Compare Match B */
#define TIMER1_OVF_vect				_VECTOR(9)	/* Timer/Counter1 Overflow */
#define TIMER0_COMP_vect			_VECTOR(10)	/* Timer/Counter0 Compare Match */
#define TIMER0_OVF_vect				_VECTOR(11)	/* Timer/Counter0 Overflow */
#define SPI_STC_vect				_VECTOR(12)	/* Serial Transfer Complete */
#define USART_RXC_vect				_VECTOR(13)	/* USART, Rx Complete */
#define USART_UDRE_vect				_VECTOR(14)	/* USART Data Register Empty */
#define USART_TXC_vect				_VECTOR(15)	/* USART, Tx Complete */
#define ADC_vect					_VECTOR(16)	/* ADC Conversion Complete */
#define EE_RDY_vect					_VECTOR(17)	/* EEPROM Ready */
#define ANA_COMP_vect				_VECTOR(18)	/* Analog Comparator */
#define TWI_vect					_VECTOR(19)	/* 2-wire Serial Interface */
#define SPM_RDY_vect				_VECTOR(20)	/* Store Program Memory Ready */

#define _VECTORS_SIZE 				84

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

LCTY_INLINE void INTP_vidEnable(void){
	S_SREG->sBits.m_I = LBTY_SET;
	//sei();
}

LCTY_INLINE void INTP_vidDisable(void){
	S_SREG->sBits.m_I = LBTY_RESET;
	//cli();
}

LCTY_INLINE void INTP_vidCallBack(void){
	nop();
}

#endif /* INTP_H_ */
/*************************** E N D (INT.h) ******************************/
