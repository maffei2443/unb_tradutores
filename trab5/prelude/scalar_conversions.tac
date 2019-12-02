.table
.code

int2float:
  mov $0, #0
  inttofl $0, $0
  return $0


float2int:
  mov $0, #0
  fltoint $0, $0
  return $0

main:
  mov $0, 15
  println $0
  
  param $0
  call int2float, 1
  pop $0
  println $0
