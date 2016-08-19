	#include <stdio.h>
int main()
{
	FILE *inp = fopen("p10469.inp", "r");
	FILE *out = fopen("p10469.out", "w");
	long long int n, m;
	while (fscanf(inp,"%lld %lld", &n, &m) != EOF)
	{
		fprintf(out,"%lld\n", n^m);
	}
	return 0;
}