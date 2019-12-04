#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

int main(){
  int i, j, pontos;
  img imagem;
  img *ptrimg = &imagem;
  pixel **matriz_img;
  pixel clear, color;
  pixel *ptrclear = &clear, *ptrcolor = &color;
  circ circulo;
  pixel ver;


  FILE *arquivo_org = fopen("testando.txt","r");

  if(arquivo_org == NULL){
    printf("Erro\n");
    exit(0);
  }
  else{
    while(fscanf(arquivo_org, "%s", imagem.acao) != EOF){
    printf("%s\n", imagem.acao);

    if(strcmp(imagem.acao, "image") == 0){
      imag(ptrimg, arquivo_org);

      matriz_img = (pixel **) calloc(imagem.altura, sizeof(pixel*));
      for(i = 0; i < imagem.altura; i++){
        matriz_img[i] = (pixel *) calloc(imagem.coluna, sizeof(pixel));
      }
    }
    else if (strcmp(imagem.acao, "clear") == 0){
      clr(imagem,clear ,ptrclear, arquivo_org, matriz_img);
    }
    else if (strcmp(imagem.acao, "color") == 0){
      i_cor(imagem, color, ptrcolor, arquivo_org, matriz_img);
    }
    else if(strcmp(imagem.acao, "line") == 0){
      fscanf(arquivo_org, "%d", &imagem.x1);
      fscanf(arquivo_org, "%d", &imagem.y1);
      fscanf(arquivo_org, "%d", &imagem.x2);
      fscanf(arquivo_org, "%d", &imagem.y2);
                
      desenhar_linha(imagem.x1, imagem.y1, imagem.x2,imagem.y2, matriz_img, color);
    }
    else if(strcmp(imagem.acao, "polygon") == 0){

      fscanf(arquivo_org, "%d", &pontos);
      int vetor_x [pontos], vetor_y[pontos];

      for(i = 0; i < pontos; i++){
        fscanf(arquivo_org, "%d", &vetor_x[i]);
        fscanf(arquivo_org, "%d", &vetor_y[i]);
      }
      vetor_x[pontos] = vetor_x[0];
      vetor_y[pontos] = vetor_y[0];
       
      poligono(vetor_x, vetor_y, imagem ,matriz_img, color, pontos);
    }
    else if(strcmp(imagem.acao, "circle") == 0){
      fscanf(arquivo_org, "%d", &circulo.x_c);
      fscanf(arquivo_org, "%d", &circulo.y_c);
      fscanf(arquivo_org, "%d", &circulo.r);
              
      circle(circulo.x_c, circulo.y_c, circulo.r, matriz_img, color);

    }
    else if(strcmp(imagem.acao, "fill") == 0){
      fscanf(arquivo_org, "%d", &imagem.x1);
      fscanf(arquivo_org, "%d", &imagem.y1);
      
      ver.r = matriz_img[imagem.x1][imagem.y1].r;
      ver.g = matriz_img[imagem.x1][imagem.y1].g;
      ver.b = matriz_img[imagem.x1][imagem.y1].b;
      
      printf("%d %d %d\n",ver.r, ver.g, ver.b);    
      preencher(imagem.x1, imagem.y1, matriz_img,ver,color);
    }
    else if (strcmp(imagem.acao, "save") == 0){
      save(arquivo_org, ptrimg, matriz_img);
    }   
            
    }
  }

  fclose(arquivo_org);
  
  return 0;
}
