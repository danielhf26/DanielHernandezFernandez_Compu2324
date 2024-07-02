#include <stdio.h>
#include <math.h>
#include "pendulo.h"
#include <time.h>


int main(){
    clock_t comienzo, final;
    comienzo=clock();
    double y[4], k1[4], k2[4], k3[4],k4[4], a[4];
    double g=9.81;
    double psi, En, mo, pi, vphi, vpsi;
    double E[5];
    E[0]=1;
    E[1]=3;
    E[2]=5;
    E[3]=10;
    E[4]=14.8;

    pi=3.1415926535;
    double t, h, Tmax;
    int i, j;

    t=0;
    h=0.00001;
    Tmax=30;

    double *ap=a;
    double *yp=y;
    double *k1p=k1;
    double *k2p=k2;
    double *k3p=k3;
    double *k4p=k4;

    int cont=0;

    //Abrimos el fichero en el que vamos a escribir los datos
    FILE* fichero;
    FILE* fichero2;
    FILE* fichero3;
    FILE* fichero4;
    FILE* fichero5;
    fichero=fopen("Datos_pendulo.txt", "w");
    fichero2=fopen("Datos_pendulo2.txt", "w");
    fichero3=fopen("Datos_pendulo3.txt", "w");
    fichero4=fopen("Datos_pendulo4.txt", "w");
    fichero5=fopen("Datos_pendulo5.txt", "w");

    //las y son nuestras variables el 0 significa radio, el 1 momento de radio
    //el 2 angulo phi e 3 momento conjugadodel angulo phi
    for(j=0;j<2;j++){
    t=0;
    
    y[0]=0.1;
    y[1]=0.22;
    y[2]=sqrt(E[j]-2*g*(1-cos(y[0]))-g*(1-cos(y[1]))); //Calcula la velocidad phi inicial

    y[3]=y[2]*cos(y[1]-y[0]);  //Con esta velocidad podemos calcular el momento psi inicial 
    y[2]=2*y[2];//Multiplicando por dos conseguimos el momento phi inicial

    double Ener;
    Ener=energia(y[0], y[1], y[2], y[3], g);
    //fprintf(fichero, "%lf \n", Ener);

    while(t<Tmax){

        for(i=0;i<4;i++){
            a[i]=0;
        }
        funcion(k1p, yp, ap, g, h);

        for(i=0;i<4;i++){
            a[i]=k1[i]/2;
        }

        funcion(k2p, yp, ap, g, h);


        for(i=0;i<4;i++){
            a[i]=k2[i]/2;
        }

        funcion(k3p, yp, ap, g, h);

        for(i=0;i<4;i++){
            a[i]=k3[i];
        }

        funcion(k4p, yp, ap, g, h);

        for(i=0;i<4;i++){
            y[i]=y[i]+(k1[i]+2*k2[i]+2*k3[i]+k4[i])/6;
        }

        

        t=t+h;
       
        //Ener=energia(y[0], y[1], y[2], y[3], g);

       //vphi=momento_velocidad_phi(y[0], y[1], y[2], y[3]);
    
       if(j==0){
        fprintf(fichero,"%lf, %lf \n", y[0], y[1]);
       }
       else if(j==1){
        fprintf(fichero2,"%lf, %lf \n", y[0], y[1]);
       }
       else if(j==2){
        fprintf(fichero3,"%lf, %lf \n", y[0], y[1]);
       }
       else if(j==3){
        fprintf(fichero4,"%lf, %lf \n", y[0], y[1]);
       }
       else if(j==4){
        fprintf(fichero5,"%lf, %lf \n", y[0], y[1]);
       }
       

       // vpsi=momento_velocidad_psi(y[0], y[1], y[2], y[3]);
       
     
       // fprintf(fichero, "%lf \n", Ener);
    //    if(cont%10==0){
    //      fprintf(fichero, "%lf, %lf \n", +sin(y[0]), -cos(y[0]));
    //      fprintf(fichero, "%lf, %lf \n", +sin(y[0])+sin(y[1]), -cos(y[0])-cos(y[1]));
    //      fprintf(fichero, "\n");
    //    }
    //    cont=cont+1;
        
      
       
        

        }


            printf("hola");
    }

    fclose(fichero2);
    fclose(fichero3);
    fclose(fichero4);
    fclose(fichero5);
    fclose(fichero);

    final=clock();
    
    double tiempo=(double)(final-comienzo)/CLOCKS_PER_SEC;

    printf("Tiempo transcurrido desde el comienzo hasta el fin del algoritmo utilizado: %lf ", tiempo);
    
}

    





