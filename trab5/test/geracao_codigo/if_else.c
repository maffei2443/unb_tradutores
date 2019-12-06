// Testa comando de atribuicao +
// if +
// tamanho alocado em caso de atribuicao entre matrizes COM CAST

int main() {
  int a = 0;
  PRINT(a);
  PRINT('');
  IREAD(a);
  if ( a ) {
    PRINT( a );
  } else {
  	a = a  * a;
    PRINT(a);
  }
  a = a - 4 % a;
  if( a ){
  	if( a ){
      PRINT('a');
      PRINT(' ');
      PRINT('x');
      PRINT('2');
      PRINT(' ');
      PRINT('=');
      PRINT(' ');
      PRINT( a );
      PRINT('');
    } else ;
  } else {
    a = a + 44;
    PRINT(a);
  }
}