#include "header.h"

static int* g_socket_fd = (int*)-1;
static int* g_server_fd = (int*)-1;

void interruption_handler(){
	const char *mensaje = "\nInterrupción\n";
	close(*g_socket_fd);
	close(*g_server_fd);
	write(STDOUT_FILENO, mensaje, strlen(mensaje));
}

void setup_sigterm_handler(int* socket_fd, int* server_fd){
	g_socket_fd = socket_fd;
	g_server_fd = server_fd;

	struct sigaction action = {
		.sa_handler = interruption_handler,
		.sa_flags = 0,
		.sa_mask = {0}
	};
	sigaction(SIGINT, &action, NULL);
}
