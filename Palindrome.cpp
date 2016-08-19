#include <stdio.h>
char arr[1001];
int f(int p,int q,int count)
{
	int buf[2];
	while(p<q)
	{
		if(arr[p]==arr[q])
			p++,q--;
		else if(count<2)
		{
			buf[0] = f(p,q-1,count+1);
			buf[1] = f(p+1,q,count+1);
			if(buf[0]>0 && buf[1]>0)
			{
				return buf[0]>buf[1]?buf[1]:buf[0];
			}
			else if(buf[0]>0)
			{
				return buf[0];
			}
			else if(buf[1]>0)
			{
				return buf[1];
			}
			else
			{
				return -1;
			}
		}
		else
		{
			return -1;
		}
	}
	return count;
}
int main()
{
	FILE *inp = fopen("Palindrome.inp","r");
	FILE *out = fopen("Palindrome.out","w");
	int testcase;
	int iCount;
	
	int size = 0 ;
	int i = 0;
	fscanf(inp,"%d",&testcase);
	for(iCount = 0 ; iCount < testcase; iCount ++ )
	{
		fscanf(inp,"%s",arr);
		for(size = 0;arr[size]!=NULL; size++){}
		//size  = arr size;
		fprintf(out,"%d\n",f(0,size-1,0));
	}
	return 0;
}
