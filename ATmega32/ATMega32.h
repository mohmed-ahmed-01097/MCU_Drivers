#ifndef ATMAEGA32_H
#define ATMAEGA32_H

#include "MCAL\SWC_BSW\LBTY_int.h"

/*************************************************************************/
#define __IO    volatile
#define __O     volatile
#define __I     volatile const
/*************************************************************************/

typedef enum{
    External_Clock               = (u8)0u,

    Internal_RC_Oscillator_1MHz  = (u8)1u,      //default
    Internal_RC_Oscillator_2MHz  = (u8)2u,
    Internal_RC_Oscillator_4MHz  = (u8)3u,
    Internal_RC_Oscillator_8MHz  = (u8)4u,

    External_RC_Oscillator_900KHz  = (u8)5u,
    External_RC_Oscillator_3MHz    = (u8)6u,
    External_RC_Oscillator_8MHz    = (u8)7u,
    External_RC_Oscillator_12Mhz   = (u8)8u,

    External_Low_Freq_Crystal_Oscillator   = (u8)9u,

    /** 12 - 22 C1 and C2 for Use with Crystals (pF) **/
    External_Crystal_Low_Freq0      =(u8)10u,   /** 900kHz Ceramic resonator, slowly rising power **/
    External_Crystal_Low_Freq1      =(u8)11u,   /** 2MHz   Crystal Oscillator, slowly rising power **/
    External_Crystal_Medium_Freq0   =(u8)12u,   /** 3MHz   Ceramic resonator, fast rising power **/
    External_Crystal_Medium_Freq1   =(u8)13u,   /** 8MHz   Crystal Oscillator, fast rising power **/
    External_Crystal_High_Freq0     =(u8)14u,   /** 8MHz   Ceramic resonator, BODenabled **/
    External_Crystal_High_Freq1     =(u8)15u,   /** 16MHz  Crystal Oscillator, BOD enabled **/
}SysClockOption_type;                              // CKSEL[3 0]

typedef union{
    __IO u8 FUSE_L;
    struct {
        u8 CKSEL    : 4;        // SysClockOption_t
        u8 SUT      : 2;        // Select start-up time
        u8 BODEN    : 1;        // Brown-out Detector
        u8 BODLEVEL : 1;        // Brown-out Detector trigger level
    }sBits;
}Fuse_Low_Byte_type;


typedef union{
    __IO u8 FUSE_H;
    struct {
        u8 BOOTRST  : 1;        // Select reset vector
        u8 BOOTSZ   : 2;        // Select Boot Size
        u8 EESAVE   : 1;        // EEPROM memory
        u8 CKOPT    : 1;        // Oscillator options
        u8 SPIEN    : 1;        // Enable SPI Serial Program and Data Downloading
        u8 JTAGEN   : 1;        // Enable JTAG
        u8 OCDEN    : 1;        // Enable OCD
    }sBits;
}Fuse_High_Byte_type;

/*************************************************************************/

typedef enum{
    IDEL_Mode = 0u,
    ADC_Noise_Reduction_Mode = 1u,
    Power_Down_Mode = 2u,
    Power_Save_Mode = 3u,

    Standby_Mode = 6u,
    Extended_Standby_Mode = 7u
}SleeS_Mode_type;

/*************************************************************************/

typedef enum{
    INT_Low_Level = (u8)0u,
	INT_Logic_Change,
	INT_Falling_Edge,
	INT_Rising_Edge,

	INT2_Falling_Edge = (u8)0u,
	INT2_Rising_Edge
}INT_tenuSenseControl;      // Interrupt Sense Control

/*************************************************************************/

typedef union{
    u8 u_Reg;
    struct {
        u8 m_TWIE : 1;   // TWI Interrupt Enable
        u8        : 1;
        u8 m_TWEN : 1;   // TWI Enable Bit
        u8 m_TWWC : 1;   // TWI Write Collision Flag
        u8 m_TWSTO: 1;   // TWI STOP Condition Bit
        u8 m_TWSTA: 1;   // TWI START Condition Bit
        u8 m_TWEA : 1;   // TWI Enable Acknowledge Bit
        u8 m_TWINT: 1;   // TWI Interrupt Flag
    }sBits;
}TWCR_type; // TWI Control Register

/*************************************************************************/

typedef union{
    u8 u_Reg;
    struct {
        u8 m_TWPS : 2;   // TWI Prescaler Bits
        u8        : 1;
        u8 m_TWS3 : 1;   // TWI Status
        u8 m_TWP4 : 1;   // TWI Status
        u8 m_TWP5 : 1;   // TWI Status
        u8 m_TWP6 : 1;   // TWI Status
        u8 m_TWP7 : 1;   // TWI Status
    }sBits;
}TWSR_type; // TWI Status Register

/*************************************************************************/

typedef union{
    u8 u_Reg;
    struct {
        u8 m_TWPS : 1;   // TWI General Call Recognition Enable Bit
        u8 m_TWA  : 7;   // TWI Slave Address
    }sBits;
}TWAR_type; // TWI Address Register

/*************************************************************************/

typedef struct{
    __IO u8         m_TWBR;
    __IO TWSR_type  m_TWSR;
    __IO TWAR_type  m_TWAR;
    __IO u8         m_TWDR;
    __I  u8         REVERSE[50];
    __IO TWCR_type  m_TWCR;
}TWI_type;

/*************************************************************************/

typedef union{
    u8 u_Reg;
    struct {
        u8 m_ADPS : 3;   // ADC Prescaler Select Bits
        u8 m_ADIE : 1;   // ADC Interrupt Enable
        u8 m_ADIF : 1;   // ADC Interrupt Flag
        u8 m_ADATE: 1;   // ADC Auto Trigger Enable
        u8 m_ADSC : 1;   // ADC Start Conversion
        u8 m_ADEN : 1;   // ADC Enable
    }sBits;
}ADCSRA_type; // ADC Control and Status Register A

/*************************************************************************/

typedef union{
    u8 u_Reg;
    struct {
        u8 m_MUX  : 5;   // Analog Channel and Gain Selection Bits
        u8 m_ADLAR: 1;   // ADC Left Adjust Result
        u8 m_REFS : 2;   // Reference Selection Bits
    }sBits;
}ADMUX_type; // ADC Multiplexer Selection Register

/*************************************************************************/

typedef union{
    u8 u_Reg;
    struct {
        u8 m_ACIS : 2;   // Analog Comparator Interrupt Mode Select
        u8 m_ACIC : 1;   // Analog Comparator Input Capture Enable
        u8 m_ACIE : 1;   // Analog Comparator Interrupt Enable
        u8 m_ACI  : 1;   // Analog Comparator Interrupt Flag
        u8 m_ACO  : 1;   // Analog Comparator Output
        u8 m_ACBG : 1;   // Analog Comparator Bandgap Select
        u8 m_ACD  : 1;   // Analog Comparator Disable
    }sBits;
}ACSR_type; // Analog Comparator Control and Status

/*************************************************************************/

typedef struct{
#if ADC_ADJUSTMENT
    __I  u16                : 6;
    __I  u16          m_ADC : 10;
#else
    __I  u16          m_ADC : 10;
    __I  u16                : 6;
#endif
    __IO ADCSRA_type  m_ADCSRA;
    __IO ADMUX_type   m_ADMUX;
    __IO ACSR_type    m_ACSR;
}ADC_type;

/*************************************************************************/

typedef union{
    u8 u_Reg;
    struct {
        u8 m_UCPOL: 1;   // Clock Polarity
        u8 m_UCSZ0: 1;   // Character Size
        u8 m_UCSZ1: 1;   // Character Size
        u8 m_USBS : 1;   // Stop Bit Select
        u8 m_UPM  : 2;   // Parity Mode
        u8 m_UMSEL: 1;   // USART Mode Select
        u8 m_URSEL: 1;   // Register Select
    }sUCSRC;
    struct {
        u8 m_UBRR : 4;   // USART Baud Rate High
        u8        : 3;
        u8 m_URSEL: 1;   // Register Select
    }sUBRRH;
}UCSRC_type; // USART Control and Status Register

/*************************************************************************/

typedef union{
    u8 u_Reg;
    struct {
        u8 m_TXB8 : 1;   // Transmit Data Bit 8
        u8 m_RXB8 : 1;   // Receive Data Bit 8
        u8 m_UCSZ2: 1;   // Character Size
        u8 m_TXEN : 1;   // Transmitter Enable
        u8 m_RXEN : 1;   // Receiver Enable
        u8 m_UDRIE: 1;   // USART Data Register Empty Interrupt Enable
        u8 m_TXCIE: 1;   // TX Complete Interrupt Enable
        u8 m_RXCIE: 1;   // RX Complete Interrupt Enable
    }sBits;
}UCSRB_type; // USART Control and Status Register

/*************************************************************************/

typedef union{
    u8 u_Reg;
    struct {
        u8 m_MPCM: 1;   // Multi-processor Communication Mode
        u8 m_U2X : 1;   // Double the USART Transmission Speed
        u8 m_PE  : 1;   // Parity Error
        u8 m_DOR : 1;   // Data OverRun
        u8 m_FE  : 1;   // Frame Error
        u8 m_UDRE: 1;   // USART Data Register Empty
        u8 m_TXC : 1;   // USART Transmit Complete
        u8 m_RXC : 1;   // USART Receive Complete
    }sBits;
}UCSRA_type; // USART Control and Status Register

/*************************************************************************/

typedef struct{
    __IO u8         m_UBRRL;
    __IO UCSRB_type m_UCSRB;
    __IO UCSRA_type m_UCSRA;
    __IO u8         m_UDR;
    __I  u8         REVERSE[13];
    __IO UCSRC_type m_UCSRC;
}USART_type;

/*************************************************************************/

typedef union{
    u8 u_Reg;
    struct {
        u8 m_SPR : 2;   // SPI Clock Rate Select 1 and 0
        u8 m_CPHA: 1;   // Clock Phase
        u8 m_CPOL: 1;   // Clock Polarity
        u8 m_MSTR: 1;   // Master/Slave Select
        u8 m_DORD: 1;   // Data Order
        u8 m_SPE : 1;   // SPI Enable
        u8 m_SPIE: 1;   // SPI Interrupt Enable
    }sBits;
}SPCR_type; // SPI Control Register

/*************************************************************************/

typedef union{
    u8 u_Reg;
    struct {
        u8 m_SPI2X: 1;   // Double SPI Speed Bit
        u8        : 5;
        u8 m_WCOL : 1;   // Write Collision Flag
        u8 m_SPIF : 1;   // SPI Interrupt Flag
    }sBits;
}SPSR_type; // SPI Status Register

/*************************************************************************/

typedef struct{
    __IO SPCR_type m_SPCR;
    __IO SPSR_type m_SPSR;
    __IO u8        m_SPDR;
}SPI_type;

/*************************************************************************/

typedef union{
    u8 u_Reg;
    struct {
        u8 m_B0 : 1;
        u8 m_B1 : 1;
        u8 m_B2 : 1;
        u8 m_B3 : 1;
        u8 m_B4 : 1;
        u8 m_B5 : 1;
        u8 m_B6 : 1;
        u8 m_B7 : 1;
    }sBits;
}BYTE_type; // byte bit exchange

/*************************************************************************/

typedef struct{
    __I  BYTE_type m_PIN;
    __IO BYTE_type m_DDR;
    __IO BYTE_type m_PORT;
}GPIOx_type;    // General Purpose Input Output Registers

/*************************************************************************/

typedef union{
    u8 u_Reg;
    struct {
        u8 m_EERE : 1;   // EEPROM Read Enable
        u8 m_EEWE : 1;   // EEPROM Write Enable
        u8 m_EEMWE: 1;   // EEPROM Master Write Enable
        u8 m_EERIE: 1;   // EEPROM Ready Interrupt Enable
        u8        : 4;
    }sBits;
}EECR_type; // EEPROM Control Register

/*************************************************************************/

typedef struct{
    __IO EECR_type  m_EECR ;
    __IO u8         m_EEDR ;
    __IO u16        m_EEAR : 10;
    __IO u16               : 6;
}EEPROM_type;

/*************************************************************************/

typedef union{
    __IO u8 u_Reg;
    struct {
        u8 m_WDP  : 3;        // Watchdog Timer Prescaler
        u8 m_WDE  : 1;        // Watchdog Enable
        u8 m_WDTOE: 1;        // Watchdog Turn-off Enable
        u8        : 3;
    }sBits;
}WDTCR_type;   // Watchdog Control Register

/*************************************************************************/

typedef union{
    __IO u8 u_Reg;
    struct {
        __I  u8 m_TCR2UB : 1;        // Timer/Counter Control Register2 Update Busy
        __I  u8 m_OCR2UB : 1;        // Output Compare Register2 Update Busy
        __I  u8 m_TCN2UB : 1;        // Timer/Counter2 Update Busy
        __IO u8 m_AS2    : 1;        // Asynchronous Timer/Counter2
        __IO u8          : 4;
    }sBits;
}ASSR_type;   // Asynchronous Status Register

/*************************************************************************/

typedef union{
    __IO u8 u_Reg;
    struct {
        u8 m_CSx  : 3;        // Clock Select
        u8 m_WGMx1: 1;        // Waveform Generation Mode
        u8 m_COMx : 2;        // Compare Match Output Mode
        u8 m_WGMx0: 1;        // Waveform Generation Mode
        u8 m_FOCx : 1;        // Force Output Compare
    }sBits;
}TCCRx_type;   // Timer/Counter Control Register

/*************************************************************************/

typedef struct{
    __IO ASSR_type  m_ASSR;     // Asynchronous Status Register
    __IO u8         m_OCR2;     // Output Compare Register
    __IO u8         m_TCNT2;    // Timer/Counter Register
    __IO TCCRx_type m_TCCR2;    // Timer/Counter Control Register
}GPTMR2_type;    // General Purpose Input Output Registers

/*************************************************************************/

typedef union{
    __IO u8 u_Reg;
    struct {
        u8 m_CS1  : 3;        // Clock Select
        u8 m_WGM12: 1;        // Waveform Generation Mode
        u8 m_WGM13: 1;        // Waveform Generation Mode
        u8        : 1;
        u8 m_ICES1: 1;        // Input Capture Edge Select
        u8 m_ICNC1: 1;        // Input Capture Noise Canceler
    }sBits;
}TCCR1B_type;   // Timer/Counter Control Register

/*************************************************************************/

typedef union{
    __IO u8 u_Reg;
    struct {
        u8 m_WGM10: 1;        // Waveform Generation Mode
        u8 m_WGM11: 1;        // Waveform Generation Mode
        u8 m_FOC1B: 1;        // Force Output Compare
        u8 m_FOC1A: 1;        // Force Output Compare
        u8 m_COM1B: 2;        // Compare Match Output Mode
        u8 m_COM1A: 2;        // Compare Match Output Mode
    }sBits;
}TCCR1A_type;   // Timer/Counter Control Register

/*************************************************************************/

typedef union{
    u16 u16Reg;
    struct {
    	BYTE_type m_u8Low;
    	BYTE_type m_u8High;
    }sBytes;
    struct {
        u8 m_B0 : 1;
        u8 m_B1 : 1;
        u8 m_B2 : 1;
        u8 m_B3 : 1;
        u8 m_B4 : 1;
        u8 m_B5 : 1;
        u8 m_B6 : 1;
        u8 m_B7 : 1;
        u8 m_B8 : 1;
        u8 m_B9 : 1;
        u8 m_B10: 1;
        u8 m_B11: 1;
        u8 m_B12: 1;
        u8 m_B13: 1;
        u8 m_B14: 1;
        u8 m_B15: 1;
    }sBits;
}Word_type;

/*************************************************************************/

typedef struct{
    __IO Word_type   m_ICR1;	 // Output Compare Register
    __IO Word_type   m_OCR1B;	 // Output Compare Register
    __IO Word_type   m_OCR1A;	 // Output Compare Register
    __IO Word_type   m_TCNT1;	 // Output Compare Register
    __IO TCCR1B_type m_TCCR1B;   // Timer/Counter Control Register
    __IO TCCR1A_type m_TCCR1A;   // Timer/Counter Control Register
}GPTMR1_type;    // General Purpose Input Output Registers

/*************************************************************************/

typedef union{
    __IO u8 u_Reg;
    struct {
        u8 m_PSR10: 1;        // Prescaler Reset Timer/Counter1 and Timer/Counter0
        u8 m_PSR2 : 1;        // Prescaler Reset Timer/Counter2
        u8 m_PUD  : 1;        // Pull-up disable
        u8 m_ACME : 1;        // Analog Comparator Multiplexer Enable
        u8        : 1;
        u8 m_ADTS : 3;        // ADC Auto Trigger Source
    }sBits;
}SFIOR_type;   // Special Function I/O Register

/*************************************************************************/

typedef struct{
    __IO u8         m_TCNT0;    // Timer/Counter Register
    __IO TCCRx_type m_TCCR0;    // Timer/Counter Control Register
    __I  u8         REVERSE[8];
    __IO u8         m_OCR0;     // Output Compare Register
}GPTMR0_type;    // General Purpose Input Output Registers

/*************************************************************************/

typedef union{
    __IO u8 u_Reg;
    struct {
        u8 m_PORF : 1;        // Power-on  Reset Flag
        u8 m_EXTRF: 1;        // External  Reset Flag
        u8 m_BORF : 1;        // Brown-out Reset Flag
        u8 m_WDRF : 1;        // Watchdog  Reset Flag
        u8 m_JTRF : 1;        // JTAG      Reset Flag
        u8        : 1;
        u8 m_ISC2 : 1;        // Interrupt 2 Sense Control
        u8 m_JTD  : 1;        // JTAG Interface Disable
    }sBits;
}MCUCSR_type;   // Control and Status Register

/*************************************************************************/

typedef union{
    __IO u8 u_Reg;
    struct {
        u8 m_ISC0 : 2;        // Interrupt 0 Sense Control
        u8 m_ISC1 : 2;        // Interrupt 1 Sense Control
        u8 m_SM   : 3;        // Sleep Mode
        u8 m_SE   : 1;        // Sleep Enable
    }sBits;
}MCUCR_type;   // MCU Control Register

/*************************************************************************/

typedef union{
    __IO u8 u_Reg;
    struct {
        u8 m_SPMEN : 1;        // Store Program Memory Enable
        u8 m_PGERS : 1;        // Page Erase
        u8 m_PGWRT : 1;        // Page Write
        u8 m_BLBSET: 1;        // Boot Lock Bit Set
        u8 m_RWWSRE: 1;        // Read-While-Write Section Read Enable
        u8         : 1;        //
        u8 m_RWWSB : 1;        // Read-While-Write Section Busy
        u8 m_SPMIE : 1;        // SPM Interrupt Enable
    }sBits;
}SPMCR_type;   // MCU Control Register

/*************************************************************************/

typedef union{
    __IO u8 u_Reg;
    struct {
        u8 m_TOV0 : 1;        // Timer/Counter1 Overflow Flag
        u8 m_OCF0 : 1;        // Timer/Counter1 Output Compare Match Flag
        u8 m_TOV1 : 1;        // Timer/Counter1 Overflow Flag
        u8 m_OCF1B: 1;        // Timer/Counter1 Output Compare Match Flag
        u8 m_OCF1A: 1;        // Timer/Counter1 Output Compare Match Flag
        u8 m_ICF1 : 1;        // Timer/Counter1, Input Capture Flag
        u8 m_TOV2 : 1;        // Timer/Counter2 Overflow Flag
        u8 m_OCF2 : 1;        // Timer/Counter2 Output Compare Match Flag
    }sBits;
}TIFR_type;   // Timer/Counter Interrupt Flag Register Register

/*************************************************************************/

typedef union{
    __IO u8 u_Reg;
    struct {
        u8 m_TOIE0 : 1;        // Timer/Counter1 Overflow Interrupt Enable
        u8 m_OCIE0 : 1;        // Timer/Counter1 Output Compare Match Interrupt Enable
        u8 m_TOIE1 : 1;        // Timer/Counter1 Overflow Interrupt Enable
        u8 m_OCIE1B: 1;        // Timer/Counter1 Output Compare Match Interrupt Enable
        u8 m_OCIE1A: 1;        // Timer/Counter1 Output Compare Match Interrupt Enable
        u8 m_TICIE1: 1;        // Timer/Counter1, Input Capture Interrupt Enable
        u8 m_TOIE2 : 1;        // Timer/Counter2 Overflow Interrupt Enable
        u8 m_OCIE2 : 1;        // Timer/Counter2 Output Compare Match Interrupt Enable
    }sBits;
}TIMSK_type;   // Timer/Counter Interrupt Mask Register

/*************************************************************************/

typedef union{
    __IO u8 u_Reg;
    struct {
        u8        : 5;
        u8 m_INT2F: 1;        // External Interrupt Request Flag 2
        u8 m_INT0F: 1;        // External Interrupt Request Flag 0
        u8 m_INT1F: 1;        // External Interrupt Request Flag 1
    }sBits;
}GIFR_type;   // General Interrupt Flag Register

/*************************************************************************/

typedef union{
    __IO u8 u_Reg;
    struct {
        u8 m_IVCE : 1;        // Interrupt Vector Change Enable
        u8 m_IVSEL: 1;        // Interrupt Vector Select
        u8        : 3;
        u8 m_INT2E: 1;        // External Interrupt Request Enable 2
        u8 m_INT0E: 1;        // External Interrupt Request Enable 0
        u8 m_INT1E: 1;        // External Interrupt Request Enable 1
    }sBits;
}GICR_type;   // General Interrupt Control Register

/*************************************************************************/

typedef union{
    __IO u8 u_Reg;
    struct {
        u8 m_C : 1;        // Carry Flag
        u8 m_Z : 1;        // Zero Flag
        u8 m_N : 1;        // Negative Flag
        u8 m_V : 1;        // Two’s Complement Overflow Flag
        u8 m_S : 1;        // Sign Bit
        u8 m_H : 1;        // Half Carry Flag
        u8 m_T : 1;        // Bit Copy Storage
        u8 m_I : 1;        // Global Interrupt Enable
    }sBits;
}SREG_type;   // General Interrupt Control Register

/*************************************************************************/

/** Interrupt Vectors **/
/**************************************************************************
* Vector No.	Program Address 	Source 		Interrupt Definition
* 1  			$000 				RESET  		External Pin,
* 											    Power-on Reset,
* 											    Brown-out Reset,
* 											    Watchdog Reset,
* 											    and JTAG AVR Reset
* 2  			$002 				INT0   		External Interrupt Request 0
* 3  			$004 				INT1   		External Interrupt Request 1
* 4  			$006 				INT2   		External Interrupt Request 2
* 5  			$008 				TIMER2 		COMP Timer/Counter2 Compare Match
* 6  			$00A 				TIMER2 		OVF Timer/Counter2 Overflow
* 7  			$00C 				TIMER1 		CAPT Timer/Counter1 Capture Event
* 8  			$00E 				TIMER1 		COMPA Timer/Counter1 Compare Match A
* 9  			$010 				TIMER1 		COMPB Timer/Counter1 Compare Match B
* 10 			$012 				TIMER1 		OVF Timer/Counter1 Overflow
* 11 			$014 				TIMER0 		COMP Timer/Counter0 Compare Match
* 12 			$016 				TIMER0 		OVF Timer/Counter0 Overflow
* 13 			$018 				SPI,   		STC Serial Transfer Complete
* 14 			$01A 				USART, 		RXC USART, Rx Complete
* 15 			$01C 				USART, 		UDRE USART Data Register Empty
* 16 			$01E 				USART, 		TXC USART, Tx Complete
* 17 			$020 				ADC    		ADC Conversion Complete
* 18 			$022 				EE_RDY 		EEPROM Ready
* 19 			$024 				ANA_COMP   	Analog Comparator
* 20 			$026 				TWI    		Two-wire Serial Interface
* 21 			$028 				SPM_RDY    	Store Program Memory Ready
**************************************************************************/
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

/** Memory Mapped **/
/** Two-Wire Serial Interface **/
#define S_TWI           ((TWI_type*)0x20U)
#define TWBR            *(volatile u8*)0x20U
#define TWSR            *(volatile u8*)0x21U
#define TWAR            *(volatile u8*)0x22U
#define TWDR            *(volatile u8*)0x23U

#define TWCR            *(volatile u8*)0x56U

/** Analog Digital Converter **/
#define S_ADC           ((ADC_type*)0x24U)
#define ADCL            *(volatile u8*)0x24U
#define ADCH            *(volatile u8*)0x25U
#define ADCSRA          *(volatile u8*)0x26U
#define ADMUX           *(volatile u8*)0x27U
#define ACSR            *(volatile u8*)0x28U

/** USART **/
#define S_USART         ((USART_type*)0x29U)
#define UBRRL           *(volatile u8*)0x29U
#define UCSRB           *(volatile u8*)0x2AU
#define UCSRA           *(volatile u8*)0x2BU
#define UDR             *(volatile u8*)0x2CU

#define UCSRC           *(volatile u8*)0x40U
#define UBRRH           *(volatile u8*)0x40U

/** SPI **/
#define S_SPI           ((SPI_type*)0x2DU)
#define SPCR            *(volatile u8*)0x2DU
#define SPSR            *(volatile u8*)0x2EU
#define SPDR            *(volatile u8*)0x2FU

/** GPIOD **/
#define S_GPIOD         ((GPIOx_type*)0x30U)
#define PIND            *(volatile u8*)0x30U
#define DDRD            *(volatile u8*)0x31U
#define PORTD           *(volatile u8*)0x32U

/** GPIOC **/
#define S_GPIOC         ((GPIOx_type*)0x33U)
#define PINC            *(volatile u8*)0x33U
#define DDRC            *(volatile u8*)0x34U
#define PORTC           *(volatile u8*)0x35U

/** GPIOB **/
#define S_GPIOB         ((GPIOx_type*)0x36U)
#define PINB            *(volatile u8*)0x36U
#define DDRB            *(volatile u8*)0x37U
#define PORTB           *(volatile u8*)0x38U

/** GPIOA **/
#define S_GPIOA         ((GPIOx_type*)0x39U)
#define PINA            *(volatile u8*)0x39U
#define DDRA            *(volatile u8*)0x3AU
#define PORTA           *(volatile u8*)0x3BU

/** EEPROM **/
#define S_EEPROM        ((EEPROM_type*)0x3CU)
#define EECR            *(volatile u8*)0x3CU
#define EEDR            *(volatile u8*)0x3DU
#define EEARL           *(volatile u8*)0x3EU
#define EEARH           *(volatile u8*)0x3FU

/** Watchdog Control Register **/
#define S_WDTCR         ((WDTCR_type*)0x41U)
#define WDTCR           *(volatile u8*)0x41U

/** Timer/Counter 0 Register **/
#define S_TMR2          ((GPTMR2_type*)0x42U)
#define ASSR            *(volatile u8*)0x42U
#define OCR2            *(volatile u8*)0x43U
#define TCNT2           *(volatile u8*)0x44U
#define TCCR2           *(volatile u8*)0x45U

/** Timer/Counter 1 Register **/
#define S_TMR1          ((GPTMR1_type*)0x46U)
#define ICR1L           *(volatile u8*)0x46U
#define ICR1H           *(volatile u8*)0x47U
#define OCR1BL          *(volatile u8*)0x48U
#define OCR1BH          *(volatile u8*)0x49U
#define OCR1AL          *(volatile u8*)0x4AU
#define OCR1AH          *(volatile u8*)0x4BU
#define TCNT1L          *(volatile u8*)0x4CU
#define TCNT1H          *(volatile u8*)0x4DU
#define TCCR1B          *(volatile u8*)0x4EU
#define TCCR1A          *(volatile u8*)0x4FU

/** Special Function I/O Register **/
#define S_SFIOR         ((SFIOR_type*)0x50U)
#define SFIOR           *(volatile u8*)0x50U

/** On-chip Debug Register **/
#define OCDR            *(volatile u8*)0x51U

/** Timer/Counter 0 Register **/
#define S_TMR0          ((GPTMR0_type*)0x52U)
#define TCNT0           *(volatile u8*)0x52U
#define TCCR0           *(volatile u8*)0x53U

#define OCR0            *(volatile u8*)0x5CU

/** MCU Control and Status Register **/
#define S_MCUCSR        ((MCUCSR_type*)0x54U)
#define MCUCSR          *(volatile u8*)0x54U

/** MCU Control Register **/
#define S_MCUCR         ((MCUCR_type*)0x55U)
#define MCUCR           *(volatile u8*)0x55U

/** Store Program Memory Control Register **/
#define S_SPMCR         ((SPMCR_type*)0x57U)
#define SPMCR           *(volatile u8*)0x57U

/** Timer/Counter Interrupt Flag Register **/
#define S_TIFR          ((TIFR_type*)0x58U)
#define TIFR            *(volatile u8*)0x58U

/** Timer/Counter Interrupt Mask Register **/
#define S_TIMSK         ((TIMSK_type*)0x59U)
#define TIMSK           *(volatile u8*)0x59U

/** General Interrupt Flag Register **/
#define S_GIFR          ((GIFR_type*)0x5AU)
#define GIFR            *(volatile u8*)0x5AU

/** General Interrupt Control Register **/
#define S_GICR          ((GICR_type*)0x5BU)
#define GICR            *(volatile u8*)0x5BU


/** Stack Pointer **/
#define SPL             *(volatile u8*)0x5DU
#define SPH             *(volatile u8*)0x5EU

/** Status Register **/
#define S_SREG          ((SREG_type*)0x5FU)
#define SREG            *(volatile u8*)0x5FU

/*************************************************************************/


#endif // ATMAEGA32_H
