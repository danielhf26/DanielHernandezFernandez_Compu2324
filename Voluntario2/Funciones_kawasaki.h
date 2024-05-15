//Función delta energía
double energia(int* s, int N){
    double E;
    
    E=-0.5*(*s)*(*(s+1)+*(s-1)+*(s+N)+*(s-N));
    return E;
   
    

}



void intercambio(int *s, int* n ){
  int puente;
  puente=*s;
  *s=*(n);
  *(n)=puente;

}

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

double Magnetización_superior(int*s, int N){
  int i, j;
  double suma=0;
  for(i=1;i<N/2;i++){
    for(j=2;j<N+2;j++){
        suma=suma+*(s+i*(N+4)+j);
    }
  }
  suma=4*suma/(N*N);
  return suma;
}

double Magnetización_inferior(int*s, int N){
  int i, j;
  double suma=0;
  for(i=N/2;i<N-1;i++){
    for(j=2;j<N+2;j++){
        suma=suma+*(s+i*(N+4)+j);
    }
  }
  suma=4*suma/(N*N);
  return suma;
}




//Funció que calculala magnetización


//Funcion aleatoria
//int aleatory_gsl1(int n, int semilla){
  //  double x;
  //  gsl_rng*tau;
  //  tau=gsl_rng_alloc(gsl_rng_taus);
  //  gsl_rng_set(tau, semilla);
  //  x=gsl_rng_uniform_int(tau, n);


  //  gsl_rng_free(tau);

   // return x;
//}
//int aleatory_gsl2(int semilla){
  //  double x;
  //  gsl_rng*tau;
  //  tau=gsl_rng_alloc(gsl_rng_taus);
  //  gsl_rng_set(tau, semilla);
  //  x=gsl_rng_uniform(tau, n);


  //  gsl_rng_free(tau);

   // return x;
//}