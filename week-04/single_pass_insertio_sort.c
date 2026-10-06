#include<stdio.h>
int main(){
    int n, i, j, key;
    int a[50];

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);

    for(i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    //single pass of insertion sort
    key=a[1];
    j=0;
    while(j>=0 && a[j]>key){
        a[j+1]=a[j];
        j--;
    }
    a[j+1]=key;
    printf("Array after inserting the second element correctly: ");
    for(i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    return 0;
}