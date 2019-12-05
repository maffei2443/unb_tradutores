#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void show_mat(int m [][3], int i, int j) {
  for(int a = 0; a < i; a++) {
    printf("\t");
    for(int b = 0; b < j; b++)
      printf("%d ", m[a][b]);
    printf("\n");
  }
}

int main() {
	/* mat  */int m[2][2] = {{1,2}, {3, 4}};
	/* mat  */int n[2][2] = {{1,2}, {3, 4}};
	int lm = 3;
	/* mat  */int three[3][3] = {{1,2, 3}, {4, 5, 6}, {7, 8, 9}};
	/* mat  */int three_res[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
	/* mat  */int res[2][2] = {{0, 0}, {0, 0}};

	int i;  int j;  int k;
	i = 0;
	while(i < lm) {
		k = 0;
		while (k < lm) {
			j = 0;
			while (j < lm) {
				three_res[i][k] = three_res[i][k] + three[i][j] * three[j][k];
				j = j + 1;
			}
			k = k + 1;
		}
		i = i + 1;
	}
  
  printf("Correct: \n");
  show_mat(three_res, lm, lm);
  // memset(res, 0, 4 * sizeof(int));

 //  i = 1;
	// do {
	// 	k = 1;
	// 	do {
	// 		j = 1;
	// 		do {
	// 			res[i][k] = res[i][k] + m[i][j] * n[j][k];
	// 			j = j - 1;
	// 		} while(j >= 0);
 //      // printf("%d ", res[i][k]);
	// 		k = k - 1;
	// 	} while(k >= 0);
	// 	i = i - 1;
 //    // printf("\n");
	// } while (i >= 0);

  printf("New ???: \n");
  // show_mat(res, 2, 2);
  // memset(res, 0, 4 * sizeof(int));
  
}
