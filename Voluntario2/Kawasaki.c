#include <stdio.h>
//#include "gsl_rng.h"
#include "Funciones_kawasaki.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>


int main(){
    srand(time(NULL));
    int semilla=time(NULL);
    int N=20;
    int i, j, k, ij;
    int m, n, r;
    double E, E2, expo, T, p, xi;
    double delta_E;
    double t, h, Tmax;
    FILE* fichero_out;
    fichero_out=fopen("Datos_kawasaki.txt", "w");

    T=1.7;
    
    //Ponemos unn valor aleatorio en todo la malla
     int s[N+4][N+4];
    for(i=2;i<N+2;i++){
        for(j=2;j<N+2;j++){
            s[i][j]=rand() % 2;
            //s[i][j]=aleatory_gsl1(2)
            if(s[i][j]==0){
                s[i][j]=-1;
            }
        }
    }
    for(i=2;i<N+2;i++){
        s[2][i]=1;
        s[N+1][i]=-1;
    }
   
   int* sp=s[0];
    Tmax=10000;
    h=1;
    t=0;
    while(t<Tmax){
        
         //Nuestra matriz es dos filas y dos columnas más grande 
    //De esta forma podemos imponer las condiciones de contorno periodicas de la siguiente forma
        for(ij=1;ij<N*N;ij++){
            for(k=2;k<N+2; k++){
            s[1][k]=s[N+1][k];
            s[k][1]=s[k][N+1];
            s[N+2][k]=s[2][k];
            s[k][N+2]=s[k][2];

            s[0][k]=s[N][k];
            s[k][0]=s[k][N];
            s[N+3][k]=s[3][k];
            s[k][N+3]=s[k][3];
            
            }
            
            
            //Elegimos el punto incial de la matriz
            n=rand() % (N-2)+3;
            m=rand() % N+2;
          
         

            //Escogemos también al vecino
            //Para ello generamos un numero aleatorio entre 0 y 3
            //Si sale 0 interpretamos que cambia con el de la izquierda
            //Si sale 1 cambia con la derecha
            //Si sale 2 cambia con el de arriba
            //Si sale 3 cambia con el de abajo
            r=(rand() % 4);

            //Las condiones de contorno nos obligan a asignar valores a ciertos cuadrantes de nuestra matriz
            //según la dirección en la que rote
            if(r!=3 && n!=N-3){
                if(r!=2 && n!=3){}

            }
            if(n==2 && m==2){
                if(r==0){
                    s[1][1]=s[1][N+1];
                }
                if(r==2){
                    s[1][1]=s[N+1][1];
                }
            }
            if(n==N+1 && m==2){
                if(r==0){
                    s[N+2][1]=s[N+2][N+1];
                }
                if(r==3){
                    s[N+2][1]=s[2][1];
                }
            }
            if(n==2 && m==N+1){
                if(r==1){
                    s[1][N+2]=s[1][2];
                }
                if(r==2){
                    s[1][N+2]=s[N+1][N+2];
                }
            }
            if(n==N+1 && m==N+1){
                if(r==1){
                    s[N+2][N+2]=s[N+2][2];
                }
                if(r==3){
                    s[N+2][N+2]=s[2][N+2];
                }
            }

            
         
            
            //*sp=*(sp+n+m*(N+2));
            if(m==3 && r==2){
                
            }
            E=0;
            //Calculamos la energía de los valores cercanos a nuestro valor
            //Solo a los valores cercanos ya que son los únicos que van a cambiar la energía
            for(i=n-2;i<=n+2;i++){
                for(j=m-2;j<=m+2;j++){
                    E+=energia(sp+i*(N+4)+j, N+4);
                }
            }

            //Realizamos el cambio de valores para ver como afecta a la energía
            intercambio_spin(sp+n*(N+4)+m, r, N);

            //Calculamos la energía en la nueva posición
            E2=0;
            for(i=n-2;i<=n+2;i++){
                for(j=m-2;j<=m+2;j++){
                    E2+=energia(sp+i*(N+4)+j, N+4);
                }
            }
           
           //Calculamos la variación de la energía y la exponencial
            delta_E=E2-E;

            expo=exp(-delta_E/T);

            //Le asignamos el valor correspondiente a p
            if(1<expo){
                p=1;
            }
            else{
                p=expo;
            }
            
            //Generamos un numero aleatorio 
            xi=rand();
            xi=xi/RAND_MAX;
            //Comprobamos si se cumple la condición de cambio
            if(xi>p){
                //Si no se cumple deshacemos el intercambio
                intercambio_spin(sp+n*(N+4)+m, r, N);
            }
            else{
                //Si se cumple nos aseguramos que las condiciones de contorno se cumplan correctamente
                if(n==2 && r==2)
                {
                        s[n+1][m]=s[1][m];
                }
                if(n==N+1 && r==3){
                        s[2][m]=s[N+2][m];
                }
                if(m==2 && r==0){
                    s[n][N+1]=s[n][1];
                }
                if(m==N+1 && r==1){
                    s[n][2]=s[n][N+2];
                }
            }
        }

        //Escribimos los datos obtenidos en un fichero
        for(i=2;i<N+2;i++){
            for(j=2;j<N+1;j++){
                fprintf(fichero_out, "%d, ", s[i][j]);
            }
            fprintf(fichero_out, "%d", s[i][N+1]);
            fprintf(fichero_out, "\n");
        }
        fprintf(fichero_out, "\n");
        //Aumentamos en 1 el paso montecarlo
        t+=1;
        
        
        
    }
int suma=0;
    for(i=2;i<N+2;i++){
        for(j=2;j<N+2;j++){
            suma+=s[i][j];
        }
    }
printf("%d, ", suma);
fclose(fichero_out);



}