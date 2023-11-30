;   MASM 64bit Windows11

INCLUDE  includes/includes64.inc

.data

    ;Filename        BYTE    "sample.txt",0;
    Filename        BYTE    "input.txt",0;
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


  ;lea    rdx,buffer
  ;call   WriteString

  ; print answer
  xor  rax,rax
  call WriteInt64
  call Crlf

  call WriteInt64

  xor  rcx, rcx     ; return 0
  call ExitProcess  ; Exit;

    ret
main endp


END