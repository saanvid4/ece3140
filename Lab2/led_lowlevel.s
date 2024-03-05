.section .text
.global set
.type set %function

.equ     PCORE,      0x400FF108 //GPIOE PCOR
.equ     PSORE,      0x400FF104 //GPIOE PSOR
.equ    LED_PIN,    0x8         //GPIO LED_PIN
.equ    MASK, 0x1000000    		// 1 << 24

set:
    PUSH {R4-R6, LR}
    MOV   R4, R0

    LDR   R0, = PCORE
    LDR   R1, = PSORE
    LDR   R2, = LED_PIN
    LDR   R5, = MASK

pulse:
    LSR   R5, R5, #1
    BEQ   pulsebits
    MOV   R6, R5
    NOP
    NOP
	NOP
	AND   R6, R6, R4
	BNE   led1

led0:
	STR   R2, [R1]
	NOP
	STR   R2, [R0]
	B     pulse
led1:

	STR   R2, [R1]
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	STR   R2, [R0]
	B     pulse


pulsebits:
    POP {R4-R6, PC}
