    .model flat,c			; This code is suppose to be called from C++ function
							
	extern N: dword			; N - array size, defined in main.cpp
	.code

Foo_ proc

        push ebp
        mov ebp,esp
		push esi
		push edi
		
		mov eax, [ebp + 8]	; eax = x
		xor esi, esi		; esi = i = 0
		xor edi, edi		; edi = j = 0
		xor ecx, ecx

		mov ebx, -1		;ebx - i counter
						;ecx - j counter
	iLoop:
		inc ebx
		cmp ebx, N
		je Finish		; je - jump if equal
		mov ecx, N		; j = N

	jLoop:
		dec ecx
		cmp ecx, ebx
		je iLoop
		mov esi, [eax + ecx*4]		
		mov edi, [eax + ecx*4 - 4]		
		cmp edi, esi
		jle jLoop
		mov dl, [eax + ecx*4]		
		mov dh, [eax + ecx*4 - 4]		
		mov [eax + ecx*4], dh		
		mov [eax + ecx*4 - 4], dl		
		jmp jLoop


	Finish:
		pop edi
		pop esi
	    pop ebp
    	ret

Foo_ endp
        end
