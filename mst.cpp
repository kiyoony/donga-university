#include <stdio.h>
int n , m;
int sum;
int edge[100001][3]; // �������� ���� ����ġ, ������, ����
int floor[10001];    // ����� ������ ����
int prim[10001][10001][2]; //prim[i]  ���� i�� ������ִ� �������� ���� ( ������ floor[i]�� ����) 0�� ����ġ 1�� ������ȣ�� ��Ÿ��
int check[10001];	//prim���� �湮�ߴ����� ���� ����
int heapData[10001][2]; // ����ġ , ������ȣ
int kruscal[100001][2];//����ġ, ���� ��ȣ
int head[10001]; // ������ ����Ű�� �ִ���
int HeadUnion[10001][10001]; // �ڽ��� ������ ������ ����
int UnionFloor[10001]; //�� �� ���� �ִ���
int SelectEdge[10001]; // ���õ� ���� ��ȣ
void swap(int *a,int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
int partition(int p,int q) // ����ġ�� ���� ����
{
	int L = p+1;
	int R = q;
	while(1)
	{
		while( L < R && kruscal[L][0] < kruscal[p][0] ) L++;
		while( L <=R && kruscal[R][0] >= kruscal[p][0] ) R--;

		if(L < R)
		{
			swap(&kruscal[L][0],&kruscal[R][0]);
			swap(&kruscal[L][1],&kruscal[R][1]);
		}
		else
		{
			swap(&kruscal[p][0],&kruscal[R][0]);
			swap(&kruscal[p][1],&kruscal[R][1]);
			return R;
		}

	}
}
int sub_partition(int p,int q) //�ߺ��� ����ġ�� ���� ����
{
	int L = p+1;
	int R = q;
	while(1)
	{
		while( L < R && kruscal[L][1] < kruscal[p][1] ) L++;
		while( L <= R && kruscal[R][1] >=kruscal[p][1] ) R--;

		if(L < R)
		{
			swap(&kruscal[L][1],&kruscal[R][1]);
		}
		else
		{
			swap(&kruscal[p][1],&kruscal[R][1]);
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
void sub_quicksort(int p,int q)
{
	if(p < q)
	{
		int position = sub_partition(p,q);
		sub_quicksort(p,position-1);
		sub_quicksort(position+1,q);
	}
}
void duplicate_process(int p,int q)
{
	int i = 0 ;
	while(p <= q)
	{

		for( i = p  ; i <= q; i ++ )
		{
			if(kruscal[i][0]!=kruscal[p][0])break;
		}
		if(i!=p)
		{
			sub_quicksort(p,i-1);
		}
		p = i;
	}
}
void merge(int f_u1,int f_u2,int u1,int u2,int target)
{
	int i = 0;
	for( i = f_u1 ; i < f_u1 + f_u2 ; i ++ )
	{
		HeadUnion[u1][i] = HeadUnion[u2][i-f_u1];
		head[HeadUnion[u1][i]] = head[target];
		UnionFloor[u1]++;
	}
}
int iSUnion(int x,int y)
{
	int u1 , u2,i,j, f_u1,f_u2;
	if( head[x] >=0 && head[y] >=0 ) // �� �� ��� �����տ� ����
	{
		if(head[x] == head[y])
			return 0;
		else //���� �ٸ� ������ ��ħ
		{
			u1 = head[x] , u2 = head[y] ; // ���� 1 , 2
			f_u1 = UnionFloor[u1] , f_u2 = UnionFloor[u2];
			if(f_u1 > f_u2) // u1�� u2�� ����
			{
				merge(f_u1,f_u2,u1,u2,head[x]);
			}
			else
			{
				merge(f_u2,f_u1,u2,u1,head[y]);
			}
		}
	}
	else
	{
		if(head[x] >=0)// head[y] == -1
		{
			u1 = head[x];
			HeadUnion[u1][UnionFloor[u1]++] = y;
			head[y] = head[x];
		}
		else if(head[y] >=0) // head[x] == -1
		{
			u1 = head[y];
			HeadUnion[u1][UnionFloor[u1]++] = x;
			head[x] = head[y];
		}
		else
		{
			head[x] = x , head[y] = x;
			UnionFloor[x] = 2;
			HeadUnion[x][0] = x;
			HeadUnion[x][1] = y;
		}
	}
	return 1;
}
void process_Krusal()
{
	int EdgeCount = 0;
	int EdgeNumber = 0;
	int vertex;
	int sP,eP;
	while(EdgeCount < n-1)
	{
		vertex = kruscal[EdgeNumber][1];
		sP = edge[vertex][1] , eP = edge[vertex][2];
		if(iSUnion(sP,eP))
		{
			SelectEdge[EdgeCount++] = vertex;
			sum += edge[vertex][0];
		}
		EdgeNumber++;
	}
}
int adjust(int a, int b,int target) // ���� �ƴ϶�� �ٲ���� �ڸ��� ��ȯ     ���̸� -1 ��ȯ
{
	if(a && b)
	{
		if( a < target && b < target)
			return a < b ? 0 : 1;
		else if( a < target)
			return 0;
		else if( b < target)
			return 1;
		else
			return -1;
	}
	else if(a)
		return a < target ? 0 : -1;
	else if(b)
		return b < target ? 1 : -1;
	else
		return -1;
}
int getMinHeap(int n) // n���� �ִ� arr�迭���� �ּҰ� ��ȯ �� �� ���� ����
{
	int p , temp = 0;
	swap(&heapData[1][0],&heapData[n][0]);
	swap(&heapData[1][1],&heapData[n][1]);
	p = 1;
	while( p < n )
	{
		if((2*p)+1 < n ) //�� �ڽ� �� �����ȿ� �� ��
		{
			temp = adjust(heapData[2*p][0],heapData[2*p +1][0], heapData[p][0]);
			if(temp < 0)
			{
				if(heapData[2*p][0] == heapData[p][0] && heapData[2*p +1][0] == heapData[p][0]) // �ڽ��� �� ���� ��
				{
					temp = adjust(heapData[2*p][1],heapData[2*p+1][1] , heapData[p][1]);
					if(temp<0)
						break;
					else
						swap(&heapData[2*p +temp][1],&heapData[p][1]);
				}
				else if(heapData[2*p][0] == heapData[p][0])
				{
					if(heapData[2*p][1] < heapData[p][1])
					{
						swap(&heapData[2*p][0],&heapData[p][0]);
						swap(&heapData[2*p][1],&heapData[p][1]);
						temp = 0;
					}
					else
						break;
				}
				else if(heapData[2*p +1][0] == heapData[p][0])
				{
					if(heapData[2*p +1][1] < heapData[p][1])
					{
						swap(&heapData[2*p +1][0],&heapData[p][0]);
						swap(&heapData[2*p +1][1],&heapData[p][1]);
						temp = 1;
					}
					else
						break;
				}
				else // �ڽĵ� ��� �θ𺸴� ũ�� ( ���� ���� )
					break;
			}
			else// �ڽ� �߿� ���� �����Ͱ� ������
			{
				if(heapData[2*p][0] == heapData[2*p +1][0]) // ����ġ�� ���� ����
				{
					if(heapData[2*p][1] < heapData[2*p+1][1]) // ��ȣ�� ���� ������
					{
						temp = 0;
					}
					else
					{
						temp = 1;
					}
				}
				swap(&heapData[2*p +temp][0],&heapData[p][0]);
				swap(&heapData[2*p +temp][1],&heapData[p][1]);
				// ����
			}
		}
		else if(2*p < n) // ���� �ڽĸ� ����
		{
			if(heapData[2*p][0] < heapData[p][0])
			{
				swap(&heapData[2*p][0],&heapData[p][0]);
				swap(&heapData[2*p][1],&heapData[p][1]);
				temp = 0;
			}
			else if(heapData[2*p][0] == heapData[p][0] && heapData[2*p][1] < heapData[p][1])
			{
				swap(&heapData[2*p][1],&heapData[p][1]);
				temp = 0;
			}
			else
				break;
		}

		p = (2*p) + temp;
	}
	return heapData[n][0];
}
void findPosition(int p) // �� ����
{
	int parent = 0;
	while(p>1)
	{
		parent = p/2;
		if(heapData[p][0] < heapData[parent][0])
		{
			swap(&heapData[p][0] , &heapData[parent][0]);
			swap(&heapData[p][1] , &heapData[parent][1]);
		}
		else if(heapData[p][0] == heapData[parent][0] && heapData[p][1] < heapData[parent][1])
		{
			swap(&heapData[p][1] , &heapData[parent][1]);
		}

		p = parent;
	}
}
void process_prim(int num,int type)
{
	int EdgeCount = 0 ,EdgeNumber = 0;
	int index = 1 ,i = 0; //heap �ڷᱸ�� �ε���
	while(EdgeCount < n-1)
	{
		if(check[num]!=type) // num ���� �湮�ؼ� ���� �������� ��� ���� �߰�
		{
			check[num] = type; // �湮 üũ
			for( i = 0; i < floor[num]; i ++)
			{
				if(check[ edge[ prim[num][i][1] ][1] ] != type || check[ edge[ prim[num][i][1] ][2] ] != type) //�湮���� ���� ����
				{
					heapData[index][0] = prim[num][i][0];
					heapData[index][1] = prim[num][i][1];
					findPosition(index++);
				}
			}
		}
		while(index>0) //���� �̱�
		{
			getMinHeap(index-1);
			EdgeNumber = heapData[index-1][1];
			num = check[ edge[EdgeNumber][1] ] != type ? edge[EdgeNumber][1] : edge[EdgeNumber][2];
			index--;
			if(check[num]!=type)
			{
				SelectEdge[EdgeCount++] = EdgeNumber;
				break;
			}
		}
	}
}
int main()
{
	
	int i , j , pX, pY, weight;

	FILE *inp = fopen("mst.inp","r");
	FILE *out = fopen("mst.out","w");

	fscanf(inp,"%d %d",&n, &m);
	for( i = 0 ; i < n; i ++ )
	{
		head[i] = -1;
	}
	for( i = 0 ; i < m ; i ++ )
	{
		fscanf(inp,"%d %d %d",&pX,&pY,&weight);
		edge[i][0] = weight;
		edge[i][1] = pX , edge[i][2] = pY;
		kruscal[i][0] = weight;
		kruscal[i][1] = i;
		prim[pX][floor[pX]][0] = weight;
		prim[pX][floor[pX]++][1] = i;
		prim[pY][floor[pY]][0] = weight;
		prim[pY][floor[pY]++][1] = i;
	}
	quicksort(0,m-1); //ũ�罺Į ����ġ�� ���� ����
	duplicate_process(0,m-1); //�ߺ��Ǵ� ����ġ�鿡 ���Ͽ� ���� ��ȣ��� ����
	process_Krusal();
	fprintf(out,"Tree edges by Kruskal algorithm: %d\n",sum);
	for( i = 0 ; i < n-1; i ++)
	{
		fprintf(out,"%d\n",SelectEdge[i]);
	}
	fprintf(out,"Tree edges by Prim algorithm with starting vertex %d: %d\n",0,sum);
	process_prim(0,1);
	for( i = 0 ; i < n-1; i ++)
	{
		fprintf(out,"%d\n",SelectEdge[i]);
	}
	fprintf(out,"Tree edges by Prim algorithm with starting vertex %d: %d\n",n/2,sum);
	process_prim(n/2,2);
	for( i = 0 ; i < n-1; i ++)
	{
		fprintf(out,"%d\n",SelectEdge[i]);
	}
	fprintf(out,"Tree edges by Prim algorithm with starting vertex %d: %d\n",n-1,sum);
	process_prim(n-1,3);
	for( i = 0 ; i < n-1; i ++)
	{
		fprintf(out,"%d\n",SelectEdge[i]);
	}
	return 0;
}