.586P 
.MODEL FLAT, STDCALL 
includelib krnel32.lib 

ExitProcess PROTO : DWORD 
MessageBoxA PROTO : DWORD, : DWORD, : DWORD, : DWORD 

.STACK 4096 

.CONST 

.DATA 
MB_OK  EQU 0 
NM1    DB 4 
NM2    DB 5
HW     DB ? 

.CODE 

main PROC  
START :

        MOV 
 

   push - 1  
   call ExitProcess  
main ENDP 

end main