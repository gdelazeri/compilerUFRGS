	.file "example.language"
	.globl a
	.data
	.align 4
	.type a, @object
	.size a, 4
a:
	.long 0
	.globl i
	.data
	.align 4
	.type i, @object
	.size i, 4
i:
	.long 2
	.globl v
	.data
	.align 4
	.type v, @object
	.size v, 40
v:
	.long 0
	.long 97
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.globl mat
	.data
	.align 4
	.type mat, @object
	.size mat, 40
mat:
	.globl f
	.data
	.align 4
	.type f, @object
	.size f, 4
f:
	.long 10
	.globl c
	.data
	.align 4
	.type c, @object
	.size c, 4
c:
	.long 120
	.globl x
	.data
	.align 4
	.type x, @object
	.size x, 4
x:
	.long 65
	.text
	.globl main
	.type main, @function
main:
	.cfi_startproc
	pushq %rbp
	movq %rsp, %rbp
	movl $7, %eax
	movl %eax, a(%rip)
	movl a(%rip), %eax
	movl $90, %edx
	cltq
	movl %edx, v(,%rax,4)
	.comm __temp0, 4, 4
	movl a(%rip), %eax
	cltq
	movl v(,%rax,4), %eax
	movl %eax, __temp0(%rip)
	movl __temp0(%rip), %esi
	movl $.LC0, %edi
	movl $0, %eax
	call printf
__label0:
	.comm __temp1, 4, 4
	movl a(%rip), %eax
	cmp $10, %eax
	jl _fstlc0
	movl $0, __temp1(%rip)
	jmp _sndlc0
_fstlc0:
	movl $1, __temp1(%rip)
_sndlc0:
	cmpl $0, __temp1(%rip)
	je __label1
	movl a(%rip), %edi
	movl $1, %esi
	call incn
	.comm __temp2, 4, 4
	movl %eax, __temp2(%rip)
	movl __temp2(%rip), %eax
	movl %eax, a(%rip)
	jmp __label0
__label1:
	movl %eax, %esi
	movl $.LC1, %edi
	movl $0, %eax
	call printf
	movl a(%rip), %esi
	movl $.LC0, %edi
	movl $0, %eax
	call printf
	movl %eax, %esi
	movl $.LC2, %edi
	movl $0, %eax
	call printf
	.comm __temp3, 4, 4
	movl a(%rip), %eax
	movl $5, %edx
	cmpl %eax, %edx
	sete %al
	movzbl %al, %eax
	movl %eax, __temp3(%rip)
	cmpl $0, __temp3(%rip)
	je __label2
	movl %eax, %esi
	movl $.LC3, %edi
	movl $0, %eax
	call printf
__label2:
	.comm __temp4, 4, 4
	movl a(%rip), %eax
	movl $11, %edx
	cmpl %eax, %edx
	sete %al
	movzbl %al, %eax
	movl %eax, __temp4(%rip)
	.comm __temp5, 4, 4
	movl a(%rip), %eax
	movl $17, %edx
	cmpl %eax, %edx
	sete %al
	movzbl %al, %eax
	movl %eax, __temp5(%rip)
	.comm __temp6, 4, 4
	cmpl $0, __temp4(%rip)
	jne .ORTRUE1
	cmpl $0, __temp5(%rip)
	jne .ORTRUE1
	movl $0, %eax
	jmp .UPDATEVALUE1
.ORTRUE1:
	movl $1, %eax
.UPDATEVALUE1:
	movl %eax, __temp6(%rip)
	cmpl $0, __temp6(%rip)
	je __label3
	movl %eax, %esi
	movl $.LC4, %edi
	movl $0, %eax
	call printf
__label3:
	.comm __temp7, 4, 4
	movl a(%rip), %eax
	movl $10, %edx
	cmpl %eax, %edx
	sete %al
	movzbl %al, %eax
	movl %eax, __temp7(%rip)
	cmpl $0, __temp7(%rip)
	je __label4
	movl %eax, %esi
	movl $.LC5, %edi
	movl $0, %eax
	call printf
__label4:
	.comm __temp8, 4, 4
	movl a(%rip), %eax
	movl $11, %edx
	cmpl %eax, %edx
	sete %al
	movzbl %al, %eax
	movl %eax, __temp8(%rip)
	cmpl $0, __temp8(%rip)
	je __label5
	jmp __label6
__label5:
	movl %eax, %esi
	movl $.LC6, %edi
	movl $0, %eax
	call printf
__label6:
	popq %rbp
	ret
	.cfi_endproc
	.globl incn
	.type incn, @function
incn:
	.cfi_startproc
	pushq %rbp
	movq %rsp, %rbp
	.comm xa, 4, 4
	movl %edi, xa(%rip)
	.comm n, 4, 4
	movl %esi, n(%rip)
	.comm __temp9, 4, 4
	movl xa(%rip), %eax
	addl n(%rip), %eax
	movl %eax, __temp9(%rip)
	movl __temp9(%rip), %eax
	popq %rbp
	ret
	.cfi_endproc
.LC0:
	.string "%d\n"
.LC1:
	.string "Incrementado algumas vezes fica "
.LC2:
	.string "\n"
.LC3:
	.string "Parou no meio\n"
.LC4:
	.string "Var a ficou 11 ou 17\n"
.LC5:
	.string "Pelo if then var a ficou 10\n"
.LC6:
	.string "Pelo if then else var a ficou 10\n"
