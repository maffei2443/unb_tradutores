.table
	int m1[4] = { 1, 2, 3, 4 } // matriz
	int m2[4] = { 1, 2, 3, 4 } // matriz
.code

// 
__mulMatMat_ikj:
  mul $0, #0, #1
  mema $20, $0  // new_mat de tramanho  sie_i * size_k

  mov $0, 0                   // i = 0
  while_i:                      // while (i < #2) {
    mul $4, $0, #1              //  [i][?]
    mov $1, 0                   //  k = 0
    while_k:                      //  while (k < #4) {
      mov $2, 0   // iterador     //    j = 0
      add $5, $4, $1              // offset de [i][k]
      mov $20[$5], 0              // inicializa elemento com zero
      while_j:                      //    while (j < #3) {
        mov $7, $20[$5]             // mat_temp[i][k]

        add $8, $4, $2                // [i][j]
        
        mul $9, $2, #1                // [j][?] (dim. comum eh size_k [#1])
        add $9, $9, $1                // [j][k]
        
        mov $10, #3[$8]               // left[i][j]
        mov $11, #4[$9]               // right[j][k]

        mul $11, $10, $11             // left[i][j] * right[j][k]

        add $11, $7, $11             //  mat_temp[i][k] + left[i][j] * right[j][k]

        mov $20[$5], $11              //  mat_temp[i][k] = mat_temp[i][k] + left[i][j] * right[j][k]

        add $2, $2, 1                 // j = j + 1
        sub $21, $2, #2 
        brnz while_j, $21             // if j - size_j == 0, entao sai pois terminou a matriz
      end_while_j:
        add $1, $1, 1                 // k = k + 1
        sub $21, $1, #1
        brnz while_k, $21             // if k - size_k == 0, entao sai pois terminou a matriz
    end_while_k:
      add $0, $0, 1
      sub $21, $0, #0         // se i == size_i, soh segue em frente e retorna
      brnz while_i, $21
  end_while_i:
    return $20    // referencia para memoria contendo a matriz resultadoo
// ########### TESTADO

//$$$$$$$$$$44

__showMat_ij:
  mov $0, 0   // iterador i
  mov $5, 0   // iterador j
__pre_again_ij:
  mul $7, $5, #1
  // mostrou n-esima linha. Agora, voltar i para zero
  mov $0, 0
__again_ij:
  add $8, $0, $7
  mov $1, #0[$8]
  print $1
  print ' '
  add $0, $0, 1
  mov $2, $0
  sub $2, $2, #1
  brnz __again_ij, $2
  println ' '
  // e incrementar $5 em 1 unidade
  add $5, $5, 1
  // printar novamente SSE $5 < j => $5 != j
  sub $6, $5, #2
  brnz __pre_again_ij, $6
  return #0 



// $$$$$$$$$$$


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
	jump __subStart
__subEnd:
	return $10
		// calculando indice de acesso
//

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


// PRELUDIO
main:
	mema $0, 4
///* lvalue type : mat(int)//*/
///* lvalue type : mat(int)//*/
///* lvalue type : mat(int)//*/
	mov $2, &m1
	mov $3, &m2
	param $2
	param 4
	param $3
	param 4
	call __addMat, 4
	pop $4
///* lvalue type : mat(int)//*/
///* lvalue type : mat(int)//*/
	mov $6, &m2
	mov $7, &m1
	param $6
	param 4
	param $7
	param 4
	call __subMat, 4
	pop $8
	param $4
	param 4
	param $8
	param 4
	call __addMat, 4
	pop $10
	param $10    // src =2
	param $0    // dest
// Tamanhos: 2, 2
	param 4    // qtd 
	call __copyN, 3
///* lvalue type : mat(int)//*/
///* lvalue type : mat(int)//*/
///* lvalue type : mat(int)//*/
// multiplicacao de matrizes
	param 2 // i
	param 2 // k
	param 2 // j
	param $0
	param $0
	call __mulMatMat_ikj, 5
	pop $11
// fim multiplicacao
	param $11    // src =2
	param $0    // dest
// Tamanhos: 2, 2
	param 4    // qtd 
	call __copyN, 3
///* lvalue type : mat(int)//*/
// 
	param $0
	param 2
	param 2
	call __showMat_ij, 3
// end showMat_ij
	jump __yh42340xsAyb8
__yh42340xsAyb8:
	nop
///* -------TAC'S END---------//*/
