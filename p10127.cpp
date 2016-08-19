#include <stdio.h>
int main()
{
	FILE *inp = fopen("p10127.inp", "r");
	FILE *out = fopen("p10127.out", "w");

	int n;
	while (fscanf(inp,"%d",&n)!=EOF)
	{
		int mod = 1,sum =0,count = 1;
		while (1)
		{
			sum += mod % n;
			if (!sum || !(sum % n))break;
			mod = (mod % n) * 10;
			count++;
		}
		fprintf(out,"%d\n", count);
		
	}
	return 0;
}