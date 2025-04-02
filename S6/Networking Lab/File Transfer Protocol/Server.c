#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <linux/limits.h>
#include <dirent.h>

#define PORT 8091
#define BUFFER_SIZE 1024

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(struct sockaddr_in);
    char buffer[BUFFER_SIZE];
    int state = 0;

    // Directory
    DIR *dir;
    struct dirent *entry;

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
    listen(server_socket, 5);
    printf("Server listening on port %d...\n", PORT);

    // Accept a connection from a client
    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_size);
    if (client_socket == -1) {
        perror("Error accepting connection");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Receive message from client
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received <= 0) {
            perror("Error receiving data or connection closed");
            break;
        }
        
        buffer[strcspn(buffer, "\r\n")] = 0; // Removing newline to rectify strcmp
        buffer[bytes_received] = '\0'; // Ensure null termination
        printf("Client: %s\n", buffer);
        
        char response[BUFFER_SIZE];

        if ((strcmp(buffer, "PWD") == 0) && state == 0) {
            char cwd[1024];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                snprintf(response, BUFFER_SIZE, "Current working dir: %s\n", cwd);
            }
            state = 1;
        } 
        else if (strcmp(buffer, "LIST") == 0 && state == 1) {
            dir = opendir(".");
            if (dir == NULL) {
                snprintf(response, BUFFER_SIZE, "Failed to open directory\n");
            } else {
                response[0] = '\0';
                while ((entry = readdir(dir)) != NULL) {
                    strcat(response, entry->d_name);
                    strcat(response, ", ");
                }
                closedir(dir);
            }
            state = 2;
        } 
        else if (strcmp(buffer, "RETR") == 0 && state == 2) {
            snprintf(response, BUFFER_SIZE, "Enter file name:");
            state = 3;
        } 
        else if (state == 3) {
            FILE *file = fopen(buffer, "rb");
            if (file == NULL) {
                snprintf(response, BUFFER_SIZE, "Error: File not found\n");
                send(client_socket, response, strlen(response), 0);
                state = 2;
                continue;
            }
            printf("Sending file content\n");
            while (!feof(file)) {
                size_t bytes_read = fread(buffer, 1, BUFFER_SIZE, file);
                send(client_socket, buffer, bytes_read, 0);
            }
            fclose(file);
            state = 4;
            continue;
        } 
        else if (state == 4) {
            snprintf(response, BUFFER_SIZE, "Bye");
            send(client_socket, response, strlen(response), 0);
            break;
        }

        send(client_socket, response, strlen(response), 0);
    }

    close(client_socket);
    close(server_socket);
    return 0;
}
