;   MASM 64bit Windows11

INCLUDE includes/includes64.inc   ; Include external files

.data
             Buffer          BYTE    4096*10           dup(?)              ; Buffer to store file content
             MaxBufferSize   EQU     4096*10                               ; Maximum buffer size
             Filename        BYTE    "input.txt",0                         ; Input file name

             bignum          QWORD   2                 dup(0)              ; Array for big numbers
             times           QWORD   4                 dup(0)              ; Array for times
             dists           QWORD   4                 dup(0)              ; Array for distances

.code
main proc
    LOCAL   buf[4096]:BYTE, dwBytesWritten:QWORD, qwBytesRead:QWORD

             mov             rsi, OFFSET Filename                          ; Set RSI to the address of Filename
             lea             rdi, Buffer                                   ; Set RDI to the address of Buffer
             mov             rbx, MaxBufferSize                            ; Set RBX to MaxBufferSize
             call            ReadTextFile                                  ; Call function to read text file

    ; -----------------------------------------------------
             lea             rsi, Buffer                                   ; Set RSI to the address of Buffer
             mov             rcx, rsi                                      ; Set RCX to the current position in the buffer
             add             rcx, qwBytesRead                              ; Add the number of bytes read to RCX
             xor             r8, r8                                        ; Clear R8 register
             cld                                                           ; Clear direction flag (forward string operations)

ParseLoop:
             lodsb                                                         ; Load the next byte from the buffer into AL
             cmp             al, 0                                         ; Check if the byte is null terminator
             je              ExitLoop                                      ; If yes, exit the loop
             cmp             al, ':'                                       ; Check if the byte is ':'
             jne             ParseLoop                                     ; If not, continue parsing

             mov             rdi, 0                                        ; Clear RDI register for storing digits
             mov             r9, 0                                         ; Clear R9 register for storing another set of digits
             mov             r10, 0                                        ; Clear R10 register for index tracking

SpaceLoop:
             lodsb                                                         ; Load the next byte from the buffer into AL
             cmp             al, ' '                                       ; Check if the byte is a space
             je              SpaceLoop                                     ; If yes, skip to SpaceLoop

    Digit:    
             sub             al, '0'                                       ; Convert ASCII character to integer
             movzx           rbx, al                                       ; Zero-extend the integer to RBX
             mov             rax, 10                                       ; Set RAX to 10 for multiplication
             mul             rdi                                           ; Multiply RDI by 10
             mov             rdi, rax                                      ; Update RDI with the result
             add             rdi, rbx                                      ; Add the new digit to RDI
    ; --------------
             mov             rax, 10
             mul             r9
             mov             r9, rax
             add             r9, rbx
    ; --------------


             lodsb
             cmp             al,' '
             je              Calc
             cmp             al,13
             je              Calc

             jmp             Digit

Calc:
             cmp             r9,0
             je              SpaceLoop
             cmp             r8,0                                          ; r8 = Line Index
             je              Times
             mov             [dists+ r10*8],r9
             jmp             SpaceContinue
Times:
             mov             [times + r10*8],r9
SpaceContinue:
             inc             r10
             mov             r9,0
  
             cmp             al,13
             je              newline

             jmp             SpaceLoop


newline:
             lodsb
             mov             [bignum+r8*8],rdi
             inc             r8
             cmp             rcx,rsi
             ja              ParseLoop                                     ; ParseLoop

ExitLoop:

             mov             rcx, r10                                      ; Set RCX to the count of items in the array
             mov             r9, 0                                         ; Clear R9 register (accumulator)
             mov             r10, 1                                        ; Set R10 to 1 (initial result)

             mov             rsi,0

Part1Loop:
             push            rcx                                           ; Save the loop counter on the stack
             mov             rcx, [times + rsi*8]                          ; Load the time from the array
             mov             rbx,rcx

TimeLoop:
             mov             rax, rbx                                      ; Set RAX to rbx (total time)
             sub             rax, rcx                                      ; Calculate rcx*(rbx-rcx)
             mul             rcx                                           ; Result in RAX
             cmp             rax, [dists + rsi*8]                          ; Compare with dists array value
             jb              ContinueTimeLoop                                     ; Jump if below
             inc             r9                                            ; Increment accumulator

ContinueTimeLoop:
             loop            TimeLoop                                         ; Loop until rcx becomes zero
             pop             rcx                                           ; Restore the loop counter from the stack
             mov             rax, r9                                       ; Move the accumulator to RAX
             mul             r10                                           ; Multiply the result with the current total
             mov             r10, rax                                      ; Update the total
             mov             r9, 0                                         ; Clear the accumulator
             inc             rsi                                           ; Move to the next item in the array
             loop            Part1Loop                                     ; Loop until all items are processed

    ; Print the answer
             mov             rax, r10                                      ; Load the result into RAX
             call            WriteInt64                                    ; Call function to write 64-bit integer
             call            Crlf                                          ; Call function to print a new line

    ; ------------------------------------------------
    ; Part 2

             mov             rcx, [bignum]                                 ; Load big time
             mov             r8, [bignum + 8]                              ; Load big dist
             mov             rdi, rcx                                      ; Set RDI to big time
             xor             rsi, rsi                                      ; Clear RSI (loop counter)
             xor             r9, r9                                        ; Clear R9 (accumulator)

Part2Loop:
    ; Calculate dist = rsi * (rdi-rsi)
             mov             rax, rdi
             sub             rax, rsi
             mul             rsi                                           ; Result in RAX
             cmp             rax, r8                                       ; Compare with big dist
             jb              ContinuePart2Loop                             ; jb = Did not WIN

             inc             r9                                            ; Won. Increment accumulator

ContinuePart2Loop:
             inc             rsi                                           ; Increment loop counter
             loop            Part2Loop                                     ; Loop until rsi reaches zero

    ; Print the answer
             mov             rax, r9                                       ; Load the result into RAX
             call            WriteInt64                                    ; Call function to write 64-bit integer
             call            Crlf                                          ; Call function to print a new line

             xor             rcx, rcx                                      ; Set return value to 0
             call            ExitProcess                                   ; Call function to exit the program

             ret
main endp

END
