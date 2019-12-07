.table
.code

// Espera receber 4 parametros:
// - endereço simbólico de mat1
// - quantidade de elementos de mat1
// - endereco simbolico de mat2
// - quantidade de elementos de mat2 (debug)
// Retorna endereco da nova mtriz contendo resultado da operacao
__addMat:
	mov $0, #0
	mov $1, #1
	mov $2, #2
	mov $99, #3
	mema $10, $1
	// setar todas as posicoes de memoria para inteiro
	mov $3, $1	// iterador
	sub $3, $3, 1
__addMat_loop:			
	mov $4, $0[$3]
	mov $5, $2[$3]
	add $6, $4, $5

	mov $10[$3], $6
	println $6
	brz __endAddMat, $3 
	sub $3, $3, 1				
	jump __addMat_loop
__endAddMat:
	return $10
		// calculando indice de acesso

//

// Espera receber 4 parametros:
// - endereço simbólico de mat1
// - quantidade de elementos de mat1
// - endereco simbolico de mat2
// - quantidade de elementos de mat2 (debug)
__subMat:
	mov $0, #0
	mov $1, #1
	mov $2, #2
	mov $99, #3
	mema $10, $1
	mov $3, $1	// iterador
	sub $3, $3, 1
__subStart:			
	mov $4, $0[$3]
	mov $5, $2[$3]
	sub $6, $4, $5

	mov $10[$3], $6
	println $6
	brz __subEnd, $3 
	sub $3, $3, 1				
	__jump subStart
__subEnd:
	return $10
		// calculando indice de acesso

//

// 
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
	
	call __addMat, 4

