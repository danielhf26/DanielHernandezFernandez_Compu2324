#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Funciones_Sistema_Solar.h"




int main(){
    int i, j;
    int d=2;
    int n=8;
    double a[n][d];
    double r[n][d];
    double r_anterior[n];
    double r_geo[n][d];
    double v[n][d];
    double w[n][d];
    double T[n];
    double V[n];
    double E[n];
    double m[n];
    double vueltas[2];
    vueltas[0]=0;
    vueltas[1]=0;
    double Perio=0;
    double Dias;
   
    FILE* fichero_int;
    fichero_int=fopen("Datos_init_planetas.txt", "r");
    i=0;
    while(fscanf(fichero_int, "%lf, %lf, %lf, %lf, %lf", &m[i], &r[i][0], &r[i][1], &v[i][0], &v[i][1])!=EOF){
        i++;
    }
   
    double* rp=r[0];
    double* r_geop=r_geo[0]; 
    double* r_anteriorp=r_anterior;
    double* ap=a[0];
    double* vp=v[0];
    double* wp=w[0];
    double* Tp=T;
    double* Vp=V;
    double *mp=m;
    double h=0.01;
    double t=0;
    double Tf=50;
    rees_masa(mp, n);
    rees_pos(rp, n, d);
    rees_veloc(vp, n, d);
    
    FILE* fichero;
    FILE* fichero2;
    FILE* fichero_geo;
    fichero=fopen("Datos_planetas.txt","w");
    fichero2=fopen("Datos_Energia.txt", "w");
    fichero_geo=fopen("Datos_planetas_geo.txt", "w");
   
    


    for(i=0;i<n;i++){
        fprintf(fichero,"%f, %f \n", r[i][0], r[i][1]);
    }






    //Calculmos las aceleraciones iniciales
    acel(rp,ap,mp,n, d);



    //Nos metemos en el bucle de actualización, para sacar los valores en cada tiempo segun el paso
    for(t=0;t<Tf;t=t+h){

        fprintf(fichero, "\n");
    


        //Para el calculo del periodo requerimos de un vector que guarde las posiciones del eje y anteriores
        //Lo rellenamos con las posiciones del eje y antes de ejecutar el algoritmo de Vernet    
        for(i=0;i<n;i++){
            r_anterior[i]=r[i][1];
        }
        

        //Calculo de las nuevas velocidades
        veloc(vp, ap, wp, h, n, d );

        //Calculo de las nuevas posiciones
        posic(rp, vp, ap,h, n, d );

        //Con las nuevas posiciones sacamos las nuevas aceleraciones
        acel(rp, ap, mp, n, d);

        //Con los nuevos valores de las aceleraciones calculamos las velocidades
        veloc(wp,ap,vp,h,n,d);

        

        
        //Ponemos en un fichero las posiciones de los planetas 
        for(i=0;i<n;i++){
        fprintf(fichero,"%f, %f \n", r[i][0], r[i][1]);
        }


        //Calculo de la energia cinetica y de la potencial
        kinetic(vp, mp, Tp, n, d);
        potential(rp,Vp, mp, n, d);

        //Calculo de la energia total, suma de las dos
        for(i=0;i<n;i++){
            E[i]=V[i]+T[i];
            
        }
        //fprintf(fichero2, "%f \t %f \t %f \t %f   \n",E[1], V[1], T[1], t);




       
        //Calculo del periodo
        //Requerimos de otro vector auxiliar que guarde las posiciones del momento anterior
        if(r_anterior[3]<=0 && r[3][1]>=0){
            
            Dias=t-Perio;
            Perio=t;
            Dias=des_rees_tiempo(Dias);
            fprintf(fichero2, "%f    \n",Dias);    
        }
        
        //Otra manera de calcular el periodo 
        //Contamos el numero de vueltas que da
        if(r_anterior[3]<=0 && r[3][1]>=0 && t>0){
            vueltas[0]=vueltas[0]+1;
            vueltas[1]=t;
        }


        //ORBITAS GEOESTACIONARIAS
        geocentro(rp, r_geop, n, d, 3);
        for(i=0;i<n;i++){
        fprintf(fichero_geo,"%f, %f \n", r_geo[i][0], r_geo[i][1]);
        }
        fprintf(fichero_geo, "\n");


    }



    //Se divide el iempo que tard entre le numeor de vueltas que el planeta da
    //De esta forma obtenemos también el periodo
    Perio=vueltas[1]/vueltas[0];
    Perio=des_rees_tiempo(Perio);

    fclose(fichero);
    fclose(fichero2);
    fclose(fichero_int);

    




   


}












