mat<int> m 3 3 = [1 2 3,
				4 5 6,
				7 8 9];
int a[5] = {1 2 33 4 57};

AHEAD fn foo (void) -> int;

fn foo(void) -> int {
	return 1+3;
}

fn showMat(mat<int> m) -> int {
	PRINT(m);
}

int a;
a = 23;
a = a + 12;	// TODO: IMPLEMENTAR

fn main(void) -> int {
	char c;
	READ(c);
	PRINT(c);
	int v[5];
	v = {0 3 33 12 4};
	v[0] = 21;
	float f;
	f = 1.89;
	while(0) {
		PRINT('N'); PRINT('E');
		PRINT('V'); PRINT('R');
		PRINT('R');
	}
	showMat(m 3 3);
	return 0;
}