#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8083
#define BUFFER_SIZE 1024
#define TIMEOUT 1

void bubble_sort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    int done = 0, messages[10][2], waiting[5], finished[10];

    // Initialize messages and waiting queues
    for (int i = 0; i < 10; i++) {
        messages[i][0] = i;
        messages[i][1] = 1;
    }
    for (int i = 0; i < 5; i++) {
        waiting[i] = messages[i][0];
        messages[i][1] = 0;
    }

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
        for (int i = 0; i < 5; i++) {
            sprintf(buffer, "Message %d", waiting[i]);
            printf("Sending %s\n", buffer);

            // Send message to server
            send(client_socket, buffer, strlen(buffer), 0);

            if (rand() % 2 == 0) {
                sleep(TIMEOUT);
            }

            memset(buffer, 0, BUFFER_SIZE);
            int recv_status = recv(client_socket, buffer, BUFFER_SIZE, 0);

            if (strcmp(buffer, "ACK") == 0) {
                printf("Server : %s\n", buffer);
                finished[done] = waiting[i];
                done++;
                waiting[i] = 100;

                // Check for new messages to send
                for (int j = 0; j < 10; j++) {
                    if (messages[j][1] == 1 && rand() % 2 == 0) {
                        messages[j][1] = 0;
                        waiting[i] = messages[j][0];
                        break;
                    }
                }

                // Sort waiting messages
                int n = sizeof(waiting) / sizeof(waiting[0]);
                bubble_sort(waiting, n);
                break;
            }

            if (done == 10) {
                break;
            }

            printf("Timeout/NACK received, resending...\n");
        }

        printf("\n");
        if (done == 10) {
            break;
        }
    }

    // Print finished messages
    printf("\nfinished\n");
    for (int j = 0; j < 10; j++) {
        printf("%d ", finished[j]);
    }
    printf("\n");

    close(client_socket);
    return 0;
}
