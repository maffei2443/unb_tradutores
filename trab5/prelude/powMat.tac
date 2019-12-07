.table
  int id[3] = {1, 0, 0, 0, 1, 0, 0, 0, 1}
.code

// #0 : dimensao i
// #1 : potencia
// #2 : 
__matPow_ijp:
  // mov $
  return

// ################## TESTADO
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

// ################## TESTADO


// #0 : dimensao
__identidade:
  mul $0, #0, #0
  mema $99, $0
  // println $0
  mov $0, 0   // i = 0
  __identidadeWhile_i:
    mov $1, 0 // j = 0
    __identidadeWhile_j:
      mul $3, $0, #0  // i * #0
      add $3, $3, $1
      println $3
      // print '*'
      // println $3
      seq $4, $0, $1
      mov $99[$3], $4
      // println $4
      add $1, $1, 1       // j = j + 1
      seq $5, $1, #0      // temp = j == dimensao
      brz __identidadeWhile_j, $5
    add $0, $0, 1
    seq $5, $0, #0
    brz __identidadeWhile_i, $5
  return $99
main:
  param 3
  call __identidade, 1
  pop $0
  
  param $0
  param 3
  param 3
  call showMat_ij, 3
  
