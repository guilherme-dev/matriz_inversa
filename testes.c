#include <stdio.h>		
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int n = 100;
	int size = n * n + n / 2;
	printf("size: %d\n", size);
	int v[size];

	int i, j;

	for (i = 0; i < size; ++i)
	{
		v[i] = i;
	}

	


	return 0;
}