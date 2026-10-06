#include<stdio.h>
int main(){
    int i,temp;
    int a[50];
    printf("enter number of elements: ");
    int n;
    scanf("%d",&n);
    printf("enter %d elements:\n",n);
    for(i=0;i<n;i++){
        scanf("%d",&a[i]);      
    }
    for(i=0;i<n-1;i+=2){
        temp=a[i];
        a[i]=a[i+1];    
        a[i+1]=temp;    
    }
    printf("Array after swapping adjacent elements: ");
    for(i=0;i<n;i++){
        printf("%d ",a[i]);
    }
    return 0;
    
}