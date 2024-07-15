


//Función de energía
//Calcula la energía que posee cualquier espí de la malla
double energia(int* s, int N){
    double E;
    
    E=-0.5*(*s)*(*(s+1)+*(s-1)+*(s+N)+*(s-N));
    return E;
   
    

}


//Función que intercambia los valores de dos espines
//Pasas los punteros que deseas intercambiar y los itercambia
void intercambio(int *s, int* n ){
  int puente;
  puente=*s;
  *s=*(n);
  *(n)=puente;

}


//Funcion que realiza el intercambio de dos espines, teniendo en cuenta la direccióon en la que lo intercamibia y las condiciones de contorno
//Se le pasa el puntero del espin a intercambiar con el valor de r, el número que indica la dirección de intercambio
void intercambio_spin(int *s, int r, int N){
  if(r==0){
    intercambio(s, s-1);
  }
  if(r==1){
    intercambio(s, s+1);
  }
  if(r==2){
    intercambio(s, s-(N+4));
  }
  if(r==3){
    intercambio(s, s+(N+4));
  }   

}

//Función que comprueba si dos espines tienen el mismo signo
//Devuelve un entero si es nulo, no tienen el mismo signo, si vale 1, tienen el mismo signo
int comprobacion_spin(int *s, int r, int N){
  int a=0;

  if(r==0 && *s==*(s-1)){
    a=1;
  }
  else if(r==1 && *s==(*s+1)){
    a=1;
  }
  else if(r==2 && *s==*(s-(N+4))){
     a=1;
  }
  else if(r==3 && *s==*(s+(N+4))){
     a=1;
  } 
  return a;
}


//Función que calcula la energía de los espines de alrededor del que queremos intercambiar
//Se le pasa el puntero del espin a intercambiar junto con la posicion en la malla y la dirreción de intercambio
//Lo calculamos para los alrededores de los que queremos intercambiar ya que no es necesario calcularlo para toda la malla y ahorra tiempo de computación
double energia_total(int *s, int n, int m , int r, int N){
  int i, j;
  double E=0;
  if(r==0){
    for(i=n-1;i<=n+1;i++){
      for(j=m-2;j<m+2;j++){
        E+=energia(s+i*(N+4)+j, N+4);
      }
    }
  }
  else if(r==1){
    for(i=n-1;i<=n+1;i++){
        for(j=m-1;j<=m+2;j++){
            E+=energia(s+i*(N+4)+j, N+4);
        }
    }
  }
  else if(r==2){
    for(i=n-2;i<=n+1;i++){
        for(j=m-1;j<=m+1;j++){
            E+=energia(s+i*(N+4)+j, N+4);
        }
    }
  }
  else if(r==3){
    for(i=n-1;i<=n+2;i++){
        for(j=m-1;j<=m+1;j++){
            E+=energia(s+i*(N+4)+j, N+4);
        }
    }
  }

  return E;
}



//Función que calcula la energíapor partícual de toda la malla
//Devuelve un real con el valor de la energía
double energia_por_particula(int *s, int N){
    int i, j;
  double E=0;
  for(i=1;i<N-1;i++){
    for(j=2;j<N+2;j++){
      E=E+energia(s+i*(N+4)+j, N+4);
    }
  }
  E=E/((N)*(N)); //Hace la energía por particula
  return E;
}


//Función que calcula la magnetización en toda la malla
//Devuelve un realcon el valor de la magnetización
double Magnetización(int*s, int N){
  int i, j;
  double suma=0;
  for(i=1;i<N-1;i++){
    for(j=2;j<N+2;j++){
        suma=suma+*(s+i*(N+4)+j);
    }
  }
  suma=suma/(N*N);
  return suma;
}

//Función que calcula la magnetización en la parte superior, teneidno en cuenta el valor de x
//Devuelve el valor de la magnetización superior
double Magnetización_superior(int*s, int N, double x){
  int i, j;
  double suma=0;
  for(i=0;i<x*N;i++){
    for(j=2;j<N+2;j++){
        suma=suma+*(s+i*(N+4)+j);
    }
  }
  suma=suma/(N*N*x);
  return suma;
}

//Igual que la función anterior pero para la parte inferior
double Magnetización_inferior(int*s, int N, double x){
  int i, j;
  double suma=0;
  for(i=N-1;i>N*x;i--){
    for(j=2;j<N+2;j++){
        suma=suma+*(s+i*(N+4)+j);
    }
  }
  suma=suma/(N*N*x);
  return suma;
}


//Función que calcula la densidad de numero de espines positivos para una fila de la malla
//Devuelve un real con el valor de la densidad para esa fila
double densidad_positivo(int *s, int N){
  int i, j;
  double suma1, suma2;
  
    suma1=0;
    for(i=2;i<N+2;i++){
      if(*(s+i)==1){
        suma1=suma1+1;
      }
      
      
    }
    suma1=suma1/N;

  return suma1;

}


//Función varianza
//Calcula la varianza de un puntero
double var(double *m, double media, int N){
  int i, j;
  double var;
  var=0;

  for(i=0;i<N;i++){
    var=var+(*(m+i)-media)*(*(m+i)-media);
  }

  var=var/N;
  return var;
}

