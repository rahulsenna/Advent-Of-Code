;									                      Calling Convention
; +----------------------------------+------------------+------------------+------------------+------------------+------------------+
; |    Parameter type                |  fifth and higher|      fourth      |      third       |     second       |   leftmost       |
; +----------------------------------+------------------+------------------+------------------+------------------+------------------+
; |    floating-point                |      stack       |      XMM3        |      XMM2        |     XMM1         |      XMM0        |
; +----------------------------------+------------------+------------------+------------------+------------------+------------------+
; |    integer                       |      stack       |       R9         |       R8         |      RDX         |       RCX        |
; +----------------------------------+------------------+------------------+------------------+------------------+------------------+
; |    Aggregates (8, 16, 32, or 64  |      stack       |       R9         |       R8         |      RDX         |       RCX        |
; |    bits) and __m64               |                  |                  |                  |                  |                  |
; +----------------------------------+------------------+------------------+------------------+------------------+------------------+
; |    Other aggregates, as pointers |      stack       |       R9         |       R8         |      RDX         |       RCX        |
; +----------------------------------+------------------+------------------+------------------+------------------+------------------+
; |    __m128, as a pointer          |      stack       |       R9         |       R8         |      RDX         |       RCX        |
; +----------------------------------+------------------+------------------+------------------+------------------+------------------+



;***** WinCall *********************************************************************************************************
;
; Every function invoking this macro MUST have a local "holder" variable declared.

                                                 ;***** [Declare macro] ************************************************

WinCall                                          macro               call_dest:req, argnames:vararg                    ; Declare macro

                                                 local               jump_1, lpointer, numArgs                         ; Declare local labels

                                                 ;***** [Process] ******************************************************

                                                 numArgs             = 0                                               ; Initialize # arguments passed

                                                 for                 argname, <argnames>                               ; Loop through each argument passed
                                                   numArgs           = numArgs + 1                                     ; Increment local # arguments count
                                                 endm                                                                  ; End of FOR looop

                                                 if numArgs lt 4                                                       ; If # arguments passed < 4
                                                   numArgs = 4                                                         ; Set count to 4
                                                 endif                                                                 ; End IF

                                                 mov                 holder, rsp                                       ; Save the entry RSP value

                                                 sub                 rsp, numArgs * 8                                  ; Back up RSP 1 qword for each parameter passed

                                                 test                rsp, 0Fh                                          ;
                                                 jz                  jump_1                                            ;
                                                 and                 rsp, 0FFFFFFFFFFFFFFF0h                           ; Clear low 4 bits for para alignment
jump_1:
                                                 lPointer            = 0                                               ; Initialize shadow area @ RSP + 0

                                                 for                 argname, <argnames>                               ; Loop through arguments
                                                   if                lPointer gt 24                                    ; If not on argument 0, 1, 2, 3
                                                     mov             rax, argname                                      ; Move argument into RAX
                                                     mov             [ rsp + lPointer ], rax                           ; Shadow the next parameter on the stack
                                                   elseif            lPointer eq 0                                     ; If on argument 0
                                                     mov             rcx, argname                                      ; Argument 0 -> RCX
                                                   elseif            lPointer eq 8                                     ; If on argument 1
                                                     mov             rdx, argname                                      ; Argument 1 -> RDX
                                                   elseif            lPointer eq 16                                    ; If on argument 2
                                                     mov             r8, argname                                       ; Argument 2 -> R8
                                                   elseif            lPointer eq 24                                    ; If on argument 3
                                                     mov             r9, argname                                       ; Argument 3 -> R9
                                                   endif                                                               ; End IF
                                                   lPointer          = lPointer + 8                                    ; Advance the local pointer by 1 qword
                                                 endm                                                                  ; End FOR looop

                                                 call                call_dest                                         ; Execute call to destination function

                                                 mov                 rsp, holder                                       ; Reset the entry RSP value

                                                 ;***** [End macro] ****************************************************

                                                 endm                                                                  ; End macro declaration


;-------------------------------------------------------------
CheckInit MACRO
;
; Helper macro
; Check to see if the console handles have been initialized
; If not, initialize them now.
;-------------------------------------------------------------
LOCAL exit
	cmp InitFlag,0
	jne exit
	call Initialize
exit:
ENDM

option casemap:none ; Disable case sensitivity


extern CreateFileA: PROC
; HANDLE CreateFileA(
;   [in]           LPCSTR                lpFileName,
;   [in]           DWORD                 dwDesiredAccess,
;   [in]           DWORD                 dwShareMode,
;   [in, optional] LPSECURITY_ATTRIBUTES lpSecurityAttributes,
;   [in]           DWORD                 dwCreationDisposition,
;   [in]           DWORD                 dwFlagsAndAttributes,
;   [in, optional] HANDLE                hTemplateFile
; );


extern ReadFile: PROC
; BOOL ReadFile(
;   [in]                HANDLE       hFile,
;   [out]               LPVOID       lpBuffer,
;   [in]                DWORD        nNumberOfBytesToRead,
;   [out, optional]     LPDWORD      lpNumberOfBytesRead,
;   [in, out, optional] LPOVERLAPPED lpOverlapped
; );

extern WriteFile: PROC
; BOOL WriteFile(
;   [in]                HANDLE       hFile,
;   [in]                LPCVOID      lpBuffer,
;   [in]                DWORD        nNumberOfBytesToWrite,
;   [out, optional]     LPDWORD      lpNumberOfBytesWritten,
;   [in, out, optional] LPOVERLAPPED lpOverlapped
; );

extern GetCurrentDirectoryA: PROC
; DWORD GetCurrentDirectory(
;   [in]  DWORD  nBufferLength,
;   [out] LPTSTR lpBuffer
; );

extern GetStdHandle: PROC
; HANDLE WINAPI GetStdHandle(
;   _In_ DWORD nStdHandle
; );

; STD_INPUT_HANDLE  ((DWORD)-10)	The standard input device. Initially, this is the console input buffer, CONIN$.
; STD_OUTPUT_HANDLE ((DWORD)-11)	The standard output device. Initially, this is the active console screen buffer, CONOUT$.
; STD_ERROR_HANDLE  ((DWORD)-12)	The standard error device. Initially, this is the active console screen buffer, CONOUT$.

extern ExitProcess: PROC
; void ExitProcess(
;   [in] UINT uExitCode
; );

extern MessageBoxA: PROC



WriteConsoleA proto


WriteInt64 proto
Crlf proto
ReadTextFile proto
WriteString proto









;---------------------------------------------------------------------
;            VARS

    STD_INPUT_HANDLE          equ  -11
    STD_OUTPUT_HANDLE         equ  -11
    STD_ERROR_HANDLE          equ  -11


    GENERIC_READ              equ   80000000h
    OPEN_EXISTING             equ   3
    FILE_ATTRIBUTE_NORMAL     equ   80h
    INVALID_HANDLE_VALUE      equ  -1
    NULL                      equ   0

    EXTERNDEF                holder:QWORD
; QWORD 8bytes 64bit
; DWORD 4bytes 32bit
; WORD  2bytes 16bit
; BYTE  1byte   8bit










;-----------------------------------------------------

;
; Explain  what proc  does.
; Receives: RSI: Filename, RDI: OutputBuffer
; Returns: EAX = match count
;-----------------------------------------------------