#include <math.h>
double f_phi(double phi, double psi, double pphi, double ppsi){
    double f;
    f=pphi-ppsi*cos(psi-phi);
    f=f/(1+pow(sin(phi-psi),2));
    return f;
}

double f_psi(double phi, double psi, double pphi, double ppsi){
   double f;
    f=2*ppsi-pphi*cos(psi-phi);
    f=f/(1+pow(sin(phi-psi),2));
    return f;
}

double f_pphi(double phi, double psi, double pphi, double ppsi, double g){
    double f;
    double h1, h2;
    h1=2*pphi*ppsi*sin(phi-psi)/(1+sin(phi-psi)*sin(phi-psi));
    h2=pphi*pphi+2*ppsi*ppsi-2*pphi*ppsi*cos(phi-psi);
    h2=h2/(pow((1+sin(phi-psi)*sin(phi-psi)),2));
    f=-2*g*sin(phi)+h1-h2*sin(2*(phi-psi));
    
    return f;
}

double f_ppsi(double phi, double psi, double pphi, double ppsi, double g){
    double f;
    double h1, h2;
    h1=2*pphi*ppsi*sin(phi-psi)/(1+sin(phi-psi)*sin(phi-psi));
    h2=pphi*pphi+2*ppsi*ppsi-2*pphi*ppsi*cos(phi-psi);
    h2=h2/(pow((1+sin(phi-psi)*sin(phi-psi)),2));
    f=-g*sin(psi)-h1+h2*sin(2*(phi-psi));
    
    return f;
}


double energia(double phi, double psi, double pphi, double ppsi, double g){
    double E, div;
    E=pphi*pphi+2*ppsi*ppsi-2*pphi*ppsi*cos(phi-psi);
    div=(2-cos(phi-psi)*cos(phi-psi));
    E=E/div;
    E=E+2*g*(1-cos(phi))+g*(1-cos(psi));

    return E;

}





double funcion(double *k, double *y, double * a, double g, double h){
    *k=h*f_phi(*(y)+*(a), *(y+1)+*(a+1), *(y+2)+*(a+2), *(y+3)+*(a+3));
    *(k+1)=h*f_psi(*(y)+*(a), *(y+1)+*(a+1), *(y+2)+*(a+2), *(y+3)+*(a+3));
    *(k+2)=h*f_pphi(*(y)+*(a), *(y+1)+*(a+1), *(y+2)+*(a+2), *(y+3)+*(a+3), g);
    *(k+3)=h*f_pphi(*(y)+*(a), *(y+1)+*(a+1), *(y+2)+*(a+2), *(y+3)+*(a+3), g);
   

}