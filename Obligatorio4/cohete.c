#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cochete.h"



int main(){
    //Definimos las variables necesarias
    double y[4], k1[4], k2[4], k3[4], k4[4], a[4], pos_x[3], pos_y[3];
    double G=6.67e-11;
    double m=10;
    double Delta, mu, r_prima, omega, t, Mt, Ml, H_prime, r_prime;
    double dtl;
    double h, Tmax;
    int i, cont;

    //Valores de masa de la luna y la tierra y calculo de la masa reducida 
    Ml=0.07349e24;
    Mt=5.9736e24;
    mu=Ml/Mt;

    //Distancia tierra lna y velocidad de rotacion de la luna
    dtl=3.844e8;
    omega=2.6617e-6;

    //Cálculo del valor de delta
    Delta=G*Mt/pow(dtl, 3);

    t=0;
    //Paso
    h=200;
    //Tiempo de duración de la simulación
    Tmax=1000000;


    //Inicializamos los vectores posición. Si i=0 es tierra, si i=1 luna y si i=2 cohete
    for(i=0;i<3;i++){
        pos_x[i]=0;
        pos_y[i]=0;
    }


    double *ap=a;
    double *yp=y;
    double *k1p=k1;
    double *k2p=k2;
    double *k3p=k3;
    double *k4p=k4;

    //Abrimos el fichero en el que vamos a escribir los datos
    FILE* fichero;
    fichero=fopen("Datos_cohete.txt", "w");

    //las y son nuestras variables el 0 significa radio, el 1 momento del radio
    //el 2 angulo phi e 3 momento conjugado del angulo phi

    y[0]=6378160;
    y[1]=11100;
    y[2]=3.14159265/4.15 ;
    y[3]=1.11e2;


    //Las reescalamos

    y[3]=y[3]/pow(dtl, 2);
    y[0]=y[0]/dtl;
    y[1]=y[1]/dtl;
    

    cont=0;
    //Iniciamos el bucle temporal
    while(t<Tmax){


        //Se ha definido un nuevo vector que nos permita relizar más facilmente el algoritmo de runge kutta (a[i])
        //Para el cálculo de k1 este vector es nulo
        for(i=0;i<4;i++){
            a[i]=0;
        }

        //Calculamos k1
        funcion(k1p, yp, ap, Delta, mu, omega, h, t);

        //Para el calculo de k2 el vector es k1/2
        for(i=0;i<4;i++){
            a[i]=k1[i]/2;
        }

        //Calculamos k2
        funcion(k2p, yp, ap, Delta, mu, omega, h, t+h/2);

        //Para el calculo de k3 es k2/2
        for(i=0;i<4;i++){
            a[i]=k2[i]/2;
        }

        //Calculamos k3
        funcion(k3p, yp, ap, Delta, mu, omega, h, t+h/2);

        //Para el calculo de k4 es k3
        for(i=0;i<4;i++){
            a[i]=k3[i];
        }

        //Calculamos k4
        funcion(k4p, yp, ap, Delta, mu, omega, h, t+h);


        //Calculamos los nuevos valores de las coordenanadas y momentos generalizados siguiendo el algoritmo runge kutta

        for(i=0;i<4;i++){
            y[i]=y[i]+(k1[i]+2*k2[i]+2*k3[i]+k4[i])/6;
        }

        
        t=t+h;


        //Calculamos las posiciones x e y de la luna y el cochete
        pos_x[2]=y[0]*cos(y[2]);
        pos_y[2]=y[0]*sin(y[2]);
        pos_x[1]=cos(omega*t);
        pos_y[1]=sin(omega*t);


        //Para reducir el número de datos se ha puesto un contador de manera que solo recoge 1 de cada 5 datos
        //Esto no afecta a la precisión de la simulación solo a la fluidez del video
        if(cont%5==0){

        for(i=0;i<3;i++){
            fprintf(fichero, "%lf, %lf \n", pos_x[i], pos_y[i]);
        }
        fprintf(fichero, "\n");
        }
        
        cont=cont+1;
        

    }//Fin del bucle temporal

    //Cerramos fichero
    fclose(fichero);


}