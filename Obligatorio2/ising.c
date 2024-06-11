#include <stdio.h>
//#include "gsl_rng.h"
#include "Funciones_ising.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>



int main(){
    clock_t comienzo, final;
    comienzo=clock();
    srand(time(NULL));
    int semilla=time(NULL);
    int N=200;
    int i, j, k;
    int m, n;
    double E, expo, T, p, xi;
    double t, h, Tmax;
    FILE* fichero_out;
    fichero_out=fopen("Datos_isin.txt", "w");

    T=4;
    //Pone un valor de espin aleatorio en cada punto de la malla
    int s[N+2][N+2];
    for(i=1;i<N+1;i++){
        for(j=1;j<N+1;j++){
            s[i][j]=rand() % 2;
            //s[i][j]=aleatory_gsl1(2)
            if(s[i][j]==0){
                s[i][j]=-1;
            }
        }
    }
   
   
    Tmax=1000;
    h=1;
    t=0;
    while(t<Tmax){
        
        //Nuestra matriz es dos filas y dos columnas más grande 
        //De esta forma podemos imponer las condiciones de contorno periodicas de la siguiente forma
        for(i=1;i<N*N;i++){
            for(k=0;k<N+1; k++){
            s[0][k]=s[N][k];
            s[k][0]=s[k][N];
            s[N+1][k]=s[1][k];
            s[k][N+1]=s[k][1];
            }
            
            //Elegimos el punto incial de la matriz
            n=rand() % N+1;
            m=rand() % N+1;
            //n=aleatory_gsl1(N+1, semilla);
            //m=aleatory_gsl2(N+2, semilla);

            int* sp=s[0];
            //*sp=*(sp+n+m*(N+2));

            E=delta_energia(sp+n*(N+2)+m, N+2);

            expo=exp(-E/T);

            if(1<expo){
                p=1;
            }
            else{
                p=expo;
            }
            
            //Generamos un numero aleatorio 
            xi=rand();
            xi=xi/RAND_MAX;
            //xi=aleatory_gsl2(semilla);
            if(xi<p){
                s[n][m]=-s[n][m];
            }
        }
        for(i=0;i<N+1;i++){
            for(j=0;j<N;j++){
                fprintf(fichero_out, "%d, ", s[i][j]);
            }
            fprintf(fichero_out, "%d", s[i][N]);
            fprintf(fichero_out, "\n");
        }
        fprintf(fichero_out, "\n");
        t+=1;
        
    }

fclose(fichero_out);
final=clock();
    
double tiempo=(double)(final-comienzo)/CLOCKS_PER_SEC;

printf("Tiempo transcurrido desde el comienzo hasta el fin del algoritmo utilizado: %lf ", tiempo);



}