#include "header.h"

int main(){
	int pid;
	int server_fd;
	int new_socket;
	setup_sigterm_handler(&server_fd, &new_socket);			// no es realmente sigterm, tener cuidado con eso, es SIGINT
	
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	// AF_INET = IPv4, 
	// SOCK_STREAM = TCP
	if (server_fd < 0){
		perror("Falló creación de socket");
		exit(-1);
	}

	// A qué canal escuchará?
	struct sockaddr_in address = {
		.sin_family = AF_INET,
		.sin_addr.s_addr = INADDR_ANY,
		.sin_port = htons(8080)
	};
	
	// Para que se pueda reutilizar el socket y no se bloquee si está ocupado
	int yes = 1;
	setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

	// Reserva la pareja (address, port) a éste socket
	if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0){
		perror("Falló bind");
		exit(-1);
	}
	
	// Abre el proceso a conexiones remotas
	if (listen(server_fd,3) < 0){
		perror("Falla escucha");
		exit(-1);
	}

	// Bloquea proceso hasta recibir una conexión
	int addrlen = sizeof(address);
	new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);

	if (new_socket < 0){
		perror("Fallo la recepción del nuevo socket");
		exit(-1);
	}

	// Interrcambio de info :)

	pid = fork();

	if (pid < 0){
		perror("Falla fork!");
		exit(-1);
	}
	
	// Hijo recibe mensajes y los imprime
	if (pid == 0){
		char buffer[1024] = {0};
		for (int i = 0; i < 3; i++){
			memset(buffer, 0, sizeof(buffer));
			read(new_socket, buffer, 1024);
			printf("Cliente: %s\n", (char*)buffer);
		}
	}
	// Padre escanea terminal y manda mensajes
	else{	
		char mensaje[1024] = {0};
		for(int i = 0; i < 3; i++){
			memset(mensaje, 0, sizeof(mensaje));
			fgets(mensaje, sizeof(mensaje), stdin);
			send(new_socket, &mensaje, 1024,0);
		}	
	}


	close(new_socket);
	close(server_fd);

	return 1;
}



