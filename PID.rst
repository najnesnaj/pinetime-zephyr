                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 3.8.0 #10562 (Linux)
                                      4 ;--------------------------------------------------------
                                      5 	.module PID
                                      6 	.optsdcc -mstm8
                                      7 	
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _PIDController_Init
                                     12 	.globl _PIDController_Update
                                     13 ;--------------------------------------------------------
                                     14 ; ram data
                                     15 ;--------------------------------------------------------
                                     16 	.area DATA
                                     17 ;--------------------------------------------------------
                                     18 ; ram data
                                     19 ;--------------------------------------------------------
                                     20 	.area INITIALIZED
                                     21 ;--------------------------------------------------------
                                     22 ; absolute external ram data
                                     23 ;--------------------------------------------------------
                                     24 	.area DABS (ABS)
                                     25 
                                     26 ; default segment ordering for linker
                                     27 	.area HOME
                                     28 	.area GSINIT
                                     29 	.area GSFINAL
                                     30 	.area CONST
                                     31 	.area INITIALIZER
                                     32 	.area CODE
                                     33 
                                     34 ;--------------------------------------------------------
                                     35 ; global & static initialisations
                                     36 ;--------------------------------------------------------
                                     37 	.area HOME
                                     38 	.area GSINIT
                                     39 	.area GSFINAL
                                     40 	.area GSINIT
                                     41 ;--------------------------------------------------------
                                     42 ; Home
                                     43 ;--------------------------------------------------------
                                     44 	.area HOME
                                     45 	.area HOME
                                     46 ;--------------------------------------------------------
                                     47 ; code
                                     48 ;--------------------------------------------------------
                                     49 	.area CODE
                                     50 ;	PID.c: 4: void PIDController_Init(PIDController *pid) {
                                     51 ;	-----------------------------------------
                                     52 ;	 function PIDController_Init
                                     53 ;	-----------------------------------------
      008923                         54 _PIDController_Init:
                                     55 ;	PID.c: 7: pid->integrator = 0.0f;
      008923 16 03            [ 2]   56 	ldw	y, (0x03, sp)
      008925 93               [ 1]   57 	ldw	x, y
      008926 1C 00 24         [ 2]   58 	addw	x, #0x0024
      008929 6F 03            [ 1]   59 	clr	(0x3, x)
      00892B 6F 02            [ 1]   60 	clr	(0x2, x)
      00892D 6F 01            [ 1]   61 	clr	(0x1, x)
      00892F 7F               [ 1]   62 	clr	(x)
                                     63 ;	PID.c: 8: pid->prevError  = 0.0f;
      008930 93               [ 1]   64 	ldw	x, y
      008931 1C 00 28         [ 2]   65 	addw	x, #0x0028
      008934 6F 03            [ 1]   66 	clr	(0x3, x)
      008936 6F 02            [ 1]   67 	clr	(0x2, x)
      008938 6F 01            [ 1]   68 	clr	(0x1, x)
      00893A 7F               [ 1]   69 	clr	(x)
                                     70 ;	PID.c: 10: pid->differentiator  = 0.0f;
      00893B 93               [ 1]   71 	ldw	x, y
      00893C 1C 00 2C         [ 2]   72 	addw	x, #0x002c
      00893F 6F 03            [ 1]   73 	clr	(0x3, x)
      008941 6F 02            [ 1]   74 	clr	(0x2, x)
      008943 6F 01            [ 1]   75 	clr	(0x1, x)
      008945 7F               [ 1]   76 	clr	(x)
                                     77 ;	PID.c: 11: pid->prevMeasurement = 0.0f;
      008946 93               [ 1]   78 	ldw	x, y
      008947 1C 00 30         [ 2]   79 	addw	x, #0x0030
      00894A 6F 03            [ 1]   80 	clr	(0x3, x)
      00894C 6F 02            [ 1]   81 	clr	(0x2, x)
      00894E 6F 01            [ 1]   82 	clr	(0x1, x)
      008950 7F               [ 1]   83 	clr	(x)
                                     84 ;	PID.c: 13: pid->out = 0.0f;
      008951 93               [ 1]   85 	ldw	x, y
      008952 1C 00 34         [ 2]   86 	addw	x, #0x0034
      008955 6F 03            [ 1]   87 	clr	(0x3, x)
      008957 6F 02            [ 1]   88 	clr	(0x2, x)
      008959 6F 01            [ 1]   89 	clr	(0x1, x)
      00895B 7F               [ 1]   90 	clr	(x)
                                     91 ;	PID.c: 15: }
      00895C 81               [ 4]   92 	ret
                                     93 ;	PID.c: 17: float PIDController_Update(PIDController *pid, float setpoint, float measurement) {
                                     94 ;	-----------------------------------------
                                     95 ;	 function PIDController_Update
                                     96 ;	-----------------------------------------
      00895D                         97 _PIDController_Update:
      00895D 52 75            [ 2]   98 	sub	sp, #117
                                     99 ;	PID.c: 22: float error = setpoint - measurement;
      00895F 1E 80            [ 2]  100 	ldw	x, (0x80, sp)
      008961 89               [ 2]  101 	pushw	x
      008962 1E 80            [ 2]  102 	ldw	x, (0x80, sp)
      008964 89               [ 2]  103 	pushw	x
      008965 1E 80            [ 2]  104 	ldw	x, (0x80, sp)
      008967 89               [ 2]  105 	pushw	x
      008968 1E 80            [ 2]  106 	ldw	x, (0x80, sp)
      00896A 89               [ 2]  107 	pushw	x
      00896B CD 8C 40         [ 4]  108 	call	___fssub
      00896E 5B 08            [ 2]  109 	addw	sp, #8
      008970 1F 70            [ 2]  110 	ldw	(0x70, sp), x
      008972 17 6E            [ 2]  111 	ldw	(0x6e, sp), y
                                    112 ;	PID.c: 28: float proportional = pid->Kp * error;
      008974 16 78            [ 2]  113 	ldw	y, (0x78, sp)
      008976 17 6C            [ 2]  114 	ldw	(0x6c, sp), y
      008978 93               [ 1]  115 	ldw	x, y
      008979 90 EE 02         [ 2]  116 	ldw	y, (0x2, y)
      00897C FE               [ 2]  117 	ldw	x, (x)
      00897D 1F 30            [ 2]  118 	ldw	(0x30, sp), x
      00897F 1E 70            [ 2]  119 	ldw	x, (0x70, sp)
      008981 89               [ 2]  120 	pushw	x
      008982 1E 70            [ 2]  121 	ldw	x, (0x70, sp)
      008984 89               [ 2]  122 	pushw	x
      008985 90 89            [ 2]  123 	pushw	y
      008987 1E 36            [ 2]  124 	ldw	x, (0x36, sp)
      008989 89               [ 2]  125 	pushw	x
      00898A CD 8C 63         [ 4]  126 	call	___fsmul
      00898D 5B 08            [ 2]  127 	addw	sp, #8
      00898F 1F 74            [ 2]  128 	ldw	(0x74, sp), x
      008991 17 72            [ 2]  129 	ldw	(0x72, sp), y
                                    130 ;	PID.c: 34: pid->integrator = pid->integrator + 0.5f * pid->Ki * pid->T * (error + pid->prevError);
      008993 1E 6C            [ 2]  131 	ldw	x, (0x6c, sp)
      008995 1C 00 24         [ 2]  132 	addw	x, #0x0024
      008998 1F 2E            [ 2]  133 	ldw	(0x2e, sp), x
      00899A E6 03            [ 1]  134 	ld	a, (0x3, x)
      00899C 6B 08            [ 1]  135 	ld	(0x08, sp), a
      00899E E6 02            [ 1]  136 	ld	a, (0x2, x)
      0089A0 6B 07            [ 1]  137 	ld	(0x07, sp), a
      0089A2 FE               [ 2]  138 	ldw	x, (x)
      0089A3 1F 05            [ 2]  139 	ldw	(0x05, sp), x
      0089A5 1E 6C            [ 2]  140 	ldw	x, (0x6c, sp)
      0089A7 90 93            [ 1]  141 	ldw	y, x
      0089A9 90 EE 06         [ 2]  142 	ldw	y, (0x6, y)
      0089AC EE 04            [ 2]  143 	ldw	x, (0x4, x)
      0089AE 90 89            [ 2]  144 	pushw	y
      0089B0 89               [ 2]  145 	pushw	x
      0089B1 5F               [ 1]  146 	clrw	x
      0089B2 89               [ 2]  147 	pushw	x
      0089B3 4B 00            [ 1]  148 	push	#0x00
      0089B5 4B 3F            [ 1]  149 	push	#0x3f
      0089B7 CD 8C 63         [ 4]  150 	call	___fsmul
      0089BA 5B 08            [ 2]  151 	addw	sp, #8
      0089BC 1F 03            [ 2]  152 	ldw	(0x03, sp), x
      0089BE 17 01            [ 2]  153 	ldw	(0x01, sp), y
      0089C0 1E 6C            [ 2]  154 	ldw	x, (0x6c, sp)
      0089C2 1C 00 20         [ 2]  155 	addw	x, #0x0020
      0089C5 1F 3E            [ 2]  156 	ldw	(0x3e, sp), x
      0089C7 90 93            [ 1]  157 	ldw	y, x
      0089C9 90 EE 02         [ 2]  158 	ldw	y, (0x2, y)
      0089CC FE               [ 2]  159 	ldw	x, (x)
      0089CD 90 89            [ 2]  160 	pushw	y
      0089CF 89               [ 2]  161 	pushw	x
      0089D0 1E 07            [ 2]  162 	ldw	x, (0x07, sp)
      0089D2 89               [ 2]  163 	pushw	x
      0089D3 1E 07            [ 2]  164 	ldw	x, (0x07, sp)
      0089D5 89               [ 2]  165 	pushw	x
      0089D6 CD 8C 63         [ 4]  166 	call	___fsmul
      0089D9 5B 08            [ 2]  167 	addw	sp, #8
      0089DB 1F 3C            [ 2]  168 	ldw	(0x3c, sp), x
      0089DD 17 3A            [ 2]  169 	ldw	(0x3a, sp), y
      0089DF 1E 6C            [ 2]  170 	ldw	x, (0x6c, sp)
      0089E1 1C 00 28         [ 2]  171 	addw	x, #0x0028
      0089E4 1F 38            [ 2]  172 	ldw	(0x38, sp), x
      0089E6 90 93            [ 1]  173 	ldw	y, x
      0089E8 90 EE 02         [ 2]  174 	ldw	y, (0x2, y)
      0089EB FE               [ 2]  175 	ldw	x, (x)
      0089EC 90 89            [ 2]  176 	pushw	y
      0089EE 89               [ 2]  177 	pushw	x
      0089EF 1E 74            [ 2]  178 	ldw	x, (0x74, sp)
      0089F1 89               [ 2]  179 	pushw	x
      0089F2 1E 74            [ 2]  180 	ldw	x, (0x74, sp)
      0089F4 89               [ 2]  181 	pushw	x
      0089F5 CD 90 23         [ 4]  182 	call	___fsadd
      0089F8 5B 08            [ 2]  183 	addw	sp, #8
      0089FA 89               [ 2]  184 	pushw	x
      0089FB 90 89            [ 2]  185 	pushw	y
      0089FD 1E 40            [ 2]  186 	ldw	x, (0x40, sp)
      0089FF 89               [ 2]  187 	pushw	x
      008A00 1E 40            [ 2]  188 	ldw	x, (0x40, sp)
      008A02 89               [ 2]  189 	pushw	x
      008A03 CD 8C 63         [ 4]  190 	call	___fsmul
      008A06 5B 08            [ 2]  191 	addw	sp, #8
      008A08 89               [ 2]  192 	pushw	x
      008A09 90 89            [ 2]  193 	pushw	y
      008A0B 1E 0B            [ 2]  194 	ldw	x, (0x0b, sp)
      008A0D 89               [ 2]  195 	pushw	x
      008A0E 1E 0B            [ 2]  196 	ldw	x, (0x0b, sp)
      008A10 89               [ 2]  197 	pushw	x
      008A11 CD 90 23         [ 4]  198 	call	___fsadd
      008A14 5B 08            [ 2]  199 	addw	sp, #8
      008A16 1F 36            [ 2]  200 	ldw	(0x36, sp), x
      008A18 1E 2E            [ 2]  201 	ldw	x, (0x2e, sp)
      008A1A 7B 37            [ 1]  202 	ld	a, (0x37, sp)
      008A1C E7 03            [ 1]  203 	ld	(0x3, x), a
      008A1E 7B 36            [ 1]  204 	ld	a, (0x36, sp)
      008A20 E7 02            [ 1]  205 	ld	(0x2, x), a
      008A22 FF               [ 2]  206 	ldw	(x), y
                                    207 ;	PID.c: 37: if (pid->integrator > pid->limMaxInt) {
      008A23 1E 2E            [ 2]  208 	ldw	x, (0x2e, sp)
      008A25 E6 03            [ 1]  209 	ld	a, (0x3, x)
      008A27 6B 4D            [ 1]  210 	ld	(0x4d, sp), a
      008A29 E6 02            [ 1]  211 	ld	a, (0x2, x)
      008A2B 6B 4C            [ 1]  212 	ld	(0x4c, sp), a
      008A2D FE               [ 2]  213 	ldw	x, (x)
      008A2E 1F 4A            [ 2]  214 	ldw	(0x4a, sp), x
      008A30 1E 6C            [ 2]  215 	ldw	x, (0x6c, sp)
      008A32 E6 1F            [ 1]  216 	ld	a, (0x1f, x)
      008A34 6B 49            [ 1]  217 	ld	(0x49, sp), a
      008A36 E6 1E            [ 1]  218 	ld	a, (0x1e, x)
      008A38 6B 48            [ 1]  219 	ld	(0x48, sp), a
      008A3A EE 1C            [ 2]  220 	ldw	x, (0x1c, x)
      008A3C 1F 46            [ 2]  221 	ldw	(0x46, sp), x
      008A3E 1E 36            [ 2]  222 	ldw	x, (0x36, sp)
      008A40 89               [ 2]  223 	pushw	x
      008A41 90 89            [ 2]  224 	pushw	y
      008A43 1E 4C            [ 2]  225 	ldw	x, (0x4c, sp)
      008A45 89               [ 2]  226 	pushw	x
      008A46 1E 4C            [ 2]  227 	ldw	x, (0x4c, sp)
      008A48 89               [ 2]  228 	pushw	x
      008A49 CD 8F 29         [ 4]  229 	call	___fslt
      008A4C 5B 08            [ 2]  230 	addw	sp, #8
      008A4E 4D               [ 1]  231 	tnz	a
      008A4F 27 0B            [ 1]  232 	jreq	00104$
                                    233 ;	PID.c: 39: pid->integrator = pid->limMaxInt;
      008A51 1E 2E            [ 2]  234 	ldw	x, (0x2e, sp)
      008A53 16 48            [ 2]  235 	ldw	y, (0x48, sp)
      008A55 EF 02            [ 2]  236 	ldw	(0x2, x), y
      008A57 16 46            [ 2]  237 	ldw	y, (0x46, sp)
      008A59 FF               [ 2]  238 	ldw	(x), y
      008A5A 20 29            [ 2]  239 	jra	00105$
      008A5C                        240 00104$:
                                    241 ;	PID.c: 41: } else if (pid->integrator < pid->limMinInt) {
      008A5C 1E 6C            [ 2]  242 	ldw	x, (0x6c, sp)
      008A5E 90 93            [ 1]  243 	ldw	y, x
      008A60 90 EE 1A         [ 2]  244 	ldw	y, (0x1a, y)
      008A63 EE 18            [ 2]  245 	ldw	x, (0x18, x)
      008A65 1F 42            [ 2]  246 	ldw	(0x42, sp), x
      008A67 90 89            [ 2]  247 	pushw	y
      008A69 90 89            [ 2]  248 	pushw	y
      008A6B 1E 46            [ 2]  249 	ldw	x, (0x46, sp)
      008A6D 89               [ 2]  250 	pushw	x
      008A6E 1E 52            [ 2]  251 	ldw	x, (0x52, sp)
      008A70 89               [ 2]  252 	pushw	x
      008A71 1E 52            [ 2]  253 	ldw	x, (0x52, sp)
      008A73 89               [ 2]  254 	pushw	x
      008A74 CD 8F 29         [ 4]  255 	call	___fslt
      008A77 5B 08            [ 2]  256 	addw	sp, #8
      008A79 90 85            [ 2]  257 	popw	y
      008A7B 4D               [ 1]  258 	tnz	a
      008A7C 27 07            [ 1]  259 	jreq	00105$
                                    260 ;	PID.c: 43: pid->integrator = pid->limMinInt;
      008A7E 1E 2E            [ 2]  261 	ldw	x, (0x2e, sp)
      008A80 EF 02            [ 2]  262 	ldw	(0x2, x), y
      008A82 16 42            [ 2]  263 	ldw	y, (0x42, sp)
      008A84 FF               [ 2]  264 	ldw	(x), y
      008A85                        265 00105$:
                                    266 ;	PID.c: 52: pid->differentiator = -(2.0f * pid->Kd * (measurement - pid->prevMeasurement)	/* Note: derivative on measurement, therefore minus sign in front of equation! */
      008A85 1E 6C            [ 2]  267 	ldw	x, (0x6c, sp)
      008A87 1C 00 2C         [ 2]  268 	addw	x, #0x002c
      008A8A 1F 40            [ 2]  269 	ldw	(0x40, sp), x
      008A8C 1E 6C            [ 2]  270 	ldw	x, (0x6c, sp)
      008A8E 90 93            [ 1]  271 	ldw	y, x
      008A90 90 EE 0A         [ 2]  272 	ldw	y, (0xa, y)
      008A93 EE 08            [ 2]  273 	ldw	x, (0x8, x)
      008A95 90 89            [ 2]  274 	pushw	y
      008A97 89               [ 2]  275 	pushw	x
      008A98 5F               [ 1]  276 	clrw	x
      008A99 89               [ 2]  277 	pushw	x
      008A9A 4B 00            [ 1]  278 	push	#0x00
      008A9C 4B 40            [ 1]  279 	push	#0x40
      008A9E CD 8C 63         [ 4]  280 	call	___fsmul
      008AA1 5B 08            [ 2]  281 	addw	sp, #8
      008AA3 1F 6A            [ 2]  282 	ldw	(0x6a, sp), x
      008AA5 17 68            [ 2]  283 	ldw	(0x68, sp), y
      008AA7 1E 6C            [ 2]  284 	ldw	x, (0x6c, sp)
      008AA9 1C 00 30         [ 2]  285 	addw	x, #0x0030
      008AAC 1F 66            [ 2]  286 	ldw	(0x66, sp), x
      008AAE 90 93            [ 1]  287 	ldw	y, x
      008AB0 90 EE 02         [ 2]  288 	ldw	y, (0x2, y)
      008AB3 FE               [ 2]  289 	ldw	x, (x)
      008AB4 90 89            [ 2]  290 	pushw	y
      008AB6 89               [ 2]  291 	pushw	x
      008AB7 1E 84            [ 2]  292 	ldw	x, (0x84, sp)
      008AB9 89               [ 2]  293 	pushw	x
      008ABA 1E 84            [ 2]  294 	ldw	x, (0x84, sp)
      008ABC 89               [ 2]  295 	pushw	x
      008ABD CD 8C 40         [ 4]  296 	call	___fssub
      008AC0 5B 08            [ 2]  297 	addw	sp, #8
      008AC2 89               [ 2]  298 	pushw	x
      008AC3 90 89            [ 2]  299 	pushw	y
      008AC5 1E 6E            [ 2]  300 	ldw	x, (0x6e, sp)
      008AC7 89               [ 2]  301 	pushw	x
      008AC8 1E 6E            [ 2]  302 	ldw	x, (0x6e, sp)
      008ACA 89               [ 2]  303 	pushw	x
                                    304 ;	PID.c: 53: + (2.0f * pid->tau - pid->T) * pid->differentiator)
      008ACB CD 8C 63         [ 4]  305 	call	___fsmul
      008ACE 5B 08            [ 2]  306 	addw	sp, #8
      008AD0 1F 64            [ 2]  307 	ldw	(0x64, sp), x
      008AD2 17 62            [ 2]  308 	ldw	(0x62, sp), y
      008AD4 1E 6C            [ 2]  309 	ldw	x, (0x6c, sp)
      008AD6 90 93            [ 1]  310 	ldw	y, x
      008AD8 90 EE 0E         [ 2]  311 	ldw	y, (0xe, y)
      008ADB EE 0C            [ 2]  312 	ldw	x, (0xc, x)
      008ADD 90 89            [ 2]  313 	pushw	y
      008ADF 89               [ 2]  314 	pushw	x
      008AE0 5F               [ 1]  315 	clrw	x
      008AE1 89               [ 2]  316 	pushw	x
      008AE2 4B 00            [ 1]  317 	push	#0x00
      008AE4 4B 40            [ 1]  318 	push	#0x40
      008AE6 CD 8C 63         [ 4]  319 	call	___fsmul
      008AE9 5B 08            [ 2]  320 	addw	sp, #8
      008AEB 1F 60            [ 2]  321 	ldw	(0x60, sp), x
      008AED 17 5E            [ 2]  322 	ldw	(0x5e, sp), y
      008AEF 1E 3E            [ 2]  323 	ldw	x, (0x3e, sp)
      008AF1 E6 03            [ 1]  324 	ld	a, (0x3, x)
      008AF3 6B 5D            [ 1]  325 	ld	(0x5d, sp), a
      008AF5 E6 02            [ 1]  326 	ld	a, (0x2, x)
      008AF7 6B 5C            [ 1]  327 	ld	(0x5c, sp), a
      008AF9 FE               [ 2]  328 	ldw	x, (x)
      008AFA 1F 5A            [ 2]  329 	ldw	(0x5a, sp), x
      008AFC 1E 5C            [ 2]  330 	ldw	x, (0x5c, sp)
      008AFE 89               [ 2]  331 	pushw	x
      008AFF 1E 5C            [ 2]  332 	ldw	x, (0x5c, sp)
      008B01 89               [ 2]  333 	pushw	x
      008B02 1E 64            [ 2]  334 	ldw	x, (0x64, sp)
      008B04 89               [ 2]  335 	pushw	x
      008B05 1E 64            [ 2]  336 	ldw	x, (0x64, sp)
      008B07 89               [ 2]  337 	pushw	x
      008B08 CD 8C 40         [ 4]  338 	call	___fssub
      008B0B 5B 08            [ 2]  339 	addw	sp, #8
      008B0D 1F 58            [ 2]  340 	ldw	(0x58, sp), x
      008B0F 1E 40            [ 2]  341 	ldw	x, (0x40, sp)
      008B11 E6 03            [ 1]  342 	ld	a, (0x3, x)
      008B13 6B 55            [ 1]  343 	ld	(0x55, sp), a
      008B15 E6 02            [ 1]  344 	ld	a, (0x2, x)
      008B17 6B 54            [ 1]  345 	ld	(0x54, sp), a
      008B19 FE               [ 2]  346 	ldw	x, (x)
      008B1A 7B 55            [ 1]  347 	ld	a, (0x55, sp)
      008B1C 88               [ 1]  348 	push	a
      008B1D 7B 55            [ 1]  349 	ld	a, (0x55, sp)
      008B1F 88               [ 1]  350 	push	a
      008B20 89               [ 2]  351 	pushw	x
      008B21 1E 5C            [ 2]  352 	ldw	x, (0x5c, sp)
      008B23 89               [ 2]  353 	pushw	x
      008B24 90 89            [ 2]  354 	pushw	y
      008B26 CD 8C 63         [ 4]  355 	call	___fsmul
      008B29 5B 08            [ 2]  356 	addw	sp, #8
      008B2B 1F 50            [ 2]  357 	ldw	(0x50, sp), x
      008B2D 17 4E            [ 2]  358 	ldw	(0x4e, sp), y
      008B2F 1E 50            [ 2]  359 	ldw	x, (0x50, sp)
      008B31 89               [ 2]  360 	pushw	x
      008B32 1E 50            [ 2]  361 	ldw	x, (0x50, sp)
      008B34 89               [ 2]  362 	pushw	x
      008B35 1E 68            [ 2]  363 	ldw	x, (0x68, sp)
      008B37 89               [ 2]  364 	pushw	x
      008B38 1E 68            [ 2]  365 	ldw	x, (0x68, sp)
      008B3A 89               [ 2]  366 	pushw	x
      008B3B CD 90 23         [ 4]  367 	call	___fsadd
      008B3E 5B 08            [ 2]  368 	addw	sp, #8
      008B40 1F 2C            [ 2]  369 	ldw	(0x2c, sp), x
      008B42 17 2A            [ 2]  370 	ldw	(0x2a, sp), y
      008B44 16 2C            [ 2]  371 	ldw	y, (0x2c, sp)
      008B46 17 28            [ 2]  372 	ldw	(0x28, sp), y
      008B48 7B 2B            [ 1]  373 	ld	a, (0x2b, sp)
      008B4A 6B 27            [ 1]  374 	ld	(0x27, sp), a
      008B4C 7B 2A            [ 1]  375 	ld	a, (0x2a, sp)
      008B4E A8 80            [ 1]  376 	xor	a, #0x80
      008B50 6B 26            [ 1]  377 	ld	(0x26, sp), a
                                    378 ;	PID.c: 54: / (2.0f * pid->tau + pid->T);
      008B52 1E 5C            [ 2]  379 	ldw	x, (0x5c, sp)
      008B54 89               [ 2]  380 	pushw	x
      008B55 1E 5C            [ 2]  381 	ldw	x, (0x5c, sp)
      008B57 89               [ 2]  382 	pushw	x
      008B58 1E 64            [ 2]  383 	ldw	x, (0x64, sp)
      008B5A 89               [ 2]  384 	pushw	x
      008B5B 1E 64            [ 2]  385 	ldw	x, (0x64, sp)
      008B5D 89               [ 2]  386 	pushw	x
      008B5E CD 90 23         [ 4]  387 	call	___fsadd
      008B61 5B 08            [ 2]  388 	addw	sp, #8
      008B63 89               [ 2]  389 	pushw	x
      008B64 90 89            [ 2]  390 	pushw	y
      008B66 1E 2C            [ 2]  391 	ldw	x, (0x2c, sp)
      008B68 89               [ 2]  392 	pushw	x
      008B69 1E 2C            [ 2]  393 	ldw	x, (0x2c, sp)
      008B6B 89               [ 2]  394 	pushw	x
      008B6C CD 95 B9         [ 4]  395 	call	___fsdiv
      008B6F 5B 08            [ 2]  396 	addw	sp, #8
      008B71 1F 24            [ 2]  397 	ldw	(0x24, sp), x
      008B73 17 22            [ 2]  398 	ldw	(0x22, sp), y
      008B75 1E 40            [ 2]  399 	ldw	x, (0x40, sp)
      008B77 16 24            [ 2]  400 	ldw	y, (0x24, sp)
      008B79 EF 02            [ 2]  401 	ldw	(0x2, x), y
      008B7B 16 22            [ 2]  402 	ldw	y, (0x22, sp)
      008B7D FF               [ 2]  403 	ldw	(x), y
                                    404 ;	PID.c: 60: pid->out = proportional + pid->integrator + pid->differentiator;
      008B7E 1E 6C            [ 2]  405 	ldw	x, (0x6c, sp)
      008B80 1C 00 34         [ 2]  406 	addw	x, #0x0034
      008B83 1F 20            [ 2]  407 	ldw	(0x20, sp), x
      008B85 1E 2E            [ 2]  408 	ldw	x, (0x2e, sp)
      008B87 90 93            [ 1]  409 	ldw	y, x
      008B89 90 EE 02         [ 2]  410 	ldw	y, (0x2, y)
      008B8C FE               [ 2]  411 	ldw	x, (x)
      008B8D 90 89            [ 2]  412 	pushw	y
      008B8F 89               [ 2]  413 	pushw	x
      008B90 1E 78            [ 2]  414 	ldw	x, (0x78, sp)
      008B92 89               [ 2]  415 	pushw	x
      008B93 1E 78            [ 2]  416 	ldw	x, (0x78, sp)
      008B95 89               [ 2]  417 	pushw	x
      008B96 CD 90 23         [ 4]  418 	call	___fsadd
      008B99 5B 08            [ 2]  419 	addw	sp, #8
      008B9B 1F 1E            [ 2]  420 	ldw	(0x1e, sp), x
      008B9D 1E 24            [ 2]  421 	ldw	x, (0x24, sp)
      008B9F 89               [ 2]  422 	pushw	x
      008BA0 1E 24            [ 2]  423 	ldw	x, (0x24, sp)
      008BA2 89               [ 2]  424 	pushw	x
      008BA3 1E 22            [ 2]  425 	ldw	x, (0x22, sp)
      008BA5 89               [ 2]  426 	pushw	x
      008BA6 90 89            [ 2]  427 	pushw	y
      008BA8 CD 90 23         [ 4]  428 	call	___fsadd
      008BAB 5B 08            [ 2]  429 	addw	sp, #8
      008BAD 1F 1A            [ 2]  430 	ldw	(0x1a, sp), x
      008BAF 1E 20            [ 2]  431 	ldw	x, (0x20, sp)
      008BB1 7B 1B            [ 1]  432 	ld	a, (0x1b, sp)
      008BB3 E7 03            [ 1]  433 	ld	(0x3, x), a
      008BB5 7B 1A            [ 1]  434 	ld	a, (0x1a, sp)
      008BB7 E7 02            [ 1]  435 	ld	(0x2, x), a
      008BB9 FF               [ 2]  436 	ldw	(x), y
                                    437 ;	PID.c: 62: if (pid->out > pid->limMax) {
      008BBA 1E 20            [ 2]  438 	ldw	x, (0x20, sp)
      008BBC E6 03            [ 1]  439 	ld	a, (0x3, x)
      008BBE 6B 17            [ 1]  440 	ld	(0x17, sp), a
      008BC0 E6 02            [ 1]  441 	ld	a, (0x2, x)
      008BC2 6B 16            [ 1]  442 	ld	(0x16, sp), a
      008BC4 FE               [ 2]  443 	ldw	x, (x)
      008BC5 1F 14            [ 2]  444 	ldw	(0x14, sp), x
      008BC7 1E 6C            [ 2]  445 	ldw	x, (0x6c, sp)
      008BC9 E6 17            [ 1]  446 	ld	a, (0x17, x)
      008BCB 6B 13            [ 1]  447 	ld	(0x13, sp), a
      008BCD E6 16            [ 1]  448 	ld	a, (0x16, x)
      008BCF 6B 12            [ 1]  449 	ld	(0x12, sp), a
      008BD1 EE 14            [ 2]  450 	ldw	x, (0x14, x)
      008BD3 1F 10            [ 2]  451 	ldw	(0x10, sp), x
      008BD5 1E 1A            [ 2]  452 	ldw	x, (0x1a, sp)
      008BD7 89               [ 2]  453 	pushw	x
      008BD8 90 89            [ 2]  454 	pushw	y
      008BDA 1E 16            [ 2]  455 	ldw	x, (0x16, sp)
      008BDC 89               [ 2]  456 	pushw	x
      008BDD 1E 16            [ 2]  457 	ldw	x, (0x16, sp)
      008BDF 89               [ 2]  458 	pushw	x
      008BE0 CD 8F 29         [ 4]  459 	call	___fslt
      008BE3 5B 08            [ 2]  460 	addw	sp, #8
      008BE5 6B 0F            [ 1]  461 	ld	(0x0f, sp), a
      008BE7 27 0B            [ 1]  462 	jreq	00109$
                                    463 ;	PID.c: 64: pid->out = pid->limMax;
      008BE9 1E 20            [ 2]  464 	ldw	x, (0x20, sp)
      008BEB 16 12            [ 2]  465 	ldw	y, (0x12, sp)
      008BED EF 02            [ 2]  466 	ldw	(0x2, x), y
      008BEF 16 10            [ 2]  467 	ldw	y, (0x10, sp)
      008BF1 FF               [ 2]  468 	ldw	(x), y
      008BF2 20 2E            [ 2]  469 	jra	00110$
      008BF4                        470 00109$:
                                    471 ;	PID.c: 66: } else if (pid->out < pid->limMin) {
      008BF4 16 6C            [ 2]  472 	ldw	y, (0x6c, sp)
      008BF6 17 0D            [ 2]  473 	ldw	(0x0d, sp), y
      008BF8 93               [ 1]  474 	ldw	x, y
      008BF9 E6 13            [ 1]  475 	ld	a, (0x13, x)
      008BFB 6B 0C            [ 1]  476 	ld	(0x0c, sp), a
      008BFD E6 12            [ 1]  477 	ld	a, (0x12, x)
      008BFF 6B 0B            [ 1]  478 	ld	(0x0b, sp), a
      008C01 EE 10            [ 2]  479 	ldw	x, (0x10, x)
      008C03 1F 09            [ 2]  480 	ldw	(0x09, sp), x
      008C05 1E 0B            [ 2]  481 	ldw	x, (0x0b, sp)
      008C07 89               [ 2]  482 	pushw	x
      008C08 1E 0B            [ 2]  483 	ldw	x, (0x0b, sp)
      008C0A 89               [ 2]  484 	pushw	x
      008C0B 1E 1A            [ 2]  485 	ldw	x, (0x1a, sp)
      008C0D 89               [ 2]  486 	pushw	x
      008C0E 1E 1A            [ 2]  487 	ldw	x, (0x1a, sp)
      008C10 89               [ 2]  488 	pushw	x
      008C11 CD 8F 29         [ 4]  489 	call	___fslt
      008C14 5B 08            [ 2]  490 	addw	sp, #8
      008C16 4D               [ 1]  491 	tnz	a
      008C17 27 09            [ 1]  492 	jreq	00110$
                                    493 ;	PID.c: 68: pid->out = pid->limMin;
      008C19 1E 20            [ 2]  494 	ldw	x, (0x20, sp)
      008C1B 16 0B            [ 2]  495 	ldw	y, (0x0b, sp)
      008C1D EF 02            [ 2]  496 	ldw	(0x2, x), y
      008C1F 16 09            [ 2]  497 	ldw	y, (0x09, sp)
      008C21 FF               [ 2]  498 	ldw	(x), y
      008C22                        499 00110$:
                                    500 ;	PID.c: 73: pid->prevError       = error;
      008C22 1E 38            [ 2]  501 	ldw	x, (0x38, sp)
      008C24 16 70            [ 2]  502 	ldw	y, (0x70, sp)
      008C26 EF 02            [ 2]  503 	ldw	(0x2, x), y
      008C28 16 6E            [ 2]  504 	ldw	y, (0x6e, sp)
      008C2A FF               [ 2]  505 	ldw	(x), y
                                    506 ;	PID.c: 74: pid->prevMeasurement = measurement;
      008C2B 1E 66            [ 2]  507 	ldw	x, (0x66, sp)
      008C2D 16 80            [ 2]  508 	ldw	y, (0x80, sp)
      008C2F EF 02            [ 2]  509 	ldw	(0x2, x), y
      008C31 16 7E            [ 2]  510 	ldw	y, (0x7e, sp)
      008C33 FF               [ 2]  511 	ldw	(x), y
                                    512 ;	PID.c: 77: return pid->out;
      008C34 1E 20            [ 2]  513 	ldw	x, (0x20, sp)
      008C36 90 93            [ 1]  514 	ldw	y, x
      008C38 90 EE 02         [ 2]  515 	ldw	y, (0x2, y)
      008C3B FE               [ 2]  516 	ldw	x, (x)
      008C3C 51               [ 1]  517 	exgw	x, y
                                    518 ;	PID.c: 79: }
      008C3D 5B 75            [ 2]  519 	addw	sp, #117
      008C3F 81               [ 4]  520 	ret
                                    521 	.area CODE
                                    522 	.area CONST
                                    523 	.area INITIALIZER
                                    524 	.area CABS (ABS)
