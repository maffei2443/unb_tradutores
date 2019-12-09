.table

.code
main:
	mov $0, 8
///* lvalue type : int//*/
	inttofl $2, $0
	mov $1, $2
	println 'I'
///* lvalue type : int//*/
	println $0
	println 'F'
///* lvalue type : float//*/
	println $1
	jump __yh42340xsAyb8
__yh42340xsAyb8:
	nop
///* -------TAC'S END---------//*/
