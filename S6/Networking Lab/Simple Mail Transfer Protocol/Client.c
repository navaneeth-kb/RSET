#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8091
#define BUFFER_SIZE 1024

// Function to check if email is a Gmail address
int is_gmail_address(const char *email) {
    return strstr(email, "@gmail.com") != NULL;
}

// Function to get a valid Gmail address from the user
void get_valid_email(char *email, const char *prompt) {
    while (1) {
        printf("%s", prompt);
        scanf("%s", email);
        if (is_gmail_address(email)) {
            break;
        } else {
            printf("Invalid email! Please enter a Gmail address ending with @gmail.com.\n");
        }
    }
}

void send_and_receive(int socket, const char *message) {
    char buffer[BUFFER_SIZE];
    send(socket, message, strlen(message), 0);
    printf("C: %s", message); // Client message
    memset(buffer, 0, BUFFER_SIZE);
    recv(socket, buffer, BUFFER_SIZE, 0);
    printf("S: %s", buffer); // Server response
}

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    char sender_email[100], recipient_email[100], email_body[BUFFER_SIZE];

    // Get valid Gmail addresses
    get_valid_email(sender_email, "Enter sender email: ");
    get_valid_email(recipient_email, "Enter recipient email: ");

    // Get email subject and body
    printf("Enter email subject: ");
    getchar(); // Consume newline left by scanf
    fgets(buffer, BUFFER_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = 0; // Remove newline character
    snprintf(email_body, BUFFER_SIZE, "Subject: %s\n", buffer);

    printf("Enter email body (type '.' on a new line to end):\n");
    while (1) {
        fgets(buffer, BUFFER_SIZE, stdin);
        if (strcmp(buffer, ".\n") == 0) break; // Stop input when user enters "."
        strcat(email_body, buffer);
    }
    strcat(email_body, ".\n"); // Ensure email ends with "."

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

    // SMTP Communication
    send_and_receive(client_socket, "HELO localhost\n");

    snprintf(buffer, BUFFER_SIZE, "MAIL FROM: <%s>\n", sender_email);
    send_and_receive(client_socket, buffer);

    snprintf(buffer, BUFFER_SIZE, "RCPT TO: <%s>\n", recipient_email);
    send_and_receive(client_socket, buffer);

    send_and_receive(client_socket, "DATA\n");

    // Send email content
    printf("C: %s", email_body);
    send(client_socket, email_body, strlen(email_body), 0);
    
    recv(client_socket, buffer, BUFFER_SIZE, 0);
    printf("S: %s", buffer);

    send_and_receive(client_socket, "QUIT\n");

    close(client_socket);
    return 0;
}
