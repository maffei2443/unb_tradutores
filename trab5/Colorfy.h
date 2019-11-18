#ifndef COLORFY_H
#define COLORFY_H

#pragma once
#include <stdio.h>
#define rfprintf(x, y, z) fprintf(x,y,z), Reset();
#define rprintf(x, y) fprintf(x,y), Reset();

void Reset();

void Red();
void BoldRed();
void Green();
void BoldGreen();
void Yellow();
void BoldYellow();
void Blue();
void BoldBlue();
void Magenta();
void BoldMagenta();
void Cyan();
void BoldCyan();
void Gray();
void BoldGray();
#endif