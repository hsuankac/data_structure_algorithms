

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

/*
 function prototypes
 */

/**
 Description: tests whether the array is sorted or not in a particular order. If sorted
 returns 1 otherwise returns 0.
 array[]: integer array containing n elements in the index range 1:n
 n: total number of elements in the array
 order: if 1 passed then the function tests for ascending order, for 0 tests for descending order.
 Return value: 1, if the array is sorted in a particular order, 0 otherwise.
 */
int isSorted(int array[], int n, int order);

/**
 Description: to input integers from console and assign them into the elements of array
 Input Parameters:
 heapArray[]: array of integers, base index is 1, 0th index is not used
 n: number of elements in the array
 return value: Nothing
 
 */
void inputDataFromConsole(int array[], int n);

/**
 Description: To print the content of the array into output console
 Input Parameters:
 heapArray[]: array of integers, base index is 1, 0th index is not used
 n: number of elements in the array
 return value: Nothing
 
 */
void printDataToConsole(int array[], int n);

/**
 Description: Randomly generates n integer using the rand function and assigns them
 into the array element.
 Input Parameters:
 heapArray[]: array of integers, base index is 1, 0th index is not used
 n: number of elements in the array
 return value: Nothing
 
 */
void fillRandomData(int array[], int n);

/**
 Description: Helper function to get time difference in milli-seconds.
 Input Parameters:
 struct timeval start: start time
 struct timeval end: end time
 Return value: elapsed time in milli sec (float).
 */
float timediff(struct timeval start, struct timeval end);


/**
 Description: At index 2*i and 2*i+1 max heap is maintained, but Max heap is not maintained at index i, adjusts the index i so that a max heap is maintained at index i. 
    heapArray[]: integer array for keeping the heap. First elements index is 1, last index is n.
    i: integer, this is the index that should be restored.
    n: total elements in the heap.
 
 
 */
void adjust(int heapArray[], int i, int n);

/**
 Description: sorts the integer array in ascending in-place using heapsort algorithm
 heapArray[]: Unsorted integer array containing n numbers in the range 1:n, first
    index is 1 last is n.
 n: total number of elements in the array.
 */
void heapSort(int array[], int n);

/**
 Description: builds a max heap in-place in the supplied array by adjusting index starting from n/2 to 1. The array contains n elements in the range 1:n, that is first index is 1 and last is n.
 n: total number of elements in the array
 */
void heapify(int array[], int n);



// ------ Implementations -----
void adjust(int heapArray[], int i, int n){
    int j = 2 * i; // left child of i
    int item = heapArray[i];  // getting the content of the index i in variable temp
    
    // iterate as long as j is valid, that means there is an element at j
    while(j <= n){
        // compare between j and its sibling if sibling exists
        if(j < n && heapArray[j] < heapArray[j+1]){
            j = j + 1;
        }
        if (item >= heapArray[j]){
            break;
        }
        heapArray[j/2] = heapArray[j];
        j = 2 * j;
    }
    heapArray[j/2] = item;
}

void heapSort(int array[], int n){
    // calling heapify for building the heap in place
    heapify(array, n);
    int i;
    int temp;
    // doing the heap sort.
    for(i = n; i >=2 ; --i){
        // getting the largest element from the root
        temp = array[1];
        // copying the last element from the heap into the root.
        array[1] = array[i];
        // adjust the root
        adjust(array, 1, i-1);
        //place the largest element that we just deleted into the index i
        array[i] = temp;
    }
}

void heapify(int array[], int n){
    int i;
    for(i = n/2; i>=1; --i){
        adjust(array, i, n);
    }
}




int isSorted(int array[], int n, int order){
    int i;
    int sorted = 1;
    for(i = 1; i <= n - 1 && sorted; ++i){
        // if order is not 0, we should check for ascending
        // order sorting, in this case if current ith element is greater than
        // the next one, then the array is not sorted in ascending.
        if (order != 0 && array[i] > array[i+1]){
            sorted = 0;
        }
        
        // if order is 0, we should check for descending order checking, so
        // if ith element is less than the next, then no more in descending order,
        // we should terminate checking.
        if (order == 0 && array[i] < array[i+1]){
            sorted = 0;
        }
    }
    return sorted;
}

void inputDataFromConsole(int array[], int n){
    int i;
    printf("Please input integer numbers\n");
    printf("You will need to input %d integers in total\n\n", n);
    // iterate n times from 0 to n-1, each time ask for input and
    // take the input using scanf into the ith element of the array
    for(i = 1; i <= n; ++i){
        printf("array [%d]: ", i);
        scanf("%d", &array[i]);
    }
    
}

void printDataToConsole(int array[], int n){
    int i;
    printf("Content of the array\n");
    printf("----------------------\n");
    for(i = 1; i <= n; ++i){
        printf("%6d", array[i]);
        // give a line break after every 10 numbers
        if (i % 10 == 0){
            printf("\n");
        }
    }
    
    printf("\n\n");
}

void fillRandomData(int array[], int n){
    int i;
    // randomize the seed using current system time, this is required to generate
    // different series of random numbers on every call. Otherwise, rand() function
    // will generate the same set of random numbers.
    srand((unsigned)time(NULL));
    // Now fill the array
    for(i = 1; i <= n; ++i){
        array[i] = rand() % 10000;  // we fill the array with numbers from 0 - 9999
    }
}

float timediff(struct timeval start, struct timeval end)
{
    return (end.tv_sec - start.tv_sec) * 1000.0f + (end.tv_usec - start.tv_usec) / 1000.0f;
}

int main(){
    
    struct timeval start;
    struct timeval end;
    float elapsed;
    
    int n;
    n = 10;
    int *array = (int *)malloc(sizeof(int) * (n+1));
    if (array == NULL){
        printf("Unable to allocate dynamic memory\n");
        return 1;
    }
    // fill the array with the elements
    fillRandomData(array, n);
    
    // uncomment the following if you want to display the array content into console
    //printf("Unsorted array: \n");
    //printDataToConsole(array, n);
    
    
    printf("Going to perform heap sort on %d numbers, please wait ...\n", n);
    gettimeofday(&start, 0);
    heapSort(array, n);
    gettimeofday(&end, 0);
    
    // check if the array is sorted.
    if (isSorted(array, n, 1))
        printf("Sorted in ascending order\n");
    else
        printf("Not sorted in ascending order\n");
    
    // uncomment the following if you want to display the sorted content of the array
    // into console.

    printf("Sorted array: \n");
    printDataToConsole(array, n);
    
    elapsed = timediff(start, end);
    printf("Time taken to sort %d numbers using heap sort is: %f msec\n", n, elapsed);
    free(array);
    
    return 0;
}
