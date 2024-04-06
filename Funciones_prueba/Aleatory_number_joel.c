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


///////COSOAS GROSAS
//Primero calculamos una matriz que contenga las distancias entre todos los planetas
    for(i=0; i<n;i++) {
//Realzamos un bucle for desde i+1, ya que es una matriz antisimetrica. (Tenemos menos grados de libertad)
        for(k=i+1;k<n;k++){
        
            R[i][k][j]=Restar_vec((r+i*n),(r+k*n),3);
           
            
        }
    }

//Ponemos los componentes de la diagoonal igual a cero
    for(i=0;i<n;i++){
        for(j=0;j<3;j++){
            R[i][i][j]=0
        }
    }
//Ponemos el resto de componentes sabiendo que son antisimétricas
    for(i=0;i<n;i++){
        for(j=0;j<i-1;j++){
            for(k=0;k<3;k++){
                R[i][j][k]=-R[j][i][k]
            }

        }
    }
}
