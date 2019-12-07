mat int m1[2][2] = {1, 2, 3, 4};
mat int m2[2][2] = {1, 2, 3, 4};

int main() {
  mat int m3[2][2];
  m3 = m1 + m2 + (m2 - m1);
  PRINT(m3);
}