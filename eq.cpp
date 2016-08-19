#include <stdio.h>
int main()
{
	FILE *inp = fopen("eq.inp", "r");
	FILE *out = fopen("eq.out", "w");
	int testcase;
	int iCount = 0;
	int n, a, b, c, i, j, k;
	fscanf(inp, "%d", &testcase);
	
	for (iCount = 0; iCount < testcase; iCount++)
	{
		fscanf(inp, "%d %d %d", &a, &b, &c); 
		int flag = 0;
		for (i = -316; (i * 3) <= a && i<= 316; i++)
		{
			for (j = i; (i + (2 * j)) <= a && j <= 316; j++)
			{
				for (k = j; (i * j) > 0 && (i + j + k) <= a && k <=316; k++) // ÃÖ´ë 316  ( 317 * 317 > 100,000 )
				{
					if (((i + j + k) == a ) && ((i * j * k) == b) && (((i*i) + (j*j) + (k*k) )== c) )
					{
						flag = 1;
						break;
					}
				}
				if (flag)break;
			}
			if (flag)break;
		}
		if (flag)
		{
			fprintf(out, "%d %d %d\n", i, j, k);
		}
		else
		{
			fprintf(out, "No solution.\n");
		}
	}
	return 0;
}