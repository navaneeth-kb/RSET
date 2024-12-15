.model small
.stack 100h
.data
	str db 'madam$'
	msg1 db 'Pallindrome$'
	msg2 db 'Not pallindrome$'
.code
	mov ax,@data
	mov ds,ax

	mov si,offset str
	mov di,offset str
	mov al,'$'
	
	find_end:
		cmp al,[di]
		je dec_di
		inc di
		jmp find_end
	
	dec_di:
		dec di
		mov bh,1

	check_pall:
		cmp si,di
		jge pall
		mov al,[si]
		mov bl,[di]
		cmp al,bl
		jne not_pall
		inc si
		dec di
		jmp check_pall

	pall:
		lea dx,msg1
		mov ah,09h
		int 21h
		jmp end_prg

	not_pall:
		lea dx,msg2
		mov ah,09h
		int 21h

	end_prg:
		mov ah,4ch
		int 21h
end
		
