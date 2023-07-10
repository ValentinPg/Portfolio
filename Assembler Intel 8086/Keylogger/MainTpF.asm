.8086
.model small
.stack 100h
.data
	;ACA VAN LAS VARIABLES
	cartel1 db , 0dh, 0ah, 0dh, 0ah
			db "             ______        _           _                    _    ", 0dh, 0ah
			db " 	    |  ____|      | |         | |                  | |   ", 0dh, 0ah
			db "	    | |__    __ _ | | __  ___ | |__    ___    ___  | | __", 0dh, 0ah
			db "	    |  __|  / _` || |/ / / _ \| '_ \  / _ \  / _ \ | |/ /", 0dh, 0ah
			db " 	    | |    | (_| ||   < |  __/| |_) || (_) || (_) ||   < ", 0dh, 0ah
			db "	    |_|     \__,_||_|\_\ \___||_.__/  \___/  \___/ |_|\_\", 0dh, 0ah
			db 0dh, 0ah, 0dh, 0ah, 0dh, 0ah, 0dh, 0ah, 24h
	espacio db 0dh, 0ah, 0dh, 0ah, 0dh, 0ah, 0dh, 0ah, 0dh, 0ah, 0dh, 0ah, 0dh, 0ah, 0dh, 0ah, 24h
	cartel2 db "Se est  por crear una cuenta en la red social mas usada en Tasmania", 0dh, 0ah, 0dh, 0ah
			db "Recuerde que nunca utilizaremos su informaci¢n para: ", 0dh, 0ah
			db "- tr?fico de informaci?n", 0dh, 0ah
			db "- usurpaci¢n de identidad", 0dh, 0ah
			db "- hurto y/o manipulaci¢n de cuentas bancarias", 0dh, 0ah
			db "- venta de informaci?n a bases de datos orientales", 0dh, 0ah, 0dh, 0ah, 24h
	textoIngresa db 255 dup (24h)
	usuario 	db "Ingrese su nuevo nombre de usuario", 0dh, 0ah, 24h
	contrasena 	db "Ingrese una contrase?a, debe tener al menos 6 caracteres, una letra y un n?mero", 0dh, 0ah, 24h
	email 		db "Ingrese un mail para recibir las novedades", 0dh, 0ah, 24h
	telefono	db "Ingrese un n?mero de tel?fono como respaldo de su contrase?a", 0dh, 0ah, 24h
	cuil		db "Ingrese su n?mero de documento y/o cuil", 0dh, 0ah, 24h
	cpa			db "Ingrese su c?digo postal", 0dh, 0ah
				db "lo puede ver en: https://www.correoargentino.com.ar/formularios/cpa", 0dh, 0ah, 24h
	mascota		db "Ingrese el nombre de su primer mascota", 0dh, 0ah, 24h
	horario		db "Ingrese horarios aproximados en que usted est? fuera de su vivienda.", 0dh, 0ah
				db "Es para que podamos brindarle un mejor servicio :D", 0dh, 0ah, 24h
	claveBanco	db "??CAPTCHA DE SEGURIDAD!!", 0dh, 0ah, 0dh, 0ah
				db "Si tiene que elegir una clave de 4 digitos n£mericos para su cuenta bancaria.", 0dh, 0ah
				db "?Cual usar?a?", 0dh, 0ah, 24h
	msgFinal 	db "?Su cuenta ah sido creada exitosamente!", 0dh, 0ah, 0dh, 0ah
				db "Recibir? un email de confirmaci?n de 3 a 5 dias h?biles.", 0dh, 0ah
				db "Le rogamos no realizar movimientos bancarios hasta que reciba nuestro email", 0dh, 0ah, 0dh, 0ah
				db "                 ??Gracias por confiar!!", 0dh, 0ah
;agregar nombre de mascota, horario en que no hay nadie en casa

.code
extrn validacion:proc
extrn carga:proc
extrn reseteo:proc

main proc
	mov ax, @data
	mov ds, ax

	;limpio pantalla e imprimo primero carteles
	mov ah, 0
	mov al, 3
	int 10h 

	mov ah, 9
	lea dx, cartel1
	int 21h

	mov ah, 9
	lea dx, cartel2
	int 21h

pidoUsuario:
	mov ah, 9
	lea dx, usuario
	int 21h

	;cargo variable
	lea bx, textoIngresa
	push bx
	call carga

	;limipio variable
	lea bx, textoIngresa
	push bx
	call reseteo

pidoContrasenia:
	mov ah, 9 				;pido contrase?a
	lea dx, contrasena
	int 21h

	;cargo contrase?a
	lea bx, textoIngresa
	push bx
	call carga
	
valida:
	lea bx, textoIngresa	
	push bx					;envio offset de variable
	call validacion 
	cmp al,	0				;comparo
	je finValidacion		;si es v?lida termina validaci?n
	
	lea bx, textoIngresa	;limipio variable
	push bx
	call reseteo
	jmp pidoContrasenia 	;pido de nuevo contrase?a

finValidacion:
	;limpio pantalla e imprimo cartel
	mov ah, 0
	mov al, 3
	int 10h 

	mov ah, 9
	lea dx, cartel1
	int 21h

	mov ah, 9
	lea dx, espacio
	int 21h

pidoEmail:
	mov ah, 9
	lea dx, email
	int 21h

	lea bx, textoIngresa
	push bx
	call carga

pidoTelefono:
	mov ah, 9
	lea dx, telefono
	int 21h

	lea bx, textoIngresa
	push bx
	call carga

	;limpio pantalla e imprimo cartel
	mov ah, 0
	mov al, 3
	int 10h 

	mov ah, 9
	lea dx, cartel1
	int 21h

	mov ah, 9
	lea dx, espacio
	int 21h

pidoCuil:
	mov ah, 9
	lea dx, cuil
	int 21h

	lea bx, textoIngresa
	push bx
	call carga

pidoCpa:
	mov ah, 9
	lea dx, cpa 
	int 21h

	lea bx, textoIngresa
	push bx
	call carga

	;limpio pantalla e imprimo cartel
	mov ah, 0
	mov al, 3
	int 10h 

	mov ah, 9
	lea dx, cartel1
	int 21h

	mov ah, 9
	lea dx, espacio
	int 21h

pidoMascota:
	mov ah, 9
	lea dx, mascota
	int 21h

	lea bx, textoIngresa
	push bx
	call carga

pidoHorario:
	mov ah, 9
	lea dx, horario 
	int 21h

	lea bx, textoIngresa
	push bx
	call carga

	;limpio pantalla e imprimo cartel
	mov ah, 0
	mov al, 3
	int 10h 

	mov ah, 9
	lea dx, cartel1
	int 21h

	mov ah, 9
	lea dx, espacio
	int 21h

Captcha:
	mov ah, 9
	lea dx, claveBanco 
	int 21h

	lea bx, textoIngresa
	push bx
	call carga

	;limpio pantalla e imprimo cartel
	mov ah, 0
	mov al, 3
	int 10h 

	mov ah, 9
	lea dx, cartel1
	int 21h

	mov ah, 9
	lea dx, espacio
	int 21h

textoFinal:
	mov ah, 9
	lea dx, msgFinal 
	int 21h

	mov ax, 4c00h
	int 21h
main endp

end main