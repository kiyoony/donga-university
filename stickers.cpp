#include <stdio.h>
int arr[100000][3];
int MaxData(int index, int number)
{
	int x , y;
	if(!number)
		x = 1 , y = 2;
	else if(number==1)
		x = 0 , y = 2;
	else
		x = 0 , y = 1;

	return arr[index][x] > arr[index][y] ? arr[index][x] : arr[index][y];
}
int main()
{
	int iCount;
	int testcase;
	int i = 0, n = 0, j = 0 ,max = 0;
	FILE *inp = fopen("stickers.inp","r");
	FILE *out = fopen("stickers.out","w");
	fscanf(inp,"%d",&testcase);
	for( iCount = 0 ; iCount < testcase; iCount ++ )
	{
		fscanf(inp,"%d",&n);
		for( i = 0 ; i < n ; i ++ )
		{
			fscanf(inp,"%d",&arr[i][0]);
		}
		for( i = 0 ; i < n ; i ++ )
		{
			fscanf(inp,"%d",&arr[i][1]);
			arr[i][2] = 0;
		}
		for( i = 1; i < n; i ++ )
		{
			for(j = 0 ; j < 3; j ++)
			{
				arr[i][j] += MaxData(i-1,j);
			}
		}

		max = MaxData(n-1,0); // 0 , 1 Áß Å« °ª
		max = max > arr[n-1][0] ? max : arr[n-1][0];
		fprintf(out,"%d\n",max);
	}
	return 0;
}

