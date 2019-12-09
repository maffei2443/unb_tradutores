.table

.code
main:
	mov $0, 8
	mov $1, 9.800000
///* lvalue type : float//*/
///* lvalue type : int//*/
///* lvalue type : float//*/
	inttofl $3, $0
	add $2, $3, $1
// scalar on check_type_and_convert_on_lr_attr
	mov $1, $2
///* lvalue type : float//*/
	println $1
///* lvalue type : int//*/
	println $0
	jump __yh42340xsAyb8
__yh42340xsAyb8:
	nop
///* -------TAC'S END---------//*/
