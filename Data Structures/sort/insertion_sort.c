#include <stdio.h>

void main() {
    int max;
    printf("Enter max value: ");
    scanf("%d", &max);
    int arr[max];

    for (int i = 0; i < max; i++) {
        printf("Input array element: ");
        scanf("%d", &arr[i]);

        int curr = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > curr) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = curr;

        printf("Array after insertion: ");
        for (int k = 0; k <= i; k++) {
            printf("%d\t", arr[k]);
        }
        printf("\n");
    }
}
