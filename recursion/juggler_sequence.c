#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// printing Juggler sequence
int juggler(int a){
    if(a == 1){
        printf("%4d", a);
        return;
    }

    printf("%4d", a);
    juggler(a % 2 != 0 ? (int)pow(a, 1.5) : (int)pow(a, 0.5));
}

int main(){
    juggler(3);
    return 0;
}