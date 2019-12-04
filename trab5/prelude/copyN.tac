.table
  int src[3] = {1, 2, 3}
  int dest[3] = {0, 0, 0}
.code

// #0 - src
// #1 - dest
// #2 - qtd
copyN:
  mov $0, #2
  sub $0, $0, 1
copyN_loop:
  mov $1, #0[$0]
  mov #1[$0], $1
  brz copyN_end, $0
  sub $0, $0, 1
  jump copyN_loop
copyN_end:
  return

main:
  mov $1, &src
  param $1
  mov $1, &dest
  param $1
  param 3
  call copyN, 3
  mov $0, $1[0]
  println $0
  mov $0, $1[1]
  println $0
  mov $0, $1[2]
  println $0
