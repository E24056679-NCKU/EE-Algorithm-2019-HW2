#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>

void insertionSort(int* head, int* tail) // [a, b)
{
    int* rightPtr = head+1; // the last number of subarray

    while(rightPtr < tail)
    {
        if( *(rightPtr-1) > *rightPtr )
        {
            int tmp = *rightPtr;
            int* i_ptr;
            // right shift numbers in the range
            for(i_ptr = rightPtr-1 ; *(i_ptr) > tmp && i_ptr >= head ; --i_ptr)
            {
                *(i_ptr+1) = *i_ptr;
            }
            *(i_ptr+1) = tmp;
        }
        rightPtr++;
    }
}

void quickSort(int* head, int* tail) // [a, b)
{
    if(tail-head <= 1) // if array size <= 1, return
        return;
    int pivot = *head; // select head to be the pivot
    int* leftPtr = head+1, *rightPtr = tail-1;
    
    while(leftPtr <= rightPtr)
    {
        while(leftPtr < tail)
            if(*leftPtr <= pivot)
                leftPtr++;
            else
                break;
        while(rightPtr > head)
            if(*rightPtr >= pivot)
                rightPtr--;
            else
                break;
        if(leftPtr <= rightPtr)
        {
            std::swap(*leftPtr, *rightPtr);
            leftPtr++;
            rightPtr--;
        }
    }
    std::swap(*rightPtr, *head);
    
    quickSort(head, rightPtr);
    quickSort(rightPtr+1, tail);
}

int* generateNearlySortedArray(int size)
{
    int* a = new int[size];
    for(int i=0;i<size;++i)
        a[i] = i;
    // randomly swap 1% of elements
    for(int i=0, bound=size/100;i<bound;++i)
        std::swap(a[rand()%size], a[rand()%size]);
    return a;
}

int main()
{
    srand(time(0));
    clock_t start, end;

    int size = 10000;
    const int* A = generateNearlySortedArray(size); // a is the array for functions to sort
    int* arr = new int[size]; // the array which is actually be sorted, it should be a copy of array A

    memcpy(arr, A, sizeof(int)*(size)); // copy A to arr
    start = clock();
    insertionSort(arr, arr+size);
    end = clock();
    printf("InsertionSort ==> Time = %.3lfms\n", 1000.0*(end-start)/CLOCKS_PER_SEC);
    
    memcpy(arr, A, sizeof(int)*(size));
    start = clock();
    quickSort(arr, arr+size);
    end = clock();
    printf("QuickSort ==> Time = %.3lfms\n", 1000.0*(end-start)/CLOCKS_PER_SEC);

    delete[] A;
    delete[] arr;
    return 0;
}