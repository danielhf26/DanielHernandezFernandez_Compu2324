#include <stdio.h>
#include <gsl/gsl_rng.h>

int main(void) {
    const gsl_rng_type *T;
    gsl_rng *r;

    gsl_rng_env_setup();

    T = gsl_rng_default;
    r = gsl_rng_alloc(T);

    printf("Generando 10 números aleatorios:\n");
    for (int i = 0; i < 10; ++i) {
        double u = gsl_rng_uniform(r);
        printf("%f\n", u);
    }

    gsl_rng_free(r);

    return 0;
}