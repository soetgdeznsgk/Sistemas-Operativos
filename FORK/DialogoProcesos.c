#import <unistd.h>
#import <stdlib.h>
#import <stdio.h>

int main(){
  pid_t pid = fork();
  
  if (pid == -1){
    perror("Fork ha fallado");
    exit(-1);
  }
  // Proceso para el hijo
  else if (pid == 0){
  	   printf("NOOOOOOOOOOOOOOOOOOOO\n");
  }
  // Proceso para el padre
  else {
  	  printf("No, Luke, yo soy tu padre\n");
  }
  return 0;
}
