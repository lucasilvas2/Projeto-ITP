#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define carct 100


typedef struct{
    int r, g, b;
}pixel;

typedef struct{
  char formato_img[3];
  int altura, coluna, color_max;
  char acao[10];
  int x1, x2, y1, y2;
  char nome_imagem[carct];

}img;
typedef struct{
  int x_c, y_c, r;
}circ;

void imag();
void clr();
void i_cor();
void preencher();
void desenhar_linha();
void poligono();
void circle();
void pintapixel();
void save();



#endif // FUNC_H_INCLUDED
