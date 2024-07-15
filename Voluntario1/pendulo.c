#include <stdio.h>
#include <math.h>
#include "pendulo.h"
#include <time.h>


int main(){

    //Definimos las variables necesarias
    clock_t comienzo, final;
    comienzo=clock();
    double y[4], k1[4], k2[4], k3[4],k4[4], a[4];
    double g=9.81;
    double psi, En, mo, pi, vphi, vpsi;
    double E[5];  //Se ha puesto la energíacomo un vector para poder repetir de una sola vez todas las energías
    E[0]=1;
    E[1]=3;
    E[2]=5;
    E[3]=10;
    E[4]=15;

    pi=3.1415926535;
    double t, h;
    int i, j;

    t=0;
    h=0.001;  //VALOR DEL PASO
    double Tmax=30; //VALOR DEL TIEMPO DE SIMULACIÓN

    double *ap=a;
    double *yp=y;
    double *k1p=k1;
    double *k2p=k2;
    double *k3p=k3;
    double *k4p=k4;

    int cont=0;

    //Abrimos los ficheros en los que vamos a escribir los datos
    FILE* fichero;
    FILE* fichero1;
    FILE* fichero2;
    FILE* fichero3;
    FILE* fichero4;
    FILE* fichero5;
    fichero=fopen("Datos_pendulo.txt", "w");
    fichero1=fopen("Datos_pendulo1.txt", "w");
    fichero2=fopen("Datos_pendulo2.txt", "w");
    fichero3=fopen("Datos_pendulo3.txt", "w");
    fichero4=fopen("Datos_pendulo4.txt", "w");
    fichero5=fopen("Datos_pendulo5.txt", "w");
    

   
    for(j=0;j<1;j++){//Este bucle sirve para ejecutar varias energías de una vez, si se quieren ejecutar todas variar el valorde j hasta j<5
    t=0;

    //DEFINIMOS LAS CONDICIONES INICIALES
    //las y son nuestras variables y[0] es el primer ángulo, y[1] el segundo ángulo 
    //y[2] el momento asociadoal primer ángulo, e y[3] el momento asociado al segundo ángulo

    //ANGULOS INICIALES, CONDIONES QUE SE CAMBIAN
    y[0]=0.1;
    y[1]=0.3;


    y[2]=sqrt(E[j]-2*g*(1-cos(y[0]))-g*(1-cos(y[1]))); //Calcula la velocidad phi inicial con la energía

    y[3]=y[2]*cos(y[1]-y[0]);  //Con esta velocidad podemos calcular el momento psi inicial 
    y[2]=2*y[2];//Multiplicando por dos conseguimos el momento phi inicial

    

    while(t<Tmax){//AQUÍ COMIENZA EL ALGORITMO DE RUNGE KUTTA

        for(i=0;i<1;i++){
            a[i]=0;
        }
        funcion(k1p, yp, ap, g, h); //Calcula k1

        for(i=0;i<4;i++){
            a[i]=k1[i]/2;
        }

        funcion(k2p, yp, ap, g, h); //Calcula k2


        for(i=0;i<4;i++){
            a[i]=k2[i]/2;
        }

        funcion(k3p, yp, ap, g, h); //Calcula k3

        for(i=0;i<4;i++){
            a[i]=k3[i];
        }

        funcion(k4p, yp, ap, g, h); //Calcula k4

        for(i=0;i<4;i++){
            y[i]=y[i]+(k1[i]+2*k2[i]+2*k3[i]+k4[i])/6; //Calcula el valor de las variables siguiendo runge kutta
        }

        

        t=t+h; //Subimos el paso
       

       vphi=momento_velocidad_phi(y[0], y[1], y[2], y[3]); //Calculamos la velocidad enphi si la queremos respresentar
        vpsi=momento_velocidad_psi(y[0], y[1], y[2], y[3]); //Lo mismo para psi



        //AÑADIMOS LOS DATOS AL FICHERO PARA MAPAS DE POINCARE
       if(j==0){
        //fprintf(fichero,"%lf, %lf, %lf \n", y[0], vphi);
        fprintf(fichero,"%lf, %lf \n", y[0],  y[1]);
       }
       else if(j==1){
        //fprintf(fichero2,"%lf, %lf, %lf \n", y[0],  vphi);
        fprintf(fichero2,"%lf, %lf \n", y[0],  y[1]);
       }
       else if(j==2){
        fprintf(fichero3,"%lf, %lf \n", y[0],  y[1]);
       }
       else if(j==3){
        fprintf(fichero4,"%lf, %lf \n", y[0],  y[1]);
       }
       else if(j==4){
        fprintf(fichero5,"%lf, %lf \n", y[0],  y[1]);
       }
       

       
       
        //Aqui se añaden los datos al fichero si se quiere visualizar la animación del péndulo doble
        //Se usa un coantador para coger mens datos y obtener una animación mas fluida
       if(cont%10==0){
         fprintf(fichero, "%lf, %lf \n", +sin(y[0]), -cos(y[0]));
         fprintf(fichero, "%lf, %lf \n", +sin(y[0])+sin(y[1]), -cos(y[0])-cos(y[1]));
         fprintf(fichero, "\n");
       }
       cont=cont+1;
        
      
       
        

        }//FIN DEL BUCLE DE RUNGE KUTTA


    }//FIN DEL BUCLE DE LAS ENERGIAS


    //Cerramos los ficeros y calculamos el tiempo de ejecución
    fclose(fichero2);
    fclose(fichero3);
    fclose(fichero4);
    fclose(fichero5);
    fclose(fichero);
    fclose(fichero1);

    final=clock();
    
    double tiempo=(double)(final-comienzo)/CLOCKS_PER_SEC;

    printf("Tiempo transcurrido desde el comienzo hasta el fin del algoritmo utilizado: %lf, %lf \n", tiempo, Tmax);
    
    
}




    





