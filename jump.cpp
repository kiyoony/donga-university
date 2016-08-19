#include <stdio.h>
int arr[10000];
void swap(int *a,int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
int partition(int p,int q)
{
	int L = p+1;
	int R = q;
	while(1)
	{
		while( L < R && arr[L] < arr[p] ) L++;
		while( L <=R && arr[R] >= arr[p] ) R--;

		if(L < R)
		{
			swap(&arr[L],&arr[R]);
		}
		else
		{
			swap(&arr[R],&arr[p]);
			return R;
		}

	}
}
void quicksort(int p, int q)
{
	if(p < q)
	{
		int position = partition(p,q);
		quicksort(p,position-1);
		quicksort(position+1,q);
	}
}
int main()
{
	int iCount = 0 ;
	int testcase;
	int i ,n;
	int max = 0;
	int temp =0;
	FILE *inp = fopen("jump.inp","r");
	FILE *out = fopen("jump.out","w");
	fscanf(inp,"%d",&testcase);
	for(iCount = 0 ; iCount < testcase; iCount ++)
	{
		fscanf(inp,"%d",&n);
		for( i = 0 ; i < n; i ++)
		{
			fscanf(inp,"%d",&arr[i]);
		}
		quicksort(0,n-1);
		max = arr[1] - arr[0];
		max = max > arr[n-1] - arr[n-2] ?  max : arr[n-1]-arr[n-2];
		for( i = 0 ; i+2 < n; i ++ )
		{
			temp = arr[i+2] - arr[i];
			max = max > temp ? max : temp;
		}
		fprintf(out,"%d\n",max);
	}
	return 0;
}