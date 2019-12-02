.table
.code

// Espera receber 4 parametros:
// - endereço simbólico de mat1
// - quantidade de elementos de mat1
// - endereco simbolico de mat2
// - quantidade de elementos de mat2 (debug)

addMat:
	mov $0, #0
	mov $1, #1
	mov $2, #2
	mov $99, #3
	mema $10, $1
	// setar todas as posicoes de memoria para inteiro
	mov $3, $1	// iterador
	sub $3, $3, 1
start:			
	mov $4, $0[$3]
	mov $5, $2[$3]
	add $6, $4, $5

	mov $10[$3], $6
	println $6
	brz end, $3 
	sub $3, $3, 1				
	jump start
end:
	return $2
		// calculando indice de acesso
main:
	mema $0, 2
	mema $1, 2
	
	param $0
	param 2
	param $1
	param 2

	mov $0[0], 2
	mov $0[1], 7

	mov $1[0], 5
	mov $1[1], -17
	
	call addMat, 4

