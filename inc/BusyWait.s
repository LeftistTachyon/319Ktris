; BusyWait.s
; Student names: Dylan Rogers and Jed Wang
; Last modification date: 3/5/22

; Runs on TM4C123

; As part of Lab 7, students need to implement these two functions
; This file is in the inc folder so it automatically will be applied to labs 7 8 9 and 10


      EXPORT   SPIOutCommand
      EXPORT   SPIOutData

      AREA    |.text|, CODE, READONLY, ALIGN=2
      THUMB
      ALIGN
; Used in ECE319K Labs 7,8,9,10. You write these two functions

; ***********SPIOutCommand*****************
; This is a helper function that sends an 8-bit command to the LCD.
; Inputs: R0 = 32-bit command (number)
;         R1 = 32-bit SPI status register address
;         R2 = 32-bit SPI data register address
;         R3 = 32-bit GPIO port address for D/C
; Outputs: none
; Assumes: SPI and GPIO have already been initialized and enabled
; Note: must be AAPCS compliant
; Note: access to bit 6 of GPIO must be friendly
SPIOutCommand
; --UUU-- Code to write a command to the LCD
;1) Read the SPI status register (R1 has address) and check bit 4, 
;2) If bit 4 is high, loop back to step 1 (wait for BUSY bit to be low)
;3) Clear D/C (GPIO bit 6) to zero, be friendly (R3 has address)
;4) Write the command to the SPI data register (R2 has address)
;5) Read the SPI status register (R1 has address) and check bit 4, 
;6) If bit 4 is high, loop back to step 5 (wait for BUSY bit to be low)
	PUSH {R4, LR}
Step1
	LDR	R4, [R1]
	AND R4, #0x10
	CMP R4, #0
	BEQ SPICReady
	B Step1
	
SPICReady
	LDR R4, [R3]
	BIC R4, #0x40
	STR R4, [R3]
	
	STR R0, [R2]
	
Step5	
	LDR R4, [R1]
	AND R4, #0x10
	CMP R4, #0
	BEQ SPICDone
	B Step5
	
SPICDone
	POP {R4, LR}
    BX  LR             ;   return



; ***********SPIOutData*****************
; This is a helper function that sends an 8-bit data to the LCD.
; Inputs: R0 = 32-bit data (number)
;         R1 = 32-bit SPI status register address
;         R2 = 32-bit SPI data register address
;         R3 = 32-bit GPIO port address for D/C
; Outputs: none
; Assumes: SPI and GPIO have already been initialized and enabled
; Note: must be AAPCS compliant
; Note: access to bit 6 of GPIO must be friendly
SPIOutData
; --UUU-- Code to write data to the LCD
;1) Read the SPI status register (R1 has address) and check bit 1, 
;2) If bit 1 is low, loop back to step 1 (wait for TNF bit to be high)
;3) Set D/C (GPIO bit 6) to one, be friendly (R3 has address)
;4) Write the data to the SPI data register (R2 has address)
	PUSH {LR, R4}
Step1A
	LDR R4, [R1]
	AND R4, #0x2
	CMP R4, #0
	BNE SPIOReady
	B Step1A
	
SPIOReady   
	LDR R4, [R3]
	ORR R4, #0x40
	STR R4, [R3]
	
	STR R0, [R2]
	POP {LR, R4}
    BX  LR             ;return
;****************************************************

    ALIGN                           ; make sure the end of this section is aligned
    END                             ; end of file
