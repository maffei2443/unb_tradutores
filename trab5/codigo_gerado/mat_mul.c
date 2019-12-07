mat int mi[2][2] = {1, 2, 3, 4};
mat int mv[2][2] = {1, 2, 3, 4};
int main() {
  mat int mg[2][2];
  mg = (mi @ mv) @ mi;
  // mg = mi @ mg;
  PRINT(mg);
}