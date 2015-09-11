%include "asm_io.inc"
segment .text
global encrip , decrip

;subrutuna de encriptamiento

;            [EBP+8]     [EBP+12]     [EBP+16]
;void encrip(char *str, char key, char *encripted_str) 
encrip:
	enter 0,0
	mov eax , 0
	mov al , [ebp+12]
	;en la parte baja de AX tengo la key
	shl al , 1  ; tiro al carry el bit mas significativo de la clave
	; si hay carry salto al bloque que llama al procedimiento para shift derecha
	jc call_shift_to_right 

	;sino llamo a shiftear hacia la izquierda
	push dword[ebp+16]
	push dword[ebp+12]
	push dword[ebp+8]
	call shift_to_left
	add esp , 12

	;salto para no ejecutar el shifteo hacia el otro lado
	jmp return_encrip_after_shift

	call_shift_to_right:
	push dword[ebp+16]
	push dword[ebp+12]
	push dword[ebp+8]
	call shift_to_right
	add esp , 12

	return_encrip_after_shift: ;despues de shiftear segun corresponda vuelvo aca

	;call swap

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



;------------------------------------------------------------------------------------------
;------------------------------------------------------------------------------------------

;rutinas


;	*********SHIFT  TO  RIGHT*************

;	pre = [EBP+8]  char *str (comienzo de la cadena a codificar)
;		  [EBP+12] cahr key
;		  [EBP+16] char *encripted_str

;	pos = [EBP+16] char *encripted_str (cadena original con los byte's shifteados segun key)
	shift_to_right:
	mov eax , 0
	mov ebx , 127 ; mascara 0111 1111
	mov al , [ebp+12] ; copio la key a la parte baja AX
	and eax , ebx
	mov ebx ,[ebp+8]
	mov ecx , 0
	mov edx , 0
	mov edi , [ebp+16]
	; EAX tengo la canditad de veces que tengo que siftear hacia la derecha
	; EBX char *str (comienzo de la canena a codificar)
	; ECX contador del ciclo, ECX = 0
	; DL  almacena cada byte temporalmente para ser shifteado
	; EDI char *encripted_str
	begin_shift_to_rigt_loop:
		mov dl , [ebx] ; muevo el byte actual a un registro temporal
		cmp dl , 0 ; comparo si el byte actual es el fin de cadena
		je end_shift_to_rigt_loop
		; si no es el fin de cadena
			mov ecx , 0
			begin_loop1:
				cmp ecx , eax ;comparo el contador con la cantidad de veces que tengo que shiftear
				je end_loop1

				ror dl , 1

				inc ecx ; incremento el contador
				jmp begin_loop1
			end_loop1:

			;dl tengo el byte shifteado
			mov [edi] , dl ;mevo el byte listo a el arreglo final
			inc edi ; avanzo el pintero a encripted_str

			inc ebx ; avanzo al siguiente byte
		jmp begin_shift_to_rigt_loop
	end_shift_to_rigt_loop:
	leave
	ret

;-------------------------------------------------------------------------------------------

	shift_to_left:
	mov eax , 0
	mov ebx , 127 ; mascara 0111 1111
	mov al , [ebp+12] ; copio la key a la parte baja AX
	and eax , ebx
	mov ebx ,[ebp+8]
	mov ecx , 0
	mov edx , 0
	mov edi , [ebp+16]
	; EAX tengo la canditad de veces que tengo que siftear hacia la derecha
	; EBX char *str (comienzo de la canena a codificar)
	; ECX contador del ciclo, ECX = 0
	; DL  almacena cada byte temporalmente para ser shifteado
	; EDI char *encripted_str
	begin_shift_to_left_loop:
		mov dl , [ebx] ; muevo el byte actual a un registro temporal
		cmp dl , 0 ; comparo si el byte actual es el fin de cadena
		je end_shift_to_left_loop
		; si no es el fin de cadena
			mov ecx , 0
			begin_loop2:
				cmp ecx , eax ;comparo el contador con la cantidad de veces que tengo que shiftear
				je end_loop2
				
				rol dl , 1

				inc ecx ; incremento el contador
				jmp begin_loop2
			end_loop2:

			;dl tengo el byte shifteado
			mov [edi] , dl ;mevo el byte listo a el arreglo final
			inc edi ; avanzo el pintero a encripted_str

			inc ebx ; avanzo al siguiente byte de str
		jmp begin_shift_to_left_loop
	end_shift_to_left_loop:
	mov dword[edi] , 0
	jmp return_encrip_after_shift
;-------------------------------------------------------------------------------------------



; pre: [EBP+12] cadena de bytes terminada en null (integer 0)
; pos: [EBP+12] cadena original con los los bits pares intercambiados por los impares
swap:
	enter 0 , 0

	mov eax , [ebp+12]
	mov ecx , 0
	; EAX puntero al comienzo de la cadena
	; ECX vacio para almacenar temporalmente un byte
	begin_loop_swap:
		mov ecx , 0
		mov cl  , [eax] ; muevo el byte actual a al 
		mov ch ,[eax+1] ; muevo el siguiente al actual ah

		cmp cl , 0   ; si el acual es null (la cadena tenia numero par de byte's)
		je end_loop_swap
		cmp ch , 0 ; si el siguiente del acual es null (la cadena tenia numero inpar de bytes)
		je end_loop_swap
		

		;intercambio
		mov [eax] , ch
	;dump_regs 1
		inc eax
		mov [eax] , cl
		inc eax

		;avanzo dos bytes
		;add eax , 2

		jmp begin_loop_swap
	end_loop_swap:
	mov eax , 0
	leave
	ret