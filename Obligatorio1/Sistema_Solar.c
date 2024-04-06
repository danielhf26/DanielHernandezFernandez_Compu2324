#include <stdio.h>
#include <stdlib.h>
#include "Funciones_Sistema_Solar.h"




int main(){
    int i, j;
    int d=2;
    int n=4;
    double a[n][d];
    double r[n][d];
    double v[n][d];
    double w[n][d];
    double T[n];
    double V[n];
    double E[n];
    double m[n];
    m[0]=0.000003;
    
    m[1]=1;
    
    m[2]=0.0000003211;
    m[3]=0.00095376;
    
    r[0][0]=1;
    r[0][1]=0;
    
    r[1][0]=0;
    r[1][1]=0;

    r[2][0]=1.52;
    r[2][1]=0;

    r[3][0]=5.2;
    r[3][1]=0;
   

    v[0][0]=0;
    v[0][1]=0.8;
    
    v[1][0]=0;
    v[1][1]=0;

    v[2][0]=0;
    v[2][1]=0.8;

    v[3][0]=0;
    v[3][1]=0.438775;
    //v[3][1]=0.2;
   
    double* rp=r[0];
    double* ap=a[0];
    double* vp=v[0];
    double* wp=w[0];
    double* Tp=T;
    double* Vp=V;
    double *mp=m;
    double h=0.05;
    double t=0;
    double Tf=100;
    
    FILE* fichero;
    FILE* fichero2;
    fichero=fopen("Datos_planetas.txt","w");
    fichero2=fopen("Datos_Energia.txt", "w");
    if(fichero==NULL){
        printf("Error al abrir el rchivo \n");

    }
    

    fprintf(fichero, "%f, %f \n", r[0][0], r[0][1]);
    fprintf(fichero, "%f, %f \n",r[1][0], r[1][1]);
    fprintf(fichero, "%f, %f \n",r[2][0], r[2][1]);
    fprintf(fichero, "%f, %f \n",r[3][0], r[3][1]);






    //Calculmos las aceleraciones iniciales
    acel(rp,ap,mp,n, d);



    //Nos metemos en el bucle de actualización, para sacar los valores en cada tiempo segun el paso
    for(t=0;t<Tf;t=t+h){

        fprintf(fichero, "\n");
        

        //Calculo de las nuevas velocidades
        veloc(vp, ap, wp, h, n, d );

        //Calculo de las nuevas posiciones
        posic(rp, vp, ap,h, n, d );

        //Con las nuevas posiciones sacamos las nuevas aceleraciones
        acel(rp, ap, mp, n, d);

        //Con los nuevos valores de las aceleraciones calculamos las velocidades
        veloc(wp,ap,vp,h,n,d);

        

        fprintf(fichero, "%f, %f \n", r[0][0], r[0][1]);
        fprintf(fichero, "%f, %f \n",r[1][0], r[1][1]);
        fprintf(fichero, "%f, %f \n",r[2][0], r[2][1]);
        fprintf(fichero, "%f, %f \n",r[3][0], r[3][1]);

        kinetic(vp, mp, Tp, n, d);
        potential(rp,Vp, mp, n, d);

        for(i=0;i<n;i++){
            E[i]=V[i]+T[i];
            
        }
        fprintf(fichero2, "%f \t %f \t %f \t %f   \n",E[0], V[0], T[0], t);

    }

    fclose(fichero);

    




   


}












