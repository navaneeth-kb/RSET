#include <stdio.h>
int a[50];
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && a[left] > a[largest]) {
        largest = left;
    }

    if (right < n && a[right] > a[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(&a[i], &a[largest]);
        heapify(n, largest);
    }
}

void heap_sort(int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(&a[0], &a[i]);
        heapify(i, 0);
    }
}

void main() {
    int max;
    printf("\nEnter max value: ");
    scanf("%d", &max);

    printf("Input array elements: ");
    for (int i = 0; i < max; i++) {
        scanf("%d", &a[i]);
    }

    printf("\nThe array elements are: ");
    for (int i = 0; i < max; i++) {
        printf("%d ", a[i]);
    }

    heap_sort(max);

    printf("\nArray after sorting: ");
    for (int i = 0; i < max; i++) {
        printf("%d ", a[i]);
    }
}
