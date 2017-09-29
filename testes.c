#include <stdio.h>
#include <stdlib.h>
#define LIN (i*n) - k
int main(int argc, char const *argv[])
{
	int n = 4;
	int size = ((n * n) + n) / 2;
	printf("size: %d\n", size);
	int v[size];

	int i, j, k, col;

	for (i = 0; i < size; ++i)
	{
		v[i] = i;
	}

    k = 0;
    col = n-1;
	for (i = 0; i < n; ++i) {
        printf("%d ", v[i]);
    }
    printf("\n");
    for (i = 1; i < n; ++i) {
        for (j = 0; j < col; ++j) {
            printf("%d ", v[LIN + j]);
        }
        k += i;
        col--;
        printf("\n");
    }


	return 0;
}
