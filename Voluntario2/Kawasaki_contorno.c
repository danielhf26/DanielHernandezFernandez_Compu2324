#include <stdio.h>
//#include "gsl_rng.h"
#include "Funciones_kawasaki.h"
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>



int main(){

    //DEFINIMOS LAS VARIABLES QUE SE VAN A UTILIZAR
    clock_t comienzo, final;
    comienzo=clock();
    srand(time(NULL));
    int semilla=time(NULL);
    int N=16;  //TAMAÑO DE LA MALLA
    int i, j, k, ij, check, t;
    int m, n, r;
    double E, E2, Eprom, Epromsqrt, expo, T, p, xi, cn;
    double mag, mag_superior, mag_inferior;
    double densidad=0;
    double delta_E;
    int cont=0;
    double h, Tmax;
    double x;
    
    double var_inf, var_sup, var_mag, var_ener, var_densidad;
    int aux;

    FILE* fichero_out;
    FILE *fichero_magnetizacion;
    FILE *fichero_densidades;
    FILE* fichero_energias;
    fichero_out=fopen("Datos_kawasaki.txt", "w");
    fichero_magnetizacion=fopen("Datos_magnetizacion.txt", "w");
    fichero_densidades=fopen("Datos_densidades5.txt", "w" );
    fichero_energias=fopen("Datos_energias.txt", "w" );

    mag=0;
    mag_superior=0;
    mag_inferior=0;
    
    int s[N][N+4];
    int a;
    
  
    //Imponemos las condiciones de contorno de espines positivos arriba y negativos abajo
    for(i=0;i<N+4;i++){
        s[0][i]=1;
        s[N-1][i]=-1;
    }


   int* sp=s[0];


    Tmax=10000; //Numero de pasos montecarlo.

    a=5000; // Esta variable sirve para empezar a calcular las propiedades (como energia o magnetización) una vez psado cierto numero de pasos montecarlo

    int tmag=Tmax-a;
    double v_mag[tmag],v_mag_sup[tmag], v_mag_inf[tmag], Ener[tmag], Enersqr[tmag], dens[N];
    double* magp=v_mag;
    double* magp_sup=v_mag_sup;
    double* magp_inf=v_mag_inf;
    double* Enerp=Ener;
    double* densp=dens;
    
    h=1;
    t=0;

    T=1; //TEMPERTURA DE LA MALLA
   while(T<1.1){//Este bucle nos permite realizar simulaciones para varias temperaturas seguidas

    //PATRON INICIAL UTILIZADO EN EL APARTADO CON MAGNETIZACION NULA
     for(i=0;i<N;i++){
        for(j=2;j<N+2;j++){
            if(i%2==0){
                s[i][j]=1;
            }

            else{
                s[i][j]=-1;
            }
        }
    }

    //PATRON UTILIZADO EN EL APARTADO DE MAGNETIZACION NO NULA
    // for(i=0;i<N;i++){
        
    //     for(j=2;j<N+2;j++){
    //         if(i==0){
    //             s[i][j]==1;
    //         }
    //         else if(i==N-1){
    //             s[i][j]==-1;
    //         }
    //         else if((i+j)%3==0){
    //             s[i][j]=-1;
    //         }
    //         else{
    //             s[i][j]=+1;
    //         }
    //     }
    // }

    x=Magnetización(sp, N);
    x=(1+x)/2; //Calculamos el valor de x tal y como pone en el guión para saber como dividir a magnetizacion por bloques

        //Ponemos los datos iniciales en un fichero de espines
        for(i=0;i<N;i++){
                for(j=2;j<N+1;j++){
                    fprintf(fichero_out, "%d, ", s[i][j]);
                }
                fprintf(fichero_out, "%d", s[i][N+1]);
                fprintf(fichero_out, "\n");
            }
            fprintf(fichero_out, "\n");


        t=0;
        while(t<Tmax){//COMIENZA EL PASO MONTECARLO
           
            
            for(ij=1;ij<N*N;ij++){//Este bucle se correspone con un paso montecarlo


                //Nuestra matriz es dos filas y dos columnas más grande 
                //De esta forma podemos imponer las condiciones de contorno periodicas de la siguiente forma
                for(k=0;k<N; k++){
            
                s[k][1]=s[k][N+1];
                s[k][N+2]=s[k][2];
                s[k][0]=s[k][N];
                s[k][N+3]=s[k][3];
                
                }
                
                
                //Elegimos el punto incial de la matriz
                //n indica la fila y m la columna
                n=rand() % (N-2)+1;
                m=rand() % N+2;
            
                

                //Escogemos también al vecino
                //Para ello generamos un numero aleatorio entre 0 y 3
                //Si sale 0 interpretamos que cambia con el de la izquierda
                //Si sale 1 cambia con la derecha
                //Si sale 2 cambia con el de arriba
                //Si sale 3 cambia con el de abajo
                if(n==1){
                    r=(rand()%3);
                    if(r==2){
                        r=3;
                    }
                }
                else if(n==N-2){
                    r=rand()%3;
                   
                }
                else{
                r=(rand() % 4);
                
                }
                

                //Esta funcion nos permite comprobar si los dos espines elegidos tienen el mismo signo
                check=comprobacion_spin(sp+n*(N+4)+m, r, N);

                //Ejecutamos el codigo si y solo si los espines que se quieren intercambiar tienen diferente espin
                //De lo contrario no afectaría en nada su intercambio, por lo que lo dejamos igual
                //Eto ayuda notablemente al rendimiento del código
                if(check==0){

                    
                            
                    
                    //Calculamos la energía de los valores cercanos a nuestro valor
                    //Solo a los valores cercanos ya que son los únicos que van a cambiar la energía
                    E=energia_total(sp, n, m, r, N);

                    //Realizamos el cambio de valores para ver como afecta a la energía
                    intercambio_spin(sp+n*(N+4)+m, r, N);

                    //Calculamos la energía en la nueva posición
                    E2=energia_total(sp, n, m, r, N);
                
                
                //Calculamos la variación de la energía y la exponencial
                    delta_E=E2-E;

                    expo=exp(-delta_E/T);

                    //Le asignamos el valor correspondiente a p
                    if(1<expo){
                        p=1;
                    }
                    else{
                        p=expo;
                    }
                    
                    //Generamos un numero aleatorio 
                    xi=rand();
                    xi=xi/RAND_MAX;
                    //Comprobamos si se cumple la condición de cambio
                    if(xi>p){
                        //Si no se cumple deshacemos el intercambio
                        intercambio_spin(sp+n*(N+4)+m, r, N);
                    }
                    else{
                        //Si se cumple nos aseguramos que las condiciones de contorno se cumplan correctamente
                        if(m==2 && r==0){
                            s[n][N+1]=s[n][1];
                        }
                        if(m==N+1 && r==1){
                            s[n][2]=s[n][N+2];
                        }
                    }
                        
                    }
                
                }//FINAL DE UN PASO MONTECARLO
                
                
            
        
            //Cálculo de la magnetización de la malla, superior e inferior y la energía
            //Los datos los metemos en un vector
            if(t>a){
            Ener[t-a]=energia_por_particula(sp, N);
            v_mag[t-a]=Magnetización(sp, N);
            v_mag_sup[t-a]=Magnetización_superior(sp, N, x);
            v_mag_inf[t-a]=Magnetización_inferior(sp, N, x);


            //Cálculo de la densidad en el eje y
            for(i=0;i<N;i++){
                dens[i]=dens[i]+densidad_positivo(sp+i*(N+4), N);

            }
            }
            


            
                
            //Escribimos los datos obtenidos en un fichero
            if(cont%10==0){
            for(i=0;i<N;i++){
                for(j=2;j<N+1;j++){
                    fprintf(fichero_out, "%d, ", s[i][j]);
                }
                fprintf(fichero_out, "%d", s[i][N+1]);
                fprintf(fichero_out, "\n");
            }
            fprintf(fichero_out, "\n");
        
            }
            cont=cont+1;
            //Aumentamos en 1 el paso montecarlo
            t+=1;
        }//FINAL DE TODOS LOS PASOS MONTECARLO

        //Calculamos la energía promedio por particula
        Eprom=0;
        for(i=0;i<Tmax-a;i++){
            Eprom=Eprom+Ener[i];
        }
        Eprom=Eprom/(Tmax-a);    
 

        //A continuacion calculamos las varianzas de la energía y lo añadimos a un fichero
         var_ener=var(Enerp, Eprom, Tmax-a);
         var_ener=3*sqrt(var_ener/(Tmax-a));
         fprintf(fichero_energias, "%lf, %lf, %lf \n", T, Eprom, var_ener);



        //CALCULAMOS LA MAGNETIZACION PROMEDIO
        mag=0;
        mag_inferior=0;
        mag_inferior=0;
        for(i=0;i<Tmax-a;i++){
            mag=mag+v_mag[i];
            mag_inferior+=v_mag_inf[i];
            mag_superior+=v_mag_sup[i];
        }


        //CALCULO DE LA MAGNETIZACION Y VARIANZAS
        mag=mag/(Tmax-a);
        mag_inferior=mag_inferior/(Tmax-a);
        mag_superior=mag_superior/(Tmax-a);
        var_inf=var(magp_inf, mag_inferior, Tmax-a);
        var_inf=3*sqrt(var_inf/(Tmax-a));
        var_sup=var(magp_sup, mag_superior, Tmax-a);
        var_sup=3*sqrt(var_sup/(Tmax-a));
        fprintf(fichero_magnetizacion, " %lf \t %lf \t %lf \t %lf \t %lf \t %lf \n ", T, mag, mag_inferior, var_inf,mag_superior, var_sup);



        //CALCULO DE LA DENSIDAD PROMEDIO

        for(i=0;i<N;i++){
        dens[i]=dens[i]/tmag;  
        fprintf(fichero_densidades,"%d, %lf \n", i+1, dens[i]);
        }

        
    
        T=T+0.2;//Aumentamos el valor de la temperatura cuanto deseemos
        
    
    }//FIN DEL BUCLE DE TEMPERATURAS


    //CERRAMOS FICHEROS
    fclose(fichero_out);
    fclose(fichero_magnetizacion);
    fclose(fichero_energias);
    fclose(fichero_densidades);


    //Calculamos el tiempo de ejecución y lo mostramos por pantalla
    final=clock();
    
    double tiempo=(double)(final-comienzo)/CLOCKS_PER_SEC;

    printf("Tiempo transcurrido desde el comienzo hasta el fin del algoritmo utilizado: %lf, %d \n", tiempo, N);
    
    
}