#include <stdio.h>
//La gsl solo se puede utiliar en joel
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
    int N=80;
    int i, j, k;
    int m, n;
    double E, expo, T, p, xi;
    double t, h, Tmax;
    FILE* fichero_out;
    fichero_out=fopen("Datos_isin.txt", "w");
    


    //Ponemos el valor de la temperatura
    T=1;
    //Ponemos un valor de espin aleatorio en cada punto de la malla
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
   
    int* sp=s[0];
    //definimos el paso montecarlo y el número de pasos motecarlo que se deben dar
    Tmax=1000;
    h=1;
    t=0;

    //Iniciamos el bucle de pasos montecarlo
    while(t<Tmax){
        
        //Iniciamos un buvcle for para realizar un paso montecarlo
        for(i=1;i<N*N;i++){
            //Nuestra matriz es dos filas y dos columnas más grande 
            //De esta forma podemos imponer las condiciones de contorno periodicas de la siguiente forma
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

           
            
            //Calculamos la variación de energía
            //Hay que poner la posición del espín que nos interesa  el tamaño de la malla (en nuestro caso N+2)
            E=delta_energia(sp+n*(N+2)+m, N+2);

            expo=exp(-E/T);
            

            //Damos el valor de p según montecarlo
            if(1<expo){
                p=1;
            }
            else{
                p=expo;
            }
            
            //Generamos un numero aleatorio entre 0 y 1
            xi=rand();
            xi=xi/RAND_MAX;
            //xi=aleatory_gsl2(semilla);

            //Si este numero aleatorio es menor que p entonces cambiamos el espin
            if(xi<p){
                s[n][m]=-s[n][m];
            }
        }//FIN del bucle for

        //Lo metemos en un fichero tras cada paso montecarlo
        for(i=0;i<N+1;i++){
            for(j=0;j<N;j++){
                fprintf(fichero_out, "%d, ", s[i][j]);
            }
            fprintf(fichero_out, "%d", s[i][N]);
            fprintf(fichero_out, "\n");
        }
        fprintf(fichero_out, "\n");

        //Actualizamos el paso montecarlo
        t+=1;
        
    }//Fin del paso montecarlo


//Cerramos ficheros y calculamos y mostramos el tiempo requerido
fclose(fichero_out);
final=clock();
    
double tiempo=(double)(final-comienzo)/CLOCKS_PER_SEC;

printf("Tiempo transcurrido desde el comienzo hasta el fin del algoritmo utilizado: %lf ", tiempo);



}