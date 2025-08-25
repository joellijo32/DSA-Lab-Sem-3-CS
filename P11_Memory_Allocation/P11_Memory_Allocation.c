#include <stdio.h>
#include <stdlib.h>

struct Block {
   int size;
   int free;
   int pid;
};

void reset(struct Block blocks[], int n){
   for(int i=0;i<n;i++){
      blocks[i].free=blocks[i].size;
      blocks[i].pid=-1;
   }
}

void allocate(struct Block blocks[], int n, int process[], int p, int choice){
   for(int i=0;i<p;i++){
      int index=-1 , j;
      if(choice==1){
         for(j=0;j<n;j++){
            if(blocks[j].free>=process[i]){ index=j; break; }
         }
      }
      else if(choice==2){
         int min=100000;
         for(j=0;j<n;j++){
            if(blocks[j].free>=process[i] && blocks[j].free<min){
               min=blocks[j].free; index=j;
            }
         }
      }
      else if(choice==3){
         int max=-1;
         for(j=0;j<n;j++){
            if(blocks[j].free>=process[i] && blocks[j].free>max){
               max=blocks[j].free; index=j;
            }
         }
      }
      if(index!=-1){
         blocks[index].free-=process[i];
         blocks[index].pid=i;
         printf("Process %d allocated to Block %d\n",i+1,index+1);
      } else {
         printf("Process %d not allocated\n",i+1);
      }
   }
}

int main(){
   int n,p,i;
   printf("Enter number of memory blocks: ");
   scanf("%d",&n);
   struct Block blocks[n];
   for(i=0;i<n;i++){
      printf("Size of block %d: ",i+1);
      scanf("%d",&blocks[i].size);
      blocks[i].free=blocks[i].size;
      blocks[i].pid=-1;
   }
   printf("Enter number of processes: ");
   scanf("%d",&p);
   int process[p];
   for(i=0;i<p;i++){
      printf("Size of process %d: ",i+1);
      scanf("%d",&process[i]);
   }
   int ch;
   while(1){
      printf("\n1.First Fit\n2.Best Fit\n3.Worst Fit\n4.Exit\n");
      scanf("%d",&ch);
      if(ch==4) break;
      reset(blocks,n);
      allocate(blocks,n,process,p,ch);
   }
   return 0;
}
