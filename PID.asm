;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.8.0 #10562 (Linux)
;--------------------------------------------------------
	.module PID
	.optsdcc -mstm8
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _PIDController_Init
	.globl _PIDController_Update
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area DATA
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area INITIALIZED
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
; global & static initialisations
;--------------------------------------------------------
	.area HOME
	.area GSINIT
	.area GSFINAL
	.area GSINIT
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area HOME
	.area HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area CODE
;	PID.c: 4: void PIDController_Init(PIDController *pid) {
;	-----------------------------------------
;	 function PIDController_Init
;	-----------------------------------------
_PIDController_Init:
;	PID.c: 7: pid->integrator = 0.0f;
	ldw	y, (0x03, sp)
	ldw	x, y
	addw	x, #0x0024
	clr	(0x3, x)
	clr	(0x2, x)
	clr	(0x1, x)
	clr	(x)
;	PID.c: 8: pid->prevError  = 0.0f;
	ldw	x, y
	addw	x, #0x0028
	clr	(0x3, x)
	clr	(0x2, x)
	clr	(0x1, x)
	clr	(x)
;	PID.c: 10: pid->differentiator  = 0.0f;
	ldw	x, y
	addw	x, #0x002c
	clr	(0x3, x)
	clr	(0x2, x)
	clr	(0x1, x)
	clr	(x)
;	PID.c: 11: pid->prevMeasurement = 0.0f;
	ldw	x, y
	addw	x, #0x0030
	clr	(0x3, x)
	clr	(0x2, x)
	clr	(0x1, x)
	clr	(x)
;	PID.c: 13: pid->out = 0.0f;
	ldw	x, y
	addw	x, #0x0034
	clr	(0x3, x)
	clr	(0x2, x)
	clr	(0x1, x)
	clr	(x)
;	PID.c: 15: }
	ret
;	PID.c: 17: float PIDController_Update(PIDController *pid, float setpoint, float measurement) {
;	-----------------------------------------
;	 function PIDController_Update
;	-----------------------------------------
_PIDController_Update:
	sub	sp, #117
;	PID.c: 22: float error = setpoint - measurement;
	ldw	x, (0x80, sp)
	pushw	x
	ldw	x, (0x80, sp)
	pushw	x
	ldw	x, (0x80, sp)
	pushw	x
	ldw	x, (0x80, sp)
	pushw	x
	call	___fssub
	addw	sp, #8
	ldw	(0x70, sp), x
	ldw	(0x6e, sp), y
;	PID.c: 28: float proportional = pid->Kp * error;
	ldw	y, (0x78, sp)
	ldw	(0x6c, sp), y
	ldw	x, y
	ldw	y, (0x2, y)
	ldw	x, (x)
	ldw	(0x30, sp), x
	ldw	x, (0x70, sp)
	pushw	x
	ldw	x, (0x70, sp)
	pushw	x
	pushw	y
	ldw	x, (0x36, sp)
	pushw	x
	call	___fsmul
	addw	sp, #8
	ldw	(0x74, sp), x
	ldw	(0x72, sp), y
;	PID.c: 34: pid->integrator = pid->integrator + 0.5f * pid->Ki * pid->T * (error + pid->prevError);
	ldw	x, (0x6c, sp)
	addw	x, #0x0024
	ldw	(0x2e, sp), x
	ld	a, (0x3, x)
	ld	(0x08, sp), a
	ld	a, (0x2, x)
	ld	(0x07, sp), a
	ldw	x, (x)
	ldw	(0x05, sp), x
	ldw	x, (0x6c, sp)
	ldw	y, x
	ldw	y, (0x6, y)
	ldw	x, (0x4, x)
	pushw	y
	pushw	x
	clrw	x
	pushw	x
	push	#0x00
	push	#0x3f
	call	___fsmul
	addw	sp, #8
	ldw	(0x03, sp), x
	ldw	(0x01, sp), y
	ldw	x, (0x6c, sp)
	addw	x, #0x0020
	ldw	(0x3e, sp), x
	ldw	y, x
	ldw	y, (0x2, y)
	ldw	x, (x)
	pushw	y
	pushw	x
	ldw	x, (0x07, sp)
	pushw	x
	ldw	x, (0x07, sp)
	pushw	x
	call	___fsmul
	addw	sp, #8
	ldw	(0x3c, sp), x
	ldw	(0x3a, sp), y
	ldw	x, (0x6c, sp)
	addw	x, #0x0028
	ldw	(0x38, sp), x
	ldw	y, x
	ldw	y, (0x2, y)
	ldw	x, (x)
	pushw	y
	pushw	x
	ldw	x, (0x74, sp)
	pushw	x
	ldw	x, (0x74, sp)
	pushw	x
	call	___fsadd
	addw	sp, #8
	pushw	x
	pushw	y
	ldw	x, (0x40, sp)
	pushw	x
	ldw	x, (0x40, sp)
	pushw	x
	call	___fsmul
	addw	sp, #8
	pushw	x
	pushw	y
	ldw	x, (0x0b, sp)
	pushw	x
	ldw	x, (0x0b, sp)
	pushw	x
	call	___fsadd
	addw	sp, #8
	ldw	(0x36, sp), x
	ldw	x, (0x2e, sp)
	ld	a, (0x37, sp)
	ld	(0x3, x), a
	ld	a, (0x36, sp)
	ld	(0x2, x), a
	ldw	(x), y
;	PID.c: 37: if (pid->integrator > pid->limMaxInt) {
	ldw	x, (0x2e, sp)
	ld	a, (0x3, x)
	ld	(0x4d, sp), a
	ld	a, (0x2, x)
	ld	(0x4c, sp), a
	ldw	x, (x)
	ldw	(0x4a, sp), x
	ldw	x, (0x6c, sp)
	ld	a, (0x1f, x)
	ld	(0x49, sp), a
	ld	a, (0x1e, x)
	ld	(0x48, sp), a
	ldw	x, (0x1c, x)
	ldw	(0x46, sp), x
	ldw	x, (0x36, sp)
	pushw	x
	pushw	y
	ldw	x, (0x4c, sp)
	pushw	x
	ldw	x, (0x4c, sp)
	pushw	x
	call	___fslt
	addw	sp, #8
	tnz	a
	jreq	00104$
;	PID.c: 39: pid->integrator = pid->limMaxInt;
	ldw	x, (0x2e, sp)
	ldw	y, (0x48, sp)
	ldw	(0x2, x), y
	ldw	y, (0x46, sp)
	ldw	(x), y
	jra	00105$
00104$:
;	PID.c: 41: } else if (pid->integrator < pid->limMinInt) {
	ldw	x, (0x6c, sp)
	ldw	y, x
	ldw	y, (0x1a, y)
	ldw	x, (0x18, x)
	ldw	(0x42, sp), x
	pushw	y
	pushw	y
	ldw	x, (0x46, sp)
	pushw	x
	ldw	x, (0x52, sp)
	pushw	x
	ldw	x, (0x52, sp)
	pushw	x
	call	___fslt
	addw	sp, #8
	popw	y
	tnz	a
	jreq	00105$
;	PID.c: 43: pid->integrator = pid->limMinInt;
	ldw	x, (0x2e, sp)
	ldw	(0x2, x), y
	ldw	y, (0x42, sp)
	ldw	(x), y
00105$:
;	PID.c: 52: pid->differentiator = -(2.0f * pid->Kd * (measurement - pid->prevMeasurement)	/* Note: derivative on measurement, therefore minus sign in front of equation! */
	ldw	x, (0x6c, sp)
	addw	x, #0x002c
	ldw	(0x40, sp), x
	ldw	x, (0x6c, sp)
	ldw	y, x
	ldw	y, (0xa, y)
	ldw	x, (0x8, x)
	pushw	y
	pushw	x
	clrw	x
	pushw	x
	push	#0x00
	push	#0x40
	call	___fsmul
	addw	sp, #8
	ldw	(0x6a, sp), x
	ldw	(0x68, sp), y
	ldw	x, (0x6c, sp)
	addw	x, #0x0030
	ldw	(0x66, sp), x
	ldw	y, x
	ldw	y, (0x2, y)
	ldw	x, (x)
	pushw	y
	pushw	x
	ldw	x, (0x84, sp)
	pushw	x
	ldw	x, (0x84, sp)
	pushw	x
	call	___fssub
	addw	sp, #8
	pushw	x
	pushw	y
	ldw	x, (0x6e, sp)
	pushw	x
	ldw	x, (0x6e, sp)
	pushw	x
;	PID.c: 53: + (2.0f * pid->tau - pid->T) * pid->differentiator)
	call	___fsmul
	addw	sp, #8
	ldw	(0x64, sp), x
	ldw	(0x62, sp), y
	ldw	x, (0x6c, sp)
	ldw	y, x
	ldw	y, (0xe, y)
	ldw	x, (0xc, x)
	pushw	y
	pushw	x
	clrw	x
	pushw	x
	push	#0x00
	push	#0x40
	call	___fsmul
	addw	sp, #8
	ldw	(0x60, sp), x
	ldw	(0x5e, sp), y
	ldw	x, (0x3e, sp)
	ld	a, (0x3, x)
	ld	(0x5d, sp), a
	ld	a, (0x2, x)
	ld	(0x5c, sp), a
	ldw	x, (x)
	ldw	(0x5a, sp), x
	ldw	x, (0x5c, sp)
	pushw	x
	ldw	x, (0x5c, sp)
	pushw	x
	ldw	x, (0x64, sp)
	pushw	x
	ldw	x, (0x64, sp)
	pushw	x
	call	___fssub
	addw	sp, #8
	ldw	(0x58, sp), x
	ldw	x, (0x40, sp)
	ld	a, (0x3, x)
	ld	(0x55, sp), a
	ld	a, (0x2, x)
	ld	(0x54, sp), a
	ldw	x, (x)
	ld	a, (0x55, sp)
	push	a
	ld	a, (0x55, sp)
	push	a
	pushw	x
	ldw	x, (0x5c, sp)
	pushw	x
	pushw	y
	call	___fsmul
	addw	sp, #8
	ldw	(0x50, sp), x
	ldw	(0x4e, sp), y
	ldw	x, (0x50, sp)
	pushw	x
	ldw	x, (0x50, sp)
	pushw	x
	ldw	x, (0x68, sp)
	pushw	x
	ldw	x, (0x68, sp)
	pushw	x
	call	___fsadd
	addw	sp, #8
	ldw	(0x2c, sp), x
	ldw	(0x2a, sp), y
	ldw	y, (0x2c, sp)
	ldw	(0x28, sp), y
	ld	a, (0x2b, sp)
	ld	(0x27, sp), a
	ld	a, (0x2a, sp)
	xor	a, #0x80
	ld	(0x26, sp), a
;	PID.c: 54: / (2.0f * pid->tau + pid->T);
	ldw	x, (0x5c, sp)
	pushw	x
	ldw	x, (0x5c, sp)
	pushw	x
	ldw	x, (0x64, sp)
	pushw	x
	ldw	x, (0x64, sp)
	pushw	x
	call	___fsadd
	addw	sp, #8
	pushw	x
	pushw	y
	ldw	x, (0x2c, sp)
	pushw	x
	ldw	x, (0x2c, sp)
	pushw	x
	call	___fsdiv
	addw	sp, #8
	ldw	(0x24, sp), x
	ldw	(0x22, sp), y
	ldw	x, (0x40, sp)
	ldw	y, (0x24, sp)
	ldw	(0x2, x), y
	ldw	y, (0x22, sp)
	ldw	(x), y
;	PID.c: 60: pid->out = proportional + pid->integrator + pid->differentiator;
	ldw	x, (0x6c, sp)
	addw	x, #0x0034
	ldw	(0x20, sp), x
	ldw	x, (0x2e, sp)
	ldw	y, x
	ldw	y, (0x2, y)
	ldw	x, (x)
	pushw	y
	pushw	x
	ldw	x, (0x78, sp)
	pushw	x
	ldw	x, (0x78, sp)
	pushw	x
	call	___fsadd
	addw	sp, #8
	ldw	(0x1e, sp), x
	ldw	x, (0x24, sp)
	pushw	x
	ldw	x, (0x24, sp)
	pushw	x
	ldw	x, (0x22, sp)
	pushw	x
	pushw	y
	call	___fsadd
	addw	sp, #8
	ldw	(0x1a, sp), x
	ldw	x, (0x20, sp)
	ld	a, (0x1b, sp)
	ld	(0x3, x), a
	ld	a, (0x1a, sp)
	ld	(0x2, x), a
	ldw	(x), y
;	PID.c: 62: if (pid->out > pid->limMax) {
	ldw	x, (0x20, sp)
	ld	a, (0x3, x)
	ld	(0x17, sp), a
	ld	a, (0x2, x)
	ld	(0x16, sp), a
	ldw	x, (x)
	ldw	(0x14, sp), x
	ldw	x, (0x6c, sp)
	ld	a, (0x17, x)
	ld	(0x13, sp), a
	ld	a, (0x16, x)
	ld	(0x12, sp), a
	ldw	x, (0x14, x)
	ldw	(0x10, sp), x
	ldw	x, (0x1a, sp)
	pushw	x
	pushw	y
	ldw	x, (0x16, sp)
	pushw	x
	ldw	x, (0x16, sp)
	pushw	x
	call	___fslt
	addw	sp, #8
	ld	(0x0f, sp), a
	jreq	00109$
;	PID.c: 64: pid->out = pid->limMax;
	ldw	x, (0x20, sp)
	ldw	y, (0x12, sp)
	ldw	(0x2, x), y
	ldw	y, (0x10, sp)
	ldw	(x), y
	jra	00110$
00109$:
;	PID.c: 66: } else if (pid->out < pid->limMin) {
	ldw	y, (0x6c, sp)
	ldw	(0x0d, sp), y
	ldw	x, y
	ld	a, (0x13, x)
	ld	(0x0c, sp), a
	ld	a, (0x12, x)
	ld	(0x0b, sp), a
	ldw	x, (0x10, x)
	ldw	(0x09, sp), x
	ldw	x, (0x0b, sp)
	pushw	x
	ldw	x, (0x0b, sp)
	pushw	x
	ldw	x, (0x1a, sp)
	pushw	x
	ldw	x, (0x1a, sp)
	pushw	x
	call	___fslt
	addw	sp, #8
	tnz	a
	jreq	00110$
;	PID.c: 68: pid->out = pid->limMin;
	ldw	x, (0x20, sp)
	ldw	y, (0x0b, sp)
	ldw	(0x2, x), y
	ldw	y, (0x09, sp)
	ldw	(x), y
00110$:
;	PID.c: 73: pid->prevError       = error;
	ldw	x, (0x38, sp)
	ldw	y, (0x70, sp)
	ldw	(0x2, x), y
	ldw	y, (0x6e, sp)
	ldw	(x), y
;	PID.c: 74: pid->prevMeasurement = measurement;
	ldw	x, (0x66, sp)
	ldw	y, (0x80, sp)
	ldw	(0x2, x), y
	ldw	y, (0x7e, sp)
	ldw	(x), y
;	PID.c: 77: return pid->out;
	ldw	x, (0x20, sp)
	ldw	y, x
	ldw	y, (0x2, y)
	ldw	x, (x)
	exgw	x, y
;	PID.c: 79: }
	addw	sp, #117
	ret
	.area CODE
	.area CONST
	.area INITIALIZER
	.area CABS (ABS)
