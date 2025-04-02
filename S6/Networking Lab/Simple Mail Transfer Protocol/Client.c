#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <arpa/inet.h>

#define PORT 8091 
#define BUFFER_SIZE 1024

// Function to check if email is a Gmail address
int is_gmail_address(const char *email) 
{ 
return strstr(email, "@gmail.com") != NULL; 
}

int main() { int client_socket; struct sockaddr_in server_addr; char buffer[BUFFER_SIZE]; char sender_email[100], recipient_email[100], email_body[BUFFER_SIZE];

// Get valid Gmail addresses
do {
    printf("Enter sender email: ");
    scanf("%s", sender_email);
    if (!is_gmail_address(sender_email)) {
        printf("Invalid email! Please enter a Gmail address ending with @gmail.com.\n");
    }
} while (!is_gmail_address(sender_email));

do {
    printf("Enter recipient email: ");
    scanf("%s", recipient_email);
    if (!is_gmail_address(recipient_email)) {
        printf("Invalid email! Please enter a Gmail address ending with @gmail.com.\n");
    }
} while (!is_gmail_address(recipient_email));

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
strcpy(buffer, "HELO localhost\n");
send(client_socket, buffer, strlen(buffer), 0);
recv(client_socket, buffer, BUFFER_SIZE, 0);
printf("S: %s", buffer);

snprintf(buffer, BUFFER_SIZE, "MAIL FROM: <%s>\n", sender_email);
send(client_socket, buffer, strlen(buffer), 0);
recv(client_socket, buffer, BUFFER_SIZE, 0);
printf("S: %s", buffer);

snprintf(buffer, BUFFER_SIZE, "RCPT TO: <%s>\n", recipient_email);
send(client_socket, buffer, strlen(buffer), 0);
recv(client_socket, buffer, BUFFER_SIZE, 0);
printf("S: %s", buffer);

strcpy(buffer, "DATA\n");
send(client_socket, buffer, strlen(buffer), 0);
recv(client_socket, buffer, BUFFER_SIZE, 0);
printf("S: %s", buffer);

// Send email content
printf("C: %s", email_body);
send(client_socket, email_body, strlen(email_body), 0);
recv(client_socket, buffer, BUFFER_SIZE, 0);
printf("S: %s", buffer);

strcpy(buffer, "QUIT\n");
send(client_socket, buffer, strlen(buffer), 0);
recv(client_socket, buffer, BUFFER_SIZE, 0);
printf("S: %s", buffer);

close(client_socket);
return 0;

}

