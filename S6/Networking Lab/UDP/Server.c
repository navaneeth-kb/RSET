#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8091
#define BUFFER_SIZE 1024

int main() {
    int server_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    // Create socket
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
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

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        // Receive message from client
        memset(buffer, 0, BUFFER_SIZE);
        int n = recvfrom(server_socket, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&client_addr, &addr_size);
        if (n == -1) {
            perror("Error receiving message");
            continue;
        }
        buffer[n] = '\0'; // Ensure null-termination
        printf("Client: %s", buffer);

        // Send response to the client
        printf("Server: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        sendto(server_socket, buffer, strlen(buffer), 0, (struct sockaddr*)&client_addr, addr_size);
    }

    close(server_socket);
    return 0;
}
