.table
.code

main:
	mov $1, 0
	print $1
	println ' '
	scani $1
__newFlow0:
	brz __afterIfBlock0, $1
	print $1
	jump __endFlow0
__afterIfBlock0:
	mul $2, $1, $1
	mov $1, $2
	print $1
__afterElseBlock0:
// hfasdfhakjf

__endFlow0:
	mod $3, 4, $1
	sub $5, $1, $4
	mov $1, $5
__newFlow1:
	brz __afterIfBlock1, $1
__newFlow2:
	brz __afterIfBlock2, $1
	print 'a'
	print ' '
	print 'x'
	print '2'
	print ' '
	print '='
	print ' '
	print $1
	jump __endFlow2
__afterIfBlock2:
__afterElseBlock2:
// hfasdfhakjf

__endFlow2:
	jump __endFlow1
__afterIfBlock1:
	add $6, $1, 44
	mov $1, $6
	print $1
__afterElseBlock1:
// hfasdfhakjf

__endFlow1:
	jump __yh42340xsAyb8
__yh42340xsAyb8:
	nop
///* -------TAC'S END---------//*/
