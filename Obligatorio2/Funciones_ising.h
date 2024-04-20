//Función delta energía
double delta_energia(int* s, int N){
    double E;
    
    E=2*(*s)*(*(s+1)+*(s-1)+*(s+N)+*(s-N));
    return E;
   
    

}
// s[i][j]=rand() % 2;
            // if(s[i][j]==0){
            //     s[i][j]=-1;