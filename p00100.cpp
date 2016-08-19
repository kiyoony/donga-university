#include <stdio.h>
void swap(int *p, int *q)
{
	int temp = *p;
	*p = *q;
	*q = temp;
}
int cnt(int n)
{
	long long int rt = n;
	int length = 1;
	while (n != 1)
	{
		if (n % 2)
			n = 3 * n + 1;
		else
			n = n / 2;

		length++;
	}
	return length;
}
int main()
{
	FILE *inp = fopen("p00100.inp", "r");
	FILE *out = fopen("p00100.out","w");
	int a, b,max,c,d;
	while (fscanf(inp, "%d %d", &a, &b) != EOF)
	{
		max = 0;
		c = a, d = b;
		if (a > b)swap(&a, &b);
		for (int i = a; i <= b; i++)
		{
			int temp = cnt(i);
			max = max > temp ? max : temp;
		}
		fprintf(out, "%d %d %d\n", c, d, max);
	}
	return 0;
}