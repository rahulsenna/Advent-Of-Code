;   MASM 64bit Windows11

INCLUDE  includes/includes64.inc

.data

    ;Filename        BYTE "sample.txt",0;
    Filename        BYTE "input.txt",0;
    ; ALIGN 4
    buffer          BYTE    4096*10    dup(?)
    MaxBufferSize   EQU     4096*10

    elves           DWORD    1000    dup(0)
    elf_cnt         DWORD    0

    ans1            DWORD    0
    ans2            DWORD    0

.code
main proc
    LOCAL   buf[4096]:BYTE, dwBytesWritten:QWORD,qwBytesRead:QWORD


  mov     rsi, OFFSET Filename
  lea     rdi,buffer
  mov     rbx,MaxBufferSize
  call    ReadTextFile

  mov rsi,rdi
  mov rcx,qwBytesRead
  sub rcx,3

  mov  edi,1   ; power of 10
  xor  ebx,ebx ; accumulator
  xor  r8d,r8d ; build number

  std          ; direction flag (reverse)
  add  rsi,rcx
L1:
  cmp  rcx,0
  jl   ExitLoop
  xor  eax,eax

  lodsb
  cmp   al,10       ; '\n'
  je    newLine
  sub al,'0'
                    
  mul  edi          ; multiply num with pow of 10
  add  r8d,eax      ; building number

  mov  eax,10       ; next power of 10
  mul  edi
  mov  edi,eax

loop    L1
newLine:
  add  ebx,r8d      ; accumlate
  xor  r8d,r8d      ; build number reset on new line
  mov  edi,1        ; reset power of 10
  dec  rsi          ; '\r'


  cmp  byte ptr[rsi],10
  je   newElf


loop    L1
newElf:
  sub  rsi,2      ; skip '\r\n'
  mov   eax,elf_cnt
  mov   [elves +eax*4],ebx
  inc  elf_cnt
  xor  ebx,ebx    ; reset accumulator

loop    L1
ExitLoop:

;------------------------------------
;     Bubble Sort
  mov rsi, OFFSET elves
BubbleOuter:
  xor rcx,rcx
  mov ecx,elf_cnt
  dec ecx
  xor edx,edx
BubbleInner:
  mov  eax,[rsi + rcx*4]
  cmp  eax,[rsi + rcx*4-4]
  jle  continue
  xchg eax,[rsi + rcx*4-4]
  mov  [rsi + rcx*4],eax
  inc  edx
continue:
  loop  BubbleInner
  cmp  edx,0
  ja  BubbleOuter
;------------------------------------
 

  ;lea    rdx,buffer
  ;call   WriteString

  ; print answer
  xor  rax,rax
  mov  eax, [elves]
  call WriteInt64
  call Crlf

  mov  eax, [elves]
  add  eax,[elves+4]
  add  eax,[elves+8]
  call WriteInt64

  xor  rcx, rcx     ; return 0
  call ExitProcess  ; Exit;

    ret
main endp


END