#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
//#include "schrodinger.h"

double pi=3.14159265;
void calculo_betha(double complex * phi, double complex * alpha, double complex * betha,  double * V, int N, double s_tilde);

int main(){
    int j, i;
    
    double nc, lambda, k, k_tilde, h, s_tilde, norma;
    int N=200;
    nc=5 ;
    double V[N], phi2[N], imag[N], real[N];
    double complex phi[N], alpha[N-1], betha[N-1], chi[N];
    k_tilde=2*pi*nc/(N);
    s_tilde=1/(4*k_tilde*k_tilde);
    lambda=1;
    double complex * phip=phi;
    double complex * alphap=alpha;
    double complex * bethap=betha;
    double * Vp=V;

    int Tmax=500;
    int n=0;

    FILE* fichero;
    FILE* fichero_norma;
    fichero=fopen("Datos_Schrodinger.txt", "w");
    fichero_norma=fopen("Datos_norma.txt", "w");


    for(j=0;j<N;j++){
        if(j>=2*N/5 && j<=3*N/5){
            V[j]=lambda*k_tilde*k_tilde; 
        }
        else{
            V[j]=0;
        }
    }
    //Contorno
    phi[0]=0;
    phi[N-1]=0;
    norma=0;
    for(j=1;j<N-1;j++){
        phi[j]=cexp(I*k_tilde*j)*exp(-8*pow((4*j-N),2)/(N*N));
        phi2[j]=cabs(phi[j])*cabs(phi[j]);
        real[j]=creal(phi[j]);
        imag[j]=cimag(phi[j]);
        norma=norma+phi2[j]/N;
        
    }
    for(j=1;j<N;j++){
        phi[j]=phi[j]/sqrt(norma);
    }
     for(j=0;j<N;j++){
            fprintf(fichero, "%d, %lf, %lf \n", j, phi2[j], V[j]);
        }
        fprintf(fichero, "\n");


    //Calculamos los valores de alpha
    alpha[N-2]=0;
    for(j=N-2;j>-1;j--){
        alpha[j-1]=-1/(alpha[j]-2+2*I/s_tilde-V[j]);
    }

    while(n<Tmax){

        betha[N-2]=0;

        calculo_betha(phip, alphap, bethap, Vp, N, s_tilde);

        //Calculamos el valor de chi una vez conocidos alpha y betha
        chi[0]=0;
        for(j=0;j<N-1;j++){
            chi[j+1]=alpha[j]*chi[j]+betha[j];
        }

        //Calculamos la función de onda en el siguiente instante 
        norma=0;
        for(j=0;j<N;j++){
            phi[j]=chi[j]-phi[j];
            phi2[j]=cabs(phi[j])*cabs(phi[j]);
            imag[j]=cimag(phi[j]);
            real[j]=creal(phi[j]);
            norma=norma+phi2[j]/N;
        }
        for(j=0;j<N;j++){
            fprintf(fichero, "%d, %lf, %lf \n", j, phi2[j], V[j]);
        }
        fprintf(fichero, "\n");

        fprintf(fichero_norma, "%lf, %d \n", norma, n);

        n=n+1;
    }

    fclose(fichero);
    fclose(fichero_norma);

    
}

void calculo_betha(double complex * phi, double complex * alpha, double complex * betha, double * V, int N, double s_tilde){
     int j;
    for(j=N-2;j>0;j--){
        *(betha+j-1)=(4*I*(*(phi+j))/s_tilde-*(betha+j))/(*(alpha+j)-2+2*I/s_tilde-*(V+j));
    }
}