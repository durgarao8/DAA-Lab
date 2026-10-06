#include <stdio.h>

int main() {
    int n, i, minIndex, temp;
    int a[50];

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);

    for(i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    // Find the smallest element
    minIndex = 0;

    for(i = 1; i < n; i++) {
        if(a[i] < a[minIndex]) {
            minIndex = i;
        }
    }

    // Swap the smallest element with the first element
    temp = a[0];
    a[0] = a[minIndex];
    a[minIndex] = temp;

    printf("Array after selecting the first minimum:\n");

    for(i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }

    printf("\n");

    return 0;
}