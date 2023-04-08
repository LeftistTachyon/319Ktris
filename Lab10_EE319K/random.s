;Random number generator;
; Linear congruential generator 
; from Numerical Recipes by Press et al.
; Jonathan Valvano

; How to use: 
; 1) call Random_Init once with a seed
;     Random_Init(1);
;     Random_Init(NVIC_CURRENT_R, 0);
; 2) call Random over and over to get a new random number
;   n = Random(0);    // 8 bit number
;   m = (Random32(1)>>16)%60; // a number from 0 to 59

       THUMB
       AREA    DATA, ALIGN=2
M1     SPACE   4
M2	   SPACE   4
       ALIGN          
       AREA    |.text|, CODE, READONLY, ALIGN=2
       EXPORT  Random_Init
       EXPORT  Random
       EXPORT  Random32
;R0 is initial seed
Random_Init
	   LDR R2, =M1
       STR R0,[R2]     ; M=seen
	   LDR R2, =M2
	   STR R0,[R2]
       BX  LR
;------------Random32------------
; Input R0: which rgen to use: 0 or 1
; Return R0= random number
; Linear congruential generator 
; from Numerical Recipes by Press et al.
Random32
       TST R1, #1
       LDRNE R2,=M1       
	   LDREQ R2,=M2    ; R2 = &M
       LDR R0,[R2]  ; R0=M
       LDR R1,=1664525
       MUL R0,R0,R1 ; R0 = 1664525*M
       LDR R1,=1013904223
       ADD R0,R1    ; 1664525*M+1013904223 
       STR R0,[R2]  ; store M
       BX  LR

;------------Random------------
; Input R0: which rgen to use: 0 or 1
; Return R0= random number, 0 to 255
; Linear congruential generator 
; from Numerical Recipes by Press et al.
Random
       TST R1, #1
       LDRNE R2,=M1       
	   LDREQ R2,=M2    ; R2 = &M
       LDR R0,[R2]   ; R0=M
       LDR R1,=1664525
       MUL R0,R0,R1  ; R0 = 1664525*M
       LDR R1,=1013904223
       ADD R0,R1     ; 1664525*M+1013904223 
       STR R0,[R2]   ; store M
       LSR R0,R0,#24 ; top 8 bits of number
       BX  LR
       ALIGN      
       END  
           