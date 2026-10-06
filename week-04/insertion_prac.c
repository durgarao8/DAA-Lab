#include<stdio.h>
int  main(){
    int n,i,j,key;
    int a[50];
    printf("enter the number of elements: ");
    scanf("%d",&n);
    printf("enter %d elements:\n",n);
    for(i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    // insertion sort
    for(i=1;i<n;i++){
        key=a[i];
        j=i-1;
        while(j>=0&&a[j]>key){
            a[j+1]=a[j];
            j--;
        }
        a[j+1]=key;
    }
    printf("sorted array: ");
    for(int i=0;i<n;i++){
        printf("%d ",a[i]); 
    }

}