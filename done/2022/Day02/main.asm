;   MASM 64bit Windows11

INCLUDE  includes/includes64.inc

.data

    ; Filename        BYTE "sample.txt",0;
    Filename        BYTE "input.txt",0;
    ; ALIGN 4
    buffer 	        BYTE 	4096*10    dup(?)
    MaxBufferSize 	equ     4096*10

    map1 	        BYTE 	40    dup(0)
    map2            BYTE 	40    dup(0)

    ans1          dword  0
    ans2          dword  0

.code
main proc
    LOCAL   buf[4096]:BYTE, dwBytesWritten:QWORD,qwBytesRead:QWORD

;---------------------------------------------------
;          Map1
    lea  rsi,map1

    ;  DRAW
    mov  BYTE PTR [rsi+11], 4 ; 11 = opp=1,me=1
    mov  BYTE PTR [rsi+22], 5
    mov  BYTE PTR [rsi+33], 6

    ;  LOSE
    mov  BYTE PTR [rsi+13], 3
    mov  BYTE PTR [rsi+21], 1
    mov  BYTE PTR [rsi+32], 2 ; opp=3,me=2 ; 3x10+2 = 32

    ;  WIN
    mov  BYTE PTR [rsi+12], 8
    mov  BYTE PTR [rsi+23], 9
    mov  BYTE PTR [rsi+31], 7

;---------------------------------------------------
;          Map2
    lea  rsi,map2

    ;  NEED to LOSE
    mov  BYTE PTR [rsi+11], 3
    mov  BYTE PTR [rsi+21], 1
    mov  BYTE PTR [rsi+31], 2

    ;  NEED to DRAW
    mov  BYTE PTR [rsi+12], 4
    mov  BYTE PTR [rsi+22], 5
    mov  BYTE PTR [rsi+32], 6

    ;  NEED to WIN
    mov  BYTE PTR [rsi+13], 8
    mov  BYTE PTR [rsi+23], 9
    mov  BYTE PTR [rsi+33], 7
;---------------------------------------------------


    mov     rsi, OFFSET Filename
    lea     rdi,buffer
    mov     rbx,MaxBufferSize
    call    ReadTextFile

    mov    rcx,qwBytesRead
    mov    rsi,rdi


    cld
L1:
    xor    rax,rax
    xor    rbx,rbx

    lodsb             ; opp move
    sub    al, 64     ; 'A'-1
    cmp    al,3
    ja     LoopExit   ; quit loop if new line has invalid chars
                      ; multiply by 10
    mov    bl,al      ; oppx10+me = index to points in the map
    mov    al,10
    mul    bl
    mov    bl,al

    lodsb             ; ' '
    lodsb             ; my move
    sub    al, 64+23  ; 'A'-1
    add    al,bl

    mov    bl,[map1+eax]
    add    ans1,ebx

    mov    bl,[map2+eax]
    add    ans2,ebx

    lodsb             ;  '\r'
    lodsb             ;  '\n'
loop    L1
LoopExit:

                      ; print answer
  xor  rax,rax
  mov  eax, ans1
  call WriteInt64
  call Crlf
  mov  eax, ans2
  call WriteInt64

    xor		rcx, rcx	;   return 0
    call	ExitProcess	;   Exit;

    ret
main endp


END