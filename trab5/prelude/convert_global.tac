.table
  float v[4] = {1.4, 2.5, 7.8, 9.87}
.code

// (de tras para frente)
passaConvertendoF2I: 
  mov $0, #1  // iterador
lup:
  sub $0, $0, 1
  mov $2, #0[$0]
  println $2
  fltoint $2, $2
  print 'a'
  print 's'
  print ' '
  print 'i'
  print 'n'
  print 't'
  print ':'
  print ' '
  println $2
  brnz lup, $0
  return
// 

// ps: nao compensa fazer funcao pra isso pos soh pra empilhar gasta + linhas
access_ij:
  mov $3, &v  // base; global
  mul $4, 1, $2  // i1 * n2
  add $4, $4 ,3   //i1 * n2 + i2
  mov $5, $3[$4]
  return $5
// END
  

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
  call __showMat_ij, 3


end:
  nop
