int main() {
  int i = 0;
  while(i < 10) {
    print(i);
    print(' ');
    print('-');
    print(' ');
    if(i % 2) {
      show('I');
    } else {
      show('P');
    }
    i = i + 1;
  }
}