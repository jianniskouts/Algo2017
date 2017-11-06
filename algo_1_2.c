#include <stdio.h>
#include <stdlib.h>

int T = 0;
int d = 0;


int manhattan(int ax, int ay, int bx, int by) {
    return labs(ax - bx) + labs(ay - by);
}
int compare(const void *a, const void *b) {
    return (*(int **)a)[d] - (*(int **)b)[d];
}

int * min(int **points, int N, int dim) {
    int *min = points[0];
    int i = 0;
    for (i = 0; i < N; i++) {
        if (min[dim] > points[i][dim]) {
            min = points[i];
        }
    }
    return min;
}

int * geometric_median_with_manhattan(int **points, int N, int dim) {
    
    int temp;
    int S = 0;
    for (d = 0; d < dim; d++) {
        qsort(points, N, sizeof(int *), compare);
        S = 0;
        int i = 0;
        for (i = 0; i < N; i++) {
            int v = points[i][d];
            temp = (2 * i - N) * v - 2 * S;
            points[i][dim] += temp;
            S += v;

        }
    }
    
    return min(points, N, dim);
}
int main(){
    int N;
    scanf("%d", &N);

    int** a = (int**) malloc(sizeof(int*) * N);
    int i;
    for (i = 0; i < N; ++i) {
        a[i] = (int*) malloc(sizeof(int) * 2);
        scanf("%d %d", &a[i][0], &a[i][1]);
        a[i][2] = 0;
    }
    int *b[] = {a[0], a[1], a[2], a[3]};

    int *min = geometric_median_with_manhattan(b, 4, 2);
    //printf("geometric median at {%d, %d}\n", min[0], min[1]);
    int length = 0;
    for (i = 0; i < N; i++) {
        length += manhattan(min[0], min[1], a[i][0], a[i][1]);
    }
    printf("%d\n",length);
    return 0;
}