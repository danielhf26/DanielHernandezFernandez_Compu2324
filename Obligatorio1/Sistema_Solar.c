#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Funciones_Sistema_Solar.h"




int main(){
    //Medir tiempo
    clock_t comienzo, final;
    comienzo=clock();
    int i, j,k;
    k=0;
    int d=2;
    int n=10;
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
    double vueltas[n][2];
    //Inicializamos un vector de vueltas que se usa más adelante para calcular el periodo
    for(i=0;i<n;i++){
        for(j=0;j<d;j++){
            vueltas[i][j]=0;
        }
    }
    double Perio[n];
    double Dias;
    
    //Leemos los datos iniciales y los colocamos en nuestros vectores de posiciones y velocidades iniciales
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
    //Años que debe durar la simulación
    double Tf=100;

    //Realizamos los reescalaminetos
    Tf=rees_tiempo(Tf);
    rees_masa(mp, n);
    rees_pos(rp, n, d);
    rees_veloc(vp, n, d);
    

    //Declaramos todos los ficheros necesatios y los abrimos
    FILE* fichero;
    FILE* fichero2;
    FILE* fichero_t;
    FILE* fichero_geo;
    fichero_t=fopen("Datos_periodos.txt", "w");
    fichero=fopen("Datos_planetas.txt","w");
    fichero2=fopen("Datos_Energia.txt", "w");
    fichero_geo=fopen("Datos_planetas_geo.txt", "w");
   
    

    //Colocamos los valores iniciales de las posiciones en el fichero
    for(i=0;i<n;i++){
        fprintf(fichero,"%f, %f \n", r[i][0], r[i][1]);
    }
     fprintf(fichero, "\n");






    //Calculmos las aceleraciones iniciales
    acel(rp,ap,mp,n, d);



    //Nos metemos en el bucle de actualización, para sacar los valores en cada tiempo segun el paso
    for(t=0;t<Tf;t=t+h){

      
    


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
        //Solo cogemos uno de cada 5 puntos para no saturar la animación
        k=k+1;
        if(k%30==0){
        for(i=0;i<n;i++){
        fprintf(fichero,"%f, %f \n", r[i][0], r[i][1]);
        }
         fprintf(fichero, "\n");
        }


        //Calculo de la energia cinetica y de la potencial
        kinetic(vp, mp, Tp, n, d);
        potential(rp,Vp, mp, n, d);

        //Calculo de la energia total, suma de las dos
        for(i=0;i<n;i++){
            E[i]=V[i]+T[i];
            
        }
        //Se sacan los valores de todas las energías y el tiempo para un planeta elegido
        fprintf(fichero2, "%f \t %f \t %f \t %f   \n",E[1], V[1], T[1], t);




       
        //Calculo del periodo
        //Contamos el numero de vueltas que da
        for(i=1;i<n;i++){
            if(r_anterior[i]<=0 && r[i][1]>=0 && t>0){
                vueltas[i][0]=vueltas[i][0]+1;
                vueltas[i][1]=t;
        
            }
        }

        //ORBITAS GEOESTACIONARIAS
        geocentro(rp, r_geop, n, d, 3);
        if(k%5==0){
        for(i=0;i<n;i++){
        fprintf(fichero_geo,"%f, %f \n", r_geo[i][0], r_geo[i][1]);
        }
        fprintf(fichero_geo, "\n");
        }

    }



    //Se divide el iempo que tarda entre le numero de vueltas que el planeta da
    //De esta forma obtenemos el periodo
    for(i=0;i<n;i++){
        Perio[i]=vueltas[i][1]/vueltas[i][0];
        Perio[i]=des_rees_tiempo(Perio[i]);
        Perio[i]=Perio[i]/365;
    }
    for(i=0;i<n;i++){
            fprintf(fichero_t, "Periodo= %lf \n", Perio[i]);
    }
    
    //Cerramos ficeros
    fclose(fichero); 
    fclose(fichero2);
    fclose(fichero_int);
    fclose(fichero_t);


    //Paramos el timepo y clculamos los segundos mostrandolos por terminal
    final=clock();
    
    double tiempo=(double)(final-comienzo)/CLOCKS_PER_SEC;

    printf("Tiempo transcurrido desde el comienzo hasta el fin del algoritmo utilizado: %lf ", tiempo);
    

    




   


}