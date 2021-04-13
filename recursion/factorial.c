#include <stdio.h>
#include <stdlib.h>

unsigned int factorial(unsigned int n){
    if(n == 0){
        return 1;
    }
    return  n * factorial(n-1);
}

int main(){
    printf("%u\n",factorial(5));
    return 0;
}