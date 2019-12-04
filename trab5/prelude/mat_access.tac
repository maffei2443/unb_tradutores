.table
  int m[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8}
  int v = 7
.code

// access_ij:
//   add 

// Considerando m(2,4)
main:
  mov $1, 2   // qtd linhas
  mov $2, 4   // qtd colunas
  // acessar posicao m[1][3] == 7
  
  mov $3, &m  // base; global
  mul $4, 1, $2  // i1 * n2
  add $4, $4 ,3   //i1 * n2 + i2
  mov $5, $3[$4]
  
  println $5
  println m
  println $3
  println v
  
