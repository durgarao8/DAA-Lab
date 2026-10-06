#include <stdio.h>

// Function to perform Bubble Sort
void bubbleSort(int a[], int n) {
    int i, j, temp;

    for(i = 0; i < n - 1; i++) {
        for(j = 0; j < n - 1 - i; j++) {
            if(a[j] > a[j + 1]) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

// Function to perform Selection Sort
void selectionSort(int a[], int n) {
    int i, j, minIndex, temp;

    for(i = 0; i < n - 1; i++) {
        minIndex = i;

        for(j = i + 1; j < n; j++) {
            if(a[j] < a[minIndex]) {
                minIndex = j;
            }
        }

        temp = a[i];
        a[i] = a[minIndex];
        a[minIndex] = temp;
    }
}

// Function to perform Insertion Sort
void insertionSort(int a[], int n) {
    int i, j, key;

    for(i = 1; i < n; i++) {
        key = a[i];
        j = i - 1;

        while(j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = key;
    }
}

// Function to copy one array to another
void copyArray(int source[], int destination[], int n) {
    int i;

    for(i = 0; i < n; i++) {
        destination[i] = source[i];
    }
}

// Function to print an array
void printArray(int a[], int n) {
    int i;

    for(i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }

    printf("\n");
}

int main() {
    int n, i;
    int original[50], bubble[50], selection[50], insertion[50];

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);

    for(i = 0; i < n; i++) {
        scanf("%d", &original[i]);
    }

    
    copyArray(original, bubble, n);
    copyArray(original, selection, n);
    copyArray(original, insertion, n);


    bubbleSort(bubble, n);
    selectionSort(selection, n);
    insertionSort(insertion, n);

  
    printf("\nBubble Sort: ");
    printArray(bubble, n);

    printf("Selection Sort: ");
    printArray(selection, n);

    printf("Insertion Sort: ");
    printArray(insertion, n);

    return 0;
}