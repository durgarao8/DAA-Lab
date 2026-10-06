#include <stdio.h>

int main() {
    int n, i, j, temp;
    int swaps = 0;
    int a[50];

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);

    for(i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    // Bubble Sort with Swap Count
    for(i = 0; i < n - 1; i++) {
        for(j = 0; j < n - 1 - i; j++) {
            if(a[j] > a[j + 1]) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                swaps++;
            }
        }
    }

    printf("Sorted array:\n");

    for(i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }

    printf("\nTotal Swaps = %d\n", swaps);

    return 0;
}