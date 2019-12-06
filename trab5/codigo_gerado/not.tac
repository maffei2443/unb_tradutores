.table
.code

// digo_gerado/not.c 
main:
	add $2, 12, 20
	mov $1, $2
	not $3, 1
	print $3
__newFlow0:
	slt $5, 4, 3
	not $5, $5
	not $6, $5
	brz __afterIfBlock0, $6
	slt $8, 4, 3
	not $8, $8
	not $9, $8
	print $9
	jump __endFlow0
__afterIfBlock0:
__newFlow1:
	slt $11, 33, $1
	not $11, $11
	brz __afterIfBlock1, $11
	print 999
	jump __endFlow1
__afterIfBlock1:
__afterElseBlock1:
// hfasdfhakjf

__endFlow1:
__afterElseBlock0:
// hfasdfhakjf

__endFlow0:
	jump __yh42340xsAyb8
__yh42340xsAyb8:
	nop


///* -------TAC'S END---------//*/