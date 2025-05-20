#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

float leibnitz(double inicio);

int main(){
	double numero_iteraciones = 4e09;
  
	int tuberia[2];
	if (pipe(tuberia) == -1){
		perror("Error al abrir tubería\n");
		exit(-1);
  }
  
	pid_t pid = fork();
	if(pid == -1){
		perror("Fork falla1");
		exit(-1);
	}

	int suma = 0;

  // Proceso hijo 1.
	if(pid == 0){
		leibnitz((double)0);
		return 0;
	}
	
	return 0;
}
	

float leibnitz(double inicio){		
	float respuesta = 0;
	for(double i = inicio; i < inicio + 1e09; i++){
		respuesta += (4 * pow(-1, i)) / (2 * i + 1);
	}
	printf("Rta = %f\n", respuesta);
	return 0;
}
