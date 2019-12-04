#include <stdio.h>
int showMat(int *v, int i, int j) {
	for(int k = 0; k < i * j; k++) {
		printf("%d ", v[k]);
		if(k!=0 && k % j  == 0) printf("\n");
	}
}

int main() {
	int m[3][3];
	for(int i =0; i < 9; i++) ((int*)m) [i] = i+1;
	showMat((int*)m, 3, 3);
}