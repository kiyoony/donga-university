#include <stdio.h>
int arr[101][101][101][3];
int check(int a,int b,int c,int k)
{
	int i,x,y;
	if(k==1)
		x = 1 , y = 2;
	else if(k==2)
		x = 0 , y = 2;
	else
		x = 0 , y = 1;
	if(a>=k && !arr[a-k][b][c][x] && !arr[a-k][b][c][y])return 1;
	if(b>=k && !arr[a][b-k][c][x] && !arr[a][b-k][c][y])return 1;
	if(c>=k && !arr[a][b][c-k][x] && !arr[a][b][c-k][y])return 1;

	return 0;
}
int main()
{
	FILE *inp = fopen("coin.inp","r");
	FILE *out = fopen("coin.out","w");
	int a,b,c;
	int i,j,k,r;
	int iCount;
	int testcase;
	fscanf(inp,"%d",&testcase);
	arr[0][0][0][0] = 1;
	arr[0][0][0][1] = 1;
	arr[0][0][0][2] = 1;

	for( i = 0; i < 101;i ++)
	{
		for( j= 0 ; j < 101 ; j ++)
		{
			for(k = 0 ; k < 101; k ++)
			{
				for(r = 1 ; r <=3 ; r ++)
				{
					if(!arr[i][j][k][r])
						arr[i][j][k][r-1] = check(i,j,k,r);
				}
			}
		}
	}
	for( iCount = 0 ; iCount < testcase; iCount ++)
	{
		fscanf(inp,"%d %d %d",&a,&b,&c);
		fprintf(out,"(%d %d %d) : %d\n",a,b,c,arr[a][b][c][0] || arr[a][b][c][1] || arr[a][b][c][2] ? 1 : -1);
	}
	return 0;
}