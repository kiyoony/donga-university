#include <stdio.h>
void swap(int *x,int *y)
{
	int temp = *y;
	*y = *x;
	*x = temp;
}
int main()
{
	long long int Combo[21][21];
	long long int Factorial[21]={1,};
	FILE *inp = fopen("pole.inp","r");
	FILE *out = fopen("pole.out","w");

	int i , j;
	int n,L,R;
	int testcase;
	int iCount;
	int Cnt = 0;
	int x, y , a , b;
	long long int result = 0;
	for(i = 0 ; i <= 20; i ++)
	{
		Combo[i][0] = 1;
		Combo[0][i] = 1;
	}
	for(i = 1 ; i <=20; i ++)
	{
		Factorial[i] = i*Factorial[i-1];
	}
	for(i = 1;i <= 20; i ++)
	{
		for(j = 1; j <= 20; j ++)
		{
			Combo[i][j] = Combo[i-1][j] + Combo[i][j-1];
		}
	}
	fscanf(inp,"%d",&testcase);

	for(iCount = 0 ; iCount < testcase ; iCount ++)
	{
		fscanf(inp,"%d %d %d",&n,&L,&R);
		Cnt = 1,result = 1;
		if(/*L>n || R>n || L==R || n-(L+R-1)<0*/false)
		{
			fprintf(out,"0\n");
		}
		else
		{
			x = n - (L+R-1); // 가용 갯수
			y = (L-1) + (R-1); //가용 공간
			if(L>1 && R>1)
			{
				result = result * Combo[L-1][R-1];
			}
			if(x == 0)
			{
				fprintf(out,"%lld\n",Combo[L-1][R-1]);
			}
			else
			{
				if(y>x)
					fprintf(out,"%lld\n",Combo[y-x][x]*result);
				else
				{
					fprintf(out,"%lld\n",(Factorial[x]/Factorial[y])*result);
				}
			}
		}

	}
	return 0;
}	