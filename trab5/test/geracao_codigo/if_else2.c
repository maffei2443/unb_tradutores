int main() {
  int a = 1;
  if ( a ) {
    a = a + 1;
    a = a + 5;
  } else {
    if ( a ) {
      a = 5 + 3;
    } else {
      a = 0 + 1;
    }
  }
}