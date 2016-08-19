#include <stdio.h>
int arr[101][101][101];
int check(int a,int b,int c)
{
	int i,j,k;
	if(a>=1 &&!arr[a-1][b][c])return 1;
	if(a>=2 &&!arr[a-2][b][c])return 1;
	if(a>=3 &&!arr[a-3][b][c])return 1;
	if(b>=1 &&!arr[a][b-1][c])return 1;
	if(b>=2 &&!arr[a][b-2][c])return 1;
	if(b>=3 &&!arr[a][b-3][c])return 1;
	if(c>=1 &&!arr[a][b][c-1])return 1;
	if(c>=2 &&!arr[a][b][c-2])return 1;
	if(c>=3 &&!arr[a][b][c-3])return 1;

	return 0;
}
int main()
{
	FILE *inp = fopen("coin.inp","r");
	FILE *out = fopen("coin.out","w");
	int a,b,c;
	int i,j,k;
	int iCount;
	int testcase;
	fscanf(inp,"%d",&testcase);
	arr[1][1][0] = 1;

	for( i = 0; i < 101;i ++)
	{
		for( j= 0 ; j < 101 ; j ++)
		{
			for(k = 0 ; k < 101; k ++)
			{
				if(!arr[i][j][k])
				{
					if(check(i,j,k))
						arr[i][j][k] = 1;
					else
						arr[i][j][k] = 0;
				}
			}
		}
	}
	for( iCount = 0 ; iCount < testcase; iCount ++)
	{
		fscanf(inp,"%d %d %d",&a,&b,&c);
		fprintf(out,"(%d %d %d) : %d\n",a,b,c,arr[a][b][c] ? 1 : -1);
	}
	return 0;
}