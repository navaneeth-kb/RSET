#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <sys/stat.h>

#define PORT 5098
#define BUFFER_SIZE 2024
#define SERVER_DIR "server_files" // Directory to store files

// Function to ensure the server directory exists
void create_server_directory() {
    struct stat st;
    if (stat(SERVER_DIR, &st) == -1) {
        mkdir(SERVER_DIR, 0777); // Create directory if it doesn't exist
    }
}

// Function to handle client requests
void handle_client(int client_sock) {
    char buffer[BUFFER_SIZE], filepath[BUFFER_SIZE];
    int bytes_read;

    // Send welcome message
    send(client_sock, "220 FTP Server Ready\r\n", 22, 0);

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        bytes_read = recv(client_sock, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_read <= 0) {
            break; // Connection closed or error
        }

        buffer[bytes_read] = '\0'; // Ensure null termination
        printf("C: %s", buffer);

        if (strncmp(buffer, "PWD", 3) == 0) {
            // Respond with server directory
            snprintf(buffer, BUFFER_SIZE, "257 \"%s\" is the current directory\r\n", SERVER_DIR);
            send(client_sock, buffer, strlen(buffer), 0);
        } 
        else if (strncmp(buffer, "LIST", 4) == 0) {
            // List files in the server directory
            DIR *dir = opendir(SERVER_DIR);
            if (!dir) {
                send(client_sock, "550 Failed to open directory\r\n", 30, 0);
                continue;
            }
            struct dirent *entry;
            while ((entry = readdir(dir)) != NULL) {
                if (entry->d_name[0] != '.') { // Skip hidden files
                    snprintf(buffer, BUFFER_SIZE, "%s\r\n", entry->d_name);
                    send(client_sock, buffer, strlen(buffer), 0);
                }
            }
            closedir(dir);
        } 
        else if (strncmp(buffer, "RETR", 4) == 0) {
            // Extract filename
            char *filename = strchr(buffer, ' ');
            if (!filename) {
                send(client_sock, "500 Missing filename\r\n", 22, 0);
                continue;
            }
            filename++; // Move past space
            filename[strcspn(filename, "\r\n")] = '\0'; // Remove newline

            // Construct full file path
            snprintf(filepath, BUFFER_SIZE, "%s/%s", SERVER_DIR, filename);
            FILE *file = fopen(filepath, "rb");
            if (!file) {
                send(client_sock, "550 File not found\r\n", 20, 0);
                continue;
            }

            // Send file contents
            send(client_sock, "150 Opening data connection\r\n", 29, 0);
            while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
                send(client_sock, buffer, bytes_read, 0);
            }
            fclose(file);
            send(client_sock, "226 Transfer complete\r\n", 23, 0);
        } 
        else if (strncmp(buffer, "QUIT", 4) == 0) {
            send(client_sock, "221 Bye\r\n", 10, 0);
            break;
        } 
        else {
            send(client_sock, "500 Command not recognized\r\n", 28, 0);
        }
    }
    close(client_sock);
}

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // Ensure the server directory exists
    create_server_directory();

    // Create socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    // Set socket options
    int opt = 1;
    setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket
    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(1);
    }

    // Listen for connections
    if (listen(server_sock, 5) < 0) {
        perror("Listen failed");
        exit(1);
    }

    printf("FTP Server running on port %d...\n", PORT);

    while (1) {
        client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_len);
        if (client_sock < 0) {
            perror("Accept failed");
            continue;
        }
        printf("Client connected: %s:%d\n",
               inet_ntoa(client_addr.sin_addr),
               ntohs(client_addr.sin_port));
        handle_client(client_sock);
    }

    close(server_sock);
    return 0;
}
