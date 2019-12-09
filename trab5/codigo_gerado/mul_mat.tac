.table
	int mi[4] = { 1, 2, 3, 4 } // matriz

.code

// #0: &
// #1: size_i
// #2: size_j
__showMat_ij:
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
// #1: qtd
// #2: escalar
__mulScalarMat_ikj:
  mov $0, 0
  mema $5, #1
__again_mulScalarMat:
  mov $1, #0[$0]    // recuperar valor a ser multiplicado
  mul $1, $1, #2    // multiplicar valor
  mov $5[$0], $1    // salvar valor mutiplicado

  add $0, $0, 1
  mov $2, $0
  sub $2, $2, #1
  brnz __again_mulScalarMat, $2
  return $5
// END 


main:
	mema $0, 4
///* lvalue type : mat(int)//*/
///* lvalue type : mat(int)//*/
	mov $2, &mi
	param $2
	param 4
	param 2
	call __mulScalarMat_ikj, 3
	pop $3
///* */
	param $3    // src =2
	param $0    // dest
// Tamanhos: -1, -1
	param 1    // qtd 
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
