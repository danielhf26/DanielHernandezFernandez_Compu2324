//CODIGO QUE REALIZA DOS SIMULACIONES A LA VE DEL PENDULO DOBLE Y CALCULA LOS COEFICIENTES DE LYAPUNOV.
//LA SIMULACION EN IGUAL QUE EN LA SIMULACIÓN DE UN SOLO PENDULO
#include <stdio.h>
#include <math.h>
#include "pendulo.h"
#include <time.h>


int main(){
    double Tmax=1000;
    double E=1;
    
    //Abrimos el fichero en el que vamos a escribir los datos
    FILE* fichero;
    
    fichero=fopen("Datos_lyapunov.txt", "w");
    while(E<16){
    
    clock_t comienzo, final;
    comienzo=clock();
    double y[4], k1[4], k2[4], k3[4],k4[4], a[4], y2[4], k21[4], k22[4], k23[4],k24[4];
    double g=9.81;
    double psi, En, mo, pi, vphi, vpsi, vphi2, vpsi2;
  

    pi=3.1415926535;
    double t, h, delta, lya, delta0;
    int i, j;

    t=0;
    h=0.001;
    

    double *ap=a;
    double *yp=y;
    double *y2p=y2;
    double *k1p=k1;
    double *k2p=k2;
    double *k3p=k3;
    double *k4p=k4;
    double *k12p=k21;
    double *k22p=k22;
    double *k23p=k23;
    double *k24p=k24;

    int cont=0;
    lya=0;

   

   
    for(j=0;j<5;j++){
    t=0;
    
    y[0]=-0.1;
    y[1]=0.2;
    y[2]=sqrt(E-2*g*(1-cos(y[0]))-g*(1-cos(y[1]))); //Calcula la velocidad phi inicial
    vphi=y[2];
    y[3]=y[2]*cos(y[1]-y[0]);  //Con esta velocidad podemos calcular el momento psi inicial 
    y[2]=2*y[2];//Multiplicando por dos conseguimos el momento phi inicial

    

    //Defiinimos las otras condiciones iniciales ligermente distintas
    y2[0]=0.2+0.0005;
    y2[1]=0.2;
    y2[2]=sqrt(E-2*g*(1-cos(y2[0]))-g*(1-cos(y2[1]))); //Calcula la velocidad phi inicial
    vphi2=y2[2];
    y2[3]=y2[2]*cos(y2[1]-y2[0]);  //Con esta velocidad podemos calcular el momento psi inicial 
    y2[2]=2*y2[2];//Multiplicando por dos conseguimos el momento phi inicial
    

    delta0=pow(y[0]-y2[0],2)+h*h*pow(vphi-vphi2,2);
    delta0=sqrt(delta0);
    
    //double Ener;
    //Ener=energia(y[0], y[1], y[2], y[3], g);
    //fprintf(fichero, "%lf \n", Ener);

    while(t<Tmax){

        for(i=0;i<4;i++){
            a[i]=0;
        }
        funcion(k1p, y2p, ap, g, h);

        for(i=0;i<4;i++){
            a[i]=k1[i]/2;
        }

        funcion(k2p, y2p, ap, g, h);


        for(i=0;i<4;i++){
            a[i]=k2[i]/2;
        }

        funcion(k3p, y2p, ap, g, h);

        for(i=0;i<4;i++){
            a[i]=k3[i];
        }

        funcion(k4p, y2p, ap, g, h);

        for(i=0;i<4;i++){
            y2[i]=y2[i]+(k1[i]+2*k2[i]+2*k3[i]+k4[i])/6;
        }


        //CIclo para la otra condicion
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
       

       //CALCULAMOS LOS COEFICIENTES DE LYAPUNOV
       vphi=momento_velocidad_phi(y[0], y[1], y[2], y[3]);
       vphi2=momento_velocidad_phi(y2[0], y2[1], y2[2], y2[3]);

       delta=pow(y[0]-y2[0],2)+h*h*pow(vphi-vphi2,2);
       delta=sqrt(delta);
       lya=lya+log(delta/delta0);
       
    
    
        

        }


    }


    //Normalizamos y metemos los coeficientes de Lypunov en un fichero
    lya=lya/Tmax;
    printf("%lf \n", E);
    fprintf(fichero,"%lf, %lf \n", lya, E);
    E=E+1; //Aumentamos la energía
   

    
    
    }
     fclose(fichero);
}




    





