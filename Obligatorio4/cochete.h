#include <math.h>

double f_radio(double pr){
    double f;
    f=pr;
    return f;
}

double f_phi(double pphi, double r){
    double f;
    f=pphi/(r*r);
    return f;
}

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

double f_pphi( double r, double phi, double Delta, double mu, double omega, double t){
    double f, r_prima;
    r_prima=sqrt(1+r*r-2*r*cos(phi-omega*t));
    f=-Delta*mu*r/pow(r_prima,3);
    f=f*sin(phi-omega*t);
    return f;
}


double funcion(double *k, double *y, double * a, double Delta, double mu, double omega, double h, double t){
    *k=h*f_radio(*(y+1)+*(a+1));
    *(k+1)=h*f_pr(*(y+3)+*(a+3), *y+*(a+0),y[2]+*(a+2), Delta, mu, omega, t);
    *(k+2)=h*f_phi(*(y+3)+*(a+3), *y+*a);
    *(k+3)=h*f_pphi(*y+*a, *(y+2)+*(a+2), Delta, mu, omega, t);

}