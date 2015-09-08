%include "asm_io.inc"
segment .text
global encrip , decrip

;subrutuna de encriptamiento

;            [EBP+8]     [EBP+12]     [EBP+16]
;void encrip(char *str, char key, char *encripted_str) 
encrip:
	enter 0,0
	;
	;
	;
	;
	mov eax, 0
	; retornar a C
	leave
	ret


;                 [EBP+8]         [EBP+12]     [EBP+16]
;void decrip(char *encripted_str, char key, char *decripted_str)
decrip:
	enter 0,0
	;
	;
	;
	;
	mov eax, 0
	; retornar a C
	leave
	ret