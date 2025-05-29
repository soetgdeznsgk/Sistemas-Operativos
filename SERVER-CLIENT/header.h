#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>
#include <stdbool.h>

#ifndef DIRECCION_SERVIDOR
#define DIRECCION_SERVIDOR "192.168.0.12"
#endif

#ifndef INTERRUPTION_HANDLER_H
#define INTERRUPTION_HANDLER_H 

void interruption_handler();

#endif

#ifndef INTERRUPTION_SETUP_H
#define INTERRUPTION_SETUP_H

void setup_sigterm_handler(int* socket_fd, int* server_fd);

#endif
