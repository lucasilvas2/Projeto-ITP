#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

int main(){
    int i, j, pontos;
   img imagem;
   img * ptrimg = &imagem;
   pixel ** matriz_img;
   pixel clear, color;
   circ circulo;


   FILE *arquivo_org = fopen("testando.txt","r");

   if(arquivo_org == NULL){
        printf("Erro\n");
        exit(0);
   }
   else{
        while(fscanf(arquivo_org, "%s", imagem.acao) != EOF){
            printf("%s\n", imagem.acao);

            if(strcmp(imagem.acao, "image") == 0){
                fscanf(arquivo_org, "%d", &imagem.coluna);
                fscanf(arquivo_org, "%d", &imagem.altura);

                matriz_img = (pixel **) calloc(imagem.altura, sizeof(pixel*));
                for(i = 0; i < imagem.altura; i++){
                    matriz_img[i] = (pixel *) calloc(imagem.coluna, sizeof(pixel));
                }
            }
            else if(strcmp(imagem.acao, "clear") == 0){
                fscanf(arquivo_org, "%d", &clear.r);
                fscanf(arquivo_org, "%d", &clear.g);
                fscanf(arquivo_org, "%d", &clear.b);
                /*for(i = 0; i < imagem.altura; i++){
                    for(j = 0; j < imagem.coluna; j++){
                        matriz_img[i][j].r = clear.r;
                        matriz_img[i][j].g = clear.g;
                        matriz_img[i][j].b = clear.b;
                    }
                }*/
                printf("%d %d %d\n", clear.r, clear.g, clear.b);
            }
            else if(strcmp(imagem.acao, "color") == 0){
                fscanf(arquivo_org, "%d", &color.r);
                fscanf(arquivo_org, "%d", &color.g);
                fscanf(arquivo_org, "%d", &color.b);
                printf("%d %d %d\n", color.r, color.g, color.b);

            }
            else if(strcmp(imagem.acao, "line") == 0){
                fscanf(arquivo_org, "%d", &imagem.x1);
                fscanf(arquivo_org, "%d", &imagem.y1);
                fscanf(arquivo_org, "%d", &imagem.x2);
                fscanf(arquivo_org, "%d", &imagem.y2);
                printf("%d %d %d\n", color.r, color.g, color.b);
                
                desenhar_linha(imagem.x1, imagem.y1, imagem.x2,imagem.y2, matriz_img, color);
            }
            else if(strcmp(imagem.acao, "polygon") == 0){
              printf("%d %d %d\n", color.r, color.g, color.b);
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
              printf("%d %d %d\n", color.r, color.g, color.b);
              

              circle(circulo.x_c, circulo.y_c, circulo.r, matriz_img, color);

            }
            
        }
    }

    FILE *ger_imagem = fopen("testando.ppm","w");

        fputs("P3\n", ger_imagem);
        fprintf(ger_imagem,"%d %d\n", imagem.coluna, imagem.altura);
        fputs("255\n", ger_imagem);
        for(i = 0; i < imagem.altura; i++){
            for(j = 0; j < imagem.coluna; j++){
                fprintf(ger_imagem, "%d %d %d\n", matriz_img[i][j].r, matriz_img[i][j].g, matriz_img[i][j].b);
                /*fprintf(ger_imagem, "%d", matriz_img[i][j].r);
                fprintf(ger_imagem, " %d", matriz_img[i][j].g);
                fprintf(ger_imagem, " %d\n", matriz_img[i][j].b);*/
            }
        }

    fclose(arquivo_org);
    fclose(ger_imagem);
    return 0;
}
