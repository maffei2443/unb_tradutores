.table
	int mi[6] = {0, 0, 0, 0, 0, 0 }
.code



foo:
	mov $0, #0
	mov $1, 1
	return $0
	return 0
main:
// [++++Semantico++++] Argumentos de foo corretos

	param 4
	call foo, 1
	pop $1
	mov $0, $1
	println $0
	jump __yh42340xsAyb8
__yh42340xsAyb8:
	nop
