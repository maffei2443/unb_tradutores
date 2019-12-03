#include "Common.h"

int temp = -1;
int old_temp;
int MAX_TEMP = 1022;
unsigned long critical_error = 0;
int temp_next() {
  ++temp;
  if(temp > MAX_TEMP) {
    printf("[GeracaoCodigo] Erro: muitos temporarios utilizados!\n");
  }
  return temp;
}

void new_context() {
  old_temp = temp;
  temp = 0;
}
void old_context() {
  temp = old_temp;
}
