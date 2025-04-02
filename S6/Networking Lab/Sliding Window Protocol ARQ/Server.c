#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8091
#define BUFFER_SIZE 2048

int main() {
    int server_socket, client_socket, ran_num;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(struct sockaddr_in);
    char buffer[BUFFER_SIZE];
    int expected_seq = 0;  // Server starts expecting sequence number 0

    srand(time(NULL));

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
        int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
        
        if (bytes_received <= 0) {
            printf("\nClient disconnected.\n");
            break;
        }

        // Extract sequence number from message
        int received_seq;
        sscanf(buffer, "%d:", &received_seq);

     
        ran_num = rand() % 4;
        if (ran_num == 0) {
            printf("\nClient [%d]: %s", received_seq, buffer + 2);

            if (received_seq == expected_seq) {
                // Send ACK for the correct sequence number
                sprintf(buffer, "ACK:%d", expected_seq);
                if(rand()%2 == 0){
                	send(client_socket, buffer, strlen(buffer), 0);
                	expected_seq = 1 - expected_seq;  // Toggle expected sequence number
                }else{
                	printf("\n Ack lost");
                }
            } else {
                printf("\nOut-of-order message received, expected %d but got %d. Ignoring.\n", expected_seq, received_seq);
            }
        } else {
            printf("\nClient message lost .");
        }
    }

    close(client_socket);
    close(server_socket);
    return 0;
}
