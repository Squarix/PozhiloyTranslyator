.586
	.model flat, stdcall
	includelib libucrt.lib
	includelib kernel32.lib
	includelib default_lib.lib
	ExitProcess PROTO :DWORD

stdlen PROTO :DWORD
strsearch PROTO : WORD, : WORD
mabs PROTO : REAL4
dgr  PROTO : DWORD, : DWORD
mcos PROTO : REAL4
mexp PROTO : REAL4
mln  PROTO : REAL4
msin PROTO : REAL4
msqr PROTO : REAL4
mtan PROTO : REAL4
print1 PROTO : DWORD
print2 PROTO : DWORD
print3 PROTO : REAL4

.stack 4096
.const
	L0		DWORD	2
	L1		DWORD	4
	L2		DWORD	2
	L3		DWORD	25
	L4		DWORD	1
	L5		DWORD	15
	L6		DWORD	0
	L7		DWORD	1
	L8		DWORD	1
.data
	tempReal4 REAL4 0.0
GLOBALz		SDWORD	?
GLOBALa		SDWORD	?
GLOBALb		SDWORD	?
GLOBALk		SDWORD	?
.code
fi PROC	 fia : DWORD
	PUSH	L0
	PUSH	L1
	PUSH	L2
	POP	 EBX
	POP	 EAX
	MOV	 EDX, 0
	DIV	 EBX
	MOV	 EBX, EAX
	PUSH	 EAX
	POP	 EDX
	POP	 EBX
	ADD	 EBX, EDX
	PUSH	 EBX
	POP	EAX
	MOV	GLOBALz, EAX
	MOV EAX, GLOBALz
	ret
fi ENDP
main PROC
	PUSH	L3
	PUSH	L4
	POP	 EBX
	POP	 EAX
	MOV	 EDX, 0
	MUL	 EBX
	MOV	 EBX, EAX
	PUSH	 EAX
	POP	EAX
	MOV	GLOBALa, EAX
	PUSH	L5
	POP	EAX
	MOV	GLOBALb, EAX
	PUSH	L6
	POP	EAX
	MOV	GLOBALk, EAX
	PUSH	GLOBALa
	call print1
	PUSH	GLOBALb
	call print1
while0:
	MOV EAX, GLOBALk
	cmp EAX, L7
	jb whileblock0
	ja whilend0
	je whilend0
whileblock0:
	MOV EAX, GLOBALa
	cmp EAX, GLOBALb
	je if00
	ja if0end0
	jb if0end0
if00:
	PUSH	GLOBALa
	call print1
	PUSH	L8
	POP	EAX
	MOV	GLOBALk, EAX
if0end0:
	MOV EAX, GLOBALa
	cmp EAX, GLOBALb
	ja if01
	je if0end1
	jb if0end1
	if01:
	PUSH	GLOBALa
	PUSH	GLOBALb
	POP	 EDX
	POP	 EBX
	SUB	 EBX, EDX
	PUSH	 EBX
	POP	EAX
	MOV	GLOBALa, EAX
if0end1:
	MOV EAX, GLOBALb
	cmp EAX, GLOBALa
	ja if02
	je if0end2
	jb if0end2
	if02:
	PUSH	GLOBALb
	PUSH	GLOBALa
	POP	 EDX
	POP	 EBX
	SUB	 EBX, EDX
	PUSH	 EBX
	POP	EAX
	MOV	GLOBALb, EAX
if0end2:
	jmp while0
whilend0:
	push 0
	call ExitProcess
main ENDP
end main
