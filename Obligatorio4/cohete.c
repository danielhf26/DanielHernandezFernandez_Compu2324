#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cochete.h"



int main(){
    double y[4], k1[4], k2[4], k3[4], k4[4], a[4], pos_x[3], pos_y[3];
    double G=6.67e-11;
    double m=10;
    double Delta, mu, r_prima, omega, t, Mt, Ml, H_prime, r_prime;
    double dtl;
    double h, Tmax;
    int i, cont;


    Ml=0.07349e24;
    Mt=5.9736e24;
    mu=Ml/Mt;

    dtl=3.844e8;
    omega=2.6617e-6;

    Delta=G*Mt/pow(dtl, 3);

    t=0;
    h=200;
    Tmax=1000000;

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

    //las y son nuestras variables el 0 significa radio, el 1 momento de radio
    //el 2 angulo phi e 3 momento conjugadodel angulo phi

    y[0]=6378160;
    y[1]=11100;
    y[2]=3.14159265/4.15 ;
    y[3]=1.11e2;

    y[3]=y[3]/pow(dtl, 2);
    y[0]=y[0]/dtl;
    y[1]=y[1]/dtl;
    

    cont=0;
    while(t<Tmax){

        for(i=0;i<4;i++){
            a[i]=0;
        }
        funcion(k1p, yp, ap, Delta, mu, omega, h, t);

        for(i=0;i<4;i++){
            a[i]=k1[i]/2;
        }

        funcion(k2p, yp, ap, Delta, mu, omega, h, t+h/2);


        for(i=0;i<4;i++){
            a[i]=k2[i]/2;
        }

        funcion(k3p, yp, ap, Delta, mu, omega, h, t+h/2);

        for(i=0;i<4;i++){
            a[i]=k3[i];
        }

        funcion(k4p, yp, ap, Delta, mu, omega, h, t+h);

        for(i=0;i<4;i++){
            y[i]=y[i]+(k1[i]+2*k2[i]+2*k3[i]+k4[i])/6;
        }

        r_prime=sqrt(1+y[0]*y[0]-2*y[0]*cos(y[2]-omega*t));
        H_prime=y[1]*y[1]/2+y[3]*y[3]/(2*y[0]*y[0])-1/y[0]-Delta*mu/r_prime;

        t=t+h;

        pos_x[2]=y[0]*cos(y[2]);
        pos_y[2]=y[0]*sin(y[2]);
        pos_x[1]=cos(omega*t);
        pos_y[1]=sin(omega*t);

        if(cont%5==0){

        for(i=0;i<3;i++){
            fprintf(fichero, "%lf, %lf \n", pos_x[i], pos_y[i]);
        }
        fprintf(fichero, "\n");
        }
        
        cont=cont+1;
        

    }


    


}