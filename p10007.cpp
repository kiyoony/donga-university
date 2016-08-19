#include <stdio.h>
#define MAX 1000
char catalan[301][MAX] = { "1","1","2" };
int ctlength[301] = { 1,1,1 };
char factorial[301][MAX] = { "0","1","2" };
int faclength[301] = { 1,1,1 };
char result[MAX];
char A[MAX]="";
char B[MAX]="";

void IntToChar(char *x,int n,int *size) // xø° ¿˙¿Â
{
	int index = 0;
	while (n)
	{
		x[index] = n % 10 + '0';
		n = n / 10;
		index++;
	}
	x[index] = '\0';
	*size = index;
}
void multiple(char *x, char *y, char *rt, int xsize, int ysize, int *rsize)
{
	int i, j , carry = 0,temp;
	for (i = 0; i < xsize; i++)
	{
		carry = 0;
		for (j = 0; j < ysize; j++)
		{

			temp = ((x[i] - '0') * (y[j] - '0')) + carry;
			if (rt[i + j] != '\0') temp += rt[i + j] - '0';
			carry = temp / 10;
			rt[i + j] = (temp % 10) + '0';
		}
		if(carry)
			rt[i + ysize] = carry + '0';
	}
	*rsize = xsize + ysize - 1;
	if (carry)
		*rsize += 1;
}
void sum(char *x, char *y, char *rt, int xsize, int ysize, int *rsize)
{
	int large = xsize > ysize ? xsize : ysize;
	int i = 0,temp,carry = 0;
	for (i = 0; i < large; i++)
	{
		if (i < xsize && i < ysize)
		{
			temp = x[i] -'0' + y[i] -'0' + carry;
			rt[i] = (temp % 10) + '0';
			carry = temp / 10;
		}
		else if (i < xsize)
		{
			temp = x[i] - '0' + carry;
			rt[i] = (temp % 10) + '0';
			carry = temp / 10;
		}
		else // i < ysize
		{
			temp = y[i] - '0' + carry;
			rt[i] = (temp % 10) + '0';
			carry = temp / 10;
		}
	}
	if (carry)
	{
		rt[large] = carry + '0';
	}
	*rsize = large + carry;
}
int main()
{
	FILE *inp = fopen("p10007.inp", "r");
	FILE *out = fopen("p10007.out", "w");

	int rs, i, j, n;
	for (i = 3; i <= 300; i++)
	{
		IntToChar(A, i, &rs);
		multiple(factorial[i - 1], A, factorial[i], faclength[i - 1], rs, &faclength[i]);

		for (j = 0; j < i; j++)
		{
			char buf[MAX] = { 0, };
			multiple(catalan[j], catalan[i - j - 1], buf, ctlength[j], ctlength[i - j - 1], &rs);
			sum(catalan[i], buf, catalan[i], ctlength[i], rs, &ctlength[i]);
		}
	}
	while (1)
	{
		fscanf(inp,"%d", &n);
		if (!n)break;
		char buf[MAX] = { 0, };
		multiple(catalan[n], factorial[n], buf, ctlength[n], faclength[n], &rs);
		for (i = 0; i < rs; i++)
		{
			fprintf(out,"%c", buf[rs - i - 1]);
		}
		fprintf(out,"\n");
	}
	return 0;
}