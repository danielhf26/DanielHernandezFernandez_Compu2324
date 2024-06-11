#include <stdio.h>
#include <math.h>
#include "pendulo.h"


int main(){
    double y[4], k1[4], k2[4], k3[4],k4[4], a[4];
    double g=9.81;
    double psi, E, mo, pi;
    E=6;
    pi=3.1415926535;
    double t, h, Tmax;
    int i, j;

    t=0;
    h=0.001;
    Tmax=100;

    double *ap=a;
    double *yp=y;
    double *k1p=k1;
    double *k2p=k2;
    double *k3p=k3;
    double *k4p=k4;

    //Abrimos el fichero en el que vamos a escribir los datos
    FILE* fichero;
    fichero=fopen("Datos_pendulo.txt", "w");

    //las y son nuestras variables el 0 significa radio, el 1 momento de radio
    //el 2 angulo phi e 3 momento conjugadodel angulo phi

    y[0]=0.4;
    y[1]=0.0;
    y[2]=sqrt(E-2*g*(1-cos(y[0]))-g*(1-cos(y[1]))); 
    y[2]=y[2]/sqrt(2);

    

   
    y[3]=y[2]*cos(y[1]-y[0]);   
     y[2]=2*y[2];
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
       
        Ener=energia(y[0], y[1], y[2], y[3], g);

       

        if(y[1]<-pi){
            y[1]=y[1]+2*pi;
        }
        else if(y[1]>pi){
            y[1]=y[1]-2*pi;
        }

        if(y[0]<-pi){
            y[0]=y[0]+2*pi;
        }
        else if(y[0]>pi){
            y[0]=y[0]-2*pi;
        }


        fprintf(fichero,"%lf, %lf \n", y[0], y[2]);
       //fprintf(fichero, "%lf \n", Ener);
        //  fprintf(fichero, "%lf, %lf \n", -sin(y[0]), -cos(y[0]));
        //  fprintf(fichero, "%lf, %lf \n", -sin(y[0])-sin(y[1]), -cos(y[0])-cos(y[1]));
        //  fprintf(fichero, "\n");
       
        
      
       
        

    }


    


}



