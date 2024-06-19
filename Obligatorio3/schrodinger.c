#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
//#include "schrodinger.h"

double pi=3.14159265;
void calculo_betha(double complex * phi, double complex * alpha, double complex * betha,  double * V, int N, double s_tilde);

int main(){
    int j, i;
    
    //definimos las variables necesarias
    double nc, lambda, k, k_tilde, h, s_tilde, norma;
    //Damos valor a N y nc (normalmente nc=N/4)
    int N=200;
    nc=N/4 ;
    double V[N], phi2[N], imag[N], real[N];
    double complex phi[N], alpha[N-1], betha[N-1], chi[N];

    //Calculamos k y s según las expresiones
    k_tilde=2*pi*nc/(N);
    s_tilde=1/(4*k_tilde*k_tilde);

    //Valor de lambda, nos permite ajustar la barrera de potencial
    lambda=0.5;


    double complex * phip=phi;
    double complex * alphap=alpha;
    double complex * bethap=betha;
    double * Vp=V;


    //Introducimos el tiempo que se desea de simulación (Tmax) y el valor del paso inicial (n)
    int Tmax=500;
    int n=0;


    //Abrimos los ficheros uno para los datos de la norma y otro para los datos de la simulación
    FILE* fichero;
    FILE* fichero_norma;
    fichero=fopen("Datos_Schrodinger.txt", "w");
    fichero_norma=fopen("Datos_norma.txt", "w");

    //Rellenamos el vector de potencial, haciendo que sea un potencial cuadrado
    for(j=0;j<N;j++){
        if(j>=2*N/5 && j<=3*N/5){
            V[j]=lambda*k_tilde*k_tilde; 
        }
        else{
            V[j]=0;
        }
    }


    //Condiciones de contorno iniciales
    phi[0]=0;
    phi[N-1]=0;

    //inicializamos la norma y calculamos la norma al inicio, así como la función de onda inicial
    norma=0;
    for(j=1;j<N-1;j++){
        phi[j]=cexp(I*k_tilde*j)*exp(-8*pow((4*j-N),2)/(N*N));
        phi2[j]=cabs(phi[j])*cabs(phi[j]);
        real[j]=creal(phi[j]);
        imag[j]=cimag(phi[j]);
        norma=norma+phi2[j]/N;
        
    }

    //Con la norma podemos normalizar nuestra función de onda
    for(j=1;j<N;j++){
        phi[j]=phi[j]/sqrt(norma);
    }

    //Metemos los datos de la función de onda al inicio en el fichero
    for(j=0;j<N;j++){
        fprintf(fichero, "%d, %lf, %lf \n", j, phi2[j], V[j]);
    }
    fprintf(fichero, "\n");


    //Calculamos los valores de alpha que son fijos a lo largo del tiempo
    alpha[N-2]=0;
    for(j=N-2;j>-1;j--){
        alpha[j-1]=-1/(alpha[j]-2+2*I/s_tilde-V[j]);
    }


    //Iniciamos el bucle temporal
    while(n<Tmax){

        //Condicion de contorno para betha
        betha[N-2]=0;

        //Apartir de la condición de contorno para betha, podemos calcular el valor de betha en el espacio
        calculo_betha(phip, alphap, bethap, Vp, N, s_tilde);

        //Calculamos el valor de chi una vez conocidos alpha y betha
        chi[0]=0;
        for(j=0;j<N-1;j++){
            chi[j+1]=alpha[j]*chi[j]+betha[j];
        }

        //Calculamos la función de onda y la norma en el instante de tiempo 
        norma=0;
        for(j=0;j<N;j++){
            phi[j]=chi[j]-phi[j];
            phi2[j]=cabs(phi[j])*cabs(phi[j]);
            imag[j]=cimag(phi[j]);
            real[j]=creal(phi[j]);
            norma=norma+phi2[j]/N;
        }

        //Guuardamos los datos en los ficheros
        for(j=0;j<N;j++){
            fprintf(fichero, "%d, %lf, %lf \n", j, phi2[j], V[j]);
        }
        fprintf(fichero, "\n");

        fprintf(fichero_norma, "%lf, %d \n", norma, n);


        //Actualizamos el bucle temporal y repetimos todo el proceso
        //De esta manera vams obteniendo la evolución de la función de onda a lo largo del tiempo
        n=n+1;
    }//Fin bucle temporal

    //Cerramos ficheros
    fclose(fichero);
    fclose(fichero_norma);

    
}


//Función que calcula el valor de betha
//Se le pasa el puntero de la función de onda, el puntero de valores de alpha, el puntero co valores de betha, el puntero del potencial y los valores de N y s
//Actualiza el puntero de betha para todo el espacio
void calculo_betha(double complex * phi, double complex * alpha, double complex * betha, double * V, int N, double s_tilde){
     int j;
    for(j=N-2;j>0;j--){
        *(betha+j-1)=(4*I*(*(phi+j))/s_tilde-*(betha+j))/(*(alpha+j)-2+2*I/s_tilde-*(V+j));
    }
}