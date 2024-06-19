#include <math.h>


//Funcion que calcula el valor del radio, según ecuaciones de Hamilton
//Se le pasa el momento conjugado del radio
//devuelve un real con el valor del radio en ese instante
double f_radio(double pr){
    double f;
    f=pr;
    return f;
}


//Funcion que calcula el valor phi, según ecuaciones de Hamilton
//Se le pasa la distancia cohete-tierra y el momento conjugado del ángulo
//devuelve un real con el valor del angulo en ese instante
double f_phi(double pphi, double r){
    double f;
    f=pphi/(r*r);
    return f;
}


//Funcion que calcula el momento del radio, según ecuaciones de Hamilton
//Se le pasa el angulo tierra-cohete, la distancia entre estos y los valores de Delta, mu, omega y el tiempo t
//devuelve un real con el valor del momento conjugado del radio en ese instante
double f_pr(double pphi, double r, double phi, double Delta, double mu, double omega, double t){
    double f, resta, r_prima;
    r_prima=sqrt(1+r*r-2*r*cos(phi-omega*t));
    f=pphi*pphi/pow(r,3);
    resta=mu/pow(r_prima, 3);
    resta=resta*(r-cos(phi-omega*t));
    resta=resta+1/(r*r);


    f=f-Delta*resta;
    return f;
    

}


//Funcion que calcula el momento de phi, según ecuaciones de Hamilton
//Se le pasa la distancia cohete-tierra, el ángulo que forman y los valores de Delta, mu, omega y el tiempo t
//devuelve un real con el valor del momento conjugado del angulo en ese instante
double f_pphi( double r, double phi, double Delta, double mu, double omega, double t){
    double f, r_prima;
    r_prima=sqrt(1+r*r-2*r*cos(phi-omega*t));
    f=-Delta*mu*r/pow(r_prima,3);
    f=f*sin(phi-omega*t);
    return f;
}

//Función que realiza el algoritmo de runge kutta
//Se le introduce el puntero k a calcular, el puntero y, el putero auxiliar a, los valores de Delta mu, omega, h y t
//Actualiza el puntero k según las ecuaciones de hamilton y el algoritmo runge kutta
double funcion(double *k, double *y, double * a, double Delta, double mu, double omega, double h, double t){
    *k=h*f_radio(*(y+1)+*(a+1));
    *(k+1)=h*f_pr(*(y+3)+*(a+3), *y+*(a+0),y[2]+*(a+2), Delta, mu, omega, t);
    *(k+2)=h*f_phi(*(y+3)+*(a+3), *y+*a);
    *(k+3)=h*f_pphi(*y+*a, *(y+2)+*(a+2), Delta, mu, omega, t);

}