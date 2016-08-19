#include <stdio.h>
double arr[1000];
double abs(double n)
{
	return n > 0 ? n : -n;
}
int main()
{
	FILE *inp = fopen("p10137.inp", "r");
	FILE *out = fopen("p10137.out", "w");
	int n, i;
	double sum = 0;
	double m = 0,p = 0;
	double s = 0;
	double avg;
	
	while (1)
	{
		fscanf(inp, "%d", &n);
		if (!n)return 0;
		sum = 0;
		for (i = 0; i < n; i++)
		{
			fscanf(inp,"%lf", &arr[i]);
			sum += arr[i];	
		}
		avg = sum / n;
		m = p = 0;
		for (i = 0; i < n; i++)
		{
			s = (double)((int)((arr[i] - avg)*100))/100;
			if (s >= 0)p += s;
			else m += s;
		}
		m = abs(m);
		fprintf(out,"$%.2lf\n", m > p ? m : p);
	}
	return 0;
}