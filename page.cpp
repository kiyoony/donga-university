#include <stdio.h>
int frame;
int Memory[10000][3];
int waitingQue[10000][2];
void start(int type,FILE *out)
{
   int index = 0 ,pindex=0; //인덱스 이동 변수

   int i,j; //반복문에 사용될 변수

   int bufChange=0; //바뀔 페이지 위치

   int MaxMemory=0; //Memory의 마지막 인덱스 값 저장
   int MaxPage=0; //MaxCount의 마지막 인덱스 값 저장

   int PageFault=0; //페이지 폴트 횟수

   int isFull=0, isSame=0; //페이지 프레임수가 가득 찬 상태인지 , 이미 있는 프로세스와 페이지인지

   int MaxCount[101][2]={0,}; //프로세스 번호와 프레임 갯수 입력

   int PageList[101][4]={0,}; // 페이지와 페이지가 있는 인덱스 위치

   while(waitingQue[index][0]>=0)
   {
      isFull = 0,pindex = 0,isSame=0;
      for(i=0;i<MaxMemory;i++)
      {
         if(Memory[i][0] == waitingQue[index][0])
         {
            if(Memory[i][1] == waitingQue[index][1])
            {
               isSame++;
               break;
            }
            else if(type==2)
            {
               PageList[pindex][0] = Memory[i][1];
               PageList[pindex][1] = Memory[i][2];
               PageList[pindex][2] = i;
               PageList[pindex++][3] = -1;
            }
         }
      }
      if(!isSame)
      {
         PageFault++;
         for(i=0;i<MaxPage;i++)
         {
            if(waitingQue[index][0] == MaxCount[i][0])
            {
               if(MaxCount[i][1]==frame)isFull =1;

               break;
            }
         }
         if(i == MaxPage || !isFull)//해당 프로세스가 적재 되지 않았음
         {
            if(i == MaxPage)
            {
               MaxCount[MaxPage][0] = waitingQue[index][0];
               MaxPage++;
            }
            MaxCount[i][1]++;
            Memory[MaxMemory][0] = waitingQue[index][0];
            Memory[MaxMemory][1] = waitingQue[index][1];
            Memory[MaxMemory++][2] = index;
         }
         else //페이지 교체 해야함
         {
            if(type <2)
            {
               bufChange = -1;
               for(i=0;i<MaxMemory;i++)
               {
                  if(Memory[i][0] == waitingQue[index][0])
                  {
                     if(bufChange<0) bufChange = i;
                     else if(Memory[bufChange][2] > Memory[i][2]) bufChange = i;
                  }
               }
            }
            else
            {
               for(i = index+1;waitingQue[i][0]>0;i++)
               {
                  if(waitingQue[i][0] == waitingQue[index][0])
                  {
                     for(j=0;j < pindex;j++)
                     {
                        if(PageList[j][0] == waitingQue[i][1])
                        {
                           if(PageList[j][3] <0)PageList[j][3] = i;

                        }
                     }
                  }
               }
               bufChange = 0;
               for(i=1;i<pindex;i++)
               {
                  if(PageList[bufChange][3]<0)
                  {
                     if(PageList[i][3]<0 && (PageList[bufChange][1] > PageList[i][1]))
                        bufChange = i;
                  }
                  else if(PageList[i][3]<0)
                  {
                     bufChange = i;
                  }
                  else
                  {
                     if(PageList[bufChange][3] < PageList[i][3])
                        bufChange = i;
                  }
               }
               bufChange = PageList[bufChange][2];
            }
            
            Memory[bufChange][1] = waitingQue[index][1];
            Memory[bufChange][2] = index;
         }
      }
      else if(type == 1)
      {
         Memory[i][2] = index;
      }
      index++;
   }
   if(type == 0)fprintf(out,"FIFO: %d\n",PageFault);
   else if(type ==1)fprintf(out,"LRU: %d\n",PageFault);
   else fprintf(out,"OPT: %d\n",PageFault);
   for(i=0;i<MaxMemory;i++)
   {
      fprintf(out,"%d %d %d\n",i,Memory[i][0],Memory[i][1]);
   }
   return;
}
void getFrame(FILE *in)
{
   fscanf(in,"%d",&frame);
}
void getQue(FILE *in)
{
   int bufX=0,bufY=0;
   int i=0;
   while(bufX>=0)
   {
      fscanf(in,"%d %d",&bufX,&bufY);

      waitingQue[i][0] = bufX;
      waitingQue[i++][1] = bufY;
   }

}
int main()
{
   FILE *in = fopen("page.inp","r");
   FILE *out= fopen("page.out","w");

   getFrame(in);
   getQue(in);
   for(int i=0;i<3;i++)
   {
      start(i,out);
   }
   return 0;
}