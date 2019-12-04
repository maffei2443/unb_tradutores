int main() {
	int a = 10;
	int b = 19;
	while(a) {
		a = a - 1;
		while (a) {
			a = a - 1;
		}
	}
	b = b * 99;
	while( b ) {
		b = b - 1;
	}
}