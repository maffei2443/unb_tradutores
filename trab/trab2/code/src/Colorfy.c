#include "Colorfy.h"

void Reset(){
  fprintf(stdout, "\033[0m");
}
void Red(){
  fprintf(stdout, "\033[0;31m");
}
void BoldRed(){
  fprintf(stdout, "\033[1;31m");
}
void Green(){
  fprintf(stdout, "\033[0;32m");
}
void BoldGreen(){
  fprintf(stdout, "\033[1;32m");
}
void Yellow(){
  fprintf(stdout, "\033[0;33m");
}
void BoldYellow(){
  fprintf(stdout, "\033[01;33m");
}
void Blue(){
  fprintf(stdout, "\033[0;34m");
}
void BoldBlue(){
  fprintf(stdout, "\033[1;34m");
}
void Magenta(){
  fprintf(stdout, "\033[0;35m");
}
void BoldMagenta(){
  fprintf(stdout, "\033[1;35m");
}
void Cyan(){
  fprintf(stdout, "\033[0;36m");
}
void BoldCyan(){
  fprintf(stdout, "\033[1;36m");
}

void Gray() {
  fprintf(stdout, "\033[0;37m");
}
void BoldGray() {
  fprintf(stdout, "\033[1;37m");
}