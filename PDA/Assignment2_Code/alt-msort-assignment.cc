#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>
using namespace std;

#define SEQUENTIAL_THRESHOLD 1000

// Get Wall Clock Time
double getWallTime()
{
    struct timeval time;
    if(gettimeofday(&time, NULL))
        return 0;
    double wallTime = (double)time.tv_sec + (double)time.tv_usec * 0.000001;
    return wallTime;
}

//Function to test if array a is sorted
bool isSorted(const int * a, const int n)
{
    bool sorted = true;
    for(int i = 0; i < n-1; ++i)
    {
        if(a[i] > a[i+1])
        {
            sorted = false;
            printf("Not sorted at %d\n", i);
            break;
        }
    }
    return sorted;
}

//Function to populate array a with n random integers
void populateArray(int * a, const int n)
{
    for(int i = 0; i < n; ++i)
        a[i] = rand();
}

//Function to do serial-merge; Used by quicksort_serial
void merge_serial(int * a, int * b, const int lo,
        const int mid, const int hi)
{
    memcpy(&b[lo], &a[lo], (hi - lo)*sizeof(int));
    int i = lo;
    int j = mid;
    for(int k = lo; k < hi; ++k)
    {
        if(i >= mid)
            a[k] = b[j++];
        else if(j >= hi)
            a[k] = b[i++];
        else if(b[j] < b[i])
            a[k] = b[j++];
        else
            a[k] = b[i++];
    }
}

//Function to do serial mergesort
void quicksort_serial(int * a, int * b, const int first, const int last)
{
    //Do a quick sort
    // srand(time(NULL));
    int randex = last-1 ;  
    // int randex = rand() % (last - first) + first ;  
    int temp = a[randex];
    a[randex] = a[first];
    a[first] = temp;

    //partition subroutine
    int i = first+1;
    int pivot = a[first];
    for(int j = first + 1; j < last; j++)
    {
        if(a[j] <= pivot)
        {
            if(i != j)
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
            i++ ;
        }
    }
    temp = a[i-1];
    a[i-1] = a[first];
    a[first] = temp;
    if(i-1-first > 1)
        quicksort_serial(a,b,first,i-1);
    if(last-i > 1)
        quicksort_serial(a,b,i,last);

}

//Binary Search to find element less than or equal to the key
int b_search(int *a, int low, int high, int key)
{
    high = low < high ? high : low ;
    while (low < high)
    {
        int mid = (low + high) / 2;
        if (a[mid]<key)
            low = mid + 1;
        else
            high = mid;
    }
    return low;
}


//Function to do parallel-merge; Used by mergesort_parallel
void merge_parallel(int * a, int * b, 
        const int lo, const int mid, const int hi, 
        const int numThreads)
{
    //Ashish start
    const int length = hi - lo;
    if(length <= SEQUENTIAL_THRESHOLD || numThreads == 1)
    {
        merge_serial(a,b,lo,mid,hi);
        return;
    }

    memcpy(&b[lo], &a[lo], (hi - lo)*sizeof(int));
    const int lenX = mid-lo ;
    const int lenY = hi-mid ;

    if(lenX < lenY)
    {
        memcpy(&a[lo], &b[mid], (hi - mid)*sizeof(int));
        memcpy(&a[lo+(hi-mid)], &b[lo], (mid - lo)*sizeof(int));
        merge_parallel(a,b,lo,lo+(hi-mid),hi,numThreads);
        return;
    }

    int midX = (mid+lo)/2 ;
    int midY = b_search(b,mid,hi,b[midX]);
    int midNew = midX + midY - mid ; 
    memcpy(&a[midX], &b[mid], (midY - mid)*sizeof(int));
    a[midNew] = b[midX];
    memcpy(&a[midNew+1], &b[midX+1], (mid - midX-1)*sizeof(int));
    const int numThreadsLeft = numThreads/2;
    const int numThreadsRight = numThreads - numThreadsLeft;
    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma omp task
            {
                merge_parallel(a, b, lo, midX, midNew, numThreadsLeft);
            }
            #pragma omp task
            {
                merge_parallel(a, b, midNew+1, midY, hi, numThreadsRight);
            }
        }
    }
    //Ashish End
}

//Function to do parallel mergesort
void mergesort_parallel(int * a, int *b,
        const int lo, const int hi, const int numThreads)
{
    const int length = hi - lo;
    if(length <= 1)
        return;
    if(length <= SEQUENTIAL_THRESHOLD || numThreads == 1)
    {
        quicksort_serial(a, b, lo, hi);
        return;
    }
    const int mid = lo + length/2;
    const int numThreadsLeft = numThreads/2;
    const int numThreadsRight = numThreads - numThreadsLeft;
#pragma omp parallel
    {
#pragma omp single
        {
#pragma omp task
            {
                mergesort_parallel(a, b, lo, mid, numThreadsLeft);
            }
#pragma omp task
            {
                mergesort_parallel(a, b, mid, hi, numThreadsRight);
            }
        }
    }
    merge_parallel(a, b, lo, mid, hi, numThreads);
    return;
}

int main(const int argc, char ** argv)
{
    if(argc < 3)
        return 1;
    const int n = atoi(argv[1]); //Number of elements
    const int m = atoi(argv[2]); //Number of times sort is run
    const int numThreads = (argc > 3) ? atoi(argv[3]) : 1;

    //Initialize random number generator
    time_t tt;
    srand((unsigned) time(&tt));

    int * a = (int *)malloc(n * sizeof(int));
    int * b = (int *)malloc(n * sizeof(int));
    double elapsed = 0.0;
    for(int i = 0; i < m; ++i)
    {
        populateArray(a, n);
        double begin = getWallTime();
        mergesort_parallel(a, b, 0, n, numThreads);
        double end = getWallTime();
        elapsed += end - begin;
    }
    printf(" %g\n", elapsed/m);
    if(m == 1)
    {
        const bool sorted = isSorted(a, n);
        if(!sorted)
            printf("Not sorted\n");
    }
    free(a);
    free(b);
    return 0;
}
