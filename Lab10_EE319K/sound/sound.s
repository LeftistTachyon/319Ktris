	IMPORT DAC_Out
	IMPORT Tri
	IMPORT Square
	EXPORT Wave_SoundTick
	EXPORT Wave_SetChannel
		
	AREA    DATA, ALIGN=2
		
SoundChannels		
TriChannel1_Data
	DCW -1 ; 1 channel
TriChannel1_Count
	DCW 0 ; 1 counter
		
TriChannel2_Data
	DCW -1 ; 1 channel
TriChannel2_Count
	DCW 0 ; 1 counter
		
TriChannel3_Data
	DCW -1 ; 1 channel
TriChannel3_Count
	DCW 0 ; 1 counter
		
TriChannel4_Data
	DCW -1 ; 1 channel
TriChannel4_Count
	DCW 0 ; 1 counter
		
SquareChannel1_Data
	DCW -1 ; 1 channel
SquareChannel1_Count
	DCW 0 ; 1 counter
		
SquareChannel2_Data
	DCW -1 ; 1 channel
SquareChannel2_Count
	DCW 0 ; 1 counter
		
SquareChannel3_Data
	DCW -1 ; 1 channel
SquareChannel3_Count
	DCW 0 ; 1 counter
		
NoiseChannel_Data
	DCW -1 ; 1 channel
NoiseChannel_Count
	DCW 0 ; 1 counter
	
MaxMag    DCD 0x003FFFFF
		
	ALIGN  
		
	AREA    |.text|, CODE, READONLY, ALIGN=2
	THUMB
	
; invoked at 11kHz
; R0: number of used channels (used for balancing)
; no out (pure function)
Wave_SoundTick
	PUSH {R4-R10, LR}

	LDR R4, =SoundChannels ; the pointer to the current channel
	MOV R7, #0 ; the accumulator for the sound
	MOV R10, R0
	
	; Sine
	;LDRSH R5, [R4]
	;CMP R5, #0
	;BLE Skip_Sine
	
	;MOV R0, R5
	;LDRH R1, [R4, #2]
	;BL Sin
	;ADD R7, R0

	;LDRH R6, [R4, #2]
	;SUBS R6, #1
	;ADDLE R6, R5
	;STRH R6, [R4, #2]

;Skip_Sine
	; Tri1
	LDRSH R5, [R4, #0]
	CMP R5, #0
	BLE Skip_Tri1
	
	MOV R0, R5
	LDRH R1, [R4, #2]
	BL Tri
	ADD R7, R0

	LDRH R6, [R4, #2]
	SUBS R6, #1
	ADDLE R6, R5
	STRH R6, [R4, #2]

Skip_Tri1
	; Tri2
	LDRSH R5, [R4, #4]
	CMP R5, #0
	BLE Skip_Tri2
	
	MOV R0, R5
	LDRH R1, [R4, #6]
	BL Tri
	ADD R7, R0

	LDRH R6, [R4, #6]
	SUBS R6, #1
	ADDLE R6, R5
	STRH R6, [R4, #6]

Skip_Tri2
	; Tri3
	LDRSH R5, [R4, #8]
	CMP R5, #0
	BLE Skip_Tri3
	
	MOV R0, R5
	LDRH R1, [R4, #10]
	BL Tri
	ADD R7, R0

	LDRH R6, [R4, #10]
	SUBS R6, #1
	ADDLE R6, R5
	STRH R6, [R4, #10]

Skip_Tri3
	; Tri4
	LDRSH R5, [R4, #12]
	CMP R5, #0
	BLE Skip_Tri4
	
	MOV R0, R5
	LDRH R1, [R4, #14]
	BL Tri
	ADD R7, R0

	LDRH R6, [R4, #14]
	SUBS R6, #1
	ADDLE R6, R5
	STRH R6, [R4, #14]

Skip_Tri4
	; Square1
	LDRSH R5, [R4, #16]
	CMP R5, #0
	BLE Skip_Square1
	
	MOV R0, R5
	LDRH R1, [R4, #18]
	BL Square
	ADD R7, R0

	LDRH R6, [R4, #18]
	SUBS R6, #1
	ADDLE R6, R5
	STRH R6, [R4, #18]

Skip_Square1
	; Square2
	LDRSH R5, [R4, #20]
	CMP R5, #0
	BLE Skip_Square2
	
	MOV R0, R5
	LDRH R1, [R4, #22]
	BL Square
	ADD R7, R0

	LDRH R6, [R4, #22]
	SUBS R6, #1
	ADDLE R6, R5
	STRH R6, [R4, #22]

Skip_Square2
	; Square3
	LDRSH R5, [R4, #24]
	CMP R5, #0
	BLE Skip_Square3
	
	MOV R0, R5
	LDRH R1, [R4, #26]
	BL Square
	ADD R7, R0

	LDRH R6, [R4, #26]
	SUBS R6, #1
	ADDLE R6, R5
	STRH R6, [R4, #26]

Skip_Square3
	; Noise
	LDRSH R5, [R4, #28]
	CMP R5, #0
	BLE Skip_Noise
	
	MOV R0, R5
	LDRH R1, [R4, #30]
	BL Noise
	ADD R7, R0	
	
	LDRH R6, [R4, #30]
	TST R6, #1
	LSR R6, #1
	EORNE R6, #poly
	
	STRH R6, [R4, #30]

Skip_Noise
	
	; final stretch
	LDR R8, =MaxMag
	LDR R8, [R8]
	; final processing
	SDIV R7, R10
	ADD R7, R8
	LSR R7, #17
	
	; output
	MOV R0, R7
	AND R0, #0x3F ; unnecessary, only for debugging
	BL DAC_Out
	
	; BX LR
	POP {R4-R10, PC}
	
; R0: period (8 bits)
; R1: count	 (up to period)
; R8 + R9 + R10 scratch
; R8: tap one
; R9: tap two
; R10: output
poly EQU 0xB8
Noise
	LSL R0, R1, #15
	BX LR
	
; in: channel (soundchannel_t)
;     data (period in 11.025kHz cycles) (int16_t)
Wave_SetChannel
	PUSH {R4, R5}

	MOV R4, R0
	LSL R4, #2
	LDR R5, =SoundChannels
	ADD R4, R5 ; R4 = address of data
	
	STRH R1, [R4, #2] ; reset counter	
	STRH R1, [R4] ; set period
	
	POP {R4, R5}
	BX LR
	
	ALIGN
	END	