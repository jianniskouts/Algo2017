#include <stdio.h>
#include <stdlib.h>

long long int T = 0;
long long int d = 0;


long long int manhattan(long long int ax, long long int ay, long long int bx, long long int by) {
    return labs(ax - bx) + labs(ay - by);
}
long long int compare(const void *a, const void *b) {
    return (*(long long int **)a)[d] - (*(long long int **)b)[d];
}

int cmpfunc (const void * a, const void * b)
{
    if( (*(long long int**)a)[d] - (*(long long int**)b)[d] < 0 )
        return -1;
    if( (*(long long int**)a)[d] - (*(long long int**)b)[d] > 0 )
        return 1;
    return 0;
}


long long int * min(long long int **points, long long int N, long long int dim) {
    long long int *min = points[0];
    long long int i = 0;
    for (i = 0; i < N; i++) {
        if (min[dim] > points[i][dim]) {
            min = points[i];
        }
    }
    return min;
}

long long int * geometric_median_with_manhattan(long long int **points, long long int N, long long int dim) {
    
    long long int temp;
    long long int S = 0;
    for (d = 0; d < dim; d++) {
        //printf("point before: %lld\n",points[0][d]);
        qsort(points, N, sizeof(long long int *), cmpfunc);
       // printf("point after: %lld\n",points[0][d]);
        S = 0;
        long long int i = 0;
        for (i = 0; i < N; i++) {
            long long int v = points[i][d];
            //printf("     points: %lld\n",points[i][d]);
            temp = (2 * i - N) * v - 2 * S;
            points[i][dim] += temp;
            S += v;

        }
    }
    
    return min(points, N, dim);
}
int main(){
    long long int N;
    scanf("%lld", &N);
   // long long int** b;
    long long int** a = (long long int**) malloc(sizeof(long long int*) * N);
    long long int i;
    for ( i = 0; i < N; ++i) {
        a[i] = (long long int*) malloc(sizeof(long long int) * 2);
        scanf("%lld %lld", &a[i][0], &a[i][1]);
        a[i][2] = 0;
        //**b = *a[i];
    }
   // long long int *b[] = {a[0], a[1], a[2], a[3]};

    long long int *min = geometric_median_with_manhattan(a, N, 2);
    //printf("geometric median at {%lld, %lld}\n", min[0], min[1]);
    long long int length = 0;
    for ( i = 0; i < N; i++) {
        length += manhattan(min[0], min[1], a[i][0], a[i][1]);
    }
    printf("%lld\n",length);
    return 0;
}