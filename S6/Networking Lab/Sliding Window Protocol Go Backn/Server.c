#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#define PORT 8102
#define BUFFER_SIZE 1024
int main() {
	srand(time(NULL)); // Seed for random ACK loss simulation
	int server_socket, client_socket;
	struct sockaddr_in server_addr, client_addr;
	socklen_t addr_size = sizeof(struct sockaddr_in);
	char buffer[BUFFER_SIZE];
	int expected_seq = 0;
	// Create socket
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket == -1) {
		perror("Error creating socket");
		exit(EXIT_FAILURE);
	}
	// Configure server address
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PORT);
	// Bind the socket
	if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
		perror("Error binding socket");
		close(server_socket);
		exit(EXIT_FAILURE);
	}
	// Listen for incoming connections
	if (listen(server_socket, 5) == -1) {
		perror("Error listening on socket");
		close(server_socket);
		exit(EXIT_FAILURE);
	}
	printf("Server listening on port %d...\n", PORT);
	// Accept a connection from a client
	client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_size);
	if (client_socket == -1) {
		perror("Error accepting connection");
		close(server_socket);
		exit(EXIT_FAILURE);
	}
	while (1) {
		memset(buffer, 0, BUFFER_SIZE);
		recv(client_socket, buffer, BUFFER_SIZE, 0);
		int seq_num, number;
		if (sscanf(buffer, "%d %d", &seq_num, &number) != 2) {
			continue; 
		}

		printf("Received: Seq %d number %d\n", seq_num,number);
		if (seq_num == expected_seq) {
			// Simulate random ACK loss (20% chance)
			if (rand() % 5 != 0) {
				printf("Server: Sending ACK for sequence %d\n", expected_seq);
				sprintf(buffer, "ACK %d", expected_seq);
				send(client_socket, buffer, strlen(buffer), 0);
				expected_seq++;
			} else {
				printf("Server: Simulated ACK loss for sequence %d\n", expected_seq);
			}
		} else {
			printf("Out-of-order packet received. Expected: %d, Received: %d\n", expected_seq, seq_num);
		}
	}
	// Close the client and server sockets
	close(client_socket);
	close(server_socket);
	return 0;
}
