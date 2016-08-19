#include <stdio.h>
char suit[4][10] = { "Clubs", "Diamonds","Hearts","Spades" };
char value[13][10] = { "2","3","4","5","6","7","8","9","10","Jack","Queen","King","Ace" };

int get(char *x)
{
	int sum = 0;
	for (int i = 0; i<3; i++)
	{
		if (x[i] >= '0' && x[i] <= '9') {
			if (sum)
				sum = sum * 10;

			sum += x[i] - '0';
		}
	}
	return sum;
}
int main()
{
	FILE *inp = fopen("p10205.inp", "r");
	FILE *out = fopen("p10205.out", "w");
	int testcase;
	int iCount = 0;

	fscanf(inp, "%d", &testcase);

	for (iCount = 0; iCount < testcase; iCount++)
	{
		int n;
		int pos[101][53];
		int cur[2][53];
		char Text[5];
		int type;
		if (iCount)fprintf(out, "\n");

		fscanf(inp, "%d", &n);
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= 52; j++)
			{
				fscanf(inp, "%d", &pos[i][j]);
			}
		}
		for (int i = 1; i <= 52; i++)
		{
			cur[0][i] = cur[1][i] = i;
		}
		fgets(Text, 4, inp);
		char temp;
		int i = 0;
		while (fgets(Text, 5, inp) && Text[0])
		{
			type = get(Text);
			if (!type)break;
			for (int j = 1; j <= 52; j++)
			{
				cur[i % 2][j] = cur[(i + 1) % 2][pos[type][j]];
			}
			i++;
		}
		n = i;



		for (int i = 1; i <= 52; i++)
		{
			int suitN = (cur[(n + 1) % 2][i] - 1) / 13;
			int valueN = (cur[(n + 1) % 2][i] - 1) % 13;
			fprintf(out, "%s of %s\n", value[valueN], suit[suitN]);
		}
	}
	return 0;
}