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

// ########### TESTADO
// #0: size_i
// #1: size_k
// #2: size_j
// #3: &1
// #4: &2
__mulMatInt_ikj:
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


// #0 : dimensao i
// #1 : potencia
// #2 : referencia p/ matriz
__matPow_ijp:
  param #0
  call __identidade, 1
  pop $0      // cria matriz identidade a ser usada na exponenciacao rapida

  mov $1, #1   // para ir diminuindo a potencia

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
      
      param #0
      param #0
      param #0
      param $0
      param $2
      
      call __mulMatInt_ikj, 5
      pop $4

      param $4
      param $0
      param $15
      call __copyN, 3

      // memf $4

    __even_power:
      div $1, $1, 2

      param #0
      param #0
      param #0
      param $2
      param $2
      call __mulMatInt_ikj, 5
      pop $3

      // memf $2
      mov $2, $3
      jump __quit_if_zero


    __quit_if_zero:
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
  call showMat_ij, 3

  param 3
  param 3
  param $0
  call __matPow_ijp, 3

