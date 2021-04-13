#include <stdio.h>
#include <stdlib.h>

int bin_search(int arr[], int lb, int ub, int target){
    if(lb > ub){
        return -1;
    }
    int m = (lb + ub) / 2;
    if(arr[m] == target){
        return m;
    }
    else if(target > arr[m]){
        return bin_search(arr, m+1, ub, target);
    }
    else{
        return bin_search(arr, lb, m+1, target);
    }
}

int main(){
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    int k = bin_search(arr, 0, 8, 70);
    if(k == -1){
        printf("Target not found");
    }
    else{
        printf("Target found at index %d", k);
    }
    return 0;
}