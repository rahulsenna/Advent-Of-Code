;   MASM 64bit Windows11

INCLUDE  includes/includes64.inc

.data
    Buffer          BYTE    4096*10           dup(?)  ;
    MaxBufferSize   EQU     4096*10                   
    ;Filename        BYTE    "sample.txt",0            ;           
    Filename        BYTE    "input.txt",0             ;            

    ans1            DWORD   0                         
    ans2            DWORD   0                         
    temp_num        byte    4 dup(0)
    ID DWORD 0
    
    color_map dword 0,0,0,0,0,1,1,1
    r EQU <[color_map+5*4]>
    g EQU <[color_map+7*4]>
    b EQU <[color_map+6*4]>

.code
  mov     rsi,OFFSET Filename          ;

AsciiToINT PROC USES rcx
  dec     rdi
  mov     rcx,rdi            
  mov     dh,10             
  mov     bl,1              
  xor     bh,bh             
L1:
  mov     al, [temp_num+rcx-1]
  sub     al,'0'            
  mul     bl
  add     bh,al             
  mov     al,bl             
  mul     dh                          ; 10x
  mov     bl,al             
  loop    L1
  shr     ebx,8              
  movzx   r8d,bl                      ; res

  ret
AsciiToINT ENDP


main PROC
    LOCAL   buf[4096]:BYTE, dwBytesWritten:QWORD,qwBytesRead:QWORD


  mov     rsi,OFFSET Filename          ;
  lea     rdi,Buffer         
  mov     rbx,MaxBufferSize  
  call    ReadTextFile
;-----------------------------------------------------
  mov     rsi,rdi            
  mov     rcx,rsi            
  add     rcx,qwBytesRead    
  cld                                     ; clear direction flag (foreward)
L1:
  
  mov     r,1              
  mov     g,1              
  mov     b,1              

  add     rsi,5                           ; skipping "Game "

  mov     rdi,0              
ReadID:
  lodsb
  mov     [temp_num+rdi],al             
  inc     rdi
  cmp     al,':'            
  jne     ReadID
  call    AsciiToINT
  mov     r9d,r8d                         ; r9d = ID

  lodsb                                   ; space after ':'

  mov     rdi,0  

ReadCubeCount:
  lodsb
  mov     [temp_num+rdi],al 
  inc     rdi
  cmp     al,' '
  jne     ReadCubeCount
  
  call    AsciiToINT                      ;-----------------------------------

  mov     rdi,rsi            
ReadColor:
  lodsb
  cmp     al,','            
  je      NextCube
  cmp     al,';'
  je      NextCube
  cmp     al,13                             ; \r
  je      NextCubNewLine
  cmp     al,0                              ; \0
  je      NextCubNewLine

  jmp     ReadColor
  
NextCube:
  lodsb                                     ; space after ',' or ';'
  mov     rax,rsi                           
  sub     rax,rdi
  xor     rdi,rdi
  mov     edx,[color_map+rax*4]
  cmp     r8d,edx
  jle     ReadCubeCount
  mov     [color_map+rax*4],r8d
  jmp     ReadCubeCount

NextCubNewLine:
  lodsb                                     ; \n
  mov     rax,rsi
  sub     rax,rdi
  mov     edx,[color_map+rax*4]
  cmp     r8d,edx
  jle     Continue
  mov     [color_map+rax*4],r8d

Continue:
  mov     r8,1                              ; Possible set to TRUE
  mov     eax,r  
  cmp     eax,12                            ; red <=12 ?
  jle     RedPass
  mov     r8,0  
RedPass:
  mov     ebx,b  
  cmp     ebx,14                            ; blue <=14 ?
  jle     BluePass
  mov     r8,0  
BluePass:
  mul     ebx
  mov     ebx,g  
  cmp     ebx,13                            ; green <=13 ?
  jle     GreenPass
  mov     r8,0  
GreenPass:

  mul     ebx
  add     ans2,eax

  cmp     r8,0                              ; if r8 == 0 then NOT POSSIBLE
  je      NotPossible
  add     ans1,r9d                          ; Possible.  r9d = ID
NotPossible:

  cmp     rcx,rsi
  ja      L1
Exitloop:
;-----------------------------------------------------
  ; print answer
  xor     rax,rax
  mov     eax,ans1
  call    WriteInt64                        ; part1
  call    Crlf

  xor     rax,rax
  mov     eax,ans2
  call    WriteInt64                        ; part2 

  xor     rcx, rcx                          ; return 0
  call    ExitProcess                       ; Exit;

  ret
main ENDP


END