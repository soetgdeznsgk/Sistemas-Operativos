#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <sys/shm.h>

#define NRO_ITERACIONES 4e98
#define NRO_PROCESOS 4

double leibnitz(double inicio){
        double respuesta = 0;
        for(double i = inicio; i < inicio + 1e09; i++){
                respuesta += (4 * pow(-1, i)) / (2 * i + 1);
        }
        return respuesta;
}

int main(){
        key_t llave = 123;
        int shmId = shmget(llave, sizeof(double) * 4, IPC_CREAT|0666);
        
        if(shmId == -1){
                perror("Shmget falla!");
                exit(-1);
        }

        double *ap = shmat(shmId, 0, 0);
        if(ap == (void*) -1){
                perror("Shmat falla!");
                exit(-1);
        }
        
        for(int i = 0; i < NRO_PROCESOS; i++){
            pid_t pid = fork();
            
            if(pid == -1){
                perror("Fork falla!");
                exit(-1);
            }
            
            if(pid == 0){
                ap[i] = leibnitz((double) i * 1e09);
                printf("Hijo %d termina\n", i + 1);
                return 1;
            }
        }

        wait(NULL);
        wait(NULL);
        wait(NULL);
        wait(NULL);
        
        double suma = 0;
        for(int i = 0; i < 4; i++){
            suma += ap[i];
        }
        printf("Leibniz(%E) = %.15f;\ndiferencia con M_PI: %e\n",NRO_ITERACIONES ,suma, M_PI - suma);
        return 1;
}