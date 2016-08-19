#include <stdio.h>
#include <stdlib.h>
int pCount;//전체 갯수
typedef struct Timeslice //시간을 나타낼 리스트
{
	int time;
	int isEnd;
	struct Timeslice *next;
}Timeslice;
typedef struct MemoryList //메모리에 들어올 리스트
{
	int Number; //요청 번호
	int ArriveTime;//도착시간
	int BurstTime;//사용시간
	int Size; //크기
	struct MemoryList *link; //링크
}MemoryList;
void addMemoryList(MemoryList *M,int Number,int ArriveTime,int BurstTime,int Size) //메모리에 들어올 리스트들을 추가
{
	MemoryList *p = M;
	MemoryList *New = (MemoryList*)malloc(sizeof(MemoryList));
	New->Number = Number;
	New->ArriveTime =ArriveTime;
	New->BurstTime = BurstTime;
	New->Size = Size;
	New->link = NULL;
	while(p->link!=NULL)p=p->link;
	p->link= New;
}
void DelMemoryList(MemoryList *M,int Number)//메모리에 적재되면 리스트에서 제외
{
	MemoryList * p = M;
	MemoryList *del;
	while(p->link->Number!=Number)p = p->link;
	del = p->link;
	p->link = del->link;
	del = NULL;
	free(del);
}
void addTimeList(int time,int isEnd,Timeslice *T) //다음 도착,반환시간을 저장할 리스트
{
	Timeslice * p = T->next,*pre =T;
	Timeslice *New ;
	while(p!=NULL)
	{
		if(p->time>=time)break;
		pre = p,p=p->next;
	}
	if(p&&p->time==time)
	{
		p->isEnd=isEnd;
		return;
	}
	New = (Timeslice*)malloc(sizeof(Timeslice));
	New->next = pre->next;
	New->time = time;
	New->isEnd = isEnd;
	pre->next = New;
}
void CopyMemoryList(MemoryList *target,MemoryList*origin) //임시로 사용하기위해 메모리복제
{
	MemoryList *p =origin->link;
	MemoryList *q =target;
	MemoryList *New;
	while(p!=NULL)
	{
		New = (MemoryList*)malloc(sizeof(MemoryList));
		New->ArriveTime = p->ArriveTime;
		New->BurstTime = p->BurstTime;
		New->Number = p->Number;
		New->Size = p->Size;
		New->link = NULL;
		q->link = New;
		p = p->link,q = q->link;
	}
}
int WhoisMostFit(int Memory[1000][3],int BufPos,int CurPos,int fit) //누가 더 fit에 적합한지 (좋은 포지션,현재 포지션)
{
	fit = (fit==1)?1:-1;
	return (Memory[BufPos][1]-BufPos)*fit <= (Memory[CurPos][1]-CurPos)*fit ? BufPos:CurPos; //fit에 적합한 위치를 반환함
}
int Myposition(int Memory[1000][3],MemoryList *CurP,int time,int fit) //내가들어가야할 위치
{
	int position = 0;
	int Buf=-1;
	while(position<1000)
	{
		if((Memory[position][1] - position) >= CurP->Size && Memory[position][0]==-1) //들어갈수 있는 사이즈
		{
			if(!fit)
				return position;
			else
				Buf = (Buf<0) ? position:WhoisMostFit(Memory,Buf,position,fit);
		}
		position = Memory[position][1];
	}
	return Buf;
}
void releaseMemory(int Memory[1000][3],int time)//메모리 반환
{
	int position=0;
	while(position<1000)
	{
		if(Memory[position][2]==time)
			Memory[position][0] = -1;

		position = Memory[position][1];
	}
	position = 0 ; //빈공간 합쳐주기
	while(position<1000)
	{
		if(Memory[position][0] == -1 && Memory[Memory[position][1]][0] == -1 &&Memory[position][1]!=1000)
			Memory[position][1] = Memory[Memory[position][1]][1];
		else
			position = Memory[position][1];
	}
}
int Memory_allocation(MemoryList *M,int fit) //fit  -> 0 first 1 best 2 worst
{
	MemoryList *Copy_M = (MemoryList*)malloc(sizeof(MemoryList));
	MemoryList * p,*temp;
	Timeslice *T = (Timeslice*)malloc(sizeof(Timeslice));
	int Memory[1001][3]; //사용중인 프로세스번호,사이즈,끝나는 시간 저장
	int position = 0; //적재될 메모리 주소
	int Bufposition =0;
	T->next = NULL,T->time = -1;
	Copy_M->link = NULL;
	CopyMemoryList(Copy_M,M);	//임시로 사용하기 위한 CopyMemoryList
	p = Copy_M->link;
	Memory[0][0] = -1,Memory[1000][0] = -1;
	Memory[0][1] = 1000;
	while(p)
	{
		addTimeList(p->ArriveTime,0,T);
		p = p->link;
	}
	p = Copy_M->link;
	T = T->next; // 제일 처음 시간부터
	while(T) //모든시간을 지날때까지 ( T 는 시간에 대한 리스트)
	{
		if(T->isEnd) //반환하려는 자리가 있을 때
			releaseMemory(Memory,T->time);
		position = 0 , p = Copy_M->link; //값 초기화
		while(p)
		{
			if(p->ArriveTime <= T->time)//도착한프로세스일때
			{
				position = Myposition(Memory,p,T->time,fit);
				if(position != -1) //들어갔을 때
				{
					if(p->Number == pCount -1)return position;
					Bufposition = Memory[position][1];
					Memory[position][0] = p->Number;
					Memory[position][1] = p->Size + position;
					Memory[position][2] = T->time + p->BurstTime;
					if(Memory[position][1]!=Bufposition){
						Memory[Memory[position][1]][1] = Bufposition;
						Memory[Memory[position][1]][0] = -1;
					}
					addTimeList(T->time + p->BurstTime,1,T);
					temp = p;
					p= p->link;
					DelMemoryList(Copy_M,temp->Number);
				}
				else
					p = p->link;
			}
			else
				break;
		}
		T = T->next;
	}
}
void Datainput(FILE *in,MemoryList *M) //데이터 입력
{
	int AT,BT,SZ; //도착시간,실행시간,사이즈
	for(int i=0;i<pCount;i++)
	{
		fscanf(in,"%d %d %d",&AT,&BT,&SZ);
		addMemoryList(M,i,AT,BT,SZ);
	}
}
int main()
{
	FILE *inp = fopen("allocation.inp","r");
	FILE *out = fopen("allocation.out","w");
	fscanf(inp,"%d",&pCount);
	MemoryList *M = (MemoryList*)malloc(sizeof(MemoryList));
	M->link=NULL;
	Datainput(inp,M);
	for(int i=0;i<3;i++)
	{
		fprintf(out,"%d\n",Memory_allocation(M,i));
	}
	return 0;
}