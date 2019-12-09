/* NAO FUNCIONA  */

.table
  int id[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1}
.code


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
// 



// #0 : dimensao i
// #1 : potencia
// #2 : referencia p/ matriz
__matPow_ijp:
  param #0
  call __identidade, 1
  pop $0      // cria matriz identidade a ser usada na exponenciacao rapida

  mov $1, #1   // para ir diminuindo a potencia
  mema $2, 9
  mul $15, #0, #0
  param #2
  param $2    // copia da mtriz original (p/ n tentar da free onde n deve)
  param $15
  call __copyN, 3

  __while_pow_not_zero:
    mod $3, $1, 2     // deixa o resto da div. por 2 em $3, pra ver se eh par
    brz __even_power, $3
    __odd_power:
      sub $1, $1, 1
      
      
      param $0
      param $4
      param $15
      call __copyN, 3

      // memf $4

    __even_power:
      div $1, $1, 2

      // memf $2
      mov $2, $3
      jump __quit_if_zero


    __quit_if_zero:
  return

// ################## TESTADO
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
      seq $4, $0, $1
      mov $99[$3], $4
      add $1, $1, 1       // j = j + 1
      seq $5, $1, #0      // temp = j == dimensao
      brz __identidadeWhile_j, $5
    add $0, $0, 1
    seq $5, $0, #0
    brz __identidadeWhile_i, $5
  return $99

// TESTADO, FUNCIONA


main:
  param 3
  call __identidade, 1
  pop $0
  
  param $0
  param 3
  param 3
  call __showMat_ij, 3

  mov $0[0], 2
  mov $0[1], 2
  mov $0[2], 2
  mov $0[3], 2
  mov $0[4], 2
  mov $0[5], 2

  param 3
  param 3
  param $0
  call __matPow_ijp, 3
  pop $4

  param $4
  param 3
  param 3
  call __showMat_ij, 3
