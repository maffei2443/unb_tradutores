.table
	int mi[6] = {0, 1, 2, 3, 4, 5 }
.code

show:
	mov $0, #0
// NOT MATRIX PARAM param

	print $0
	println ' '
	return 0
foo:
// >>>>> add (0x55ec03fd3220) id, tag: x, param

	mov $0, #0
// NOT MATRIX PARAM param

	mov $1, #1
	mov $2, #2
	mov $3, #3
///* ?????//*/
// global matrix
	mov $4, &mi
	mul $5, 1, 3
	add $5, $5, 1
	mov $5, $4[$5]
///* -----//*/
// $4[$5]
// scalar on check_type_and_convert_on_lr_attr
// mat(int)
///* ahhhhh droga!//*/
	mov $4[$5], 123
///* ?????//*/
// global matrix
	mov $6, &mi
	mul $7, 1, 3
	add $7, $7, 1
	mov $7, $6[$7]
///* -----//*/
// $6[$7]
	return $7
	return 0
main:
// [++++Semantico++++] Argumentos de foo corretos

	param 47
	mov $1, &mi
	param $1
// empilhar dimensoes
	param 2
	param 3
// imensoes empilhadas
	call foo, 4
	pop $2
	mov $0, $2
// [++++Semantico++++] Argumentos de show corretos

	param $0
	call show, 1
	pop $3
	jump __yh42340xsAyb8
__yh42340xsAyb8:
	nop
///* -------TAC'S END---------//*/
