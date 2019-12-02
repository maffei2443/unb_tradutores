.table
.code
// Cohdigo para converter n-simbolos de float -> int
matToIntCast:
	// pop $1
	mov $1, #1		// tamanho da matriz
	mema $2, $1		// aloca matriz de mesmo tamanho
	mov $3, $1		// iterador
	sub $3, $3, 1	// se tem tamanho n, comece pela posicao n-1
	// setar todas as posicoes de memoria para inteiro
start:			
	mov $4, #0[$3]	
	println $4				
	fltoint $5, $4	
	mov #0[$3], $5
	brz end, $3 
	sub $3, $3, 1				
	jump start
end:
	return $2
		// calculando indice de acesso
main:
	mema $0, 10
	mov $0[0], 1.11
	mov $0[1], 5.4
	param $0
	param 2
	call matToIntCast, 2

