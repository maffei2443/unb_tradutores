.table
	int m1[4] = { 1, 2, 3, 4 } // matriz
	int m2[4] = { 1, 2, 3, 4 } // matriz
.code

// PRELUDIO

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



// #0 - src
// #1 - dest
// #2 - qtd
__copyN:
  mov $0, #2
  sub $0, $0, 1
__copyN_loop:
  mov $1, #0[$0]
  mov #1[$0], $1
  brz __copyN_end, $0
  sub $0, $0, 1
  jump __copyN_loop
__copyN_end:
  return


// #0: &
// #1: size_i
// #2: size_j
showMat_ij:
  mov $0, 0   // iterador i
  mov $5, 0   // iterador j
pre_again_ij:
  mul $7, $5, #1
  // mostrou n-esima linha. Agora, voltar i para zero
  mov $0, 0
again_ij:
  add $8, $0, $7
  mov $1, #0[$8]
  print $1
  print ' '
  add $0, $0, 1
  mov $2, $0
  sub $2, $2, #1
  brnz again_ij, $2
  println ' '
  // e incrementar $5 em 1 unidade
  add $5, $5, 1
  // printar novamente SSE $5 < j => $5 != j
  sub $6, $5, #2
  brnz pre_again_ij, $6
  return #0 


//

// PRELUDIO

main:
	mema $1, 4
	mov $3, &m1
	mov $4, &m2
	param $3
	param 4
	param $4
	param 4
	call __addMat, 4
	pop $5
	mov $7, &m2
	mov $8, &m1
	param $7
	param 4
	param $8
	param 4
	call __subMat, 4
	pop $9
	param $5
	param 4
	param $9
	param 4
	call __addMat, 4
	pop $11
	param $11    // src =2
	param $1    // dest
	param 4    // qtd 
	call __copyN, 3
	param $1
	param 2
	param 2
	call showMat_ij, 3
	jump __yh42340xsAyb8
__yh42340xsAyb8:
	nop
