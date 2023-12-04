;   MASM 64bit Windows11

INCLUDE  includes/includes64.inc

.data
            PreBuffer       BYTE    8*100           dup('.')  ; for out of bound search
            Buffer          BYTE    4096*10         dup(?)    ;
            MaxBufferSize   EQU     4096*10

            Filename        BYTE    "input.txt",0             ;
            Rows            EQU     140                       ;;     
            Cols            EQU     140                       ;;     
            LineSize        EQU     <Cols+2>                  ;;
    

            ans1            QWORD   0
            ans2            DWORD   0
            gearmap         BYTE    4096*10         dup(0)    ;
            gear_ratio      dword   4096*10         dup(0)    ;

.code

IsSymbol proc
            cmp             bl,'.'
            je              NotSymbol
            cmp             bl,13                             ; '\r' new line
            je              NotSymbol

            cmp             bl,10                             ; '\n' new line
            je              NotSymbol

            cmp             bl,0
            je              NotSymbol

            cmp             bl, '0'
            jb              NonDigit
            cmp             bl, '9'
            ja              NonDigit
            jmp             NotSymbol                         ; is digit

NonDigit:
            mov             r8,1                              ; Is a Symbol
            mov             r9, rax                           ; idx for gear ratio
            ret

NotSymbol:    
            ret
IsSymbol endp


SearchSymbol proc uses rcx
            mov             rcx, offset   Buffer
    ; left
            mov             eax,LineSize
            mul             esi
            add             eax,edi
            dec             eax                               ; -1 col
            mov             bl, [ecx+eax]
            call            IsSymbol
            cmp             r8,1
            je              EndSearch

    ; right
            mov             eax,LineSize
            mul             esi
            add             eax,edi
            inc             eax                               ; +1 col
            mov             bl, [ecx+eax]
            call            IsSymbol
            cmp             r8,1
            je              EndSearch


    ; up
            mov             eax,LineSize
            mul             esi
            add             eax,edi
            sub             eax,LineSize                      ; -1 row
            mov             bl, [ecx+eax]
            call            IsSymbol
            cmp             r8,1
            je              EndSearch
    
    ; down
            mov             eax,LineSize
            mul             esi
            add             eax,edi
            add             eax,LineSize                      ; +1 row
            mov             bl, [ecx+eax]
            call            IsSymbol
            cmp             r8,1
            je              EndSearch

    ; up-left
            mov             eax,LineSize
            mul             esi
            add             eax,edi
            sub             eax,LineSize+1                    ; -1 row, -1 col
            mov             bl, [ecx+eax]
            call            IsSymbol
            cmp             r8,1
            je              EndSearch

    ; up-right
            mov             eax,LineSize
            mul             esi
            add             eax,edi
            sub             eax,LineSize-1                    ; -1 row, +1 col   -LineSize+1 = -11
            mov             bl, [ecx+eax]
            call            IsSymbol
            cmp             r8,1
            je              EndSearch

    ; down-right
            mov             eax,LineSize
            mul             esi
            add             eax,edi
            add             eax,LineSize+1                    ; +1 row, +1 col
            mov             bl, [ecx+eax]
            call            IsSymbol
            cmp             r8,1
            je              EndSearch

    ; down-left
            mov             eax,LineSize
            mul             esi
            add             eax,edi
            add             eax,LineSize-1                    ; +1 row, -1 col  = +LineSize-1 = 11
            mov             bl, [ecx+eax]
            call            IsSymbol
            cmp             r8,1
            je              EndSearch

EndSearch:
            ret
SearchSymbol endp

main proc
    LOCAL   buf[4096]:BYTE, dwBytesWritten:QWORD,qwBytesRead:QWORD


            mov             rsi,OFFSET Filename               ;
            lea             rdi,Buffer
            mov             rbx,MaxBufferSize
            call            ReadTextFile


;-----------------------------------------------------
            mov             rsi,rdi
            mov             rcx,rsi
            add             rcx,qwBytesRead

            mov             rsi,0                             ; row
Outer:
            mov             rdi,0                             ; col
            mov             rcx,0
            mov             r8,0                              ; is symbol =false

Inner:
            mov             rax,LineSize                      ; idx = row * col_width + col 
            mul             rsi
            add             rax,rdi

            mov             al,[Buffer+rax]
            cmp             al, '0'
            jb              NonDigit
            cmp             al, '9'
            ja              NonDigit
                                                              ; <- al is a digit
            sub             al,'0'                            ; convert from ascii to dec
            movzx           rbx,al
            mov             rax,10
            mul             rcx
            mov             rcx,rax
            add             rcx,rbx

            call            SearchSymbol

            cmp             rdi,139                           ; last char in a line
            jne             Next
NonDigit:
            cmp             r8,1
            jne             IsNotGear
            add             ans1,rcx

            mov             bl,[gearmap+r9]
            inc             bl
            mov             [gearmap+r9],bl

            cmp             bl,1
            jng             NoRatio
            mov             eax,[gear_ratio+r9*4]
            mul             ecx
            mov             ecx,eax
NoRatio:
            mov             [gear_ratio+r9*4],ecx
IsNotGear:
            xor             r8,r8
            xor             rcx,rcx                           ; reset number
   
Next:
  

            inc             rdi
            cmp             rdi,Cols
            jl              Inner
            inc             rsi
            cmp             rsi,Rows
            jl              Outer

            mov             rsi, offset gear_ratio
            mov             rdi, offset gearmap
            mov             rcx, 4096*10
            cld
L3:
            mov             al,[rdi]
            cmp             al,1
            jng             Cont
            mov             eax,[rsi]
            add             ans2,eax
 Cont:
            inc             rdi
            add             rsi,4
            loop            L3


;-----------------------------------------------------
  ; print answer
            mov             rax,ans1
            call            WriteInt64
            call            Crlf

            xor             rax,rax
            mov             eax,ans2
            call            WriteInt64

            xor             rcx, rcx                          ; return 0
            call            ExitProcess                       ; Exit;

            ret
main endp


END