#include <stdio.h>
#include "gsl_rng.h"


gsl_rng *tau;
int main(void) {
    double x;
    extern gsl_rng*tau;
    int semilla=182342;
    r=gsl_rng_alloc(gsl_rng_tau);
    x=gsl_rng_uniform(tau);

    printf("%f", x);

    gsl_rng_free(tau);

    return 0;
}