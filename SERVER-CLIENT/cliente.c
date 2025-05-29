#include "header.h"

int main(){
	int pid;
	// Creación del socket
	int sock = socket(AF_INET, SOCK_STREAM,0);

	if (sock < 0){
		perror("Falla creación del socket\n");
		exit(-1);
	}

	// Localizar el servidor
	struct sockaddr_in serv_addr = {
		.sin_family = AF_INET,
		.sin_port = htons(8080)
	};

	if (inet_pton(AF_INET, DIRECCION_SERVIDOR, &serv_addr.sin_addr) <= 0){
		perror("Dirección inválida");
		exit(-1);
	}

	// Conectarse al servidor 

	if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
		perror("Conexión fallida");
		exit(-1);
	}

	// Intercambio de datos :)
	
	char mensaje[1024] = {0};
	strcpy(mensaje, "Paquete inicial del cliente");
	send(sock, mensaje, strlen(mensaje), 0);
	
	pid = fork();

	if(pid < 0){
		perror("Error en el fork");
		exit(-1);
	}
	
	// Hijo lee e imprime
	if(pid == 0){
		char buffer[1024] = {0};
		for(int i = 0; i < 3; i++){
			memset(buffer, 0, sizeof(buffer));
			read(sock, buffer, 1024);
			printf("Servidor: %s\n", (char*) buffer);
		}
	}
	// Padre escribe y envía
	else{
		char mensaje[1024] = {0};
		for(int i = 0; i < 3; i++){
			memset(mensaje, 0, sizeof(mensaje));
			fgets(mensaje, sizeof(mensaje), stdin);
			send(sock, &mensaje, 1024, 0);
		}
	}
	close(sock);
}

