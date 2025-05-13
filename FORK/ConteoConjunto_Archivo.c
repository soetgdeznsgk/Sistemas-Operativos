#import <unistd.h>
#import <stdio.h>
#import <stdlib.h>
#import <sys/wait.h>

int main(){
    
    FILE *fptr;
    
    fptr = fopen("comunicacion.txt", "w+");
    
    if (fptr == NULL){
        perror("Error al crear archivo!");
        exit(-1);
    }
    
    pid_t pid = fork();
    if(pid == -1){
        perror("Fork falla!");
        exit(-1);
    }
    
    int suma = 0;
      
    // Proceso hijo
    if(pid == 0){
        for(int i = 0; i < 500; i++){
          suma += i;
        }
        fwrite(&suma, sizeof(int), 1, fptr);
        rewind(fptr);                           // devuelve el puntero al inicio del archivo
    }
    // Proceso padre
    else{
        for(int i = 500; i < 1000; i++){
          suma += i;
        }
        wait(NULL);                              // espera a que uno de sus hijos cambie de estado
        int suma_de_hijo;
        fread(&suma_de_hijo, sizeof(int), 1,fptr);
        suma += suma_de_hijo;
        printf("%d (Suma de padre) + %d (Suma de hijo) = %d\n",suma - suma_de_hijo, suma_de_hijo, suma);
    }
    fclose(fptr);
    return 0;
}