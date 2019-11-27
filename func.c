#include "func.h"
//CRIAR IMAGEM
/*void imag(FILE * arquivo_org,img image,img *ptrimg, pixel ** matriz_img){
    int i;
    fscanf(arquivo_org, "%d", &ptrimg->coluna);
    fscanf(arquivo_org, "%d", &ptrimg->altura);
    matriz_img = (pixel **) calloc(ptrimg->altura, sizeof(pixel*));
    for(i = 0; i < ptrimg->altura; i++){
        matriz_img[i] = (pixel *) calloc(ptrimg->coluna, sizeof(pixel));
    }

}*/
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
                        printf("A X = %d || Y = %d\n",x - 1,y - 1);
                        /*matriz_img[y - 1][x - 1].r = color.r;
                        matriz_img[y - 1][x - 1].g = color.g;
                        matriz_img[y - 1][x - 1].b = color.b;*/
                        pintapixel(x , y, matriz_img, color);
                    }
                    else{
                        d+=2*deltaY;
                        x++; // varia apenas no eixo x
                        printf("B X = %d || Y = %d\n",x - 1,y - 1);
                        /*matriz_img[y - 1][x - 1].r = color.r;
                        matriz_img[y - 1][x - 1].g = color.g;
                        matriz_img[y - 1][x - 1].b = color.b;*/
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
                        printf("C X = %d || Y = %d\n",x - 1,y - 1);
                        /*matriz_img[y - 1][x - 1].r = color.r;
                        matriz_img[y - 1][x - 1].g = color.g;
                        matriz_img[y - 1][x - 1].b = color.b;*/
                        pintapixel(x , y, matriz_img, color);

                    }
                    else{
                        d+=2*(deltaY-deltaX);
                        x++;
                        y++;
                        printf("D X = %d || Y = %d\n",x - 1,y - 1);
                        /*matriz_img[y - 1][x - 1].r = color.r;
                        matriz_img[y - 1][x - 1].g = color.g;
                        matriz_img[y - 1][x - 1].b = color.b;*/
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
                    printf("E X = %d || Y = %d\n",x - 1,y - 1);
                    /*matriz_img[y - 1][x - 1].r = color.r;
                    matriz_img[y - 1][x - 1].g = color.g;
                    matriz_img[y - 1][x - 1].b = color.b;*/
                    pintapixel(x , y, matriz_img, color);
                }
                else{
                    d+=2*(deltaY+deltaX);
                    x++;
                    y--;
                    printf("F X = %d || Y = %d\n",x - 1,y - 1);
                    /*matriz_img[y - 1][x - 1].r = color.r;
                    matriz_img[y - 1][x - 1].g = color.g;
                    matriz_img[y - 1][x - 1].b = color.b;*/
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
                    printf("G X = %d || Y = %d\n",x - 1,y - 1);
                    /*matriz_img[y - 1][x - 1].r = color.r;
                    matriz_img[y - 1][x - 1].g = color.g;
                    matriz_img[y - 1][x - 1].b = color.b;*/
                    pintapixel(x , y, matriz_img, color);
                }
                else{
                    d+=(-2)*deltaX;
                    y++; // varia apenas no eixo y
                    printf("H X = %d || Y = %d\n",x - 1,y - 1);
                    /*matriz_img[y - 1][x - 1].r = color.r;
                    matriz_img[y - 1][x - 1].g = color.g;
                    matriz_img[y - 1][x - 1].b = color.b;*/
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

void circle(int x_c, int y_c, int r, pixel ** matriz_img, pixel color){
    int x = r, y = 0; 
      
    // Imprimir o ponto inicial nos eixos  
    // after translation 
    printf("ponto inicial X = %d || Y = %d \n", x + x_c, y + y_c);

   
    // espelhando pontos iniciais 
    if (r > 0) 
    { 
      printf("A X = %d || Y = %d \n", x + x_c, -y + y_c);
      pintapixel(x + x_c , -y + y_c, matriz_img, color);
      
      printf("B X = %d || Y = %d \n", y + x_c, x + y_c); 
      pintapixel(y + x_c , x + y_c, matriz_img, color);
      
      printf("C X = %d || Y = %d \n", -x + x_c, y + y_c);
      pintapixel(-x + x_c , y + y_c, matriz_img, color); 
    
      printf("D X = %d || Y = %d \n", y + x_c, -x + y_c);
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
         
        printf("E X = %d || Y = %d \n", x + x_c, y + y_c); 
        pintapixel(x + x_c , y + y_c, matriz_img, color);
        
        printf("F X = %d || Y = %d \n", -x + x_c, y + y_c); 
        pintapixel(-x + x_c , y + y_c, matriz_img, color);
        
        printf("G X = %d || Y = %d \n", x + x_c, -y + y_c); 
        pintapixel(x + x_c , -y + y_c, matriz_img, color);
        
        printf("H X = %d || Y = %d\n", -x + x_c, -y + y_c); 
        pintapixel(-x + x_c , -y + y_c, matriz_img, color);  
        
        //Se o ponto gerado estiver na linha x = y, então
        // os pontos de perímetro já foram impressos
        if (x != y) 
        { 
            printf("I X = %d || Y = %d \n", y + x_c, x + y_c);
            pintapixel(y + x_c , x + y_c, matriz_img, color);

            printf("J X = %d || Y = %d \n", -y + x_c, x + y_c); 
            pintapixel(-y + x_c , x + y_c, matriz_img, color);

            printf("L X = %d || Y = %d \n", y + x_c, -x + y_c); 
            pintapixel(y + x_c , -x + y_c, matriz_img, color);

            printf("M X = %d || Y = %d\n", -y + x_c, -x + y_c); 
            pintapixel(-y + x_c , -x + y_c, matriz_img, color);
        } 
    }  

}


//FUNÇÃO PARA PINTAR CADA PIXEL
void pintapixel(int x, int y, pixel ** matriz_img, pixel color){
    matriz_img[y - 1][x - 1].r = color.r;
    matriz_img[y - 1][x - 1].g = color.g;
    matriz_img[y - 1][x - 1].g = color.b;
}
