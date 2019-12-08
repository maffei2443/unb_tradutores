mat int mgg[3][3] = {
	1, 2, 3,
	4, 5, 6, 
	7, 8, 9
};

int show(int x) {
	PRINT(x);
	PRINT('');
}

int foo(mat int mm) {
	// int x = mm[2][1];
	// show(x);
	// mm[2][1] = 2 * mm[2][1];
	int t;
	mm[2][1] = 4;
	t = mm[2][1];
	show(t);

	mm[2][1] = mm[2][1] * 2;
	return mm[2][1];
}

int main() {
	// mat int mi[10][10];
	// int local = mgg[2][1];
	// int global = mi[10][10];
	int c = foo(mgg(3)(3));
	show(c);
	c = 0;
	c = mgg[2][1];
	show(c);	
}