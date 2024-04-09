
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//Función que calcula el módulo de un vector
//Se le pasa el puntero apuntando al inicio del vector, y la dimensión de este
double Modulo_vectores( double* v1, int n){
    int i;
    double mod;
    mod=0;
    for(i=0; i<n; i++){
        //Tenemos punteros que se van actualizando al sumar 1, esto cambia el valor de el vector a cada paso
        mod=mod + (*(v1+i))*(*(v1+i));
    }

    mod=sqrt(mod);

    return mod;
}



//Funcion que resta dos vectores
//Se pasan dos vectores en forma de puntero un tercero que será el valor de la resta, y la dimensión de ambos
void Restar_vec( double* v1, double* v2, double* res, int n){

    int i;
    for(i=0; i<n; i++){
        //Tenemos punteros que se van actualizando al sumar 1, esto cambia el valor de el vector a cada paso
        *(res+i)=*(v1+i)-*(v2+i);
    }
}


//Funcion que calcula el valor de la aceleración de cada planeta en cada uno de sus ejes
//Se le pasan los punteros de las posiciones de los planetas, el de la aceleracion(que sera el resultado)
//el puntero con las masas, el numero de planetas, y las dimensiones en las que se está trabajando
void acel(double* r, double* a, double* m, int n, int d){
    int i, j, k;
    double res[n];
    double ac[n][d];
    double R[n][n][d];
    double* resta=res;
    double* Res=R[0][0];
    double mod, prueba;


    //Primero calculamos una matriz que contenga las distancias entre todos los planetas
    for(i=0; i<n;i++){
    //Realzamos un bucle for desde i+1, ya que es una matriz antisimetrica. (Tenemos menos grados de libertad)
        for(k=i+1;k<n;k++){
        
           
            Restar_vec((r+i*d),(r+k*d), resta,d);

            for(j=0;j<d;j++){
                R[i][k][j]=*(resta+j);
            }
            
            
        }
    }

    //Ponemos los componentes de la diagoonal igual a cero
    for(i=0;i<n;i++){
        for(j=0;j<d;j++){
            R[i][i][j]=0;
        }
    }
    //Ponemos el resto de componentes sabiendo que son antisimétricas
    for(i=1;i<n;i++){
        for(j=0;j<=i-1;j++){
            for(k=0;k<d;k++){
                R[i][j][k]=-R[j][i][k];
            }

        }
    }


    //Inicializamos ac
    for(i=0;i<n;i++){
        for(j=0;j<d;j++){
            ac[i][j]=0;
        }
    }


    //Una vez obtenida la matiz de vectores simplemente utilizamos la formula para calcular la aceleracion.


    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            //Descartamos el valor de i=j de la sumatoria
            if(i!=j){
                mod=Modulo_vectores((Res+j*d+i*n*d),d);
                for(k=0;k<d;k++){
                    //Descartamos los valores que hagan 0 a R ya que sabemos que el resultado será cero (lo hacemos para evitar problemas al dividir por 0)
                    
                    //Calculamos la aceleracion con la formula
                    ac[i][k]=ac[i][k]-(*(m+j)*R[i][j][k])/(pow(mod,3));
                    prueba=*(m+j);
                    
                    
                }
            }


        }
    }

    //Por ultimo pasamos los valores de la matriz al puntero a
    for(i=0;i<n;i++){
        for(j=0;j<d;j++){
            *(a+j+i*d)=ac[i][j];
        }
    }



}


//Funcion que calcula la velocidad aproximada que llevanlos planetas segun el algoritmo de vernet.
//Se le pasa el puntero de velocidades, el de aceleraciones, el puntero de las nuevas velocidades (resultado)
//el paso con el que quieres que se calcule, el numero de planetas y la dimension en la que se trabaje
void veloc(double* v, double* a, double*w, double h, int n, int d){
    int i, j;
    for(i=0;i<n;i++){
        for(j=0;j<d;j++){
            //Calculamos cada componente de la nueva velocidad siguiendo el algoritmo de vernet
            *(w+i*d+j)=*(v+i*d+j)+*(a+i*d+j)*h/2;
        }
    }

}


//Funcion que calcula la posicion de los planetas despues de un pequeño paso segun algoritmo de vernet
//Se le pasa el puntero de las posiciones, velocidades y aceleraciones
//El paso h que se quiere, el numero de planetas y la dimension en la que se trabaja
void posic(double* r, double* v, double* a, double h, int n , int d){
    int i, j;
    for(i=0;i<n;i++){
        for(j=0;j<d;j++){
            //Calculamos cada nueva componente de la posicion siguiendo el algoritmo de vernet
            *(r+i*d+j)=*(r+i*d+j)+h*(*(v+i*d+j))+h*h*(*(a+i*d+j))/2;
        }
    }
}


//Función que calcula la energía cinetica de un planeta
//S ele pasa el puntero de las velocidades, masas y en el que se quiere guardar la energia cinetica
//Se pasa tambien el numero de planetas y la dimension
void kinetic(double *v, double *m, double *T, int n, int d){
 int i, j;
  for(i=0;i<n;i++){
    
        //Inicializamos a cero la energia cinetica 
        *(T+i)=0;
        
    }
    for(i=0;i<n;i++){
        for(j=0;j<d;j++){
            //Formula de la energia cinetica
            *(T+i)+=(*(v+i*d+j))*(*(v+i*d+j))/2;
        }
    }
}  




//Funcion que calcula el valor de el potencial de cada planeta respecto a los demás
//Se le pasan los punteros de las posiciones de los planetas, el de la energía potencial(que sera el resultado)
//el puntero con las masas, el numero de planetas, y las dimensiones en las que se está trabajando
void potential(double* r, double* Vp, double* m, int n, int d){
    int i, j, k;
    double res[n];
    double V[n];
    double R[n][n][d];
    double* resta=res;
    double* Res=R[0][0];
    double mod, prueba;


    //Primero calculamos una matriz que contenga las distancias entre todos los planetas
    for(i=0; i<n;i++){
    //Realzamos un bucle for desde i+1, ya que es una matriz antisimetrica. (Tenemos menos grados de libertad)
        for(k=i+1;k<n;k++){
        
           
            Restar_vec((r+i*d),(r+k*d), resta,d);

            for(j=0;j<d;j++){
                R[i][k][j]=*(resta+j);
            }
            
            
        }
    }

    //Ponemos los componentes de la diagoonal igual a cero
    for(i=0;i<n;i++){
        for(j=0;j<d;j++){
            R[i][i][j]=0;
        }
    }
    //Ponemos el resto de componentes sabiendo que son antisimétricas
    for(i=1;i<n;i++){
        for(j=0;j<=i-1;j++){
            for(k=0;k<d;k++){
                R[i][j][k]=-R[j][i][k];
            }

        }
    }


    //Inicializamos ac
    for(i=0;i<n;i++){
        
        V[i]=0;
        
    }


    //Una vez obtenida la matiz de vectores simplemente utilizamos la formula para calcular la aceleracion.


    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            //Descartamos el valor de i=j de la sumatoria
            if(i!=j){
                mod=Modulo_vectores((Res+j*d+i*n*d),d);
                
                //Descartamos los valores que hagan 0 a R ya que sabemos que el resultado será cero (lo hacemos para evitar problemas al dividir por 0)
                
                //Calculamos la aceleracion con la formula
                V[i]=V[i]-(*(m+j))/(mod);
                    
                
                    
                
            }


        }
    }

    //Por ultimo pasamos los valores de la matriz al puntero a
    for(i=0;i<n;i++){
        
        *(Vp+i)=V[i];
        
    }



}




//Función que renormaliza los valores de las masas de los planetas
//Se le pasa el puntero de las masas de los planetas y el numero de planetas
//Devuelve el puntero de los planetas renormalizado por la masa solar
void rees_masa(double* m, int n){
    int i;
    double Ms=1.99e30;
    //Iteramos el numero de planetas y dividimos por la masa solar
    for(i=0;i<n;i++){
        *(m+i)=*(m+i)/Ms;
    }
}
 


//Función que reescala los valores de la distancia de los planetas
//Se le pasa el puntero co las distancias en metros, la dimensión, y el número de planetas
//Devuelve el mismo puntero reescalado por la distancia tierra-sol
void rees_pos(double* r, int n, int d){
    int i, j;
    double c=1.496e11;
    //iteramos numero de planetas
    for(i=0;i<n;i++){
        //Iteramos la dimensión
        for(j=0;j<d;j++){
            //Realizamos el reesclamiento
            *(r+i*d+j)=*(r+i*d+j)/c;
        }
    }
}





//Función que reescala velocidades de los planetas
//Se le pasa el puntero de las velocidades en metros por segundo, la dimensión y el número de planetas
//Devuelve el mismo puntero de velocidades reescalado
void rees_veloc(double* v, int n, int d){
    int i, j;
    double G=6.67e-11;
    double Ms=1.99e30;
    double c=1.496e11;
    double f;
    f=sqrt(c/(G*Ms));
    for(i=0;i<n;i++){
        for(j=0;j<d;j++){
            //Reescalamiento de velocidad
            *(v+i*d+j)=*(v+i*d+j)*f;
        }
    }

}


//Funion que reescala el tiempo
//Se le pasa el valor del tiempo que se desea reescalar
//Devuelve el valor del tiempo en días
double des_rees_tiempo(double t){
    double G=6.67e-11;
    double Ms=1.99e30;
    double c=1.496e11;
    double trees;
    trees=sqrt((c*c*c)/(G*Ms))*t;
    trees=trees/(3600*24);
    return trees;
    
}



//Función que ace un cambio en las posiciones al modelo geocéntrico

void geocentro(double *r,double *r_geo, int n , int d, int p){
    int i, j;
    for (i=0;i<n;i++){
        for(j=0;j<d; j++){
            *(r_geo+i*d+j)=*(r+i*d+j)-*(r+p*d+j);
        }
    }
}
