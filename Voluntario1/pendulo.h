//FUNCIONES UTILIZADAS EN EL PROGRAMA DEL PENDULO DOBLE CON EL ALGORITMO DE RUNGE KUTTA

#include <math.h>

//Función que calcula la derivada temporal de phi según ecuaciones de hamilton
//Se le pasan los valores de los ángulos y los momentos y devuelve un real con el valor de la derivada temporal
double f_phi(double phi, double psi, double pphi, double ppsi){
    double f;
    f=pphi-ppsi*cos(psi-phi);
    f=f/(2-pow(cos(phi-psi),2));
    return f;
}



//Función que calcula la derivada temporal de psi según ecuaciones de hamilton
//Se le pasan los valores de los ángulos y los momentos y devuelve un real con el valor de la derivada temporal

double f_psi(double phi, double psi, double pphi, double ppsi){
   double f;
    f=2*ppsi-pphi*cos(psi-phi);
    f=f/(2-pow(cos(phi-psi),2));
    return f;
}


//Función que calcula la derivada temporal de pphi según ecuaciones de hamilton
//Se le pasan los valores de los ángulos y los momentos y devuelve un real con el valor de la derivada temporal

double f_pphi(double phi, double psi, double pphi, double ppsi, double g){
    double f;
    double h1, h2, h3;

    h1=pphi*ppsi*cos(psi-phi)*cos(psi-phi);
    h2=(2*ppsi*ppsi+pphi*pphi)*cos(psi-phi);
    h3=2*pphi*ppsi;
    h1=h1-h2+h3;
    h1=h1*2*sin(psi-phi);
    h2=pow((2-cos(psi-phi)*cos(psi-phi)),2);
    f=h1/h2-2*g*sin(phi);
    
    return f;
}



//Función que calcula la derivada temporal de ppsi según ecuaciones de hamilton
//Se le pasan los valores de los ángulos y los momentos y devuelve un real con el valor de la derivada temporal

double f_ppsi(double phi, double psi, double pphi, double ppsi, double g){
    double f;
    double h1, h2;
    
    h1=pphi*ppsi*cos(psi-phi)*cos(psi-phi);
    h1=h1-(2*ppsi*ppsi+pphi*pphi)*cos(psi-phi)+2*pphi*ppsi;
    h1=h1*2*sin(phi-psi);
    h2=pow((2-cos(psi-phi)*cos(psi-phi)),2);
    f=h1/h2-g*sin(psi);
    
    return f;
}


//Función que transforma el valor del momento del ángulo phi en velocidad phi
//Se le pasan los ángulos y momentos y devuelve un real con la velocidad
double momento_velocidad_phi(double phi, double psi, double pphi, double ppsi){
    double f;
    f=pphi-ppsi*cos(phi-psi);
    f=f/(2-cos(psi-phi)*cos(psi-phi));
    return f;
}


//Función que transforma el valor del momento del ángulo psi en velocidad psi
//Se le pasan los ángulos y momentos y devuelve un real con la velocidad
double momento_velocidad_psi(double phi, double psi, double pphi, double ppsi){
    double f;
    f=2*ppsi-pphi*cos(psi-phi);
    f=f/(2-cos(psi-phi)*cos(psi-phi));
    return f;
}


//Función que calcula la energía del sistema
//No se usa, pero es útil para ver como a altas energías la energía varía debiso a la simulación, generando errores
double energia(double phi, double psi, double pphi, double ppsi, double g){
    double E, div, vpsi, vphi;

    
    vphi=momento_velocidad_phi(phi, psi, pphi, ppsi);
    vpsi=momento_velocidad_psi(phi, psi, pphi, ppsi);

    E=vphi*vphi+vpsi*vpsi/2+vphi*vpsi*cos(psi-phi)+2*g*(1-cos(phi))+g*(1-cos(psi));

    return E;

}




//Función del algoritmo de Runge kutta
//Se encarga de calcular los valors de las k utilizando las funciones anteriormente mencionadas
double funcion(double *k, double *y, double * a, double g, double h){
    *k=h*f_phi(*(y)+*(a), *(y+1)+*(a+1), *(y+2)+*(a+2), *(y+3)+*(a+3));
    *(k+1)=h*f_psi(*(y)+*(a), *(y+1)+*(a+1), *(y+2)+*(a+2), *(y+3)+*(a+3));
    *(k+2)=h*f_pphi(*(y)+*(a), *(y+1)+*(a+1), *(y+2)+*(a+2), *(y+3)+*(a+3), g);
    *(k+3)=h*f_ppsi(*(y)+*(a), *(y+1)+*(a+1), *(y+2)+*(a+2), *(y+3)+*(a+3), g);
   

}