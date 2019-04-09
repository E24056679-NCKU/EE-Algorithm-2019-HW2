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

int main()
{
    int N;
    scanf("%d", &N);
    int* arr = new int[N];
    for(int i=0;i<N;++i)
        scanf("%d", arr+i);

    insertionSort(arr, arr+N);
    
    printf("%d\n", N);
    for(int i=0;i<N;++i)
        printf("%d\n", arr[i]);
    delete[] arr;
    return 0;
}