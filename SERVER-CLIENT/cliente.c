#include "header.h"

int main(){

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

	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0){
		perror("Dirección inválida");
		exit(-1);
	}

	// Conectarse al servidor 

	if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
		perror("Conexión fallida");
		exit(-1);
	}

	// Intercambio de datos :)
	
	char *mensaje = "Hola desde el cliente";
	send(sock, mensaje, strlen(mensaje), 0);
	
	char buffer[1024] = {0};
	int valread = read(sock, buffer, 1024);
	printf("Servidor dice: %s\n",buffer);


	close(sock);
}

