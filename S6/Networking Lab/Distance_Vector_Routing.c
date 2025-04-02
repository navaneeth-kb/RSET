#include <stdio.h>
#include <string.h>

#define INF 9999  // Define a large number as infinity

int costMatrix[20][20], n;

struct routers {
    int distance[20];  // Stores distance to all other nodes
    int adjNodes[20];  // Store next hop
    char name[20];     // Store the name of the router
} node[20];

// Function to read the names of nodes
void readNodeNames() {
    printf("Enter the names for the nodes:\n");
    for (int i = 0; i < n; ++i) {
        printf("Enter name for node %d: ", i + 1);
        scanf("%s", node[i].name);  // User-defined name for the node
    }
}

// Function to read the cost matrix
void readCostMatrix() {
    printf("\nEnter the cost matrix:\n");
    printf("For no direct connection, enter %d for infinity.\n", INF);
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                costMatrix[i][j] = 0;  // Distance from a node to itself is always 0
            } else {
                printf("Enter the distance from node %s to node %s: ", node[i].name, node[j].name);
                scanf("%d", &costMatrix[i][j]);
                
                if (costMatrix[i][j] == 0) {  
                    costMatrix[i][j] = INF;  // No direct connection is considered infinity
                }
            }
            node[i].distance[j] = costMatrix[i][j];
            node[i].adjNodes[j] = (costMatrix[i][j] == INF) ? -1 : j;  // Direct neighbor or no connection
        }
    }
}

// Function to compute the routing table using Distance Vector Routing
void calcRoutingTable() {
    for (int k = 0; k < n; ++k) {  // Intermediate node
        for (int i = 0; i < n; ++i) {  // Source node
            for (int j = 0; j < n; ++j) {  // Destination node
                // Check if the new path through 'k' is shorter
                if (node[i].distance[j] > costMatrix[i][k] + node[k].distance[j]) {
                    node[i].distance[j] = costMatrix[i][k] + node[k].distance[j];
                    node[i].adjNodes[j] = node[i].adjNodes[k];  // Store the correct next hop
                }
            }
        }
    }
}

// Function to display the routing table
void displayRoutes() {
    for (int i = 0; i < n; ++i) {
        printf("\nRouter %s\n", node[i].name);
        for (int j = 0; j < n; ++j) {
            if (node[i].distance[j] == INF) {
                printf("Node %s via - : INFINITY\n", node[j].name);
            } else {
                printf("Node %s via %s : %d\n", node[j].name, node[node[i].adjNodes[j]].name, node[i].distance[j]);
            }
        }
        printf("\n");
    }
}

int main() {
    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    readNodeNames();     // Input the names for all nodes
    readCostMatrix();    // Input the cost matrix
    calcRoutingTable();  // Calculate the routing table
    displayRoutes();     // Display the routing table

    return 0;
}
