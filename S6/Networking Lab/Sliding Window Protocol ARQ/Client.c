#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>

#define PORT 8091
#define BUFFER_SIZE 2048
#define TIMEOUT 3

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    int seq_num = 0;  // Initial sequence number

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

    while (1) {
        printf("\nEnter message to send to server (type 'exit' to quit): ");
        fgets(buffer, BUFFER_SIZE - 10, stdin);

        if (strcmp(buffer, "exit\n") == 0) {
            break;
        }

        char message[BUFFER_SIZE];
        sprintf(message, "%d:%s", seq_num, buffer);  // Add sequence number to message

        int ack_received = 0;
        while (!ack_received) {
            // Send message to server
            send(client_socket, message, strlen(message), 0);

            // Set up timeout for ACK
            fd_set read_fds;
            struct timeval timeout;
            FD_ZERO(&read_fds);
            FD_SET(client_socket, &read_fds);
            timeout.tv_sec = TIMEOUT;
            timeout.tv_usec = 0;

            int timer = select(client_socket + 1, &read_fds, NULL, NULL, &timeout);

            if (timer == -1) {
                printf("Error selecting.\n");
                break;
            } else if (timer == 0) {
                printf("Timed out: No ACK received, retransmitting...\n");
            } else {
                // Receive ACK from server
                memset(buffer, 0, BUFFER_SIZE);
                recv(client_socket, buffer, BUFFER_SIZE, 0);

                int received_ack;
                if (sscanf(buffer, "ACK:%d", &received_ack) == 1 && received_ack == seq_num) {
                    printf("Received from server: %s\n", buffer);
                    seq_num = 1 - seq_num;  // Toggle sequence number
                    ack_received = 1;
                } else {
                    printf("Incorrect ACK received, retransmitting...\n");
                }
            }
        }
    }

    close(client_socket);
    return 0;
}
