#include <stdio.h>
#include <stdlib.h>

void decToBin(unsigned n){
    if(n == 0){
        printf("0");
        return;
    }
    else if(n == 1){
        printf("1");
        return;
    }
    else{
        decToBin(n/2);
        printf("%d", n%2);
    }

}

int main(){
    decToBin(25);
    return 0;
}