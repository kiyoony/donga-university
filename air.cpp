//#include <stdio.h>
//int arr[201][201][201]; //축소된 X ,Y 좌표
//long long int VirtualX[201];  //가상의 X좌표
//long long int VirtualY[201];  //가상의 Y좌표
//long long int VirtualZ[201];
//long long int point[101][6];  //모든 종이의 좌표값
//int n;				 //색종이의 갯수
//int Xcnt = 1 ,Ycnt = 1 , Zcnt = 1;		 // X,Y 좌표상의 갯수
//
//void insertion(long long int *DataArray,long long int data,int count)
//{
//	while(count > 0 && DataArray[count-1] >data)
//	{
//		DataArray[count] = DataArray[count-1];
//		count--;
//	}
//	DataArray[count] = data;
//}
//int index(long long int *DataArray,long long int data,int q)
//{
//	int L = 0 , R = q , mid = 0;
//	while(L<R)
//	{
//		mid = (L+R)/2;
//
//		if(DataArray[mid] == data)return mid;
//
//		else if(DataArray[mid] < data)
//			L = mid;
//		else
//			R = mid;
//	}
//}
//void search(long long int *DataArray,long long int data,int count,int type) //삽입정렬로 배열에 저장
//{
//	int L = 0 , R = count - 1;
//	int mid = 0;
//	if(DataArray[L] == data || DataArray[R] ==data)return;
//	while(L<R && DataArray[R]>data)
//	{
//		if(mid == (L+R)/2)break;
//		mid = (L + R)/2;
//		if(DataArray[mid] == data)return;
//		
//		if(DataArray[mid] < data)
//			L = mid;
//		else
//			R = mid;
//	}
//	switch(type)
//	{
//	case 0:
//		insertion(DataArray,data,Xcnt++);
//		break;
//	case 1:
//		insertion(DataArray,data,Ycnt++);
//		break;
//	default:
//		insertion(DataArray,data,Zcnt++);
//	}
//}
//int main()
//{
//	FILE *inp = fopen("air.inp","r");
//	FILE *out = fopen("air.out","w");
//	int i,j,p,q,r,Count = 0;
//	long long int result = 0;
//
//	fscanf(inp,"%d",&n);
//	for( i = 0 ; i < n ; i ++ )
//	{
//		for(j = 0 ; j < 6; j ++ )
//		{
//			fscanf(inp,"%d",&point[i][j]);
//		}
//		for(j = 0 ; j < 2; j ++)
//		{
//			search(VirtualX,point[i][0+(j*3)],Xcnt,0);
//			search(VirtualY,point[i][1+(j*3)],Ycnt,1);
//			search(VirtualZ,point[i][2+(j*3)],Zcnt,2);
//		}
//	}
//
//	for( i = 0 ; i < n; i ++ )
//	{
//		for( p = index(VirtualX,point[i][0],Xcnt); VirtualX[p] < point[i][3]; p++)
//		{
//			for( q = index(VirtualY,point[i][1],Ycnt); VirtualY[q] < point[i][4]; q ++)
//			{
//				for( r = index(VirtualZ,point[i][2],Zcnt); VirtualZ[r] < point[i][5]; r ++)
//				{
//					arr[p][q][r]++;
//				}
//			}
//		}
//	}
//
//	for( p = 0; p < Xcnt; p++)
//	{
//		for( q = 0; q < Ycnt; q ++)
//		{
//			for( r = 0 ; r < Zcnt ; r ++)
//			{
//				if(arr[p][q][r]>1)
//				{
//					result += (VirtualX[p+1]-VirtualX[p]) * (VirtualY[q+1]-VirtualY[q]) * (VirtualZ[r+1]-VirtualZ[r]);
//				}
//			}
//		}
//	}
//
//	fprintf(out,"%lld\n",result);
//	return 0;
//}
