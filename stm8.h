//
// Global do-everything catch-all header for STM8S103F3P6
//
#define TRUE	1
#define FALSE	0
#define PA_ODR			*(unsigned char*)0x005000 // Port A data output latch register 
#define PA_IDR			*(unsigned char*)0x005001 // Port A input pin value register 
#define PA_DDR			*(unsigned char*)0x005002 // Port A data direction register  
#define PA_CR1			*(unsigned char*)0x005003 // Port A control register 1  
#define PA_CR2			*(unsigned char*)0x005004 // Port A control register 2  

#define PB_ODR			*(unsigned char*)0x005005 // Port B data output latch register 
#define PB_IDR			*(unsigned char*)0x005006 // Port B input pin value register 
#define PB_DDR			*(unsigned char*)0x005007 // Port B data direction register  
#define PB_CR1			*(unsigned char*)0x005008 // Port B control register 1  
#define PB_CR2			*(unsigned char*)0x005009 // Port B control register 2  

#define PC_ODR			*(unsigned char*)0x00500A // Port C data output latch register 
#define PC_IDR			*(unsigned char*)0x00500B // Port C input pin value register 
#define PC_DDR			*(unsigned char*)0x00500C // Port C data direction register  
#define PC_CR1			*(unsigned char*)0x00500D // Port C control register 1  
#define PC_CR2			*(unsigned char*)0x00500E // Port C control register 2  

#define PD_ODR			*(unsigned char*)0x00500F // Port D data output latch register 
#define PD_IDR			*(unsigned char*)0x005010 // Port D input pin value register 
#define PD_DDR			*(unsigned char*)0x005011 // Port D data direction register  
#define PD_CR1			*(unsigned char*)0x005012 // Port D control register 1  
#define PD_CR2			*(unsigned char*)0x005013 // Port D control register 2  

#define PE_ODR			*(unsigned char*)0x005014 // Port E data output latch register 
#define PE_IDR			*(unsigned char*)0x005015 // Port E input pin value register 
#define PE_DDR			*(unsigned char*)0x005016 // Port E data direction register  
#define PE_CR1			*(unsigned char*)0x005017 // Port E control register 1  
#define PE_CR2			*(unsigned char*)0x005018 // Port E control register 2  

#define PF_ODR			*(unsigned char*)0x005019 // Port F data output latch register 
#define PF_IDR			*(unsigned char*)0x00501A // Port F input pin value register 
#define PF_DDR			*(unsigned char*)0x00501B // Port F data direction register  
#define PF_CR1			*(unsigned char*)0x00501C // Port F control register 1  
#define PF_CR2			*(unsigned char*)0x00501D // Port F control register 2  

#define FLASH_CR1		*(unsigned char*)0x00505A // Flash control register 1   
#define FLASH_CR2		*(unsigned char*)0x00505B // Flash control register 2   
#define FLASH_NCR2		*(unsigned char*)0x00505C // Flash complementary control register 2  
#define FLASH_FPR		*(unsigned char*)0x00505D // Flash protection register    
#define FLASH_NFPR		*(unsigned char*)0x00505E // Flash complementary protection register   
#define FLASH_IAPSR		*(unsigned char*)0x00505F // Flash in-application programming status register  
#define FLASH_PUKR		*(unsigned char*)0x005062 // Flash program memory unprotection register  
#define FLASH_DUKR		*(unsigned char*)0x005064 // Data EEPROM unprotection register   

#define EXTI_CR1		*(unsigned char*)0x0050A0 // External interrupt control register 1  
#define EXTI_CR2		*(unsigned char*)0x0050A1 // External interrupt control register 2  
#define RST_SR			*(unsigned char*)0x0050B3 // Reset status register    

#define CLK_ICKR		*(unsigned char*)0x0050C0 // Internal clock control register   
#define CLK_ECKR		*(unsigned char*)0x0050C1 // External clock control register   
#define CLK_CMSR		*(unsigned char*)0x0050C3 // Clock master status register   
#define CLK_SWR			*(unsigned char*)0x0050C4 // Clock master switch register   
#define CLK_SWCR		*(unsigned char*)0x0050C5 // Clock switch control register   
#define CLK_CKDIVR		*(unsigned char*)0x0050C6 // Clock divider register    
#define CLK_PCKENR1		*(unsigned char*)0x0050C7 // Peripheral clock gating register 1  
#define CLK_CSSR		*(unsigned char*)0x0050C8 // Clock security system register   
#define CLK_CCOR		*(unsigned char*)0x0050C9 // Configurable clock control register   
#define CLK_PCKENR2		*(unsigned char*)0x0050CA // Peripheral clock gating register 2  
#define CLK_HSITRIMR		*(unsigned char*)0x0050CC // HSI clock calibration trimming register  
#define CLK_SWIMCCR		*(unsigned char*)0x0050CD // SWIM clock control register   

#define WWDG_CR			*(unsigned char*)0x0050D1 // WWDG control register    
#define WWDG_WR			*(unsigned char*)0x0050D2 // WWDR window register    
#define IWDG_KR			*(unsigned char*)0x0050E0 // IWDG key register    
#define IWDG_PR			*(unsigned char*)0x0050E1 // IWDG prescaler register    
#define IWDG_RLR		*(unsigned char*)0x0050E2 // IWDG reload register    

#define AWU_CSR1		*(unsigned char*)0x0050F0 // AWU control/status register 1   
#define AWU_APRi		*(unsigned char*)0x0050F1 // AWU asynchronous prescaler buffer register  
#define AWU_TBR			*(unsigned char*)0x0050F2 // AWU timebase selection register   

#define BEEP_CSR		*(unsigned char*)0x0050F3 // BEEP control/status register    

#define SPI_CR1			*(unsigned char*)0x005200 // SPI control register 1   
#define SPI_CR2			*(unsigned char*)0x005201 // SPI control register 2   
#define SPI_ICR			*(unsigned char*)0x005202 // SPI interrupt control register   
#define SPI_SR			*(unsigned char*)0x005203 // SPI status register    
#define SPI_DR			*(unsigned char*)0x005204 // SPI data register    
#define SPI_CRCPR		*(unsigned char*)0x005205 // SPI CRC polynomial register   
#define SPI_RXCRCR		*(unsigned char*)0x005206 // SPI Rx CRC register   
#define SPI_TXCRCR		*(unsigned char*)0x005207 // SPI Tx CRC register   

#define I2C_CR1			*(unsigned char*)0x005210 // I2C control register 1   
#define I2C_CR2			*(unsigned char*)0x005211 // I2C control register 2   
#define I2C_FREQR		*(unsigned char*)0x005212 // I2C frequency register    
#define I2C_OARL		*(unsigned char*)0x005213 // I2C Own address register low  
#define I2C_OARH		*(unsigned char*)0x005214 // I2C Own address register high  
#define I2C_DR			*(unsigned char*)0x005216 // I2C data register    
#define I2C_SR1			*(unsigned char*)0x005217 // I2C status register 1   
#define I2C_SR2			*(unsigned char*)0x005218 // I2C status register 2   
#define I2C_SR3			*(unsigned char*)0x005219 // I2C status register 3   
#define I2C_ITR			*(unsigned char*)0x00521A // I2C interrupt control register   
#define I2C_CCRL		*(unsigned char*)0x00521B // I2C Clock control register low  
#define I2C_CCRH		*(unsigned char*)0x00521C // I2C Clock control register high  
#define I2C_TRISER		*(unsigned char*)0x00521D // I2C TRISE register    
#define I2C_PECR		*(unsigned char*)0x00521E // I2C packet error checking register  

#define UART1_SR		*(unsigned char*)0x005230 // UART1 status register    
#define UART1_DR		*(unsigned char*)0x005231 // UART1 data register    
#define UART1_BRR1		*(unsigned char*)0x005232 // UART1 baud rate register 1  
#define UART1_BRR2		*(unsigned char*)0x005233 // UART1 baud rate register 2  
#define UART1_CR1		*(unsigned char*)0x005234 // UART1 control register 1   
#define UART1_CR2		*(unsigned char*)0x005235 // UART1 control register 2   
#define UART1_CR3		*(unsigned char*)0x005236 // UART1 control register 3   
#define UART1_CR4		*(unsigned char*)0x005237 // UART1 control register 4   
#define UART1_CR5		*(unsigned char*)0x005238 // UART1 control register 5   
#define UART1_GTR		*(unsigned char*)0x005239 // UART1 guard time register   
#define UART1_PSCR		*(unsigned char*)0x00523A // UART1 prescaler register    

#define TIM1_CR1		*(unsigned char*)0x005250 // TIM1 control register 1   
#define TIM1_CR2		*(unsigned char*)0x005251 // TIM1 control register 2   
#define TIM1_SMCR		*(unsigned char*)0x005252 // TIM1 slave mode control register  
#define TIM1_ETR		*(unsigned char*)0x005253 // TIM1 external trigger register   
#define TIM1_IER		*(unsigned char*)0x005254 // TIM1 interrupt enable register   
#define TIM1_SR1		*(unsigned char*)0x005255 // TIM1 status register 1   
#define TIM1_SR2		*(unsigned char*)0x005256 // TIM1 status register 2   
#define TIM1_EGR		*(unsigned char*)0x005257 // TIM1 event generation register   
#define TIM1_CCMR1		*(unsigned char*)0x005258 // TIM1 capture/compare mode register 1  
#define TIM1_CCMR2		*(unsigned char*)0x005259 // TIM1 capture/compare mode register 2  
#define TIM1_CCMR3		*(unsigned char*)0x00525A // TIM1 capture/compare mode register 3  
#define TIM1_CCMR4		*(unsigned char*)0x00525B // TIM1 capture/compare mode register 4  
#define TIM1_CCER1		*(unsigned char*)0x00525C // TIM1 capture/compare enable register 1  
#define TIM1_CCER2		*(unsigned char*)0x00525D // TIM1 capture/compare enable register 2  
#define TIM1_CNTRH		*(unsigned char*)0x00525E // TIM1 counter high    
#define TIM1_CNTRL		*(unsigned char*)0x00525F // TIM1 counter low    
#define TIM1_PSCRH		*(unsigned char*)0x005260 // TIM1 prescaler register high   
#define TIM1_PSCRL		*(unsigned char*)0x005261 // TIM1 prescaler register low   
#define TIM1_ARRH		*(unsigned char*)0x005262 // TIM1 aut o-reload register high  
#define TIM1_ARRL		*(unsigned char*)0x005263 // TIM1 auto-reload register low   
#define TIM1_RCR		*(unsigned char*)0x005264 // TIM1 repetition counter register   
#define TIM1_CCR1H		*(unsigned char*)0x005265 // TIM1 capture/compare register 1 high  
#define TIM1_CCR1L		*(unsigned char*)0x005266 // TIM1 capture/compare register 1 low  
#define TIM1_CCR2H		*(unsigned char*)0x005267 // TIM1 capture/compare register 2 high  
#define TIM1_CCR2L		*(unsigned char*)0x005268 // TIM1 capture/compare register 2 low  
#define TIM1_CCR3H		*(unsigned char*)0x005269 // TIM1 capture/compare register 3 high  
#define TIM1_CCR3L		*(unsigned char*)0x00526A // TIM1 capture/compare register 3 low  
#define TIM1_CCR4H		*(unsigned char*)0x00526B // TIM1 capture/compare register 4 high  
#define TIM1_CCR4L		*(unsigned char*)0x00526C // TIM1 capture/compare register 4 low  
#define TIM1_BKR		*(unsigned char*)0x00526D // TIM1 break register    
#define TIM1_DTR		*(unsigned char*)0x00526E // TIM1 dead-time register    
#define TIM1_OISR		*(unsigned char*)0x00526F // TIM1 output idle state register  

#define TIM2_CR1		*(unsigned char*)0x005300 // TIM2 control register 1   
#define TIM2_IER		*(unsigned char*)0x005303 // TIM2 Interrupt enable register   
#define TIM2_SR1		*(unsigned char*)0x005304 // TIM2 status register 1   
#define TIM2_SR2		*(unsigned char*)0x005305 // TIM2 status register 2   
#define TIM2_EGR		*(unsigned char*)0x005306 // TIM2 event generation register   
#define TIM2_CCMR1		*(unsigned char*)0x005307 // TIM2 capture/compare mode register 1  
#define TIM2_CCMR2		*(unsigned char*)0x005308 // TIM2 capture/compare mode register 2  
#define TIM2_CCMR3		*(unsigned char*)0x005309 // TIM2 capture/compare mode register 3  
#define TIM2_CCER1		*(unsigned char*)0x00530a // TIM2 capture/compare enable register 1  
#define TIM2_CCER2		*(unsigned char*)0x00530b // TIM2 capture/compare enable register 2  
#define TIM2_CNTRH		*(unsigned char*)0x00530c // TIM2 counter high    
#define TIM2_CNTRL		*(unsigned char*)0x00530d // TIM2 counter low    
#define TIM2_PSCR		*(unsigned char*)0x00530e // TIM2 prescaler register    
#define TIM2_ARRH		*(unsigned char*)0x00530f // TIM2 auto-reload register high   
#define TIM2_ARRL		*(unsigned char*)0x005310 // TIM2 auto-reload register low   
#define TIM2_CCR1H		*(unsigned char*)0x005311 // TIM2 capture/compare register 1 high  
#define TIM2_CCR1L		*(unsigned char*)0x005312 // TIM2 capture/compare register 1 low  
#define TIM2_CCR2H		*(unsigned char*)0x005313 // TIM2 capture/compare reg. 2 high  
#define TIM2_CCR2L		*(unsigned char*)0x005314 // TIM2 capture/compare register 2 low  
#define TIM2_CCR3H		*(unsigned char*)0x005315 // TIM2 capture/compare register 3 high  
#define TIM2_CCR3L		*(unsigned char*)0x005316 // TIM2 capture/compare register 3 low  

#define TIM4_CR1		*(unsigned char*)0x005340 // TIM4 control register 1   
#define TIM4_IER		*(unsigned char*)0x005343 // TIM4 interrupt enable register   
#define TIM4_SR			*(unsigned char*)0x005344 // TIM4 status register    
#define TIM4_EGR		*(unsigned char*)0x005345 // TIM4 event generation register   
#define TIM4_CNTR		*(unsigned char*)0x005346 // TIM4 counter     
#define TIM4_PSCR		*(unsigned char*)0x005347 // TIM4 prescaler register    
#define TIM4_ARR		*(unsigned char*)0x005348 // TIM4 auto-reload register    

#define ADC_CSR			*(unsigned char*)0x005400 // ADC control/status register    
#define ADC_CR1			*(unsigned char*)0x005401 // ADC configuration register 1   
#define ADC_CR2			*(unsigned char*)0x005402 // ADC configuration register 2   
#define ADC_CR3			*(unsigned char*)0x005403 // ADC configuration register 3   
#define ADC_DRH			*(unsigned char*)0x005404 // ADC data register high   
#define ADC_DRL			*(unsigned char*)0x005405 // ADC data register low   
#define ADC_TDRH		*(unsigned char*)0x005406 // ADC Schmitt trigger disable register high 
#define ADC_TDRL		*(unsigned char*)0x005407 // ADC Schmitt trigger disable register low 
#define ADC_HTRH		*(unsigned char*)0x005408 // ADC high threshold register high  
#define ADC_HTRL		*(unsigned char*)0x005409 // ADC high threshold register low  
#define ADC_LTRH		*(unsigned char*)0x00540A // ADC low threshold register high  
#define ADC_LTRL		*(unsigned char*)0x00540B // ADC low threshold register low  
#define ADC_AWSRH		*(unsigned char*)0x00540C // ADC analog watchdog status register high 
#define ADC_AWSRL		*(unsigned char*)0x00540D // ADC analog watchdog status register low 
#define ADC_AWCRH		*(unsigned char*)0x00540E // ADC analog watchdog control register high 
#define ADC_AWCRL		*(unsigned char*)0x00540F // ADC analog watchdog control register low 

#define ACC			*(unsigned char*)0x007F00 // Accumulator      
#define PCE			*(unsigned char*)0x007F01 // Program counter extended    
#define PCH			*(unsigned char*)0x007F02 // Program counter high    
#define PCL			*(unsigned char*)0x007F03 // Program counter low    
#define XH			*(unsigned char*)0x007F04 // X index register high   
#define XL			*(unsigned char*)0x007F05 // X index register low   
#define YH			*(unsigned char*)0x007F06 // Y index register high   
#define YL			*(unsigned char*)0x007F07 // Y index register low   
#define SPH			*(unsigned char*)0x007F08 // Stack pointer high    
#define SPL			*(unsigned char*)0x007F09 // Stack pointer low    
#define CCR			*(unsigned char*)0x007F0A // Condition code register    
#define CPU			*(unsigned char*)0x007F60 // CFG_GCR Global configuration register   

#define ITC_SPR1		*(unsigned char*)0x007F70 // Interrupt software priority register 1  
#define ITC_SPR2		*(unsigned char*)0x007F71 // Interrupt software priority register 2  
#define ITC_SPR3		*(unsigned char*)0x007F72 // Interrupt software priority register 3  
#define ITC_SPR4		*(unsigned char*)0x007F73 // Interrupt software priority register 4  
#define ITC_SPR5		*(unsigned char*)0x007F74 // Interrupt software priority register 5  
#define ITC_SPR6		*(unsigned char*)0x007F75 // Interrupt software priority register 6  
#define ITC_SPR7		*(unsigned char*)0x007F76 // Interrupt software priority register 7  
#define ITC_SPR8		*(unsigned char*)0x007F77 // Interrupt software priority register 8  

#define SWIM			*(unsigned char*)0x007F80 // SWIM_CSR SWIM control status register  

#define DM_BK1RE		*(unsigned char*)0x007F90 // DM breakpoint 1 register extended byte 
#define DM_BK1RH		*(unsigned char*)0x007F91 // DM breakpoint 1 register high byte 
#define DM_BK1RL		*(unsigned char*)0x007F92 // DM breakpoint 1 register low byte 
#define DM_BK2RE		*(unsigned char*)0x007F93 // DM breakpoint 2 register extended byte 
#define DM_BK2RH		*(unsigned char*)0x007F94 // DM breakpoint 2 register high byte 
#define DM_BK2RL		*(unsigned char*)0x007F95 // DM breakpoint 2 register low byte 
#define DM_CR1			*(unsigned char*)0x007F96 // DM debug module control register 1 
#define DM_CR2			*(unsigned char*)0x007F97 // DM debug module control register 2 
#define DM_CSR1			*(unsigned char*)0x007F98 // DM debug module control/status register 1 
#define DM_CSR2			*(unsigned char*)0x007F99 // DM debug module control/status register 2 
#define DM_ENFCTR		*(unsigned char*)0x007F9A // DM enable function register   

#define CR1_R8			(1 << 7)
#define CR1_T8			(1 << 6)
#define CR1_UARTD		(1 << 5)
#define CR1_M			(1 << 4)
#define CR1_WAKE		(1 << 3)
#define CR1_PCEN		(1 << 2)
#define CR1_PS			(1 << 1)
#define CR1_PIEN		(1 << 0)

#define CR2_TIEN		(1 << 7)
#define CR2_TCIEN		(1 << 6)
#define CR2_RIEN		(1 << 5)
#define CR2_ILIEN		(1 << 4)
#define CR2_TEN			(1 << 3)
#define CR2_REN			(1 << 2)
#define CR2_RWU			(1 << 1)
#define CR2_SBK			(1 << 0)

#define CR3_LINEN		(1 << 6)
#define CR3_STOPH		(1 << 5)
#define CR3_STOPL		(1 << 4)
#define CR3_CLKEN		(1 << 3)
#define CR3_CPOL		(1 << 2)
#define CR3_CPHA		(1 << 1)
#define CR3_LBCL		(1 << 0)

#define SR_TXE			(1 << 7)
#define SR_TC			(1 << 6)
#define SR_RXNE			(1 << 5)
#define SR_IDLE			(1 << 4)
#define SR_OR			(1 << 3)
#define SR_NF			(1 << 2)
#define SR_FE			(1 << 1)
#define SR_PE			(1 << 0)

#define CLK_REGAH		(1 << 5)
#define CLK_LSIRDY		(1 << 4)
#define CLK_LSIEN		(1 << 3)
#define CLK_FHWU		(1 << 2)
#define CLK_HSIRDY		(1 << 1)
#define CLK_HSIEN		(1 << 0)
#define CLK_SWIF		(1 << 3)
#define CLK_SWIEN		(1 << 2)
#define CLK_SWEN		(1 << 1)
#define CLK_SWBSY		(1 << 0)

// ADC registers (section 24.11 reference manual)
#define ADC_EOC			(1 << 7)
#define ADC_AWD			(1 << 6)
#define ADC_EOCIE		(1 << 5)
#define ADC_AWDIE		(1 << 4)
//AIN0 - AIN15 is lower 4 bits of CSR!
// ADC_CR1
//SPSEL is bits 6,5,4 of CR1!
#define ADC_CONT		(1 << 1)
#define ADC_ADON		(1 << 0)
#define ADC_EXTTRIG		(1 << 6)
// ADC_CR2
//EXTSEL is bits 5,4 of CR2!
#define ADC_ALIGN		(1 << 3)
#define ADC_SCAN		(1 << 1)
#define ADC_DBUF		(1 << 7)
#define ADC_OVR			(1 << 6)

// TIMx_CR1
#define TIMx_ARPE		(1 << 7)
#define TIMx_OPM		(1 << 3)
#define TIMx_URS		(1 << 2)
#define TIMx_UDIS		(1 << 1)
#define TIMx_CEN		(1 << 0)
// TIMx_IER
#define TIMx_TIE		(1 << 6)
#define TIMx_CC3IE		(1 << 3)
#define TIMx_CC2IE		(1 << 2)
#define TIMx_CC1IE		(1 << 1)
#define TIMx_UIE		(1 << 0)
// TIMx_SR1
#define TIMx_TIF		(1 << 6)
#define TIMx_CC3IF		(1 << 3)
#define TIMx_CC2IF		(1 << 2)
#define TIMx_CC1IF		(1 << 1)
#define TIMx_UIF		(1 << 0)

// Interrupt names
#define IRQ_TIM2_UPD_OVF_BRK	15
#define IRQ_TIM2_CAP_COM	16
#define IRQ_ADC1		24

// Output Data Register
#define Px_ODR7		(1 << 7)
#define Px_ODR6		(1 << 6)
#define Px_ODR5		(1 << 5)
#define Px_ODR4		(1 << 4)
#define Px_ODR3		(1 << 3)
#define Px_ODR2		(1 << 2)
#define Px_ODR1		(1 << 1)
#define Px_ODR0		(1 << 0)
// Input Data Register
#define GPIO_LOW	0
#define GPIO_HIGH	1
#define Px_IDR7		(1 << 7)
#define Px_IDR6		(1 << 6)
#define Px_IDR5		(1 << 5)
#define Px_IDR4		(1 << 4)
#define Px_IDR3		(1 << 3)
#define Px_IDR2		(1 << 2)
#define Px_IDR1		(1 << 1)
#define Px_IDR0		(1 << 0)
// Data Direction Register
#define GPIO_INPUT	0
#define GPIO_OUTPUT	1
#define Px_DDR7		(1 << 7)
#define Px_DDR6		(1 << 6)
#define Px_DDR5		(1 << 5)
#define Px_DDR4		(1 << 4)
#define Px_DDR3		(1 << 3)
#define Px_DDR2		(1 << 2)
#define Px_DDR1		(1 << 1)
#define Px_DDR0		(1 << 0)
// Port x Control Register Px_CR1
#define FLOATING_INPUT		0
#define INPUT_WITH_PULLUP	1
#define PSEUDO_OPEN_DRAIN	0
#define PUSH_PULL		1
#define Px_C1_7		(1 << 7)
#define Px_C1_6		(1 << 6)
#define Px_C1_5		(1 << 5)
#define Px_C1_4		(1 << 4)
#define Px_C1_3		(1 << 3)
#define Px_C1_2		(1 << 2)
#define Px_C1_1		(1 << 1)
#define Px_C1_0		(1 << 0)
// Port x Control Register Px_CR2
#define EXT_IRQ_DISABLED	0
#define EXT_IRQ_ENABLED		1
#define OUTPUT_SPEED_2MHZ	0
#define OUTPUT_SPEED_10MHZ	1
#define Px_C2_7		(1 << 7)
#define Px_C2_6		(1 << 6)
#define Px_C2_5		(1 << 5)
#define Px_C2_4		(1 << 4)
#define Px_C2_3		(1 << 3)
#define Px_C2_2		(1 << 2)
#define Px_C2_1		(1 << 1)
#define Px_C2_0		(1 << 0)

// I2C_CR1
#define I2C_NOSTRETCH	(1 << 7)
#define I2C_ENGC	(1 << 6)
#define I2C_PE		(1 << 0)

// I2C_CR2
#define I2C_SWRST	(1 << 7)
#define I2C_POS		(1 << 3)
#define I2C_ACK		(1 << 2)
#define I2C_STOP	(1 << 1)
#define I2C_START	(1 << 0)

// I2C_OARH
#define I2C_ADDMODE	(1 << 7)
#define I2C_ADDCONF	(1 << 6)

// I2C_CCRH
#define I2C_FS		(1 << 7)
#define I2C_DUTY	(1 << 6)

// I2C_ITR
#define I2C_ITBUFEN	(1 << 2)
#define I2C_ITEVTEN	(1 << 1)
#define I2C_ITERREN	(1 << 0)

// I2C_SR1
#define I2C_TXE		(1 << 7)
#define I2C_RXNE	(1 << 6)
#define I2C_STOPF	(1 << 4)
#define I2C_ADD10	(1 << 3)
#define I2C_BTF		(1 << 2)
#define I2C_ADDR	(1 << 1)
#define I2C_SB		(1 << 0)

// SPI related defines - SPI_CR1
#define MSBFIRST	0
#define LSBFIRST	128
#define SPI_DISABLE	0
#define SPI_ENABLE	64
#define BR_DIV2		(0 << 3)
#define BR_DIV4		(1 << 3)
#define BR_DIV8		(2 << 3)
#define BR_DIV16	(3 << 3)
#define BR_DIV32	(4 << 3)
#define BR_DIV64	(5 << 3)
#define BR_DIV128	(6 << 3)
#define BR_DIV256	(7 << 3)
#define MASTER		4
#define SLAVE		0
#define CPOL0		0
#define CPOL1		2
#define CPHA0		0
#define CPHA1		1

// SPI related defines - SPI_CR2
#define BDM_2LINE	0
#define BDM_1LINE	128
#define BDOE_INPUT	0
#define BDOE_OUTPUT	64
#define CRCEN_OFF	0
#define CRCEN_ON	32
#define CRCNEXT_TXBUF	0
#define CRCNEXT_TXCRC	16
#define FULL_DUPLEX	0
#define OUTPUT_DISABLE	4
#define SSM_DISABLE	0
#define SSM_ENABLE	2
#define SSI_SLAVE	0
#define SSI_MASTER	1

// SPI related defines - SPI_ICR
#define TXIE_MASKED	0
#define TXIE_ENABLED	128
#define RXIE_MASKED	0
#define RXIE_ENABLED	64
#define ERRIE_MASKED	0
#define ERRIE_ENABLED	32
#define WKIE_MASKED	0
#define WKIE_ENABLED	16

// SPI related defines - SPI_SR
#define SPI_NOT_BUSY	0
#define SPI_BUSY	128
#define NO_OVERRUN	0
#define OVERRUN		64
#define NO_MODE_FAULT	0
#define MODE_FAULT	32
#define CRC_MATCHES	0
#define CRC_NO_MATCH	16
#define NO_WAKEUP	0
#define WAKEUP		8
#define TXE		2
#define RXNE		1

///////
//
// NRF24L01 defines
//
///////
#define R_REGISTER		0x00 // 000AAAAA
#define W_REGISTER		0x20 // 001AAAAA
#define R_RX_PAYLOAD		0x61 // 01100001
#define W_TX_PAYLOAD		0xa0 // 10100000
#define FLUSH_TX		0xe1 // 11100001
#define FLUSH_RX		0xe2 // 11100010
#define REUSE_TX_PL		0xe3 // 11100011
#define R_RX_PL_WID		0x60 // 01100000
#define W_ACK_PAYLOAD		0xa8 // 10101PPP
#define W_TX_PAYLOAD_NO_ACK	0xb0 // 10110000
#define NOP			0xff // 11111111
#define CONFIG			0x00
#define    MASK_RX_DR		(1 << 6)
#define    MASK_TX_DS		(1 << 5)
#define    MASK_MAX_RT		(1 << 4)
#define    EN_CRC		(1 << 3)
#define    CRCO			(1 << 2)
#define    PWR_UP		(1 << 1)
#define    PRIM_RX		(1 << 0)
#define      PRX		(1 << 0)
#define      PTX		0
#define EN_AA			0x01
#define    ENAA_P5		(1 << 5)
#define    ENAA_P4		(1 << 4)
#define    ENAA_P3		(1 << 3)
#define    ENAA_P2		(1 << 2)
#define    ENAA_P1		(1 << 1)
#define    ENAA_P0		(1 << 0)
#define EN_RXADDR		0x02
#define    ERX_P5		(1 << 5)
#define    ERX_P4		(1 << 4)
#define    ERX_P3		(1 << 3)
#define    ERX_P2		(1 << 2)
#define    ERX_P1		(1 << 1)
#define    ERX_P0		(1 << 0)
#define SETUP_AW		0x03
#define    AW3			1
#define    AW4			2
#define    AW5			3
#define SETUP_RETR		0x4
#define    ARD0250		0x00
#define    ARD0500		0x01
#define    ARD0750		0x02
#define    ARD1000		0x03
#define    ARD1250		0x04
#define    ARD1500		0x05
#define    ARD1750		0x06
#define    ARD2000		0x07
#define    ARD2250		0x08
#define    ARD2500		0x09
#define    ARD2750		0x0a
#define    ARD3000		0x0b
#define    ARD3250		0x0c
#define    ARD3500		0x0d
#define    ARD3750		0x0e
#define    ARD4000		0x0f
#define    ARC00		0x00
#define    ARC01		0x01
#define    ARC02		0x02
#define    ARC03		0x03
#define    ARC04		0x04
#define    ARC05		0x05
#define    ARC06		0x06
#define    ARC07		0x07
#define    ARC08		0x08
#define    ARC09		0x09
#define    ARC10		0x0a
#define    ARC11		0x0b
#define    ARC12		0x0c
#define    ARC13		0x0d
#define    ARC14		0x0e
#define    ARC15		0x0f
#define RF_CH			0x05
#define RF_SETUP		0x06
#define    CONT_WAVE		(1 << 7)
#define    RF_DR_LOW		(1 << 5)
#define    PLL_LOCK		(1 << 4)
#define    RF_DR_HIGH		(1 << 3)
#define    RF_PWR_MAX		(3 << 1)
#define    RF_PWR_HIGH		(2 << 1)
#define    RF_PWR_MED		(1 << 1)
#define    RF_PWR_LOW		(0 << 1)
#define STATUS			0x07
#define    RX_DR		(1 << 6)
#define    TX_DS		(1 << 5)
#define    MAX_RT		(1 << 4)
#define    RX_P_0		(0 << 1)
#define    RX_P_1		(1 << 1)
#define    RX_P_2		(2 << 1)
#define    RX_P_3		(3 << 1)
#define    RX_P_4		(4 << 1)
#define    RX_P_5		(5 << 1)
#define    RX_EMPTY		(7 << 1)

#define RX_ADDR_P0		0x0a
#define RX_ADDR_P1		0x0b
#define RX_ADDR_P2		0x0c
#define RX_ADDR_P3		0x0d
#define RX_ADDR_P4		0x0e
#define RX_ADDR_P5		0x0f
#define TX_ADDR			0x10
#define RX_PW_P0		0x11
#define RX_PW_P1		0x12
#define RX_PW_P2		0x13
#define RX_PW_P3		0x14
#define RX_PW_P4		0x15
#define RX_PW_P5		0x16

#define W_RX_PAYLOAD		0x61
#define W_TX_PAYLOAD		0xa0

#define FIFO_STATUS		0x17
#define    TX_REUSE		(1 << 6)
#define    TX_FULL		(1 << 5)
#define    TX_EMPTY		(1 << 4)
#define    RX_FULL		(1 << 1)
#define    RX_EMPTY_FIFO	(1 << 0)
