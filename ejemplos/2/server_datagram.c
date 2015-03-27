#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORTNUM 9999

int main(int argc, char *argv[])
{
	char* msg = 
		"<html><body><h1>Hola Mundo</h1></body></html>";

	struct sockaddr_in dest;
	struct sockaddr_in serv;
	int server;
	int fallo_bind;
	socklen_t socksize = sizeof(struct sockaddr_in);
	// NUEVO
	int rc;
	char buf[512];
	
	memset(&serv, 0, sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	serv.sin_port = htons(PORTNUM);
	
	// AF_INET --> Tipo ipv4. SOCK_STREAM Tipo FLUJO
	server = socket(AF_INET, SOCK_DGRAM, 0);
	if (server < 0) {
		// MEJOR QUE printf usamos perror
		printf("Error: Socket()\n");
		return -1;
	}

	// CONFIGURACION de socket. Descriptor entero server, &serv configuracion tipo sockaddr_in y tamaño
	// TRATAMIENTO DE ERRORES. Igual que socket
	fallo_bind = bind(server, (struct sockaddr *)&serv, sizeof(struct sockaddr));
	if (fallo_bind < 0)
	{
		perror("Error bind()\n");
		return -1;
	}


	for(;;){
    	 	 rc = recv (server, buf, sizeof(buf), 0);
//     		 buf[rc] = (char) NULL;
     		 printf("Received: %s\n", buf);
	}
   
	close(server);
	return EXIT_SUCCESS;
}
