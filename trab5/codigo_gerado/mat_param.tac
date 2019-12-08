.table

	int mgg[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 } // matriz
.code
show:
	mov $0, #0
// NOT MATRIX PARAM param

	print $0
	println ' '
	return 0
foo:
	mov $0, #0
	mov $1, #1
	mov $2, #2
	mov $7, $0
	mul $8, 2, $2
	add $8, $8, 1
// desparafusa
	mov $9, $7[$8]
// scalar on check_type_and_convert_on_lr_attr
// mat(int)
///* ahhhhh droga!//*/
	mov $7[$8], 4
	mov $10, $0
	mul $11, 2, $2
	add $11, $11, 1
// desparafusa
	mov $12, $10[$11]
// scalar on check_type_and_convert_on_lr_attr
	mov $6, $12
// [++++Semantico++++] Argumentos de show corretos

	param $6
	call show, 1
	pop $13
	mov $14, $0
	mul $15, 2, $2
	add $15, $15, 1
// desparafusa
	mov $16, $14[$15]
	mov $17, $0
	mul $18, 2, $2
	add $18, $18, 1
// desparafusa
	mov $19, $17[$18]
	mul $20, $19, 2
// scalar on check_type_and_convert_on_lr_attr
// mat(int)
///* ahhhhh droga!//*/
	mov $14[$15], $20
	mov $21, $0
	mul $22, 2, $2
	add $22, $22, 1
// desparafusa
	mov $23, $21[$22]
	return $23
	return 0
main:
// [++++Semantico++++] Argumentos de foo corretos

	mov $1, &mgg
	param $1
// empilhar dimensoes
	param 3
	param 3
// imensoes empilhadas
	call foo, 3
	pop $2
	mov $0, $2
// [++++Semantico++++] Argumentos de show corretos

	param $0
	call show, 1
	pop $3
// scalar on check_type_and_convert_on_lr_attr
	mov $0, 0
	mov $4, &mgg
	mul $5, 2, 3
	add $5, $5, 1
// desparafusa
	mov $6, $4[$5]
// scalar on check_type_and_convert_on_lr_attr
	mov $0, $6
// [++++Semantico++++] Argumentos de show corretos

	param $0
	call show, 1
	pop $7
	jump __yh42340xsAyb8
__yh42340xsAyb8:
	nop
///* -------TAC'S END---------//*/
