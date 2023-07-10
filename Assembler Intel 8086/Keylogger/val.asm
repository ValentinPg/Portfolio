.8086
.model small
.stack 100h

.data

	textoLetra db "La contrase¤a debe contener al menos una letra",0dh,0ah,24h
	textoNum db "La contrase¤a debe contener al menos un n£mero",0dh,0ah,24h
	textoCaracteres db "La contrase¤a debe contener al menos 6 caracteres",0dh,0ah,24h
	textoPrueba db "Prueba",0dh,0ah,24h
.code
public validacion

;Recibe el offset de una cadena de texto para validar que al menos 6 caracteres
;incluyendo letras y n£meros
;Si la contrase¤a es v lida, devuelve 0 en AL
;Si es inv lida, devuelve 1 en AL
validacion proc
	push bp
	mov bp, sp
	;Cuidado del entorno
	push bx
	push cx
	;Pongo el offset en bx
	mov bx, ss:[bp+4]
	mov ax, 0 
	mov cx, 0
;Si la contrase¤a tiene un n£mero, AL se devuelve en 1. Sino, queda en 0
;Si la contrase¤a tiene una letra, AH se devuelve en 1. Sino, queda en 0
comparo:
	cmp byte ptr [bx],24h
	je finValidacion
	cmp al, 0 	;Me fijo si ya hay un n£mero en la contrase¤a. Sino, salto a la validaci¢n
	je validoNumero
comparoLetra:
	cmp ah, 0 	;Lo mismo con letras
	je validoLetra
incrementa:
	inc bx
	inc cx	;Cuento en cx la cantidad de caracteres
	jmp comparo

validoNumero:
	cmp byte ptr [bx],  30h
	jge casiNumero
	jmp comparoLetra
casiNumero:
	cmp byte ptr [bx], 39h
	jbe hayNumero
	jmp comparoLetra
hayNumero:
	mov al, 1
	jmp comparoLetra


validoLetra:
	cmp byte ptr [bx], 61h
	jge casiLetraMin
	cmp byte ptr [bx], 41h
	jge casiLetraMay
	jmp incrementa
casiLetraMin:
	cmp byte ptr [bx], 7ah
	jbe hayLetra
	jmp incrementa
casiLetraMay:
	cmp byte ptr [bx], 5ah
	jbe hayLetra
	jmp incrementa
hayLetra:
	mov ah, 1
	jmp incrementa

finValidacion:
	cmp al,0
	je mensajeNumero
	cmp ah, 0
	je mensajeLetra
	jmp cuentoCaracteres
mensajeNumero:
push ax
	mov ah, 9
	mov dx, offset textoNum
	int 21h
pop ax
	cmp ah, 0
	je mensajeLetra
	jmp contraseniaInvalida
mensajeLetra:
push ax
	mov ah, 9
	mov dx, offset textoLetra
	int 21h
	pop ax
	cmp ah, 1
	je contraseniaInvalida
	cmp al, 1
	je contraseniaInvalida

	mov al, 0
;	mov bx, ss:[bp+4]

cuentoCaracteres:

	cmp cx, 6
	jb caracteresInsuficientes
	mov al, 0
	jmp fin

contraseniaInvalida:
	mov al, 1
	jmp fin
	cmp cx, 6
	jb caracteresInsuficientes
caracteresInsuficientes:
push ax
	mov ah, 9
	mov dx, offset textoCaracteres
	int 21h
pop ax
	mov al, 1
	jmp fin

fin:
pop cx
pop bx
pop bp
ret 2
validacion endp

public carga

carga proc
	push bp
	mov bp, sp
	;Cuidado del entorno
	push ax
	push bx
	;Pongo el offset en bx
	mov bx, ss:[bp+4]
 
cargaTexto:
	mov ah, 1
	int 21h
	cmp al, 0dh			
	je finCarga		
	mov byte ptr[bx], al
	inc bx
	jmp cargaTexto

finCarga:
	pop bx
	pop ax
	pop bp
	ret 2
carga endp

public reseteo

reseteo proc
	push bp
	mov bp, sp
	push bx
	mov bx, ss:[bp+4]

inicio:
	cmp byte ptr[bx], "$"
	je finReseteo
	mov byte ptr[bx], "$"
	inc bx
	jmp inicio 

finReseteo:
	pop bx
	pop bp
	ret 2
reseteo endp

end 