#include <bits/stdc++.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
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
int guardar_base(int peso_archivo){
    FILE *apFile;
    int r;
    apFile = fopen("binaries/base.bin","w+");
    if(apFile == NULL){
        perror("error fopen:");
        exit(-1);
    }
    r = fwrite(BASE, peso_archivo,1, apFile);
    if(r <= 0){
        perror("error fwrite");
        exit(-1);
    }
    r = fclose(apFile);
    if(r < 0){
        perror("error fclose: ");
        exit(-1);
    }
    return 1;
}

void leer_base_a_recibido(int peso_archivo){
    ifstream archivo ("binaries/base.bin", ios::in|ios::binary|ios::ate);
    archivo.seekg (0, ios::beg);
    archivo.read ( (char*) RECIBIDO ,peso_archivo);
    archivo.close();
}

int main(int argc, char* argv[]){
    map <string,int> prefijos;
    prefijos["k"]=1e3;
    prefijos["m"]=1e6;
    int peso_archivo=prefijos[argv[2]]*stoi(argv[1]);
    int tamano_arreglo = peso_archivo/8;
    cout<<"tamano de arreglo : "<<tamano_arreglo<<endl;
    llenar_base(tamano_arreglo, peso_archivo);
    pid_t pid;
    int status;
    pid = fork();
    if (pid == -1) { 
      perror("fork"); exit(EXIT_FAILURE); 
    }
    if (pid == 0){
        guardar_base(peso_archivo);
    }
    else{
        if (wait(&status) == pid){
            leer_base_a_recibido(peso_archivo);
        }
    }
    
    cout<<"finalizado"<<endl;

}