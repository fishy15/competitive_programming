#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0
typedef int bool;

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int nums[100];
bool v[100];
int main() {
    FILE* fin = fopen("angry.in", "r");
    FILE* fout = fopen("angry.out", "w");
    int nums[100];
    int n;

    fscanf(fin, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(fin, "%d", &nums[i]);
    }

    qsort(nums, n, sizeof(int), cmpfunc);
}
