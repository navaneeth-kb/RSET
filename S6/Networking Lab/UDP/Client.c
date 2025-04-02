#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8091
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    socklen_t addr_size = sizeof(server_addr);
    char buffer[BUFFER_SIZE];

    // Create socket
    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);

    while (1) {
        printf("Enter message to send to server (type 'exit' to quit): ");
        fgets(buffer, BUFFER_SIZE, stdin);

        // Send message to server
        sendto(client_socket, buffer, strlen(buffer), 0, (struct sockaddr*)&server_addr, addr_size);
        
        if (strncmp(buffer, "exit", 4) == 0) {
            break;
        }

        // Receive response from server
        memset(buffer, 0, BUFFER_SIZE);
        int n = recvfrom(client_socket, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&server_addr, &addr_size);
        if (n == -1) {
            perror("Error receiving message");
            continue;
        }
        buffer[n] = '\0'; // Ensure null-termination
        printf("Received from server: %s\n", buffer);
    }

    close(client_socket);
    return 0;
}
