#include<stdio.h>
int main(){
    int n,i,j,temp;
    int comparisons=0;
    int a[50];
    printf("Enter number of elements: ");
    scanf("%d",&n);
    printf("Enter %d elements:\n",n);
    for(i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    //bubble sort with comparison count
    for(i=0;i<n-1;i++){
        for(j=0;j<n-i-1;j++){
            comparisons++;
            if(a[j]>a[j+1]){
                temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
        }
    }
    printf("Number of comparisons: %d\n", comparisons);
    return 0;
}