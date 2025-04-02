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
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("Enter PWD, LIST, RETR, filename and then EXIT: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline

        // Send command to server
        send(client_socket, buffer, strlen(buffer), 0);
        memset(buffer, 0, BUFFER_SIZE);

        // Receive response from server
        int bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received <= 0) {
            printf("Server disconnected\n");
            break;
        }
        buffer[bytes_received] = '\0';

        // If server sends "Bye", exit
        if (strcmp(buffer, "Bye") == 0) {
            printf("Server: Bye\n");
            break;
        }

        printf("Server: %s\n", buffer);

        // File retrieval process
        if (strncmp(buffer, "Enter file name", 15) == 0) {
            char filename[BUFFER_SIZE];
            printf("Enter filename to retrieve: ");
            fgets(filename, BUFFER_SIZE, stdin);
            filename[strcspn(filename, "\r\n")] = 0; // Remove newline

            // Send filename to server
            send(client_socket, filename, strlen(filename), 0);

            // Open file for writing
            FILE *file = fopen(filename, "wb");
            if (!file) {
                perror("Error creating file");
                continue;
            }

            printf("Receiving file: %s\n", filename);
            while ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
                fwrite(buffer, 1, bytes_received, file);
                if (bytes_received < BUFFER_SIZE) break; // End of file
            }
            fclose(file);
            printf("File received and saved as %s\n", filename);
        }
    }

    // Close the socket
    close(client_socket);
    return 0;
}
