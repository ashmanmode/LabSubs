#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <omp.h>
int sum=0; //Global variable touched by all threads
//Function to be called by each thread
void adder() {
#pragma omp critical
{
int t = sum; sleep(1); sum = t + 1;
}
return;
}
int main() {
const int numThreads=24;
int i;
omp_set_num_threads(numThreads);
#pragma omp parallel for shared(sum)
for(i = 0; i < numThreads; ++i)
adder();
printf("Sum computed: %d\n",sum);
return 0;
}