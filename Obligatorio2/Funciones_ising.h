
//Función delta energía
double delta_energia(int* s, int N){
    double E;
    
    E=2*(*s)*(*(s+1)+*(s-1)+*(s+N)+*(s-N));
    return E;
   
    

}

//Funcion aleatoria
int aleatory_gsl1(int n){
    double x;
    extern gsl_rng*tau;
    int semilla=time(NULL);
    tau=gsl_rng_alloc(gsl_rng_taus);
    gsl_rng_set(tau, semilla);
    x=gsl_rng_uniform_int(tau, n);


    gsl_rng_free(tau);

    return x;
}
int aleatory_gsl2(){
    double x;
    extern gsl_rng*tau;
    int semilla=time(NULL);
    tau=gsl_rng_alloc(gsl_rng_taus);
    gsl_rng_set(tau, semilla);
    x=gsl_rng_uniform(tau, n);


    gsl_rng_free(tau);

    return x;
}