#include <stdio.h>
//#include "gsl_rng.h"
#include "Funciones_kawasaki.h"
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>


int main(){
    clock_t comienzo, final;
    comienzo=clock();
    srand(time(NULL));
    int semilla=time(NULL);
    int N=64;
    int i, j, k, ij, check, t;
    int m, n, r;
    double E, E2, expo, T, p, xi;
    double mag, mag_superior, mag_inferior;
    double delta_E;
    double h, Tmax;
    FILE* fichero_out;
    FILE *fichero_magnetizacion;
    fichero_out=fopen("Datos_kawasaki.txt", "w");
    fichero_magnetizacion=fopen("Datos_magnetización", "w");

    mag=0;
    mag_superior=0;
    mag_inferior=0;
    T=1.5;
    
    //Ponemos unn valor aleatorio en todo la malla
    int s[N][N+4];
    int a=1;
    for(i=1;i<N/2;i++){
        for(j=2;j<N+2;j++){
            k=rand()%2;
            if( k==0 ){
                s[i][j]=-1;
            }
            else{
                s[i][j]=1;
            }
            
            }
            
    }

     for(i=N/2;i<N-1;i++){
        for(j=2;j<N+2;j++){
             k=rand()%2;
            if( k==0){
                s[i][j]=1;
            }
            else{
                s[i][j]=-1;
            }
            
            }
            
    }


    //PROTOTIPO DE MAGNETIZACION NULA
    // for(i=0;i<N;i++){
    //     for(j=0;j<N+3;j++){
    //         s[i][j]=0;
    //     }
    // }
    // int w;
    // w=N*N;
    // int elementos[w];
    // for(i=0;i<w;i=i+2){
    //     elementos[i]=rand()%2;
    //     if(elementos[i]==0){
    //         elementos[i]=-1;
    //     }
        
    // }

    //Escogemos unos valores randoms en la malla
    
  
    
    for(i=0;i<N+4;i++){
        s[0][i]=1;
        s[N-1][i]=-1;
    }
    a=0;
   for(i=0;i<N;i++){
        for(j=2;j<N+2;j++){
            a=a+s[i][j];
        }
    }
   int* sp=s[0];
    Tmax=5;
    h=1;
    t=0;
    while(t<Tmax){
        mag=Magnetización(sp,N);
        
         //Nuestra matriz es dos filas y dos columnas más grande 
    //De esta forma podemos imponer las condiciones de contorno periodicas de la siguiente forma
        for(ij=1;ij<N*N;ij++){
            for(k=0;k<N; k++){
        
            s[k][1]=s[k][N+1];
            s[k][N+2]=s[k][2];
            s[k][0]=s[k][N];
            s[k][N+3]=s[k][3];
            
            }
            
            
            //Elegimos el punto incial de la matriz
            n=rand() % (N-2)+1;
            m=rand() % N+2;
          
            

            //Escogemos también al vecino
            //Para ello generamos un numero aleatorio entre 0 y 3
            //Si sale 0 interpretamos que cambia con el de la izquierda
            //Si sale 1 cambia con la derecha
            //Si sale 2 cambia con el de arriba
            //Si sale 3 cambia con el de abajo
            if(n==1){
                r=(rand()%3);
                if(r==2){
                    r=3;
                }
            }
            else if(n==N-2){
                r=rand()%3;
            }
            else{
             r=(rand() % 4);
            }
            
            check=comprobacion_spin(sp+n*(N+4)+m, r, N);

            //Ejecutamos el codigo si y solo si los espines que se quieren intercmbiar tienen diferente estado
            //De lo contrario no afectaría en nada su intercambio, por lo que lo dejamos igual
            if(check==0){

            //Las condiones de contorno nos obligan a asignar valores a ciertos cuadrantes de nuestra matriz
            //según la dirección en la que rote
                
                        
                
                //Calculamos la energía de los valores cercanos a nuestro valor
                //Solo a los valores cercanos ya que son los únicos que van a cambiar la energía
                E=energia_total(sp, n, m, r, N);

                //Realizamos el cambio de valores para ver como afecta a la energía
                intercambio_spin(sp+n*(N+4)+m, r, N);

                //Calculamos la energía en la nueva posición
                E2=energia_total(sp, n, m, r, N);
               
            
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
                    if(m==2 && r==0){
                        s[n][N+1]=s[n][1];
                    }
                    if(m==N+1 && r==1){
                        s[n][2]=s[n][N+2];
                    }
                }
                    
                
            }
           
            
            
        }
        
        mag=mag+Magnetización(sp, N);
        mag_superior+=Magnetización_superior(sp, N);
        mag_inferior+=Magnetización_inferior(sp, N);
        if(t % 100 ==0){
            mag=mag/100;
            mag_superior=mag_superior/100;
            mag_inferior=mag_inferior/100;
            fprintf(fichero_magnetizacion, "%lf, %lf, %lf \n", mag, mag_superior, mag_inferior);
            mag=0;
            mag_superior=0;
            mag_inferior=0;
        }
             
        



        //Escribimos los datos obtenidos en un fichero
        for(i=0;i<N;i++){
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

fclose(fichero_out);
fclose(fichero_magnetizacion);
final=clock();
    
    double tiempo=(double)(final-comienzo)/CLOCKS_PER_SEC;

    printf("Tiempo transcurrido desde el comienzo hasta el fin del algoritmo utilizado: %lf ", tiempo);
    
}