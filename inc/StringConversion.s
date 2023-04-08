; StringConversion.s
; Student names: change this to your names or look very silly
; Last modification date: change this to the last modification date or look very silly
; Runs on TM4C123
; ECE319K lab 7 number to string conversions
;
; Used in ECE319K Labs 7,8,9,10. You write these two functions

 
    EXPORT   Dec2String
    EXPORT   Fix2String
    AREA    |.text|, CODE, READONLY, ALIGN=2
    THUMB
    PRESERVE8

  
;-----------------------Dec2String-----------------------
; Convert a 32-bit number into unsigned decimal format
; String the string into the empty array add null-termination
; Input: R0 (call by value) 32-bit unsigned number
;        R1 pointer to empty array
; Output: none
; Invariables: This function must not permanently modify registers R4 to R11

num1 EQU 0
num2 EQU 4

Dec2String
	PUSH {R4, LR}
	ADD SP, #-8 ;Init Stack
	MOV R12, SP ;Frame Pointer in R12
	
	STR R0, [R12, #num1] ;Num1 Init
	
	ADD	SP, #-4
	MOV R2, #0
	STR R2, [SP] ;Null Terminator
	
Loop1	
	LDR R2, [R12, #num1]
	MOV R3, #10
	UDIV R3, R2, R3 
	STR R3, [R12, #num2] ;num2 = num1/10
	
	MOV R4, #10
	LDR R3, [R12, #num2]
	MUL R4, R3
	SUB R3, R2, R4 ;Compute Remainder
	ADD R3, #0x30 ;ASCII
	ADD SP, #-4
	STR R3, [SP] ;Push Remainder
	
	LDR R2, [R12, #num2] ;num1 = num2
	STR R2, [R12, #num1]
	
	CMP R2, #0
	BNE Loop1
	
Loop2	
	CMP SP, R12 ;SP - FP
	BEQ Done1
	
	LDR R2, [SP]
	STRB R2, [R1]
	ADD SP, #4
	ADD R1, #1
	B Loop2
Done1
	ADD SP, #8
	POP {R4, LR}
    BX LR
;* * * * * * * * End of Dec2String * * * * * * * *


; -----------------------Fix2String----------------------
; Create characters for LCD display in fixed-point format
; unsigned decimal, resolution 0.001, range 0.000 to 9.999
; Inputs:  R0 is an unsigned 32-bit number
;          R1 pointer to empty array
; Outputs: none
; E.g., R0=0,    then create "0.000 "
;       R0=3,    then create "0.003"
;       R0=89,   then create "0.089"
;       R0=123,  then create "0.123"
;       R0=9999, then create "9.999"
;       R0>9999, then create "*.***"
; Invariables: This function must not permanently modify registers R4 to R11
num EQU 0
quotient EQU 4
Fix2String
	MOV R2, #9999
	CMP R0, R2
	BHI Over
	
	ADD SP, #-8
	STR R0, [SP, #num]
	
	MOV R2, #1000
	UDIV R2, R0, R2
	STR R2, [SP, #quotient]
	
	ADD R2, #0x30
	STRB R2, [R1] ;First digit
	ADD R1, #1
	
	MOV R2, #46
	STRB R2, [R1] ;Decimal
	ADD R1, #1
	
	LDR R2, [SP, #quotient]
	MOV R3, #1000
	MUL R2, R2, R3
	LDR R0, [SP, #num]
	SUB R0, R0, R2
	STR R0, [SP, #num]
	
	
	
	MOV R2, #100
	UDIV R2, R0, R2
	STR R2, [SP, #quotient]
	
	ADD R2, #0x30
	STRB R2, [R1] ;Second digit
	ADD R1, #1
	
	LDR R2, [SP, #quotient]
	MOV R3, #100
	MUL R2, R2, R3
	LDR R0, [SP, #num]
	SUB R0, R0, R2
	STR R0, [SP, #num]
	
	
	MOV R2, #10
	UDIV R2, R0, R2
	STR R2, [SP, #quotient]
	
	ADD R2, #0x30
	STRB R2, [R1] ;Third digit
	ADD R1, #1
	
	LDR R2, [SP, #quotient]
	MOV R3, #10
	MUL R2, R2, R3
	LDR R0, [SP, #num]
	SUB R0, R0, R2
	STR R0, [SP, #num]
	
	
	STR R0, [SP, #quotient]
	
	ADD R0, #0x30
	STRB R0, [R1] ;Last Digit
	ADD R1, #1
	
	MOV R2, #32
	STRB R2, [R1]
	ADD R1, #1
	
	MOV R2, #0
	STRB R2, [R1]
	
	
	ADD SP, #8
	B Done2
	
	
Over
	MOV R2, #42
	MOV R3, #46
	STRB R2, [R1]
	ADD R1, #1
	STRB R3, [R1]
	ADD R1, #1
	STRB R2, [R1]
	ADD R1, #1
	STRB R2, [R1]
	ADD R1, #1
	STRB R2, [R1]
	ADD R1, #1
	MOV R2, #0
	STRB R2, [R1]
	
	
Done2
    BX LR
	
     ALIGN                           ; make sure the end of this section is aligned
     END                             ; end of file
