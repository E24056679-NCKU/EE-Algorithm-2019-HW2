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



// https://github.com/E24056679-NCKU/lab3_shellsort/blob/master/shellsort.h
template<typename RandomAccessIterator>
void shellSort(RandomAccessIterator begin, RandomAccessIterator end)
{
    for(int gap = (end-begin)>>1 ; gap ; gap >>= 1)
    {
        RandomAccessIterator gap_ptr = begin + gap;
        for(RandomAccessIterator i = begin ; i != gap_ptr ; ++i)
        {
            for(RandomAccessIterator j = i + gap ; j < end ; j += gap)
            {
                RandomAccessIterator pos = j;
                while(pos != i && *(pos) < *(pos-gap) )
                {
                    std::swap(*(pos-gap), *pos);
                    pos -= gap;
                }
            }
        }
    }
}

void _sortK(int* head, int* tail, int K)
{
    if(tail-head < K)
        return;
    int pivot = *head;
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
    
    _sortK(head, rightPtr, K);
    _sortK(rightPtr+1, tail, K);
}

void sortK(int* head, int* tail, int K)
{
    _sortK(head, tail, K);
    insertionSort(head, tail);
}

double sortK_RunTime(int* head, int* tail, int K)
{
    clock_t start = clock();
    sortK(head, tail, K);
    clock_t end = clock();
    return 1000.0*(end-start)/CLOCKS_PER_SEC;
}

int ternarySearch_bestK(const int* head, const int* tail)
{
    int* arr = new int[tail-head];
    int l = 0, r = tail-head-1, m1, m2;
    double tmp1, tmp2;

    int t = 1;
    while( (r-l) >= 3 )
    {
        printf("Ternary Search Iteration %d :\n", t);
        m1 = 1 * (r-l) / 3 + l;
        m2 = 2 * (r-l) / 3 + l;

        memcpy(arr, head, sizeof(int)*(tail-head));
        tmp1 = sortK_RunTime(arr, arr+(tail-head), m1);
        printf("\tK = %d ==> Time = %.3lfms\n", m1, tmp1);

        memcpy(arr, head, sizeof(int)*(tail-head));
        tmp2 = sortK_RunTime(arr, arr+(tail-head), m2);
        printf("\tK = %d ==> Time = %.3lfms\n\n", m2, tmp2);

        if(tmp1 > tmp2)
            l = m1;
        else
            r = m2;
        t++;
    }

    int K = -1;
    double minV = 1e9;
    for(int i=l ; i<=r ; ++i)
    {
        printf("Ternary Search Final Examination :\n");
        memcpy(arr, head, sizeof(int)*(tail-head));
        tmp1 = sortK_RunTime(arr, arr+(tail-head), i);
        printf("\tK = %d ==> Time = %.3lfms\n", i, tmp1);

        if( tmp1 < minV )
        {
            minV = tmp1;
            K = i;
        }
    }
    delete[] arr;
    return K;
}

int main()
{
    srand(time(0)); // reset random seed
    clock_t start, end;

    int size = 1<<20;
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
    printf("QuickSort ==> Time = %.3lfms\n\n", 1000.0*(end-start)/CLOCKS_PER_SEC);

    memcpy(arr, A, sizeof(int)*(size));
    int K = ternarySearch_bestK(arr, arr+size);
    printf("K = %d\n", K);

    delete[] A;
    delete[] arr;
    return 0;
}