;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.8.0 #10562 (Linux)
;--------------------------------------------------------
	.module ds18b20
	.optsdcc -mstm8
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _segmentMap
	.globl _main
	.globl _timer_isr
	.globl _rt_one_second_increment
	.globl _read_display_temp
	.globl _DS18B20_ReadTemperature
	.globl _DS18B20_ReadByte
	.globl _DS18B20_WriteByte
	.globl _DS18B20_Init
	.globl __delay_ms
	.globl __delay_us
	.globl _tm1637DisplayDecimal
	.globl _tm1637Init
	.globl _InitializeUART
	.globl _print_byte_hex
	.globl _UARTPrintF
	.globl _delay
	.globl _InitializeSystemClock
	.globl _delayTenMicro
	.globl _PIDController_Update
	.globl _PIDController_Init
	.globl _sprintf
	.globl _fast
	.globl _pid
	.globl _internteller
	.globl _alarmset
	.globl _real_time
	.globl _tm1637SetBrightness
	.globl __tm1637Start
	.globl __tm1637Stop
	.globl __tm1637ReadResult
	.globl __tm1637WriteByte
	.globl __tm1637ClkHigh
	.globl __tm1637ClkLow
	.globl __tm1637DioHigh
	.globl __tm1637DioLow
	.globl _heater_on
	.globl _heater_off
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area DATA
_real_time::
	.ds 3
_alarmset::
	.ds 1
_internteller::
	.ds 2
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area INITIALIZED
_pid::
	.ds 56
_fast::
	.ds 1
;--------------------------------------------------------
; Stack segment in internal ram 
;--------------------------------------------------------
	.area	SSEG
__start__stack:
	.ds	1

;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area DABS (ABS)

; default segment ordering for linker
	.area HOME
	.area GSINIT
	.area GSFINAL
	.area CONST
	.area INITIALIZER
	.area CODE

;--------------------------------------------------------
; interrupt vector 
;--------------------------------------------------------
	.area HOME
__interrupt_vect:
	int s_GSINIT ; reset
	int 0x000000 ; trap
	int 0x000000 ; int0
	int 0x000000 ; int1
	int 0x000000 ; int2
	int 0x000000 ; int3
	int 0x000000 ; int4
	int 0x000000 ; int5
	int _timer_isr ; int6
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area HOME
	.area GSINIT
	.area GSFINAL
	.area GSINIT
__sdcc_gs_init_startup:
__sdcc_init_data:
; stm8_genXINIT() start
	ldw x, #l_DATA
	jreq	00002$
00001$:
	clr (s_DATA - 1, x)
	decw x
	jrne	00001$
00002$:
	ldw	x, #l_INITIALIZER
	jreq	00004$
00003$:
	ld	a, (s_INITIALIZER - 1, x)
	ld	(s_INITIALIZED - 1, x), a
	decw	x
	jrne	00003$
00004$:
; stm8_genXINIT() end
	.area GSFINAL
	jp	__sdcc_program_startup
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area HOME
	.area HOME
__sdcc_program_startup:
	jp	_main
;	return from main will return to caller
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area CODE
;	ds18b20.c: 62: void delayTenMicro (void) {
;	-----------------------------------------
;	 function delayTenMicro
;	-----------------------------------------
_delayTenMicro:
;	ds18b20.c: 64: for (a = 0; a < 50; ++a)
	ld	a, #0x32
	ld	xl, a
00104$:
;	ds18b20.c: 65: __asm__("nop");
	nop
	ld	a, xl
	dec	a
	ld	xl, a
;	ds18b20.c: 64: for (a = 0; a < 50; ++a)
	tnz	a
	jrne	00104$
;	ds18b20.c: 66: }
	ret
;	ds18b20.c: 70: void InitializeSystemClock() {
;	-----------------------------------------
;	 function InitializeSystemClock
;	-----------------------------------------
_InitializeSystemClock:
;	ds18b20.c: 71: CLK_ICKR = 0;                       //  Reset the Internal Clock Register.
	mov	0x50c0+0, #0x00
;	ds18b20.c: 72: CLK_ICKR = CLK_HSIEN;               //  Enable the HSI.
	mov	0x50c0+0, #0x01
;	ds18b20.c: 73: CLK_ECKR = 0;                       //  Disable the external clock.
	mov	0x50c1+0, #0x00
;	ds18b20.c: 74: while ((CLK_ICKR & CLK_HSIRDY) == 0);       //  Wait for the HSI to be ready for use.
00101$:
	ld	a, 0x50c0
	bcp	a, #0x02
	jreq	00101$
;	ds18b20.c: 75: CLK_CKDIVR = 0;                     //  Ensure the clocks are running at full speed.
	mov	0x50c6+0, #0x00
;	ds18b20.c: 76: CLK_PCKENR1 = 0xff;                 //  Enable all peripheral clocks.
	mov	0x50c7+0, #0xff
;	ds18b20.c: 77: CLK_PCKENR2 = 0xff;                 //  Ditto.
	mov	0x50ca+0, #0xff
;	ds18b20.c: 78: CLK_CCOR = 0;                       //  Turn off CCO.
	mov	0x50c9+0, #0x00
;	ds18b20.c: 79: CLK_HSITRIMR = 0;                   //  Turn off any HSIU trimming.
	mov	0x50cc+0, #0x00
;	ds18b20.c: 80: CLK_SWIMCCR = 0;                    //  Set SWIM to run at clock / 2.
	mov	0x50cd+0, #0x00
;	ds18b20.c: 81: CLK_SWR = 0xe1;                     //  Use HSI as the clock source.
	mov	0x50c4+0, #0xe1
;	ds18b20.c: 82: CLK_SWCR = 0;                       //  Reset the clock switch control register.
	mov	0x50c5+0, #0x00
;	ds18b20.c: 83: CLK_SWCR = CLK_SWEN;                //  Enable switching.
	mov	0x50c5+0, #0x02
;	ds18b20.c: 84: while ((CLK_SWCR & CLK_SWBSY) != 0);        //  Pause while the clock switch is busy.
00104$:
	ld	a, 0x50c5
	srl	a
	jrc	00104$
;	ds18b20.c: 85: }
	ret
;	ds18b20.c: 86: void delay (int time_ms) {
;	-----------------------------------------
;	 function delay
;	-----------------------------------------
_delay:
	sub	sp, #10
;	ds18b20.c: 88: for (x = 0; x < 1036*time_ms; ++x)
	clrw	x
	ldw	(0x03, sp), x
	ldw	(0x01, sp), x
	ldw	x, (0x0d, sp)
	pushw	x
	push	#0x0c
	push	#0x04
	call	__mulint
	addw	sp, #4
	ldw	(0x09, sp), x
00103$:
	ldw	y, (0x09, sp)
	ldw	(0x07, sp), y
	ld	a, (0x07, sp)
	rlc	a
	clr	a
	sbc	a, #0x00
	ld	(0x06, sp), a
	ld	(0x05, sp), a
	ldw	x, (0x03, sp)
	cpw	x, (0x07, sp)
	ld	a, (0x02, sp)
	sbc	a, (0x06, sp)
	ld	a, (0x01, sp)
	sbc	a, (0x05, sp)
	jrsge	00105$
;	ds18b20.c: 89: __asm__("nop");
	nop
;	ds18b20.c: 88: for (x = 0; x < 1036*time_ms; ++x)
	ldw	y, (0x03, sp)
	addw	y, #0x0001
	ld	a, (0x02, sp)
	adc	a, #0x00
	ld	xl, a
	ld	a, (0x01, sp)
	adc	a, #0x00
	ld	xh, a
	ldw	(0x03, sp), y
	ldw	(0x01, sp), x
	jra	00103$
00105$:
;	ds18b20.c: 90: }
	addw	sp, #10
	ret
;	ds18b20.c: 93: void UARTPrintF (char *message) {
;	-----------------------------------------
;	 function UARTPrintF
;	-----------------------------------------
_UARTPrintF:
;	ds18b20.c: 94: char *ch = message;
	ldw	x, (0x03, sp)
;	ds18b20.c: 95: while (*ch) {
00104$:
	ld	a, (x)
	jrne	00130$
	ret
00130$:
;	ds18b20.c: 96: UART1_DR = (unsigned char) *ch;     //  Put the next character into the data transmission register.
	ld	0x5231, a
;	ds18b20.c: 97: while ((UART1_SR & SR_TXE) == 0);   //  Wait for transmission to complete.
00101$:
	ld	a, 0x5230
	jrpl	00101$
;	ds18b20.c: 98: ch++;                               //  Grab the next character.
	incw	x
	jra	00104$
;	ds18b20.c: 100: }
	ret
;	ds18b20.c: 109: void print_byte_hex (unsigned char buffer) {
;	-----------------------------------------
;	 function print_byte_hex
;	-----------------------------------------
_print_byte_hex:
	sub	sp, #12
;	ds18b20.c: 112: a = (buffer >> 4);
	ld	a, (0x0f, sp)
	swap	a
	and	a, #0x0f
	clrw	x
	ld	xl, a
;	ds18b20.c: 113: if (a > 9)
	cpw	x, #0x0009
	jrsle	00102$
;	ds18b20.c: 114: a = a + 'a' - 10;
	addw	x, #0x0057
	ldw	(0x0b, sp), x
	jra	00103$
00102$:
;	ds18b20.c: 116: a += '0'; 
	addw	x, #0x0030
	ldw	(0x0b, sp), x
00103$:
;	ds18b20.c: 117: b = buffer & 0x0f;
	ld	a, (0x0f, sp)
	and	a, #0x0f
	ld	xl, a
	clr	a
	ld	xh, a
;	ds18b20.c: 118: if (b > 9)
	cpw	x, #0x0009
	jrsle	00105$
;	ds18b20.c: 119: b = b + 'a' - 10;
	addw	x, #0x0057
	ldw	(0x09, sp), x
	jra	00106$
00105$:
;	ds18b20.c: 121: b += '0'; 
	addw	x, #0x0030
	ldw	(0x09, sp), x
00106$:
;	ds18b20.c: 122: message[0] = a;
	ldw	y, sp
	incw	y
	ld	a, (0x0c, sp)
	ld	(y), a
;	ds18b20.c: 123: message[1] = b;
	ldw	x, y
	incw	x
	ld	a, (0x0a, sp)
	ld	(x), a
;	ds18b20.c: 124: message[2] = 0;
	ldw	x, y
	incw	x
	incw	x
	clr	(x)
;	ds18b20.c: 125: UARTPrintF (message);
	pushw	y
	call	_UARTPrintF
;	ds18b20.c: 126: }
	addw	sp, #14
	ret
;	ds18b20.c: 131: void InitializeUART() {
;	-----------------------------------------
;	 function InitializeUART
;	-----------------------------------------
_InitializeUART:
;	ds18b20.c: 141: UART1_CR1 = 0;
	mov	0x5234+0, #0x00
;	ds18b20.c: 142: UART1_CR2 = 0;
	mov	0x5235+0, #0x00
;	ds18b20.c: 143: UART1_CR4 = 0;
	mov	0x5237+0, #0x00
;	ds18b20.c: 144: UART1_CR3 = 0;
	mov	0x5236+0, #0x00
;	ds18b20.c: 145: UART1_CR5 = 0;
	mov	0x5238+0, #0x00
;	ds18b20.c: 146: UART1_GTR = 0;
	mov	0x5239+0, #0x00
;	ds18b20.c: 147: UART1_PSCR = 0;
	mov	0x523a+0, #0x00
;	ds18b20.c: 151: UNSET (UART1_CR1, CR1_M);        //  8 Data bits.
	bres	21044, #4
;	ds18b20.c: 152: UNSET (UART1_CR1, CR1_PCEN);     //  Disable parity.
	bres	21044, #2
;	ds18b20.c: 153: UNSET (UART1_CR3, CR3_STOPH);    //  1 stop bit.
	bres	21046, #5
;	ds18b20.c: 154: UNSET (UART1_CR3, CR3_STOPL);    //  1 stop bit.
	bres	21046, #4
;	ds18b20.c: 155: UART1_BRR2 = 0x0a;      //  Set the baud rate registers to 115200 baud
	mov	0x5233+0, #0x0a
;	ds18b20.c: 156: UART1_BRR1 = 0x08;      //  based upon a 16 MHz system clock.
	mov	0x5232+0, #0x08
;	ds18b20.c: 160: UNSET (UART1_CR2, CR2_TEN);      //  Disable transmit.
	bres	21045, #3
;	ds18b20.c: 161: UNSET (UART1_CR2, CR2_REN);      //  Disable receive.
	bres	21045, #2
;	ds18b20.c: 165: SET (UART1_CR3, CR3_CPOL);
	bset	21046, #2
;	ds18b20.c: 166: SET (UART1_CR3, CR3_CPHA);
	bset	21046, #1
;	ds18b20.c: 167: SET (UART1_CR3, CR3_LBCL);
	bset	21046, #0
;	ds18b20.c: 171: SET (UART1_CR2, CR2_TEN);
	bset	21045, #3
;	ds18b20.c: 172: SET (UART1_CR2, CR2_REN);
	bset	21045, #2
;	ds18b20.c: 173: UART1_CR3 = CR3_CLKEN;
	mov	0x5236+0, #0x08
;	ds18b20.c: 174: }
	ret
;	ds18b20.c: 201: void tm1637Init(void)
;	-----------------------------------------
;	 function tm1637Init
;	-----------------------------------------
_tm1637Init:
;	ds18b20.c: 203: tm1637SetBrightness(4);
	push	#0x04
	call	_tm1637SetBrightness
	pop	a
;	ds18b20.c: 204: }
	ret
;	ds18b20.c: 208: void tm1637DisplayDecimal(long TT,unsigned int displaySeparator)
;	-----------------------------------------
;	 function tm1637DisplayDecimal
;	-----------------------------------------
_tm1637DisplayDecimal:
	sub	sp, #11
;	ds18b20.c: 210: unsigned int v = TT & 0x0000FFFF;
	ldw	y, (0x10, sp)
;	ds18b20.c: 216: for (ii = 0; ii < 4; ++ii) {
	ldw	x, sp
	incw	x
	ldw	(0x08, sp), x
	clrw	x
	ldw	(0x0a, sp), x
00106$:
;	ds18b20.c: 217: digitArr[ii] = segmentMap[v % 10];
	ldw	x, (0x08, sp)
	addw	x, (0x0a, sp)
	ldw	(0x06, sp), x
	pushw	y
	ldw	x, y
	ldw	y, #0x000a
	divw	x, y
	ldw	x, y
	popw	y
	addw	x, #_segmentMap
	ld	a, (x)
	ldw	x, (0x06, sp)
	ld	(x), a
;	ds18b20.c: 218: if (ii == 2 && displaySeparator) {
	ldw	x, (0x0a, sp)
	cpw	x, #0x0002
	jrne	00102$
	ldw	x, (0x12, sp)
	jreq	00102$
;	ds18b20.c: 219: digitArr[ii] |= 1 << 7;
	ldw	x, (0x06, sp)
	ld	a, (x)
	or	a, #0x80
	ldw	x, (0x06, sp)
	ld	(x), a
00102$:
;	ds18b20.c: 221: v /= 10;
	ldw	x, y
	ldw	y, #0x000a
	divw	x, y
	exgw	x, y
;	ds18b20.c: 216: for (ii = 0; ii < 4; ++ii) {
	ldw	x, (0x0a, sp)
	incw	x
	ldw	(0x0a, sp), x
	cpw	x, #0x0004
	jrc	00106$
;	ds18b20.c: 224: _tm1637Start();
	call	__tm1637Start
;	ds18b20.c: 225: _tm1637WriteByte(0x40);
	push	#0x40
	call	__tm1637WriteByte
	pop	a
;	ds18b20.c: 226: _tm1637ReadResult();
	call	__tm1637ReadResult
;	ds18b20.c: 227: _tm1637Stop();
	call	__tm1637Stop
;	ds18b20.c: 229: _tm1637Start();
	call	__tm1637Start
;	ds18b20.c: 230: _tm1637WriteByte(0xc0);
	push	#0xc0
	call	__tm1637WriteByte
	pop	a
;	ds18b20.c: 231: _tm1637ReadResult();
	call	__tm1637ReadResult
;	ds18b20.c: 233: for (ii = 0; ii < 4; ++ii) {
	clrw	x
	ldw	(0x0a, sp), x
00108$:
;	ds18b20.c: 234: _tm1637WriteByte(digitArr[3 - ii]);
	ld	a, (0x0b, sp)
	ld	(0x05, sp), a
	ld	a, #0x03
	sub	a, (0x05, sp)
	ld	xl, a
	rlc	a
	clr	a
	sbc	a, #0x00
	ld	xh, a
	addw	x, (0x08, sp)
	ld	a, (x)
	push	a
	call	__tm1637WriteByte
	pop	a
;	ds18b20.c: 235: _tm1637ReadResult();
	call	__tm1637ReadResult
;	ds18b20.c: 233: for (ii = 0; ii < 4; ++ii) {
	ldw	x, (0x0a, sp)
	incw	x
	ldw	(0x0a, sp), x
	cpw	x, #0x0004
	jrc	00108$
;	ds18b20.c: 238: _tm1637Stop();
	call	__tm1637Stop
;	ds18b20.c: 239: }
	addw	sp, #11
	ret
;	ds18b20.c: 243: void tm1637SetBrightness(char brightness)
;	-----------------------------------------
;	 function tm1637SetBrightness
;	-----------------------------------------
_tm1637SetBrightness:
;	ds18b20.c: 250: _tm1637Start();
	call	__tm1637Start
;	ds18b20.c: 251: _tm1637WriteByte(0x87 + brightness);
	ld	a, (0x03, sp)
	add	a, #0x87
	push	a
	call	__tm1637WriteByte
	pop	a
;	ds18b20.c: 252: _tm1637ReadResult();
	call	__tm1637ReadResult
;	ds18b20.c: 253: _tm1637Stop();
;	ds18b20.c: 254: }
	jp	__tm1637Stop
;	ds18b20.c: 256: void _tm1637Start(void)
;	-----------------------------------------
;	 function _tm1637Start
;	-----------------------------------------
__tm1637Start:
;	ds18b20.c: 258: _tm1637ClkHigh();
	call	__tm1637ClkHigh
;	ds18b20.c: 259: _tm1637DioHigh();
	call	__tm1637DioHigh
;	ds18b20.c: 260: delay(5);
	push	#0x05
	push	#0x00
	call	_delay
	addw	sp, #2
;	ds18b20.c: 261: _tm1637DioLow();
;	ds18b20.c: 262: }
	jp	__tm1637DioLow
;	ds18b20.c: 264: void _tm1637Stop(void)
;	-----------------------------------------
;	 function _tm1637Stop
;	-----------------------------------------
__tm1637Stop:
;	ds18b20.c: 266: _tm1637ClkLow();
	call	__tm1637ClkLow
;	ds18b20.c: 267: delay(5);
	push	#0x05
	push	#0x00
	call	_delay
	addw	sp, #2
;	ds18b20.c: 268: _tm1637DioLow();
	call	__tm1637DioLow
;	ds18b20.c: 269: delay(5);
	push	#0x05
	push	#0x00
	call	_delay
	addw	sp, #2
;	ds18b20.c: 270: _tm1637ClkHigh();
	call	__tm1637ClkHigh
;	ds18b20.c: 271: delay(5);
	push	#0x05
	push	#0x00
	call	_delay
	addw	sp, #2
;	ds18b20.c: 272: _tm1637DioHigh();
;	ds18b20.c: 273: }
	jp	__tm1637DioHigh
;	ds18b20.c: 275: void _tm1637ReadResult(void)
;	-----------------------------------------
;	 function _tm1637ReadResult
;	-----------------------------------------
__tm1637ReadResult:
;	ds18b20.c: 277: _tm1637ClkLow();
	call	__tm1637ClkLow
;	ds18b20.c: 278: delay(5);
	push	#0x05
	push	#0x00
	call	_delay
	addw	sp, #2
;	ds18b20.c: 280: _tm1637ClkHigh();
	call	__tm1637ClkHigh
;	ds18b20.c: 281: delay(5);
	push	#0x05
	push	#0x00
	call	_delay
	addw	sp, #2
;	ds18b20.c: 282: _tm1637ClkLow();
;	ds18b20.c: 283: }
	jp	__tm1637ClkLow
;	ds18b20.c: 285: void _tm1637WriteByte(unsigned char b)
;	-----------------------------------------
;	 function _tm1637WriteByte
;	-----------------------------------------
__tm1637WriteByte:
	sub	sp, #2
;	ds18b20.c: 287: for (ii = 0; ii < 8; ++ii) {
	clrw	x
	ldw	(0x01, sp), x
00105$:
;	ds18b20.c: 288: _tm1637ClkLow();
	call	__tm1637ClkLow
;	ds18b20.c: 289: if (b & 0x01) {
	ld	a, (0x05, sp)
	srl	a
	jrnc	00102$
;	ds18b20.c: 290: _tm1637DioHigh();
	call	__tm1637DioHigh
	jra	00103$
00102$:
;	ds18b20.c: 293: _tm1637DioLow();
	call	__tm1637DioLow
00103$:
;	ds18b20.c: 295: delay(15);
	push	#0x0f
	push	#0x00
	call	_delay
	addw	sp, #2
;	ds18b20.c: 296: b >>= 1;
	ld	a, (0x05, sp)
	srl	a
	ld	(0x05, sp), a
;	ds18b20.c: 297: _tm1637ClkHigh();
	call	__tm1637ClkHigh
;	ds18b20.c: 298: delay(15);
	push	#0x0f
	push	#0x00
	call	_delay
	addw	sp, #2
;	ds18b20.c: 287: for (ii = 0; ii < 8; ++ii) {
	ldw	x, (0x01, sp)
	incw	x
	ldw	(0x01, sp), x
	cpw	x, #0x0008
	jrslt	00105$
;	ds18b20.c: 300: }
	addw	sp, #2
	ret
;	ds18b20.c: 304: void _tm1637ClkHigh(void)
;	-----------------------------------------
;	 function _tm1637ClkHigh
;	-----------------------------------------
__tm1637ClkHigh:
;	ds18b20.c: 309: PD_ODR |= 1 << 2;
	bset	20495, #2
;	ds18b20.c: 310: }
	ret
;	ds18b20.c: 312: void _tm1637ClkLow(void)
;	-----------------------------------------
;	 function _tm1637ClkLow
;	-----------------------------------------
__tm1637ClkLow:
;	ds18b20.c: 316: PD_ODR &= ~(1 << 2);
	bres	20495, #2
;	ds18b20.c: 320: }
	ret
;	ds18b20.c: 322: void _tm1637DioHigh(void)
;	-----------------------------------------
;	 function _tm1637DioHigh
;	-----------------------------------------
__tm1637DioHigh:
;	ds18b20.c: 326: PD_ODR |= 1 << 3;
	bset	20495, #3
;	ds18b20.c: 328: }
	ret
;	ds18b20.c: 330: void _tm1637DioLow(void)
;	-----------------------------------------
;	 function _tm1637DioLow
;	-----------------------------------------
__tm1637DioLow:
;	ds18b20.c: 332: PD_ODR &= ~(1 << 3);
	bres	20495, #3
;	ds18b20.c: 337: }
	ret
;	ds18b20.c: 340: void _delay_us(unsigned int i)
;	-----------------------------------------
;	 function _delay_us
;	-----------------------------------------
__delay_us:
;	ds18b20.c: 342: i *= 3; 
	ldw	x, (0x03, sp)
	sllw	x
	addw	x, (0x03, sp)
;	ds18b20.c: 343: while(--i);
	ldw	(0x03, sp), x
00101$:
	decw	x
	tnzw	x
	jrne	00101$
;	ds18b20.c: 344: }
	ret
;	ds18b20.c: 346: void _delay_ms(unsigned int i)
;	-----------------------------------------
;	 function _delay_ms
;	-----------------------------------------
__delay_ms:
;	ds18b20.c: 348: while(i--)
	ldw	x, (0x03, sp)
00101$:
	ldw	y, x
	decw	x
	tnzw	y
	jrne	00117$
	ret
00117$:
;	ds18b20.c: 350: _delay_us(1000);
	pushw	x
	push	#0xe8
	push	#0x03
	call	__delay_us
	addw	sp, #2
	popw	x
	jra	00101$
;	ds18b20.c: 352: }
	ret
;	ds18b20.c: 356: void DS18B20_Init(void)
;	-----------------------------------------
;	 function DS18B20_Init
;	-----------------------------------------
_DS18B20_Init:
;	ds18b20.c: 358: DS18B20_DQ_OUT;   
	bset	20482, #3
;	ds18b20.c: 359: DS18B20_DQ_PUSH_PULL;    
	bset	20483, #3
;	ds18b20.c: 360: DS18B20_DQ_HIGH;   
	bset	20480, #3
;	ds18b20.c: 361: _delay_us(10);
	push	#0x0a
	push	#0x00
	call	__delay_us
	addw	sp, #2
;	ds18b20.c: 362: DS18B20_DQ_LOW;   
	bres	20480, #3
;	ds18b20.c: 363: _delay_us(600);     //????
	push	#0x58
	push	#0x02
	call	__delay_us
	addw	sp, #2
;	ds18b20.c: 365: DS18B20_DQ_IN;   
	bres	20482, #3
;	ds18b20.c: 366: DS18B20_DQ_PULL_UP;    
	bset	20483, #3
;	ds18b20.c: 367: _delay_us(100);     
	push	#0x64
	push	#0x00
	call	__delay_us
	addw	sp, #2
;	ds18b20.c: 369: _delay_us(400);
	push	#0x90
	push	#0x01
	call	__delay_us
	addw	sp, #2
;	ds18b20.c: 370: }
	ret
;	ds18b20.c: 373: void DS18B20_WriteByte(unsigned char _data)
;	-----------------------------------------
;	 function DS18B20_WriteByte
;	-----------------------------------------
_DS18B20_WriteByte:
	push	a
;	ds18b20.c: 377: DS18B20_DQ_OUT;
	bset	20482, #3
;	ds18b20.c: 378: for (i = 0; i < 8; i++)
	clr	(0x01, sp)
00104$:
;	ds18b20.c: 380: DS18B20_DQ_LOW;
	bres	20480, #3
;	ds18b20.c: 381: _delay_us(2);
	push	#0x02
	push	#0x00
	call	__delay_us
	addw	sp, #2
;	ds18b20.c: 382: if (_data & 0x01)
	ld	a, (0x04, sp)
	srl	a
	jrnc	00102$
;	ds18b20.c: 384: DS18B20_DQ_HIGH;
	bset	20480, #3
00102$:
;	ds18b20.c: 386: _data >>= 1;
	srl	(0x04, sp)
;	ds18b20.c: 387: _delay_us(60);
	push	#0x3c
	push	#0x00
	call	__delay_us
	addw	sp, #2
;	ds18b20.c: 388: DS18B20_DQ_HIGH;
	bset	20480, #3
;	ds18b20.c: 378: for (i = 0; i < 8; i++)
	inc	(0x01, sp)
	ld	a, (0x01, sp)
	cp	a, #0x08
	jrc	00104$
;	ds18b20.c: 390: }
	pop	a
	ret
;	ds18b20.c: 392: unsigned char DS18B20_ReadByte(void)
;	-----------------------------------------
;	 function DS18B20_ReadByte
;	-----------------------------------------
_DS18B20_ReadByte:
;	ds18b20.c: 394: unsigned char i = 0, _data = 0;
	clr	a
	ld	xh, a
;	ds18b20.c: 396: for (i = 0; i < 8; i++)
	clr	a
	ld	xl, a
00104$:
;	ds18b20.c: 398: DS18B20_DQ_OUT;
	bset	20482, #3
;	ds18b20.c: 399: DS18B20_DQ_LOW;
	ld	a, 0x5000
	and	a, #0xf7
	ld	0x5000, a
;	ds18b20.c: 400: _delay_us(5);
	pushw	x
	push	#0x05
	push	#0x00
	call	__delay_us
	addw	sp, #2
	popw	x
;	ds18b20.c: 401: _data >>= 1;
	rlwa	x
	srl	a
	rrwa	x
;	ds18b20.c: 402: DS18B20_DQ_HIGH;
	bset	20480, #3
;	ds18b20.c: 403: DS18B20_DQ_IN;
	bres	20482, #3
;	ds18b20.c: 404: if (DS18B20_DQ_VALUE)
	ld	a, 0x5001
	bcp	a, #0x08
	jreq	00102$
;	ds18b20.c: 406: _data |= 0x80;
	sllw	x
	scf
	rrcw	x
00102$:
;	ds18b20.c: 408: DS18B20_DQ_OUT; 
	bset	20482, #3
;	ds18b20.c: 409: DS18B20_DQ_HIGH;
	bset	20480, #3
;	ds18b20.c: 410: _delay_us(60);
	pushw	x
	push	#0x3c
	push	#0x00
	call	__delay_us
	addw	sp, #2
	popw	x
;	ds18b20.c: 396: for (i = 0; i < 8; i++)
	ld	a, xl
	inc	a
	ld	xl, a
	cp	a, #0x08
	jrc	00104$
;	ds18b20.c: 413: return _data;
	ld	a, xh
;	ds18b20.c: 414: }
	ret
;	ds18b20.c: 416: float DS18B20_ReadTemperature(void)
;	-----------------------------------------
;	 function DS18B20_ReadTemperature
;	-----------------------------------------
_DS18B20_ReadTemperature:
	sub	sp, #14
;	ds18b20.c: 430: DS18B20_Init();
	call	_DS18B20_Init
;	ds18b20.c: 431: DS18B20_WriteByte(0xcc);
	push	#0xcc
	call	_DS18B20_WriteByte
	pop	a
;	ds18b20.c: 432: DS18B20_WriteByte(0x44);
	push	#0x44
	call	_DS18B20_WriteByte
	pop	a
;	ds18b20.c: 434: DS18B20_Init();
	call	_DS18B20_Init
;	ds18b20.c: 435: DS18B20_WriteByte(0xcc);
	push	#0xcc
	call	_DS18B20_WriteByte
	pop	a
;	ds18b20.c: 436: DS18B20_WriteByte(0xbe);
	push	#0xbe
	call	_DS18B20_WriteByte
	pop	a
;	ds18b20.c: 438: temp = DS18B20_ReadByte();
	call	_DS18B20_ReadByte
;	ds18b20.c: 439: t = (((temp & 0xf0) >> 4) + (temp & 0x07) * 0.125); 
	clrw	y
	push	a
	and	a, #0xf0
	ld	xl, a
	clr	a
	ld	xh, a
	pop	a
	sraw	x
	sraw	x
	sraw	x
	sraw	x
	ldw	(0x05, sp), x
	and	a, #0x07
	ld	xl, a
	clr	a
	ld	xh, a
	pushw	x
	call	___sint2fs
	addw	sp, #2
	pushw	x
	pushw	y
	clrw	x
	pushw	x
	push	#0x00
	push	#0x3e
	call	___fsmul
	addw	sp, #8
	ldw	(0x01, sp), y
	pushw	x
	ldw	y, (0x07, sp)
	pushw	y
	call	___sint2fs
	addw	sp, #2
	ldw	(0x0b, sp), x
	ldw	x, (0x03, sp)
	pushw	x
	ldw	x, (0x0d, sp)
	pushw	x
	pushw	y
	call	___fsadd
	addw	sp, #8
	ldw	(0x0d, sp), x
	ldw	(0x0b, sp), y
;	ds18b20.c: 440: temp = DS18B20_ReadByte();
	call	_DS18B20_ReadByte
;	ds18b20.c: 441: t += ((temp & 0x0f) << 4);
	clrw	y
	and	a, #0x0f
	ld	xl, a
	clr	a
	ld	xh, a
	sllw	x
	sllw	x
	sllw	x
	sllw	x
	pushw	x
	call	___sint2fs
	addw	sp, #2
	pushw	x
	pushw	y
	ldw	x, (0x11, sp)
	pushw	x
	ldw	x, (0x11, sp)
	pushw	x
	call	___fsadd
;	ds18b20.c: 442: return t;
;	ds18b20.c: 443: }
	addw	sp, #22
	ret
;	ds18b20.c: 465: void read_display_temp(float temp1) //every second called by interrupt
;	-----------------------------------------
;	 function read_display_temp
;	-----------------------------------------
_read_display_temp:
	sub	sp, #40
;	ds18b20.c: 469: char boodsch[12]="temp=\r\n";
	ldw	x, sp
	incw	x
	ldw	(0x17, sp), x
	ld	a, #0x74
	ld	(x), a
	ldw	x, (0x17, sp)
	incw	x
	ld	a, #0x65
	ld	(x), a
	ldw	x, (0x17, sp)
	incw	x
	incw	x
	ld	a, #0x6d
	ld	(x), a
	ldw	x, (0x17, sp)
	ld	a, #0x70
	ld	(0x0003, x), a
	ldw	x, (0x17, sp)
	ld	a, #0x3d
	ld	(0x0004, x), a
	ldw	x, (0x17, sp)
	ld	a, #0x0d
	ld	(0x0005, x), a
	ldw	x, (0x17, sp)
	ld	a, #0x0a
	ld	(0x0006, x), a
	ldw	x, (0x17, sp)
	clr	(0x0007, x)
	ldw	x, (0x17, sp)
	clr	(0x0008, x)
	ldw	x, (0x17, sp)
	clr	(0x0009, x)
	ldw	x, (0x17, sp)
	clr	(0x000a, x)
	ldw	x, (0x17, sp)
	addw	x, #0x000b
	clr	(x)
;	ds18b20.c: 473: measurement = DS18B20_ReadTemperature() ; //multiply with 100 to get everything on the 4 digit display 
	call	_DS18B20_ReadTemperature
	ldw	(0x1f, sp), x
	ldw	(0x1d, sp), y
;	ds18b20.c: 474: objTemp = measurement*100;
	ldw	x, (0x1f, sp)
	pushw	x
	ldw	x, (0x1f, sp)
	pushw	x
	clrw	x
	pushw	x
	push	#0xc8
	push	#0x42
	call	___fsmul
	addw	sp, #8
	ldw	(0x27, sp), x
	ldw	(0x25, sp), y
;	ds18b20.c: 477: while (objTemp > 1000) {
	clrw	x
	ldw	(0x21, sp), x
00101$:
	ldw	x, (0x27, sp)
	pushw	x
	ldw	x, (0x27, sp)
	pushw	x
	clrw	x
	pushw	x
	push	#0x7a
	push	#0x44
	call	___fslt
	addw	sp, #8
	tnz	a
	jreq	00123$
;	ds18b20.c: 478: vierde+=1;
	ldw	x, (0x21, sp)
	incw	x
	ldw	(0x21, sp), x
;	ds18b20.c: 479: objTemp-=1000;
	clrw	x
	pushw	x
	push	#0x7a
	push	#0x44
	ldw	x, (0x2b, sp)
	pushw	x
	ldw	x, (0x2b, sp)
	pushw	x
	call	___fssub
	addw	sp, #8
	ldw	(0x27, sp), x
	ldw	(0x25, sp), y
	jra	00101$
;	ds18b20.c: 481: while (objTemp > 100) {
00123$:
	ldw	y, (0x21, sp)
	ldw	(0x15, sp), y
	clrw	x
	ldw	(0x23, sp), x
00104$:
	ldw	x, (0x27, sp)
	pushw	x
	ldw	x, (0x27, sp)
	pushw	x
	clrw	x
	pushw	x
	push	#0xc8
	push	#0x42
	call	___fslt
	addw	sp, #8
	tnz	a
	jreq	00124$
;	ds18b20.c: 482: derde+=1;
	ldw	x, (0x23, sp)
	incw	x
	ldw	(0x23, sp), x
;	ds18b20.c: 483: objTemp-=100;
	clrw	x
	pushw	x
	push	#0xc8
	push	#0x42
	ldw	x, (0x2b, sp)
	pushw	x
	ldw	x, (0x2b, sp)
	pushw	x
	call	___fssub
	addw	sp, #8
	ldw	(0x27, sp), x
	ldw	(0x25, sp), y
	jra	00104$
;	ds18b20.c: 485: while (objTemp > 10) {
00124$:
	ldw	y, (0x23, sp)
	ldw	(0x0f, sp), y
	clrw	x
	ldw	(0x19, sp), x
00107$:
	ldw	x, (0x27, sp)
	pushw	x
	ldw	x, (0x27, sp)
	pushw	x
	clrw	x
	pushw	x
	push	#0x20
	push	#0x41
	call	___fslt
	addw	sp, #8
	tnz	a
	jreq	00125$
;	ds18b20.c: 486: tweede+=1;
	ldw	x, (0x19, sp)
	incw	x
	ldw	(0x19, sp), x
;	ds18b20.c: 487: objTemp-=10;
	clrw	x
	pushw	x
	push	#0x20
	push	#0x41
	ldw	x, (0x2b, sp)
	pushw	x
	ldw	x, (0x2b, sp)
	pushw	x
	call	___fssub
	addw	sp, #8
	ldw	(0x27, sp), x
	ldw	(0x25, sp), y
	jra	00107$
;	ds18b20.c: 489: while (objTemp > 0)
00125$:
	ldw	y, (0x19, sp)
	ldw	(0x0d, sp), y
	clrw	x
	ldw	(0x1b, sp), x
00110$:
	ldw	x, (0x27, sp)
	pushw	x
	ldw	x, (0x27, sp)
	pushw	x
	clrw	x
	pushw	x
	clrw	x
	pushw	x
	call	___fslt
	addw	sp, #8
	tnz	a
	jreq	00112$
;	ds18b20.c: 491: eerste+=1;
	ldw	x, (0x1b, sp)
	incw	x
	ldw	(0x1b, sp), x
;	ds18b20.c: 492: objTemp-=1;
	clrw	x
	pushw	x
	push	#0x80
	push	#0x3f
	ldw	x, (0x2b, sp)
	pushw	x
	ldw	x, (0x2b, sp)
	pushw	x
	call	___fssub
	addw	sp, #8
	ldw	(0x27, sp), x
	ldw	(0x25, sp), y
	jra	00110$
00112$:
;	ds18b20.c: 495: utemp=vierde*1000+derde*100+tweede*10+eerste;
	ldw	x, (0x15, sp)
	pushw	x
	push	#0xe8
	push	#0x03
	call	__mulint
	addw	sp, #4
	ldw	(0x13, sp), x
	ldw	x, (0x0f, sp)
	pushw	x
	push	#0x64
	push	#0x00
	call	__mulint
	addw	sp, #4
	addw	x, (0x13, sp)
	ldw	(0x11, sp), x
	ldw	x, (0x0d, sp)
	sllw	x
	sllw	x
	addw	x, (0x0d, sp)
	sllw	x
	addw	x, (0x11, sp)
	addw	x, (0x1b, sp)
;	ds18b20.c: 497: tm1637DisplayDecimal(utemp, 1); // eg 37:12
	clrw	y
	push	#0x01
	push	#0x00
	pushw	x
	pushw	y
	call	_tm1637DisplayDecimal
	addw	sp, #6
;	ds18b20.c: 502: PIDController_Update(&pid, temp1, measurement); 
	ldw	x, (0x1f, sp)
	pushw	x
	ldw	x, (0x1f, sp)
	pushw	x
	ldw	x, (0x31, sp)
	pushw	x
	ldw	x, (0x31, sp)
	pushw	x
	push	#<_pid
	push	#(_pid >> 8)
	call	_PIDController_Update
	addw	sp, #10
;	ds18b20.c: 503: sprintf(boodsch,"pid :%d\r\n", (int)(pid.out*10)); //todo dit moet SSD sturen of wel LED
	ldw	x, #_pid
	ldw	y, x
	ldw	y, (0x36, y)
	ldw	x, (0x34, x)
	pushw	y
	pushw	x
	clrw	x
	pushw	x
	push	#0x20
	push	#0x41
	call	___fsmul
	addw	sp, #8
	pushw	x
	pushw	y
	call	___fs2sint
	addw	sp, #4
	ldw	y, (0x17, sp)
	pushw	x
	push	#<___str_1
	push	#(___str_1 >> 8)
	pushw	y
	call	_sprintf
	addw	sp, #6
;	ds18b20.c: 504: UARTPrintF (boodsch); 
	ldw	x, (0x17, sp)
	pushw	x
	call	_UARTPrintF
;	ds18b20.c: 506: }
	addw	sp, #42
	ret
;	ds18b20.c: 509: void rt_one_second_increment (st_time *t) {
;	-----------------------------------------
;	 function rt_one_second_increment
;	-----------------------------------------
_rt_one_second_increment:
	sub	sp, #8
;	ds18b20.c: 517: t->second +=1;
	ldw	y, (0x0b, sp)
	ldw	(0x01, sp), y
	ldw	x, y
	inc	(x)
	ldw	x, (0x01, sp)
	ld	a, (x)
;	ds18b20.c: 518: if ((t->second==1)  | (t->second==21) | (t->second==41))
	ld	xl, a
	dec	a
	jrne	00134$
	ld	a, #0x01
	ld	(0x08, sp), a
	.byte 0xc1
00134$:
	clr	(0x08, sp)
00135$:
	ld	a, xl
	sub	a, #0x15
	jrne	00137$
	inc	a
	.byte 0x21
00137$:
	clr	a
00138$:
	or	a, (0x08, sp)
	ld	(0x03, sp), a
	ld	a, xl
	sub	a, #0x29
	jrne	00140$
	inc	a
	.byte 0x21
00140$:
	clr	a
00141$:
;	ds18b20.c: 520: t->heat=0;
	ldw	x, (0x01, sp)
	incw	x
	incw	x
	ldw	(0x06, sp), x
;	ds18b20.c: 518: if ((t->second==1)  | (t->second==21) | (t->second==41))
	or	a, (0x03, sp)
	jreq	00102$
;	ds18b20.c: 520: t->heat=0;
	ldw	x, (0x06, sp)
	clr	(x)
00102$:
;	ds18b20.c: 523: t->heat+=1;
	ldw	x, (0x06, sp)
	inc	(x)
;	ds18b20.c: 524: if (fast) targettemp=(int)(pid.out*2);
	btjt	_fast+0, #0, 00143$
	jra	00104$
00143$:
	ldw	x, #_pid+52
	ldw	y, x
	ldw	y, (0x2, y)
	ldw	x, (x)
	pushw	y
	pushw	x
	clrw	x
	pushw	x
	push	#0x00
	push	#0x40
	call	___fsmul
	addw	sp, #8
	pushw	x
	pushw	y
	call	___fs2sint
	addw	sp, #4
	jra	00105$
00104$:
;	ds18b20.c: 526: targettemp=(int)(pid.out);	
	ldw	x, #_pid+52
	ldw	y, x
	ldw	y, (0x2, y)
	ldw	x, (x)
	pushw	y
	pushw	x
	call	___fs2sint
	addw	sp, #4
00105$:
;	ds18b20.c: 529: if(t->heat > targettemp)
	ldw	y, (0x06, sp)
	ld	a, (y)
	ld	(0x05, sp), a
	clr	(0x04, sp)
	cpw	x, (0x04, sp)
	jrsge	00107$
;	ds18b20.c: 531: heater_off();
	call	_heater_off
	jra	00108$
00107$:
;	ds18b20.c: 535: heater_on();
	call	_heater_on
00108$:
;	ds18b20.c: 539: if(t->second > 59) {
	ldw	x, (0x01, sp)
	ld	a, (x)
	cp	a, #0x3b
	jrule	00111$
;	ds18b20.c: 540: t->second= 0;
	ldw	x, (0x01, sp)
	clr	(x)
;	ds18b20.c: 547: t->minute -=1;
	ldw	x, (0x01, sp)
	incw	x
	dec	(x)
00111$:
;	ds18b20.c: 549: }
	addw	sp, #8
	ret
;	ds18b20.c: 552: void timer_isr(void) __interrupt(BEEP_ISR) {
;	-----------------------------------------
;	 function timer_isr
;	-----------------------------------------
_timer_isr:
	clr	a
	div	x, a
;	ds18b20.c: 553: if (++internteller > 500) {
	ldw	x, _internteller+0
	incw	x
	ldw	_internteller+0, x
	cpw	x, #0x01f4
	jrule	00103$
;	ds18b20.c: 554: internteller=0;
	clrw	x
	ldw	_internteller+0, x
;	ds18b20.c: 555: rt_one_second_increment(&real_time);
	push	#<_real_time
	push	#(_real_time >> 8)
	call	_rt_one_second_increment
	addw	sp, #2
00103$:
;	ds18b20.c: 560: }
	iret
;	ds18b20.c: 564: void heater_on(void)
;	-----------------------------------------
;	 function heater_on
;	-----------------------------------------
_heater_on:
;	ds18b20.c: 566: PC_ODR = (1<<3) ; //C8 connected to SSD
	mov	0x500a+0, #0x08
;	ds18b20.c: 567: PB_ODR = (0<<5) ; //onboard LED
	mov	0x5005+0, #0x00
;	ds18b20.c: 568: }
	ret
;	ds18b20.c: 570: void heater_off(void)
;	-----------------------------------------
;	 function heater_off
;	-----------------------------------------
_heater_off:
;	ds18b20.c: 572: PC_ODR = (0<<3) ;
	mov	0x500a+0, #0x00
;	ds18b20.c: 573: PB_ODR = (1<<5) ; //onboard LED
	mov	0x5005+0, #0x20
;	ds18b20.c: 574: }
	ret
;	ds18b20.c: 576: int main () {
;	-----------------------------------------
;	 function main
;	-----------------------------------------
_main:
	sub	sp, #18
;	ds18b20.c: 584: char boodsch[12]="temp=\r\n";
	ldw	x, sp
	incw	x
	ldw	(0x0f, sp), x
	ld	a, #0x74
	ld	(x), a
	ldw	x, (0x0f, sp)
	incw	x
	ld	a, #0x65
	ld	(x), a
	ldw	x, (0x0f, sp)
	incw	x
	incw	x
	ld	a, #0x6d
	ld	(x), a
	ldw	x, (0x0f, sp)
	ld	a, #0x70
	ld	(0x0003, x), a
	ldw	x, (0x0f, sp)
	ld	a, #0x3d
	ld	(0x0004, x), a
	ldw	x, (0x0f, sp)
	ld	a, #0x0d
	ld	(0x0005, x), a
	ldw	x, (0x0f, sp)
	ld	a, #0x0a
	ld	(0x0006, x), a
	ldw	x, (0x0f, sp)
	clr	(0x0007, x)
	ldw	x, (0x0f, sp)
	clr	(0x0008, x)
	ldw	x, (0x0f, sp)
	clr	(0x0009, x)
	ldw	x, (0x0f, sp)
	clr	(0x000a, x)
	ldw	x, (0x0f, sp)
	clr	(0x000b, x)
;	ds18b20.c: 586: real_time.minute=15;
	ldw	x, #_real_time+1
	ldw	(0x0d, sp), x
	ld	a, #0x0f
	ld	(x), a
;	ds18b20.c: 587: InitializeSystemClock();
	call	_InitializeSystemClock
;	ds18b20.c: 589: BEEP_CSR = (0<<7) | (0<<6) | (1<<5) | 0x1E;
	mov	0x50f3+0, #0x3e
;	ds18b20.c: 591: PD_DDR = (1 << 3) | (1 << 2); // output mode
	mov	0x5011+0, #0x0c
;	ds18b20.c: 593: PD_DDR &=  ~(1 << 4); //PD4 input for beep?
	bres	20497, #4
;	ds18b20.c: 595: PD_CR1 = (1 << 3) | (1 << 2); // push-pull
	mov	0x5012+0, #0x0c
;	ds18b20.c: 596: PD_CR1 &= ~(1 << 4); // input with float beep?
	ld	a, 0x5012
	and	a, #0xef
	ld	0x5012, a
;	ds18b20.c: 598: PD_CR2 = (1 << 3) | (1 << 2) | (1<< 4); // up to 10MHz speed + interrupt enabled
	mov	0x5013+0, #0x1c
;	ds18b20.c: 600: EXTI_CR1 = (1<<7); //Port D external sensitivity bits7:6 10: Falling edge only
	mov	0x50a0+0, #0x80
;	ds18b20.c: 601: EXTI_CR1 &= ~(1<<6); //Port D external sensitivity bits7:6 10: Falling edge only
	ld	a, 0x50a0
	and	a, #0xbf
	ld	0x50a0, a
;	ds18b20.c: 604: PC_DDR = (1<<3) ;
	mov	0x500c+0, #0x08
;	ds18b20.c: 605: PB_DDR = (1<<5) ;
	mov	0x5007+0, #0x20
;	ds18b20.c: 607: PC_CR1 = (1<<3) ;
	mov	0x500d+0, #0x08
;	ds18b20.c: 608: PB_CR1 = (1<<5) ;
	mov	0x5008+0, #0x20
;	ds18b20.c: 611: tm1637Init();
	call	_tm1637Init
;	ds18b20.c: 613: InitializeUART();
	call	_InitializeUART
;	ds18b20.c: 615: __asm__("rim");
	rim
;	ds18b20.c: 620: PIDController_Init(&pid);
	push	#<_pid
	push	#(_pid >> 8)
	call	_PIDController_Init
	addw	sp, #2
;	ds18b20.c: 622: phase=1;
	ldw	x, #0x0001
	ldw	(0x11, sp), x
;	ds18b20.c: 623: while (1) {
00117$:
;	ds18b20.c: 627: switch (phase){
	ldw	x, (0x11, sp)
	decw	x
	jreq	00101$
	ldw	x, (0x11, sp)
	cpw	x, #0x0002
	jreq	00104$
	ldw	x, (0x11, sp)
	cpw	x, #0x0003
	jrne	00178$
	jp	00107$
00178$:
	ldw	x, (0x11, sp)
	cpw	x, #0x0004
	jrne	00181$
	jp	00110$
00181$:
	ldw	x, (0x11, sp)
	cpw	x, #0x0005
	jrne	00117$
	jp	00113$
;	ds18b20.c: 629: case 1: 
00101$:
;	ds18b20.c: 630: read_display_temp(45); //sample temp
	clrw	x
	pushw	x
	push	#0x34
	push	#0x42
	call	_read_display_temp
	addw	sp, #4
;	ds18b20.c: 631: if (real_time.minute<1) {phase =2; real_time.minute=45;
	ldw	x, (0x0d, sp)
	ld	a, (x)
	cp	a, #0x01
	jrnc	00117$
	ldw	x, #0x0002
	ldw	(0x11, sp), x
	ldw	x, (0x0d, sp)
	ld	a, #0x2d
	ld	(x), a
;	ds18b20.c: 632: fast=false;
	clr	_fast+0
;	ds18b20.c: 633: sprintf(boodsch,"to phase2\r\n"); 
	ldw	y, #___str_3
	ldw	x, (0x0f, sp)
	pushw	y
	pushw	x
	call	_sprintf
	addw	sp, #4
;	ds18b20.c: 634: UARTPrintF (boodsch); 
	ldw	x, (0x0f, sp)
	pushw	x
	call	_UARTPrintF
	addw	sp, #2
;	ds18b20.c: 636: break;
	jra	00117$
;	ds18b20.c: 638: case 2: 
00104$:
;	ds18b20.c: 639: read_display_temp(62); //sample temp
	clrw	x
	pushw	x
	push	#0x78
	push	#0x42
	call	_read_display_temp
	addw	sp, #4
;	ds18b20.c: 640: if (real_time.minute<1) {phase =3; real_time.minute=20;
	ldw	x, (0x0d, sp)
	ld	a, (x)
	cp	a, #0x01
	jrnc	00117$
	ldw	x, #0x0003
	ldw	(0x11, sp), x
	ldw	x, (0x0d, sp)
	ld	a, #0x14
	ld	(x), a
;	ds18b20.c: 641: sprintf(boodsch,"to phase3\r\n"); 
	ldw	y, #___str_4
	ldw	x, (0x0f, sp)
	pushw	y
	pushw	x
	call	_sprintf
	addw	sp, #4
;	ds18b20.c: 642: UARTPrintF (boodsch); 
	ldw	x, (0x0f, sp)
	pushw	x
	call	_UARTPrintF
	addw	sp, #2
;	ds18b20.c: 645: break;
	jp	00117$
;	ds18b20.c: 646: case 3: 
00107$:
;	ds18b20.c: 647: read_display_temp(71); //end no heating, no timer, overshoot 1degree, hence target is 72
	clrw	x
	pushw	x
	push	#0x8e
	push	#0x42
	call	_read_display_temp
	addw	sp, #4
;	ds18b20.c: 648: if (real_time.minute<1) {phase =4; real_time.minute=6;
	ldw	x, (0x0d, sp)
	ld	a, (x)
	cp	a, #0x01
	jrc	00188$
	jp	00117$
00188$:
	ldw	x, #0x0004
	ldw	(0x11, sp), x
	ldw	x, (0x0d, sp)
	ld	a, #0x06
	ld	(x), a
;	ds18b20.c: 650: sprintf(boodsch,"to phase4\r\n"); 
	ldw	y, #___str_5
	ldw	x, (0x0f, sp)
	pushw	y
	pushw	x
	call	_sprintf
	addw	sp, #4
;	ds18b20.c: 651: UARTPrintF (boodsch); 
	ldw	x, (0x0f, sp)
	pushw	x
	call	_UARTPrintF
	addw	sp, #2
;	ds18b20.c: 653: break;
	jp	00117$
;	ds18b20.c: 654: case 4: 
00110$:
;	ds18b20.c: 655: read_display_temp(78); //end no heating, no timer
	clrw	x
	pushw	x
	push	#0x9c
	push	#0x42
	call	_read_display_temp
	addw	sp, #4
;	ds18b20.c: 656: if (real_time.minute<1) {phase =5; real_time.minute=60; //end
	ldw	x, (0x0d, sp)
	ld	a, (x)
	cp	a, #0x01
	jrc	00189$
	jp	00117$
00189$:
	ldw	x, #0x0005
	ldw	(0x11, sp), x
	ldw	x, (0x0d, sp)
	ld	a, #0x3c
	ld	(x), a
;	ds18b20.c: 657: sprintf(boodsch,"to phase5\r\n"); 
	ldw	y, #___str_6
	ldw	x, (0x0f, sp)
	pushw	y
	pushw	x
	call	_sprintf
	addw	sp, #4
;	ds18b20.c: 658: UARTPrintF (boodsch); 
	ldw	x, (0x0f, sp)
	pushw	x
	call	_UARTPrintF
	addw	sp, #2
;	ds18b20.c: 661: break;
	jp	00117$
;	ds18b20.c: 662: case 5:
00113$:
;	ds18b20.c: 663: read_display_temp(0); //end no heating, no timer
	clrw	x
	pushw	x
	clrw	x
	pushw	x
	call	_read_display_temp
	addw	sp, #4
;	ds18b20.c: 664: sprintf(boodsch,"end\r\n"); 
	ldw	y, #___str_7
	ldw	x, (0x0f, sp)
	pushw	y
	pushw	x
	call	_sprintf
	addw	sp, #4
;	ds18b20.c: 665: UARTPrintF (boodsch); 
	ldw	x, (0x0f, sp)
	pushw	x
	call	_UARTPrintF
	addw	sp, #2
;	ds18b20.c: 666: break;
;	ds18b20.c: 670: }
;	ds18b20.c: 672: }
	jp	00117$
	.area CODE
	.area CONST
_segmentMap:
	.db #0x3f	; 63
	.db #0x06	; 6
	.db #0x5b	; 91
	.db #0x4f	; 79	'O'
	.db #0x66	; 102	'f'
	.db #0x6d	; 109	'm'
	.db #0x7d	; 125
	.db #0x07	; 7
	.db #0x7f	; 127
	.db #0x6f	; 111	'o'
	.db #0x77	; 119	'w'
	.db #0x7c	; 124
	.db #0x39	; 57	'9'
	.db #0x5e	; 94
	.db #0x79	; 121	'y'
	.db #0x71	; 113	'q'
	.db #0x00	; 0
___str_1:
	.ascii "pid :%d"
	.db 0x0d
	.db 0x0a
	.db 0x00
___str_3:
	.ascii "to phase2"
	.db 0x0d
	.db 0x0a
	.db 0x00
___str_4:
	.ascii "to phase3"
	.db 0x0d
	.db 0x0a
	.db 0x00
___str_5:
	.ascii "to phase4"
	.db 0x0d
	.db 0x0a
	.db 0x00
___str_6:
	.ascii "to phase5"
	.db 0x0d
	.db 0x0a
	.db 0x00
___str_7:
	.ascii "end"
	.db 0x0d
	.db 0x0a
	.db 0x00
	.area INITIALIZER
__xinit__pid:
	.byte #0x3f,#0x80,#0x00,#0x00	;  1.000000e+00
	.byte #0x3f,#0x80,#0x00,#0x00	;  1.000000e+00
	.byte #0x3f,#0x80,#0x00,#0x00	;  1.000000e+00
	.byte #0x3c,#0xa3,#0xd7,#0x0a	;  2.000000e-02
	.byte #0x00,#0x00,#0x00,#0x00	;  0.000000e+00
	.byte #0x41,#0x20,#0x00,#0x00	;  1.000000e+01
	.byte #0x00,#0x00,#0x00,#0x00	;  0.000000e+00
	.byte #0x40,#0xa0,#0x00,#0x00	;  5.000000e+00
	.byte #0x41,#0xa0,#0x00,#0x00	;  2.000000e+01
	.byte #0x00,#0x00,#0x00,#0x00	;  0.000000e+00
	.byte #0x00,#0x00,#0x00,#0x00	;  0.000000e+00
	.byte #0x00,#0x00,#0x00,#0x00	;  0.000000e+00
	.byte #0x00,#0x00,#0x00,#0x00	;  0.000000e+00
	.byte #0x00,#0x00,#0x00,#0x00	;  0.000000e+00
__xinit__fast:
	.db #0x01	;  1
	.area CABS (ABS)
