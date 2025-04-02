#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER "127.0.0.1"
#define PORT 5098
#define BUFFER_SIZE 1024

// Function to send a command and receive the server's response
void send_command(int sock, const char *cmd) {
    send(sock, cmd, strlen(cmd), 0);
    
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    
    int bytes = recv(sock, buffer, BUFFER_SIZE - 1, 0);
    if (bytes > 0) {
        buffer[bytes] = '\0';
        printf("S: %s", buffer);
    }
}

// Function to receive and print file contents after RETR command
int receive_file(int sock) {
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    
    int bytes;
    int file_found = 1; // Flag to track if the file was found

    printf("S: 150 Opening data connection\n"); // FTP response
    
    while ((bytes = recv(sock, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[bytes] = '\0';
        
        // If the server responds with "550 File not found", prompt for a new file
        if (strstr(buffer, "550 File not found") != NULL) {
            printf("Error: File not found. Please enter a valid filename.\n");
            file_found = 0; // Mark file as not found
            break;
        }

        // Check if "226 Transfer complete" is received and stop reading
        if (strstr(buffer, "226 Transfer complete") != NULL) {
            printf("%s\n", buffer); // Print completion message
            break; // Exit loop
        }

        printf("%s", buffer); // Print file contents as they arrive
    }

    printf("\n"); // Ensure clean formatting after file display
    return file_found; // Return whether the file was successfully found and retrieved
}

// Function to get user input
void get_input(char *prompt, char *buffer) {
    printf("%s", prompt);
    memset(buffer, 0, BUFFER_SIZE);
    
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        printf("Error reading input\n");
        exit(1);
    }
    
    buffer[strcspn(buffer, "\n")] = 0; // Remove newline
}

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE], message[BUFFER_SIZE];

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER);

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(1);
    }

    // Receive server greeting
    memset(buffer, 0, BUFFER_SIZE);
    int bytes = recv(sock, buffer, BUFFER_SIZE - 1, 0);
    if (bytes > 0) {
        buffer[bytes] = '\0';
        printf("S: %s", buffer);
    }

    while (1) {
        get_input("\nEnter command (PWD, LIST, RETR, QUIT): ", buffer);

        if (strncmp(buffer, "PWD", 3) == 0) {
            send_command(sock, "PWD\r\n");
        } 
        else if (strncmp(buffer, "LIST", 4) == 0) {
            send_command(sock, "LIST\r\n");
        } 
        else if (strncmp(buffer, "RETR", 4) == 0) {
            int file_received = 0;
            while (!file_received) { // Keep asking for a valid filename until found
                get_input("Enter filename: ", buffer);
                snprintf(message, BUFFER_SIZE, "RETR %s\r\n", buffer);
                send(sock, message, strlen(message), 0);
                
                // Receive and print file contents, return 1 if found, 0 if not
                file_received = receive_file(sock);
            }
        } 
        else if (strncmp(buffer, "QUIT", 4) == 0) {
            send_command(sock, "QUIT\r\n");
            break;
        } 
        else {
            printf("Invalid command.\n");
        }
    }

    close(sock);
    return 0;
}
