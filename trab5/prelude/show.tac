.table
  float v[4] = {1.4, 2.5, 7.8, 9.87}
.code


// #0: &
// #1: qtd
show_line:
  mov $0, 0
again:
  mov $1, #0[$0]
  print $1
  print ' '
  add $0, $0, 1
  mov $2, $0
  sub $2, $2, #1
  brnz again, $2
  println ' '
  return #0 
// END 

// #0: &
// #1: qtd
// #2: escalar
__mulScalarMat:
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

main:
  mov $0, &v
  // param $0
  // param 4
  // call passaConvertendoF2I, 2

  param $0
  param 4
  call show_line, 2
  print 'a'
  print 's'
  print ' '
  print 'm'
  print 'a'
  print 't'
  println ':'
  param $0
  param 2
  param 2
  call showMat_ij, 3

  param $0
  param 4
  param 2.0
  call __mulScalarMat, 3
  pop $4

  println 

  param $4
  param 2
  param 2
  call showMat_ij, 3


end:
  nop
