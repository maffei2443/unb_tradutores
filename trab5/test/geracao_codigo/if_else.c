// Testa comando de atribuicao +
// if +
// tamanho alocado em caso de atribuicao entre matrizes COM CAST

int main() {
  int a;
  float f;
  mat int mi[5][7];
  mat float mf[2][3];
  a = 1;
  f = 8.9;
  // mi = mf;
  mf = mi;
  if ( a ) {
  	a = a + a;
  	if (a) {
  		a = a + 7;
  	}
  	else {
  		a = a + 19;
  	}
  } 
  else {

  }
}