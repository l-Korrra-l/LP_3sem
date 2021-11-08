.586P 
.MODEL FLAT, STDCALL 
includelib kernel32.lib 

ExitProcess PROTO : DWORD 
MessageBoxA PROTO : DWORD, : DWORD, : DWORD, : DWORD

.STACK 4096 

.CONST 

.DATA 
MB_OK  EQU 0 
STR1   DB "Mssgbox", 0 
STR2   DB "Результат сложения чисел = ",0 
HW     DD ? 
.CODE 

main PROC  
START :   


    mov eax, 2h
    mov ebx, 3h
    add eax, ebx
    add eax, 30h                     ; 30h => "0"
    mov ebx, offset STR2
    add ebx, sizeof STR2
    dec ebx
    dec ebx
    mov [ebx], eax

INVOKE MessageBoxA, HW, OFFSET STR2,OFFSET STR1, MB_OK
 

   push - 1  
   call ExitProcess  
main ENDP 

end main