#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8091
#define BUFFER_SIZE 1024
#define TIMEOUT_SEC 5

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error connecting to server");
        exit(EXIT_FAILURE);
    }

    // Set socket receive timeout
    struct timeval timeout;
    timeout.tv_sec = TIMEOUT_SEC;  // Timeout in seconds
    timeout.tv_usec = 0;           // Timeout in microseconds
    if (setsockopt(client_socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
        perror("Error setting socket timeout");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("Enter message to send to server (type 'exit' to quit): ");
        fgets(buffer, BUFFER_SIZE, stdin);

        // Send message to server
        send(client_socket, buffer, strlen(buffer), 0);
        if (strcmp(buffer, "exit\n") == 0)
            break;

        // Receive response from server (with timeout)
        memset(buffer, 0, BUFFER_SIZE);
        ssize_t recv_size = recv(client_socket, buffer, BUFFER_SIZE, 0);

        if (recv_size < 0) {
            printf("Error or timeout waiting for ACK. Resending message...\n");
            // Resend the message
            send(client_socket, buffer, strlen(buffer), 0);
        } else {
            printf("Received from server: %s\n", buffer);
        }
    }

    close(client_socket);
    return 0;
}
