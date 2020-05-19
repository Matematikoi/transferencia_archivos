#include <bits/stdc++.h> 
using namespace std;
int * BASE,* RECIBIDO;
void llenar_base(int tamano_arreglo, int peso_archivo){
    BASE = (int*) malloc(peso_archivo+1);
    RECIBIDO = (int*) malloc(peso_archivo+1);
    for (int i = 0 ;i <tamano_arreglo;++i){
        BASE[i] = i % 1000;
    }
    memset(RECIBIDO,0,peso_archivo);
}


int main(int argc, char* argv[]){
    // Comprobamos el numero de parametros
    if (argc < 2) {
        cerr << "Uso: " << argv[0] << "n  c" << endl;
        cerr << "donde n es el numero y c un caracter. Para expresar \n";
        cerr << "100Kb se debe escribir 100 k "<<endl;
        return 1;
    }
    map <string,int> prefijos;
    prefijos["k"]=1e3;
    prefijos["m"]=1e6;
    int peso_archivo=prefijos[argv[2]]*stoi(argv[1]);
    int tamano_arreglo = peso_archivo/8;
    cerr<<"tamano de arreglo : "<<tamano_arreglo<<endl;
    llenar_base(tamano_arreglo, peso_archivo);
    for (int i =0;i<tamano_arreglo;++i)
        cout<<BASE[i]<<' ' <<RECIBIDO[i]<<endl;
    
}