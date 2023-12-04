;   MASM 64bit Windows11

DigitConv  macro
    sub al, '0' 
    movzx rbx, al 
    mov rax, 10 
    mul rdi 
    mov rdi, rax 
    add rdi, rbx 
endm
INCLUDE  includes/includes64.inc

.data
                Buffer          BYTE    4096*10          dup(?)  ;
                MaxBufferSize   EQU     4096*10
                Filename        BYTE    "input.txt",0            ;            

                ans1            QWORD   0
                ans2            QWORD   0
                win_map         BYTE    100              dup(0)
                cards           QWORD   199              dup(1)
.code
main PROC
    LOCAL   buf[4096]:BYTE, dwBytesWritten:QWORD,qwBytesRead:QWORD


                mov             rsi,OFFSET Filename              ;
                lea             rdi,Buffer
                mov             rbx,MaxBufferSize
                call            ReadTextFile
                mov             r8,0
;-----------------------------------------------------
                lea             rsi,Buffer
                mov             rcx,rsi
                add             rcx,qwBytesRead
L1:
                lodsb
                cmp             al,':'
                jne             L1
                
                mov             r10,0                            ; win_cnt

                call            clear_win_map                    ;

                mov             rdi,0
                lodsb                                            ; space before win num starts
ReadWinNumber:
                lodsb
                cmp             al,' '
                je              NextWinNumber
                cmp             al,'|'
                je              ExitWinNO
                DigitConv
                jmp             ReadWinNumber
NextWinNumber:
                cmp             rdi,0
                je              ReadWinNumber
                mov             BYTE ptr [win_map +rdi],1        ; map win num to mem location
                mov             rdi,0
                jmp             ReadWinNumber

ExitWinNO:

                mov             r9,0                             ; points

                mov             rdi,0
                lodsb                                            ; space before win num starts
ReadMyNumber:
                lodsb
                cmp             al,' '
                je              MyNextNumber
                cmp             al,13                            ; '/r'
                je              MyNextNumber
                cmp             al,10                            ; '/n'
                je              MyNumExit
                DigitConv
                jmp             ReadMyNumber
MyNextNumber:
                cmp             rdi,0
                je              ReadMyNumber
                cmp             BYTE ptr [win_map +rdi],1        ;
                jne             NextPlease
                inc             r10                              ; win_cnt
                cmp             r9,0
                jne             Inited
                mov             r9,1
                jmp             NextPlease
Inited:
                shl             r9,1                             ;
NextPlease: 
                mov             rdi,0
                jmp             ReadMyNumber

MyNumExit:
                add             ans1,r9
                cmp             r10,0
                je              Continue
                call            ProcessExtraCards

  Continue:
                inc             r8

                cmp             rcx,rsi
                ja              L1


;-----------------------------------------------------
; print answer
                mov             rax,ans1
                call            WriteInt64
                call            Crlf

                mov             rcx,199

SumAllCards:
                mov             rax,[cards+rcx*8-8]
                add             ans2,rax
                loop            SumAllCards

                mov             rax,ans2
                call            WriteInt64

                xor             rcx, rcx                         ; return 0
                call            ExitProcess                      ; Exit;

                ret
main ENDP

clear_win_map PROC uses rcx
                mov             rdi,offset win_map
                mov             rcx,100
                mov             al,0
                rep             stosb
                ret
clear_win_map ENDP

ProcessExtraCards PROC uses rcx
                mov             rdi,offset cards
                mov             rcx, [rdi+r8*8]
OuterLoop:
                push            rcx
                mov             rcx,r10
                mov             rdi,offset cards
                mov             rax,8
                mul             r8
                add             rdi,rax
InnerLoop:
                add             rdi,8
                mov             rax, [rdi]
                inc             rax
                mov             [rdi],rax
                loop            InnerLoop
                pop             rcx

                loop            OuterLoop

                ret
ProcessExtraCards ENDP
END