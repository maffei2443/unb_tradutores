// TESTADO
// NAO MEXER
int main() {
	int a;
	IREAD(a);
	if( a < 4 ) {
		PRINT('o');
		PRINT('l');
		PRINT('a');
		PRINT('');
	} else {
		PRINT('a');
		PRINT(' ');
		PRINT('=');
		PRINT(' ');
		PRINT(a);
		PRINT('');
	} /*if (a > 5) {
		a = a + a;
		PRINT(a);
	}
	else {
		PRINT('a');
		PRINT(' ');
		PRINT('=');
		PRINT(' ');
		PRINT(a);
		PRINT('');
	}*/
}