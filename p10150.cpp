#include <stdio.h>
#define MAX 25143
char Text[MAX][17];
int TextLength[MAX];
char S[17];
char E[17];
int sL, eL;
int length(char *x)
{
	int index = 0;
	while (x[index] != '\n' && x[index]!='\0')index++;
	x[index] = '\0';
	return index;
}
int match(char *x, char *y)
{
	int index = 0,cnt = 0;
	for (index; x[index] != '\0'; index++)
	{
		if (x[index] != y[index])cnt++;
	}
	return cnt;
}
int main()
{
	FILE *inp = fopen("p10150.inp", "r");
	FILE *out = fopen("p10150.out", "w");
	int N = 0, fstep = 0;

	while (1)
	{
		fgets(Text[N], 17, inp);
		TextLength[N] = length(Text[N]);
		if (!TextLength[N])break;
		else N++;
	}
	//N 개
	while (fscanf(inp, "%s %s", S, E)!=EOF)
	{
		if (fstep)fprintf(out, "\n");
		int check[MAX];
		int Queue[MAX];
		int front, rear;
		fstep = 1;
		front = rear = 0;
		sL = length(S), eL = length(E);
		int sP = -1;//시작 포인트
		for (int i = 0; i < N; i++)
		{
			check[i] = -1;
		}
		for (int i = 0; i < N; i++)
		{
			if (TextLength[i] == sL)
			{
				if (!match(Text[i], S))
				{
					sP = i;
					break;
				}
			}
		}
		if (sP < 0)
		{
			fprintf(out, "No solution.\n");
		}
		else
		{
			int flag = 0;
			Queue[rear++] = sP;
			check[sP] = sP;
			while (front < rear)
			{
				sP = Queue[front++];
				if (!match(Text[sP], E))
				{
					flag = 1;
					break;
				}

				for (int i = 0; i < N; i++)
				{
					if (sP != i && check[i] < 0 && TextLength[i] == TextLength[sP] && match(Text[i], Text[sP]) == 1)
					{
						check[i] = sP;
						Queue[rear++] = i;
					}
				}
			}
			if (!flag)
			{
				fprintf(out, "No solution.\n");
			}
			else
			{
				int flow[MAX] = { sP, };
				int i;
				for (i = 1; check[sP] != sP; i++)
				{
					flow[i] = check[sP];
					sP = check[sP];
				}
				i = i - 1;
				while (i >= 0)
				{
					fprintf(out, "%s\n", Text[flow[i--]]);
				}
			}
		}


	}
	return 0;
}