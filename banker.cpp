#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pCount,NumOfInstance; //프로세스와 자원의 갯수

typedef struct Que{
	int instance[50]; //자원
	int pNum; //프로세스 번호
	struct Que *next;
}Que;

void addQue(Que *Q,int arr[50],int pNum){ //요청 큐

	int i;
	Que *p = Q;
	Que *NewQue = (Que*)malloc(sizeof(Que));
	NewQue->pNum = pNum;
	for(i=0;i<NumOfInstance;i++){
		NewQue->instance[i] = arr[i];
	}
	NewQue->next=NULL;
	
	while(p->next!=NULL)p=p->next;

	p->next = NewQue;
}

void delQue(Que *pre_Q,Que *del_Q){
	pre_Q->next = del_Q->next;
	free(del_Q);
	del_Q=NULL;
}
int safe(int banker_c[50][50],int NEED_MAX_c[50][50],int available_c[50],int buffer[50],int pNumber){
	int i,j,n;
	int check=0; //이미 완료된 프로세스인지 확인하는 변수
	int banker[50][50];
	int NEED_MAX[50][50];
	int available[50];
	int fCount=0;
	int flag[50]={0,}; //해당 프로세스가 작업을 완료하였는지 완료 1 미완료 0
	for(i=0;i<pCount;i++){
		for(j=0;j<NumOfInstance;j++){
			banker[i][j] = banker_c[i][j];
			NEED_MAX[i][j] = NEED_MAX_c[i][j];
		}
	}
	for(j=0;j<NumOfInstance;j++){
		available[j] = available_c[j];
	}
	for(i=0;i<NumOfInstance;i++){
		if(buffer[i]>(NEED_MAX[pNumber][i] - banker[pNumber][i]))return 1;
		banker[pNumber][i] += buffer[i];
		available[i] -= buffer[i];
	}
	for(i=0;i<pCount;i++){
		for(j=0;j<NumOfInstance;j++){
			if(banker[i][j]!=NEED_MAX[i][j]){
				break;
			}
		}
		if(j==NumOfInstance){ 
			flag[i] = 1;
			fCount++;
			for(j=0;j<NumOfInstance;j++){
				available[j] += banker[i][j];
				banker[i][j] = 0;
				NEED_MAX[i][j] = 0;
			}
		}
	}

	for(n=0;n<(pCount-fCount);n++){
		check = 0;
		for(i=0;i<pCount;i++){
			for(j=0;j<NumOfInstance && !flag[i];j++){
				if((NEED_MAX[i][j] - banker[i][j]) > available[j]) //필요로 하는 자원이 모자랄 때
					break;
				if(j==NumOfInstance-1){ //모자라지않음
					for(j=0;j<NumOfInstance;j++){
						available[j] = available[j] + banker[i][j]; //할당된 자원 반환
						banker[i][j] = 0 ;
						NEED_MAX[i][j] = 0;
						check = 1;
						flag[i] = 1;
					}
				}
			}
			if(check)break;
		}
		if(!check){
			return 1; // unsafe
		}
	}
	return 0; //safe
}
int main()
{
	FILE *inp = fopen("banker.inp","r");
	FILE *out = fopen("banker.out","w");

	int banker[50][50]={0,}; //프로세스별 보유 자원
	int NEED_MAX[50][50]={0,};//필요로 하는 최대의 자원
	int available[50]={0,}; //현재 이용가능한 자원
	int buffer[50]={0,};
	
	int i,j; //반복문에 사용될 변수

	int pNumber; //프로세스 번호를 입력받을 변수
	
	int pComplete=0; //프로세스 반환이 끝인지

	int pCheck = 0; //이 요청이 유효한지

	int Deadlock_Detection = 0;  //데드락 감지 변수

	char check ; //요청, 할당, 종료를 판별할 변수

	Que *Q =(Que*)malloc(sizeof(Que));
	
	Q->next = NULL;

	Q->pNum=-1; //dummy Que Node

	Que *pre_Q , *now_Q; //대기큐를 검사하고 제거할 때 필요한 배열

	fscanf(inp,"%d %d",&pCount,&NumOfInstance); //자원과 프로세스의 갯수 입력

	for(i=0;i<NumOfInstance;i++){
		fscanf(inp,"%d",&available[i]); //시스템 자원 할당
	}
	
	for(i=0;i<pCount;i++){            //프로세스당 최대 필요 자원
		for(j=0;j<NumOfInstance;j++){
			fscanf(inp,"%d",&NEED_MAX[i][j]);
		}
	}

	for(i=0;i<pCount;i++){            //프로세스당 최대 필요 자원
		for(j=0;j<NumOfInstance;j++){
			fscanf(inp,"%d",&banker[i][j]);
			available[j]-=banker[i][j];
		}
	}
	fscanf(inp,"\n");
	while(1){
		fscanf(inp,"%c",&check);
		
		if(check =='q') //quit가 나올시 프로그램 종료
			return 0;
		//else 그밖의 경우  ( request , realease)

		fscanf(inp,"e");
		fscanf(inp,"%c",&check);
		if(check=='q'){ //요청
			fscanf(inp,"uest");
			fscanf(inp,"%d",&pNumber);
			//pCheck = 0;
			for(i=0;i<NumOfInstance;i++){
				fscanf(inp,"%d",&buffer[i]);
				/*if(NEED_MAX[pNumber][i] < buffer[i] + banker[pNumber][i])
					pCheck = 1;*/
			}
			addQue(Q,buffer,pNumber);
			fscanf(inp,"\n");
		}
		else{ //반환
			fscanf(inp,"ease");
			fscanf(inp,"%d",&pNumber); //프로세스 번호 입력
			for(i=0;i<NumOfInstance;i++){
				fscanf(inp,"%d",&buffer[i]);
				available[i] += buffer[i];
				banker[pNumber][i] -= buffer[i];
			}
			fscanf(inp,"\n");
		}

		// 연산이 필요한 부분
		pre_Q = Q;
		now_Q = Q->next;
		while(now_Q){
			Deadlock_Detection = 0;
			for(i=0;i<NumOfInstance;i++){
				if(now_Q->instance[i] > available[i]){
					Deadlock_Detection=1;
					break;
				}
			}
			if(!Deadlock_Detection){
				Deadlock_Detection = safe(banker,NEED_MAX,available,now_Q->instance,now_Q->pNum);
			}

			if(!Deadlock_Detection){ //요청에 따라 데드락이 감지되지 않으면 요청 허락
				for(i=0;i<NumOfInstance;i++){
					banker[now_Q->pNum][i] += now_Q->instance[i];
					available[i] = available[i] - now_Q->instance[i]; 
				}
				delQue(pre_Q,now_Q);
				now_Q = pre_Q->next;
			}
			else{// 데드락 감지
				pre_Q = now_Q;
				now_Q = now_Q->next; // 다음 큐 탐색
			}
		}
		for(i=0;i<NumOfInstance;i++){
			fprintf(out,"%d ",available[i]);
		}
		fprintf(out,"\n");
	}
}