#include <stdio.h>
#define MAX 1048577
int position[MAX] = {0,1,1,2};
int main()
{
	FILE *inp = fopen("p00679.inp", "r");
	FILE *out = fopen("p00679.out", "w");
	int btable[21] = { 1, };
	int testcase;
	int iCount = 0;
	int n, m;
	fscanf(inp, "%d", &testcase);
	for (int i = 1; i <= 20; i++)
	{
		btable[i] = btable[i - 1] * 2;
	}
	for (int i = 2; i <= 19; i++)
	{
		int binary = btable[i-1];
		for (int j = 0; j < binary; j++)
		{
			position[btable[i] + (2 * j)] = position[binary + j];
		}
		for (int j = 0; j < binary; j++)
		{
			position[btable[i] + (2 * j)+1] = position[binary + j] +binary;
		}
	}
	for (iCount = 0; iCount < testcase; iCount++)
	{
		fscanf(inp,"%d %d", &n, &m);

		int floor = btable[n];
		int index = 0;
		int add = m / btable[n - 1];

		m = m % btable[n - 1];
		if (!m)
		{
			m = btable[n - 1];
			add--;
		}
		for (index = btable[n-1]; ; index++)
		{
			if (m == position[index])break;
		}

		fprintf(out, "%d\n",index + add*2);
	}
	return 0;
}