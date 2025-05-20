#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <sys/shm.h>

#define NRO_ITERACIONES 4e98


double leibnitz(double inicio){
        double respuesta = 0;
        for(double i = inicio; i < inicio + 1e09; i++){
                respuesta += (4 * pow(-1, i)) / (2 * i + 1);
        }
        return respuesta;
}

int main(){
        key_t llave = 123;
        int shmId = shmget(llave, sizeof(double), IPC_CREAT|0666);

        if(shmId == -1){
                perror("Shmget falla!");
                exit(-1);
        }

        double *ap = shmat(shmId, 0, 0);
        if(ap == (void*) -1){
                perror("Shmat falla!");
                exit(-1);
        }

        pid_t pid = fork();
        if(pid == -1){
                perror("Fork falla1");
                exit(-1);
        }

        double suma = 0;

  // Proceso hijo 1.
        if(pid == 0){
                *ap = leibnitz((double)0);

        }
        else{
                wait(NULL);
                printf("%.15f\n", *ap);
        }
        return 0;
}
