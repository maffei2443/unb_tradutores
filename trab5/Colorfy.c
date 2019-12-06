#include "Colorfy.h"
extern FILE* arquivo_saida;
void Reset(){
  if(!arquivo_saida)
    fprintf(stdout, "\033[0m");
}
void Red(){
  if(!arquivo_saida)
    fprintf(stdout, "\033[0;31m");
}
void BoldRed(){
  if(!arquivo_saida)
    fprintf(stdout, "\033[1;31m");
}
void Green(){
  if(!arquivo_saida)
    fprintf(stdout, "\033[0;32m");
}
void BoldGreen(){
  if(!arquivo_saida)
    fprintf(stdout, "\033[1;32m");
}
void Yellow(){
  if(!arquivo_saida)
    fprintf(stdout, "\033[0;33m");
}
void BoldYellow(){
  if(!arquivo_saida)
    fprintf(stdout, "\033[01;33m");
}
void Blue(){
  if(!arquivo_saida)
    fprintf(stdout, "\033[0;34m");
}
void BoldBlue(){
  if(!arquivo_saida)
    fprintf(stdout, "\033[1;34m");
}
void Magenta(){
  if(!arquivo_saida)
    fprintf(stdout, "\033[0;35m");
}
void BoldMagenta(){
  if(!arquivo_saida)
    fprintf(stdout, "\033[1;35m");
}
void Cyan(){
  if(!arquivo_saida)
    fprintf(stdout, "\033[0;36m");
}
void BoldCyan(){
  if(!arquivo_saida)
    fprintf(stdout, "\033[1;36m");
}

void Gray() {
  if(!arquivo_saida)
    fprintf(stdout, "\033[0;37m");
}
void BoldGray() {
  if(!arquivo_saida)
    fprintf(stdout, "\033[1;37m");
}