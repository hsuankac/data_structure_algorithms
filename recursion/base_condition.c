#include <stdio.h>
#include <stdlib.h>

void print(int n){
    if(n<=0){ // base condition
        return;
    }
    // printf("Hello!! n = %d\n", n);
    print(n-1);
    printf("Hello!! n = %d\n", n);
}

int main(){
    print(3);
    return 0;
}