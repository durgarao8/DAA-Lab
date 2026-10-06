#include <stdio.h>

int main() {
    int n, i;
    int a[50];
    int sorted = 1;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);

    for(i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for(i = 0; i < n - 1; i++) {
        if(a[i] > a[i + 1]) {
            sorted = 0;
            break;
        }
    }

    if(sorted == 1)
        printf("Array is already sorted in ascending order.\n");
    else
        printf("Array is not sorted.\n");

    return 0;
}