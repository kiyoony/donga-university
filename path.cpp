#include <stdio.h>
long long int arr[1001][1001];
void swap(int *a,int *b)
{
   int temp = *a;
   *a = *b;
   *b = temp;   
}
int isOk(int x,int y,int z,int r,int pX,int pY) //x,y z,r사각형안에 존재하는지
{
	if(x>z)swap(&x,&z);
	if(y>r)swap(&y,&r);
   if(x<=pX && pX<=z && y <=pY && pY<=r)return 1;

   else return 0;
}
void iSplus(int *a,int *b)
{
   if(*a < 0 ) (*a) *= -1;
   if(*b < 0 ) (*b) *= -1;
}

long long int distance(int sX,int sY,int tX,int tY,int mX,int mY) //S - > T 까지 갈떄 m 을 경유함 
{
   int dX,dY;
   long long int result;
   dX = sX-mX , dY = sY - mY;
   iSplus(&dX,&dY);
   result = arr[dX][dY];
   dX = tX-mX , dY = tY - mY;
   iSplus(&dX,&dY);
   result = (result * arr[dX][dY])%1000007;
   return result;
} 
int main()
{
   FILE *inp = fopen("path.inp","r");
   FILE *out = fopen("path.out","w");
   int n;
   int iCount;
   int testcase;
   int sX,sY,tX,tY;
   int aX,aY,bX,bY;
   int dX,dY;        // distance
   int i , j ;
   long long int result = 0;
   long long int buf = 0;
   long long int temp;
   int gasA,gasB;

   for(i = 0 ; i < 1001;i ++)
   {
      arr[i][0] = arr[0][i] = 1;
   }
   for( i = 1; i < 1001; i ++ )
   {
      for( j= 1; j< 1001 ;j ++ )
      {
         arr[i][j] = (arr[i-1][j] + arr[i][j-1])%1000007;
      }
   }
   fscanf(inp,"%d",&testcase);
   for( iCount = 0 ; iCount <testcase; iCount ++ )
   {
      result = 0;
      fscanf(inp,"%d %d %d %d %d %d %d %d",&sX,&sY,&tX,&tY,&aX,&aY,&bX,&bY);

      gasA = isOk( sX, sY , tX , tY , aX , aY );
      gasB = isOk( sX, sY , tX , tY , bX , bY );

      if(!gasA && !gasB)
      {
         fprintf(out,"0\n");
      }
      else if(!gasA) //B주유소를 거침
      {
         fprintf(out,"%lld\n",distance(sX,sY,tX,tY,bX,bY));
      }
      else if(!gasB) //A 주유소를 거침
      {
         fprintf(out,"%lld\n",distance(sX,sY,tX,tY,aX,aY)); 
      }
      else
      {
		  result	= distance(sX,sY,tX,tY,aX,aY);
		  buf		= distance(sX,sY,tX,tY,bX,bY);
		  temp		= 0 ;
		  if(isOk( sX , sY , aX , aY , bX ,bY)) //a 까지가는데 b가 포함이 될 경우
		  {
			  temp = distance(sX,sY,aX,aY,bX,bY);
			  dX = tX - aX , dY = tY - aY;
			  iSplus(&dX,&dY);
			  temp = (temp * arr[dX][dY])%1000007;
		  }
		  else if(isOk( aX , aY , tX , tY ,bX,bY)) //b까지 가는데 a가 포함이 될 경우
		  {
			  temp = distance(sX,sY,bX,bY,aX,aY);
			  dX = tX - bX , dY = tY - bY;
			  iSplus(&dX,&dY);
			  temp = (temp * arr[dX][dY])%1000007;
		  }
		  result -= temp;
		  result = result < 0 ? result + 1000007 : result;
		  fprintf(out,"%lld\n",(result+buf)%1000007);
      }
   }
   return 0;
}