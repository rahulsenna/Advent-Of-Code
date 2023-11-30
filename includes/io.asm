INCLUDE includes64.inc
.data
    holder                   QWORD    ?


.code
;-----------------------------------------------------
; WriteInt64
; Writes a 64-bit signed binary integer to the 
; console window in ASCII decimal.
; Receives: RAX = the integer
; Returns:  nothing
; Comments: Displays a leading sign, no leading zeros.
;-----------------------------------------------------
WriteInt64 PROC uses rbx rcx rdi

WI_Bufsize = 21		; size of digit buffer
true  =   1
false =   0
.data
buffer_B  BYTE  WI_Bufsize DUP(0),0  ; buffer to hold digits
neg_flag  BYTE  ?

.code
	mov   neg_flag,false    ; assume neg_flag is false
	or    rax,rax             ; is AX positive?
	jns   WIS1              ; yes: jump to B1
	neg   rax                ; no: make it positive
	mov   neg_flag,true     ; set neg_flag to true

WIS1:
	mov   rcx,0              ; digit count = 0
	mov   rdi,OFFSET buffer_B
	add   rdi,(WI_Bufsize-1)
	mov   rbx,10             ; will divide by 10

WIS2:
	mov   rdx,0              ; set dividend to 0
	div   rbx                ; divide AX by 10
	or    dl,30h            ; convert remainder to ASCII
	dec   rdi                ; reverse through the buffer
	mov   [rdi],dl           ; store ASCII digit
	inc   rcx                ; increment digit count
	or    rax,rax             ; quotient > 0?
	jnz   WIS2              ; yes: divide again

	; Insert a leading sign into the buffer.
	dec   rdi						; back up in the buffer
	inc   rcx               	; increment counter
	mov   BYTE PTR [rdi],'+' 	; insert plus sign
	cmp   neg_flag,false    	; was the number positive?
	jz    WIS3              	; yes
	mov   BYTE PTR [rdi],'-' 	; no: insert negative sign

WIS3:	; Display the number
	mov   rdx,rdi
	call  WriteString

	ret
WriteInt64 ENDP


;--------------------------------------------------------
; WriteString 
; Writes a null-terminated string to the console.
; Modifies: bytesWritten
; Receives: RDX points to the string
; Returns: nothing
;--------------------------------------------------------
WriteString proc uses rcx rdx r8 r9
.data
      InitFlag BYTE 0					; initialization flag
      consoleInHandle  QWORD ?     	; handle to standard input device
      consoleOutHandle QWORD ?     	; handle to standard output device
      bytesWritten     QWORD ?     	; number of bytes written
      bytesRead        QWORD ?
.code
	sub  rsp, (5 * 8) 					; create shadow space for 5 parameters

	CheckInit							; macro that checks and verifies initialization
	mov	 rcx,rdx
	call Str_length   					; returns length of string in EAX
		
	mov	 rcx,consoleOutHandle
	mov	 rdx,rdx						; string pointer
	mov	 r8, rax						; length of string
	lea	 r9,bytesWritten
	mov	 qword ptr [rsp + 4 * SIZEOF QWORD], 0	; (reserved parameter, set to zero)
	call WriteConsoleA

	add  rsp,(5 * 8)
	ret
WriteString ENDP

;---------------------------------------------------------
; Str_length
; Returns the length of a null-terminated string.
; Receives: RCX points to the string
; Returns: RAX = string length
;---------------------------------------------------------
Str_length PROC uses rdi
	mov  rdi,rcx
	mov  rax,0     	             ; character count
L1:
	cmp  BYTE PTR [rdi],0	     ; end of string?
	je   L2	                     ; yes: quit
	inc  rdi	                     ; no: point to next
	inc  rax	                     ; add 1 to count
	jmp  L1
L2: 
	ret
Str_length ENDP

;---------------------------------------------------
; Crlf
; Writes an end of line sequence to standard output
;---------------------------------------------------
Crlf proc uses rax rcx rdx 
.data
  crlfstring  byte 0dh,0ah,0
.code
	mov  rdx,offset crlfstring
	call WriteString
	ret
Crlf endp

;----------------------------------------------------
; Initialize
; Gets the standard console handles for input and output,
; and sets a flag indicating that it has been done.
; Modifies: consoleInHandle, consoleOutHandle, InitFlag
; Receives: nothing
; Returns: nothing
; ----------------------------------------------------
Initialize PROC private uses rax rcx rdx
	sub		rsp,28h				; set aside shadow space + align stack pointer

	mov		rcx,STD_INPUT_HANDLE
	call	GetStdHandle
	mov		[consoleInHandle],rax

	mov		rcx,STD_OUTPUT_HANDLE
	call	GetStdHandle
	mov		[consoleOutHandle],rax
	mov		InitFlag,1
	add		rsp,28h				; restore stack 

	ret
Initialize ENDP

;-----------------------------------------------------
ReadTextFile PROC
;
; Reads file into the input buffer.
; Receives: RSI: Filename, RDI: OutputBuffer, RBX: MaxBufferSize
; Returns: nothing
;-----------------------------------------------------
; Prologue
    qwBytesRead  equ  [rbp+16]
	  push		rbp				; Save the previous base pointer
	  mov		rbp, rsp	; Set the current stack frame as the new base pointer
	  

    WinCall     CreateFileA, rsi, GENERIC_READ,0,0,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,0
    cmp         rax,INVALID_HANDLE_VALUE
    je          FileNotFound

    lea         rsi,qwBytesRead
	
    WinCall     ReadFile, rax, rdi, rbx, rsi,0
 
; Epilogue    
    mov         rsp,rbp  ; restore the  stack  pointer
    pop         rbp      ; Restore the previous base pointer
    ret
FileNotFound:
    mov rcx, 0FA11h
    call ExitProcess
ReadTextFile ENDP

END