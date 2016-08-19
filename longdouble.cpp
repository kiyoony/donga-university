#include <stdio.h>
#define MAX 1003
char ret[MAX];
char retf[MAX];
char A[MAX] = "";
char Af[MAX] = "";
char B[MAX] = "";
char Bf[MAX];
int Al, Bl, Afl, Bfl, rtl, rtfl;
int Ap, Bp; // 부호
int whoisBig() //큰거에서 작은것을 뺀다
{
	int large = Al > Bl ? Al : Bl;
	for (int i = 0; i < large; i++)
	{
		int p = large - 1 - i;
		if (p < Al && p < Bl)
		{
			if (A[p] - '0' > B[p] - '0')return 0;
			else if (A[p] - '0' < B[p] - '0')return 1;
		}
		else if (p < Al)
			return 0;
		else
			return 1;
	}
	large = Afl > Bfl ? Afl : Bfl;
	for (int i = 0; i < large; i++)
	{
		if (i < Afl && i < Bfl)
		{
			if (Af[i] - '0' > Bf[i] - '0')return 0;
			else if (Af[i] - '0' < Bf[i] - '0')return 1;
		}
		else if (i < Afl)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	return 2;//같다
}
int fsub(char *x, char *y, char *rt, int xsize, int ysize, int *rsize)//x 쪽이 더 큼
{
	int large = xsize > ysize ? xsize : ysize;
	int i, temp, carry = 0;
	for (i = 0; i < large; i++)
	{
		int p = large - i - 1;
		if (p< xsize && p < ysize)
		{
			temp = x[p] - '0' - carry - (y[p] - '0');
		}
		else if (p < xsize)
		{
			temp = x[p] - '0' - carry;
		}
		else
		{
			temp = -(y[p] - '0') - carry;
		}
		if (temp < 0)
		{
			carry = 1;
			temp = temp + 10;
		}
		else
		{
			carry = 0;
		}
		rt[p] = temp + '0';
	}
	*rsize = large;
	return carry;
}
void sub(char *x, char *y, char *rt, int xsize, int ysize, int *rsize, int carry)
{
	int large = xsize > ysize ? xsize : ysize;
	int i = 0, temp = 0;
	for (i = 0; i < large; i++)
	{
		if (i < xsize && i < ysize)
		{
			temp = (x[i] - '0') - (y[i] - '0') - carry;
		}
		else if (i < xsize)
		{
			temp = x[i] - '0' - carry;
		}
		else
		{
			temp = -(y[i] - '0') - carry;
		}
		if (temp < 0)
		{
			carry = 1;
			temp = temp + 10;
		}
		else
		{
			carry = 0;
		}
		rt[i] = temp + '0';
	}
	*rsize = large;
}
void sum(char *x, char *y, char *rt, int xsize, int ysize, int *rsize, int carry)
{
	int large = xsize > ysize ? xsize : ysize;
	int i = 0, temp;
	for (i = 0; i < large; i++)
	{
		if (i < xsize && i < ysize)
		{
			temp = x[i] - '0' + y[i] - '0' + carry;
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
int fsum(char *x, char *y, char *rt, int xsize, int ysize, int *rsize)
{
	int large = xsize > ysize ? xsize : ysize;
	int i = 0, temp, carry = 0;
	for (i = 0; i < large; i++)
	{
		int p = large - i - 1;
		if (p < xsize && p < ysize)
		{
			temp = x[p] - '0' + y[p] - '0' + carry;
		}
		else if (p<xsize)
		{
			temp = x[p] - '0' + carry;
		}
		else
		{
			temp = y[p] - '0' + carry;
		}
		rt[p] = temp % 10 + '0';
		carry = temp / 10;
	}
	*rsize = large;
	return carry;
}
void reverse(char *x, int length)
{
	char temp;
	for (int i = 0; i < length / 2; i++)
	{
		temp = x[i];
		x[i] = x[length - i - 1];
		x[length - i - 1] = temp;
	}
}
int refind(char *x, int length)
{
	while (x[length - 1] == '0' && length)length--;
	return length;
}
int main()
{
	FILE *inp = fopen("longdouble.inp", "r");
	FILE *out = fopen("longdouble.out", "w");
	int testcase;
	int iCount = 0, i = 0, who;
	char temp;
	fscanf(inp, "%d\n", &testcase);

	for (iCount = 0; iCount < testcase; iCount++)
	{
		Ap = Bp = 0; // 0 plus		1 minus
		rtl = rtfl = Al = Bl = Afl = Bfl = 0;
		int term = 0; //소수자리 , 정수자리
		while (1) //A 입력
		{
			fscanf(inp, "%c", &temp);
			if (temp == ' ')break;
			if (temp == '-')Ap = 1;
			else if (temp == '.')term = 1;
			else //정수
			{
				if (term)// 소수 차례
				{
					Af[Afl++] = temp;
				}
				else
				{
					A[Al++] = temp;
				}
			}
		}
		term = 0;
		while (fscanf(inp, "%c", &temp) != EOF)
		{
			if (temp == '-')Bp = 1;
			else if (temp == '.')term = 1;
			else if (temp == '\n')break;
			else
			{
				if (term)
				{
					Bf[Bfl++] = temp;
				}
				else
				{
					B[Bl++] = temp;
				}
			}
		}
		reverse(A, Al);
		reverse(B, Bl);
		if (Ap == Bp) // 부호가 같다
		{
			int carry = fsum(Af, Bf, retf, Afl, Bfl, &rtfl);
			sum(A, B, ret, Al, Bl, &rtl, carry);
			rtfl = refind(retf, rtfl);
			if (Ap)fprintf(out, "-");
			for (i = 0; i < rtl; i++) { fprintf(out, "%c", ret[rtl - i - 1]); }
			if (rtfl)
			{
				fprintf(out, ".");
				for (i = 0; i < rtfl; i++) { fprintf(out, "%c", retf[i]); }
			}
			fprintf(out, "\n");
		}
		else
		{
			who = whoisBig();
			if (who == 2)fprintf(out, "0");
			else if (who == 1)
			{
				int carry = fsub(Bf, Af, retf, Bfl, Afl, &rtfl);
				sub(B, A, ret, Bl, Al, &rtl, carry);
				rtl = refind(ret, rtl);
				rtfl = refind(retf, rtfl);
				if ((rtl || rtfl) && Bp)fprintf(out, "-");
				for (i = 0; i < rtl; i++) { fprintf(out, "%c", ret[rtl - i - 1]); }
				if (!rtl)fprintf(out, "0");
				if (rtfl)
				{
					fprintf(out, ".");
					for (i = 0; i < rtfl; i++) { fprintf(out, "%c", retf[i]); }
				}
			}
			else
			{
				int carry = fsub(Af, Bf, retf, Afl, Bfl, &rtfl);
				sub(A, B, ret, Al, Bl, &rtl, carry);
				rtl = refind(ret, rtl);
				rtfl = refind(retf, rtfl);
				if ((rtl || rtfl) && Ap)fprintf(out, "-");
				for (i = 0; i < rtl; i++) { fprintf(out, "%c", ret[rtl - i - 1]); }
				if (!rtl)fprintf(out, "0");
				if (rtfl)
				{
					fprintf(out, ".");
					for (i = 0; i < rtfl; i++) { fprintf(out, "%c", retf[i]); }
				}
			}
			fprintf(out, "\n");
		}
	}
	return 0;
}