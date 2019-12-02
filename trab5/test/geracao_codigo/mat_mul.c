int main() {
	mat int m[3][3];
	mat int n[3][3];
	int i;
  int j;
  int k;
	i = 0;
	while(i < 3) {
		j = 0;
		while (j < 3) {
			k = 0;
			while (k < 3) {
				n[i][j] = n[i][j] + m[i][k] * m[k][j];
				k = k + 1;
			}
			j = j + 1;
		}
		i = i + 1;
	}
}
