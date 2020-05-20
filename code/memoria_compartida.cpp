#include <bits/stdc++.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
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
    map <string,int> prefijos;
    prefijos["k"]=1e3;
    prefijos["m"]=1e6;
    int peso_archivo=prefijos[argv[2]]*stoi(argv[1]);
    int tamano_arreglo = peso_archivo/4;
    cout<<"tamano de arreglo : "<<tamano_arreglo<<endl;
    llenar_base(tamano_arreglo, peso_archivo);

    pid_t pid;
    int status,shmId, *ap;
    key_t key=9192;
    //crear espacio de memoria compartida
    shmId = shmget(key, peso_archivo, 0666|IPC_CREAT);
    if(shmId < 0){
        perror("Error en shmget");
        exit(-1);
    }
    //asociar espacio de memoria creada a este proceso
    ap = (int *)shmat(shmId, 0, 0);
    
    
    pid = fork();
    if (pid == -1) { 
      perror("error en fork"); exit(EXIT_FAILURE); 
    }
    if (pid == 0){
        copy(BASE,BASE + tamano_arreglo, ap);
    }
    else{
        if (wait(&status) == pid){
            copy(ap,ap + tamano_arreglo, RECIBIDO);
        }
    }
    int r = shmdt(ap);  //desasociar espacio de memoria compartida
    if(r < 0){
      perror("error shmdt ");
      exit(-1);
    }

}