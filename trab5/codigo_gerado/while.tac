.code
main:
	mov $0, 0
__newWhile0:
///* lvalue type : int//*/
	slt $2, $0, 10
	brz __endWhile0, $2
///* lvalue type : int//*/
	print $0
	print ' '
	print '-'
	print ' '
__newFlow0:
///* lvalue type : int//*/
	mod $3, $0, 2
	brz __afterIfBlock0, $3
	println 'I'
	jump __endFlow0
__afterIfBlock0:
	println 'P'
__afterElseBlock0:
// hfasdfhakjf

__endFlow0:
///* lvalue type : int//*/
///* lvalue type : int//*/
	add $4, $0, 1
// scalar on check_type_and_convert_on_lr_attr
	mov $0, $4
	mov $0, $4
	jump __newWhile0
__endWhile0:
	jump __yh42340xsAyb8
__yh42340xsAyb8:
	nop
///* -------TAC'S END---------//*/
