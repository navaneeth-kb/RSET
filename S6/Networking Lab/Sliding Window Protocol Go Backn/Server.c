#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8083
#define BUFFER_SIZE 1024

int main() {
    srand(time(NULL)); // Seed random number generator

    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(struct sockaddr_in);
    char buffer[BUFFER_SIZE];

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
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    listen(server_socket, 5);
    printf("Server listening on port %d...\n", PORT);

    // Accept a connection from a client
    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_size);
    if (client_socket == -1) {
        perror("Error accepting connection");
        exit(EXIT_FAILURE);
    }

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        ssize_t recv_size = recv(client_socket, buffer, BUFFER_SIZE, 0);

        if (recv_size <= 0) {
            printf("Client disconnected or error occurred\n");
            break; // Exit the loop if client disconnects or error occurs
        }

        printf("Client: %s", buffer);
        printf("\tServer: ");

        // Randomly choose between ACK or NACK
        if (rand() % 2 == 0) {
            printf("Acknowledging\n");
            send(client_socket, "ACK", 3, 0);
        } else {
            printf("Not Acknowledging\n");
            send(client_socket, "NACK", 4, 0);
        }
    }

    close(server_socket);
    close(client_socket);

    return 0;
}
