#include <stdio.h>
int main()
{
	FILE *inp = fopen("snail.inp", "r");
	FILE *out = fopen("snail.out", "w");
	double H, U, D, F;
	while (1)
	{
		fscanf(inp, "%lf %lf %lf %lf", &H, &U, &D, &F);
		if (!H)break;
		double u = U,cur = 0;
		F = F * 0.01;
		int day = 1,flag;
		while (1)
		{
			if(u>0)
				cur += u;
			if (cur > H) {
				flag = 1;
				break;
			}
			u = u - U*F;
			cur -= D;
			if (cur < 0) {
				flag = 0;
				break;
			}
			day++;
		}
		fprintf(out, "%s on day %d\n", flag ? "success" : "failure", day);
	}
	return 0;
}