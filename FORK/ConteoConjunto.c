#import <unistd.h>
#import <stdio.h>
#import <stdlib.h>

int main(){
  int tuberia[2];
  if (pipe(tuberia) == -1){
    perror("No se puede establecer la tuberia");
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
    write(tuberia[1], &suma, sizeof(int));
  }
  // Proceso padre
  else{
    for(int i = 500; i < 1000; i++){
      suma += i;
    }
    int suma_de_hijo;
    read(tuberia[0], &suma_de_hijo, sizeof(int));
    suma += suma_de_hijo;
    printf("%d\n", suma);
  }
  return 0;
}
