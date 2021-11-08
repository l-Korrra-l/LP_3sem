.586P 
.MODEL FLAT, STDCALL 
includelib kernel32.lib 

ExitProcess PROTO : DWORD 
MessageBoxA PROTO : DWORD, : DWORD, : DWORD, : DWORD

.STACK 4096 

.CONST 

.DATA 
myBytes     byte   10h, 20h, 30h, 40h
myWords     word   8Ah, 3Bh, 44h, 5Fh, 99h
myDoubles   dword  1, 2, 3, 4, 5, 6
myPointer   dword  myDoubles



arr         dword  3, 4, 5, 6, 1, 2
MB_OK       EQU    0 
STR0        DB    "Мергель Каролина Андреевна, 1 курс, 4 группа", 0 
STR1        DB    "Есть нулевой эелемент",0 
STR2        DB    "Нулевого элемента не найдено",0 
HW          DD    ? 
.CODE 

main PROC  
START :   

    mov ESI, 0
    mov EAX, myDoubles[ESI + 4]  ; EAX=2
    mov EDX, [myDoubles + ESI]   ; EDX=1

    mov ecx, lengthof arr
    mov esi, OFFSET arr
    mov eax, 0
    mov ebx, 1

CYCLE:
    add eax, [esi]
    mov edx, [esi]
    cmp edx, 0
    jnz zf0
    mov ebx, 0

zf0:
    add esi, 4
    loop CYCLE

    cmp ebx, 0
    jnz zf2

zf1:
    INVOKE MessageBoxA, HW, OFFSET STR1,OFFSET STR0, MB_OK
    jmp enn

zf2:
    INVOKE MessageBoxA, HW, OFFSET STR2,OFFSET STR0, MB_OK
    jmp enn

 
enn:
   push - 1  
   call ExitProcess  
main ENDP 
end main