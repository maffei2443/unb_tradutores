
.table

.code
main:
///* lvalue type : int//*/
	scani $0
__newFlow0:
	brz __afterIfBlock0, 0
	print 'G'
	jump __endFlow0
__afterIfBlock0:
///* lvalue type : int//*/
	sleq $2, $0, 0
	not $2, $2
	brz __afterIfBlock1, $2
	print 'A'
	print 'Q'
	print 'U'
	print 'I'
	println 
__newFlow1:
	brz __afterIfBlock2, 0
	println 
	jump __endFlow1
__afterIfBlock2:
	print 897
__afterElseBlock2:
// hfasdfhakjf

__endFlow1:
	jump __endFlow0
__afterIfBlock1:
	print 123456
__newFlow2:
	brz __afterIfBlock3, 1
	print 111
	jump __endFlow2
__afterIfBlock3:
	print 333
__afterElseBlock3:
// hfasdfhakjf

__endFlow2:
__afterElseBlock1:
// hfasdfhakjf

__afterElseBlock0:
// hfasdfhakjf

__endFlow0:
	print 'e'
	print 'n'
	print 'd'
	println 
	jump __yh42340xsAyb8
__yh42340xsAyb8:
	nop
///* -------TAC'S END---------//*/
