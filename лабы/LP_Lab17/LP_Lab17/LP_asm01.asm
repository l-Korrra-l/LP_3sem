.586														; ������� ������ (��������� Pentium)
.model flat, stdcall										; ������ ������(�������), ���������� � �������
includelib kernel32.lib										; ������������: ����������� � kernel32
ExitProcess PROTO: DWORD									; �������� ������� ��� ���������� �������� Windows 
MessageBoxA PROTO      ,:DWORD, :DWORD, :DWORD, :DWORD  
.stack 4096

.const
	massiv sdword -3, 18, 27, -9, -17, 12, 83, -2, 10, 11


.data
	min sdword ?
.code

getmin PROC parm1 :DWORD, parm2 :DWORD
	mov esi, parm1          
    mov ecx, parm2
    mov eax, [esi] 
L1:
	cmp [esi], eax
	jl L2													;JL - �������, ���� ������ 
	jmp next
L2:
	mov eax, [esi]
next:
	add esi, 4
	loop L1
	ret          
getmin ENDP

main PROC													; ����� ����� main
    INVOKE getmin, offset massiv, lengthof massiv			; ����� ��������� getmin
    mov min, eax											; ��������� � min
	INVOKE ExitProcess, 0									; ���������� �������� Windows
main ENDP													; ����� ���������
end main  