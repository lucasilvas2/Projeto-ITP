#include "func.h"
//LER DIMENSÃO
void imag(img * ptrimagem, FILE *arquivo_org, pixel ** matriz_img){
  fscanf(arquivo_org, "%d", &ptrimagem->coluna);
  fscanf(arquivo_org, "%d", &ptrimagem->altura);  
}

//FUNÇÃO CLEAR
void clr(img imagem,pixel clear,pixel * ptrclear, FILE *arquivo_org, pixel ** matriz_img){
  
  fscanf(arquivo_org, "%d", &ptrclear->r);
  fscanf(arquivo_org, "%d", &ptrclear->g);
  fscanf(arquivo_org, "%d", &ptrclear->b);

  for(int i = 0; i < imagem.altura; i++){
    for(int j = 0; j < imagem.coluna; j++){
      matriz_img [i][j].r = ptrclear->r;
      matriz_img [i][j].g = ptrclear->g;
      matriz_img [i][j].b = ptrclear->b;
    }
  } 
}

// FUNÇÃO PARA LEITURA DA COR
void i_cor(img imagem, pixel color, pixel * ptrcolor, FILE * arquivo_org, pixel ** matriz_img){
  fscanf(arquivo_org, "%d", &ptrcolor->r);
  fscanf(arquivo_org, "%d", &ptrcolor->g);
  fscanf(arquivo_org, "%d", &ptrcolor->b);
}
//FUNÇÃO GERAR IMAGEM E SALVAR
void save(FILE *arquivo_org, img *ptrimg, pixel ** matriz_img){
  fscanf(arquivo_org , "%s", ptrimg->nome_imagem);

  FILE *gerando_imagem = fopen(ptrimg->nome_imagem, "w");
  fputs("P3\n", gerando_imagem);
  fprintf(gerando_imagem, "%d %d\n", ptrimg->coluna, ptrimg->altura);
  fputs("255\n", gerando_imagem);

  for(int i = 0; i < ptrimg->altura; i++){
    for(int j = 0; j < ptrimg->coluna; j++){
      fprintf(gerando_imagem, "%d %d %d\n", matriz_img[i][j].r, matriz_img[i][j].g, matriz_img[i][j].b);       
    }
  }
  fclose(gerando_imagem);
}
//FUNÇÃO PARA DESENHAR LINHA
void desenhar_linha (int x1, int y1, int x2, int y2,pixel ** matriz_img, pixel color){
  printf("%d %d %d\n", color.r, color.g, color.b);
        int deltaX, deltaY, x, y;
        int inclinacao, d;

        deltaY = y2 - y1;
        deltaX = x2 - x1;

        x = x1;
        printf("X = %d\n", x);
        y = y1;
        printf("Y = %d\n", y);

        if(deltaX < 0) // caso ponto final < ponto inicial
        {
          desenhar_linha(x2, y2, x1, y1, matriz_img, color);
        }

        if(deltaY < 0){
          inclinacao = -1;
        }
        else{
          inclinacao = 1;
        }

        if(deltaX >= inclinacao*deltaY) {    // m<=1
          if(deltaY<0){ // caso y2<y1
            d = 2*deltaY+deltaX;
            while(x<x2){
              if(d<0){
                d += 2*(deltaY+deltaX);
                x++;
                y--;
                //printf("A X = %d || Y = %d\n",x - 1,y - 1);
                        
                pintapixel(x , y, matriz_img, color);
              }
              else{
                d+=2*deltaY;
                x++; // varia apenas no eixo x
                //printf("B X = %d || Y = %d\n",x - 1,y - 1);
                        
                pintapixel(x , y, matriz_img, color);
              }
            }
          }
          else{ // caso y1<y2
            d=2*deltaY-deltaX;
            while(x<x2){
              if(d<0){
                d+=2*deltaY;
                x++; // varia apenas no eixo x
                //printf("C X = %d || Y = %d\n",x - 1,y - 1);
                        
                pintapixel(x , y, matriz_img, color);

              }
              else{
                d+=2*(deltaY-deltaX);
                x++;
                y++;
                //printf("D X = %d || Y = %d\n",x - 1,y - 1);
                        
                pintapixel(x , y, matriz_img, color);

              }
            }
          }
        }
    else{ // |m|>1
        if(deltaY<0){ // caso y2<y1
            d=deltaY +2*deltaX;
            while(y > y2){
                if(d<0){
                    d += 2*deltaX;
                    y--; // varia apenas no eixo y
                    //printf("E X = %d || Y = %d\n",x - 1,y - 1);
                  
                    pintapixel(x , y, matriz_img, color);
                }
                else{
                    d+=2*(deltaY+deltaX);
                    x++;
                    y--;
                    //printf("F X = %d || Y = %d\n",x - 1,y - 1);
                   
                    pintapixel(x , y, matriz_img, color);
                }
            }
        }
        else{ // caso y1<y2
            d=deltaY-2*deltaX;
            while(y<y2){
                if(d<0){
                    d+=2*(deltaY-deltaX);
                    x++;
                    y++;
                    //printf("G X = %d || Y = %d\n",x - 1,y - 1);
                    
                    pintapixel(x , y, matriz_img, color);
                }
                else{
                    d+=(-2)*deltaX;
                    y++; // varia apenas no eixo y
                    //printf("H X = %d || Y = %d\n",x - 1,y - 1);
                    
                    pintapixel(x , y, matriz_img, color);
                }
            }
        }
    }
    return;
}
void poligono(int * vetor_x, int * vetor_y,img imagem, pixel ** matriz_img, pixel color, int pontos){
  int i;
  for(i = 0; i < pontos; i++){
    desenhar_linha(vetor_x[i], vetor_y[i], vetor_x[i + 1], vetor_y[i +1], matriz_img, color);
  }
}

void preencher(int x, int y, pixel ** matriz_img, pixel ver,pixel color){
  printf("%d %d\n", x, y);
  
  if (matriz_img[y][x].r == ver.r && matriz_img[y][x].g == ver.g && matriz_img[y][x].b == ver.b){
    
    pintapixel(x , y , matriz_img, color);
    preencher(x, y + 1, matriz_img, ver, color);
    preencher(x + 1, y, matriz_img, ver, color);
    preencher(x - 1, y, matriz_img, ver, color);
    preencher(x, y - 1, matriz_img, ver, color);
  }
  
}

void circle(int x_c, int y_c, int r, pixel ** matriz_img, pixel color){
    int x = r, y = 0; 
      
    // Imprimir o ponto inicial nos eixos  
    printf("ponto inicial X = %d || Y = %d \n", x + x_c, y + y_c);

   
    // espelhando pontos iniciais 
    if (r > 0) 
    { 
     
      pintapixel(x + x_c , -y + y_c, matriz_img, color);
      
     
      pintapixel(y + x_c , x + y_c, matriz_img, color);
      
      
      pintapixel(-x + x_c , y + y_c, matriz_img, color); 
    
      
      pintapixel(y + x_c , -x + y_c , matriz_img, color);
    } 
      
    //iniciando verificação do ponto médio
    int V = 1 - r; 
    while (x > y) 
    {  
        y++; 
          
        //dentro ou na circunferência 
        if (V <= 0) 
          V = V + 2*y + 1; 
              
        // fora da circunferência
        else
        { 
          x--; 
          V = V + 2*y - 2*x + 1; 
        } 
          
        // condição de parada - todos pixels pintados
        if (x < y){
          break;
        }
          
        // ponto gerado e espelhando nos octantes 
         
        ; 
        pintapixel(x + x_c , y + y_c, matriz_img, color);
        
        
        pintapixel(-x + x_c , y + y_c, matriz_img, color);
        
        
        pintapixel(x + x_c , -y + y_c, matriz_img, color);
        
        
        pintapixel(-x + x_c , -y + y_c, matriz_img, color);  
        
        //Se o ponto gerado estiver na linha x = y, então
        // os pontos de perímetro já foram impressos
        if (x != y) 
        { 
            
            pintapixel(y + x_c , x + y_c, matriz_img, color);

             
            pintapixel(-y + x_c , x + y_c, matriz_img, color);

           
            pintapixel(y + x_c , -x + y_c, matriz_img, color);

            
            pintapixel(-y + x_c , -x + y_c, matriz_img, color);
        } 
    }  

}


//FUNÇÃO PARA PINTAR CADA PIXEL
void pintapixel(int x, int y, pixel ** matriz_img, pixel color){
    matriz_img[y ][x ].r = color.r;
    matriz_img[y][x ].g = color.g;
    matriz_img[y ][x ].b = color.b;
}
