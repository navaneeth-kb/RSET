#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8102
#define BUFFER_SIZE 1024
#define TIMEOUT 3 // Timeout in seconds
int main() {
	int client_socket;
	struct sockaddr_in server_addr;
	int window_size, i, base = 0, next_seq_num = 0, total_numbers;
	int numbers[BUFFER_SIZE];
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
	// Connect to server
	if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
		perror("Error connecting to server");
		close(client_socket);
		exit(EXIT_FAILURE);
	}
	// Input window size and array
	printf("Enter window size: ");
	scanf("%d", &window_size);
	printf("Enter number of elements: ");
	scanf("%d", &total_numbers);
	printf("Enter the numbers: ");
	for (i = 0; i < total_numbers; i++) {
		scanf("%d", &numbers[i]);
	}
	char buffer[BUFFER_SIZE];
	while (base < total_numbers) {
			// Send numbers within window size
		while (next_seq_num < base + window_size && next_seq_num < total_numbers) {
			sprintf(buffer, "%d %d", next_seq_num, numbers[next_seq_num]);
			send(client_socket, buffer, strlen(buffer), 0);
			printf("Sent: Seq %d\n", next_seq_num);
			next_seq_num++;
		}
		// Wait for ACKs
		int ack_received = 0;
		while (!ack_received) {
			fd_set read_fds;
			struct timeval tv;
			tv.tv_sec = TIMEOUT;
			tv.tv_usec = 0;
			FD_ZERO(&read_fds);
			FD_SET(client_socket, &read_fds);
			int retval = select(client_socket + 1, &read_fds, NULL, NULL, &tv);
			if (retval == -1) {
				perror("Error during select");
				break;
			} else if (retval == 0) {
				printf("Timeout! Resending from sequence %d\n", base);
				next_seq_num = base; // Resend only unacknowledged packets
				break;
			} else {
				memset(buffer, 0, BUFFER_SIZE);
				recv(client_socket, buffer, BUFFER_SIZE, 0);
				int ack_num;
				if (sscanf(buffer, "ACK %d", &ack_num) == 1) {
					printf("Received ACK for sequence %d\n", ack_num);
					if (ack_num >= base) {
					base = ack_num + 1; // Move base forward
					ack_received = 1;
					}
				}
			}
		}
	}
printf("All numbers sent successfully!\n");
close(client_socket);
return 0;
}
