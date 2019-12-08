mat int mi[2][3] = {0, 1, 2, 3, 4, 5};
int show(int x) {
	PRINT(x);
	PRINT('');
}

int foo(int x, mat int mm) {
	// x = mm[1][1];
	show(x);
	x = mi[1][1];
	show(x);
	return x;
}

int main() {
	// mat int mi[10][10];
	// int m = mi[1][2];
	int g = foo( 47 , mi(2)(3));
	show(g);
}