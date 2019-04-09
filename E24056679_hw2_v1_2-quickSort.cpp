#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>

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

int main()
{
    int N;
    scanf("%d", &N);
    int* arr = new int[N];
    for(int i=0;i<N;++i)
        scanf("%d", arr+i);

    quickSort(arr, arr+N);
    
    printf("%d\n", N);
    for(int i=0;i<N;++i)
        printf("%d\n", arr[i]);
    delete[] arr;
    return 0;
}