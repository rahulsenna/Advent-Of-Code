;   MASM 64bit Windows11

INCLUDE  includes/includes64.inc

.data
    Buffer          BYTE    4096*10         dup(?)      ;
    MaxBufferSize   EQU     4096*10                     

    ;Filename        BYTE    "sample.txt",0;
    Filename        BYTE    "input.txt",0;              
    

    tmp_digits      BYTE    1000            dup(0)      
    CoordsSum      DWORD   0                           

    ans1            DWORD   0                           
    ans2            DWORD   0                           

.code

NewlineProcess PROC
  lodsb                             ; '\n'
  xor     rax,rax
  mov     al, [tmp_digits]
  mov     bl, 10
  mul     bl
  mov     bl, [rdi-1]
  add     al,bl
  add     CoordsSum,eax
  mov     rdi, OFFSET tmp_digits
  ret
NewlineProcess ENDP


DigitSearchAndCount PROC
  cmp     al,'0'
  jb      NonDigit

  cmp     al,'9'
  ja      NonDigit
  
  ; char is a digit
  sub     al,'0'
  mov     [rdi],al
  inc     rdi

  mov     al,1
  ret
NonDigit:
  mov     al,0
  ret
DigitSearchAndCount ENDP

Part_One PROC
  cld                     ; clear direction flag
L1:
  lodsb                   ; load char into al
  cmp     al,13           ; '\r'
  je      NewLine

  call    DigitSearchAndCount
  jmp     Continue
  
NewLine:
  call    NewlineProcess

Continue:
  loop    L1
  ret
Part_One ENDP


main PROC
    LOCAL   buf[4096]:BYTE, dwBytesWritten:QWORD,qwBytesRead:QWORD

  mov     rsi, OFFSET Filename    ;
  lea     rdi,Buffer          
  mov     rbx,MaxBufferSize   
  call    ReadTextFile

  mov     rcx,qwBytesRead     
  sub     rcx,3                  ;trim input.txt   
  mov     rsi,rdi
  mov     rdi, OFFSET tmp_digits
  
  call    Part_One
  ;part_1 print answer
  xor     rax,rax
  mov     eax,CoordsSum
  call    WriteInt64
  call    Crlf

;----------------------------------------------------------
; part_2
.data
    Numbers byte "one",0, "two",0, "three",0, "four",0, "five",0, "six",0, "seven",0, "eight",0,"nine",0,69
    MapNum byte "one",1, "two",2, "three",3, "four",4, "five",5, "six",6, "seven",7, "eight",8,"nine",9,69
.code

  mov     CoordsSum,0    ; reset for part2
  mov     rcx,qwBytesRead     
  sub     rcx,3           ;trim input.txt   
  lea     rsi,Buffer
  mov     rdi,OFFSET tmp_digits
  
  cld                     ; clear direction flag
L1:
  mov     al,[rsi]        ; load char into al
  cmp     al,13           ; '\r'
  je      NewLine

  call    DigitSearchAndCount
  cmp     al,1
  je      WasDigit
;--------------------------------
; matching sub string
  mov     r8,OFFSET Numbers
NextNum:
  xor     r9,r9
L2:
  mov     bl,[r8]
  cmp     bl,69
  je      EndNumMatch
  cmp     bl,0
  je      FoundNum
 
  mov     al,[rsi+r9]

  inc     r8
  inc     r9
  cmp     al,bl
  je      L2
RunToNextNum:
  inc     r8
  mov     bl,[r8]
  cmp     bl,0
  jne     RunToNextNum
  
  inc     r8
  jmp     NextNum

EndNumMatch:
  inc     rsi
  jmp     Continue

FoundNum:
  mov     rax, OFFSET Numbers
  sub     r8,rax
  mov     rax, OFFSET MapNum
  mov     al,[rax+r8]
  mov     [rdi],al
  inc     rdi
  sub     r9,2            ; 1 for /0 null char and 1 for non overlap matching
  add     rsi,r9
  add     rcx,r9
  jmp     Continue

NewLine:
  call   NewlineProcess

WasDigit:
  inc     rsi
Continue:

  dec     rcx
  cmp     rcx,0
  jg      L1
;loop L1

  ; print answer part 2
  xor     rax,rax
  mov     eax,CoordsSum
  call    WriteInt64
  call    Crlf

  xor     rcx,rcx        ; return 0
  call    ExitProcess    ; Exit;

  ret
main ENDP


END