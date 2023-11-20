.data
primos:	.word 1, 3, 5, 7, 11, 13, 17, 19
size:	.word 8
msg:	.asciiz "Os oito primeiros numeros primos sao : "
space:	.ascii " "

.text
	la $t0, primos
	la $t1, size
	lw $t1, 0($t1)
	addi $v0, $zero, 4
	la $a0, msg
	syscall
	
loop:	beq $t1, $zero, exit
	addi $v0, $zero, 1
	lw $a0, 0($t0)
	syscall
	addi $v0, $zero, 4
	la $a0, space
	syscall
	addi $t0, $t0, 4
	addi $t1, $t1, -1
	j loop
exit:	addi $v0, $zero, 10
	syscall