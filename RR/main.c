#include <stdio.h>
#include <stdlib.h>
int cur_end=0,cur_start=0,min_burst=0,n=0,temp_start=0,this_proc=0,start=0;
int ready [200],qp=0,rp=0;
int queue[200];
typedef struct Proc
{
    int name;
    int AT,CPU1,S,E;
    int at[200],s[200],e[200];
    int ap,sp,ep;
    int nth,CT,WT,TAT,RT;
    //strorage for cpus
    int orig_cpu;
} process[200],temporary;
process proc;
temporary temp;

void checker(int n)
{
    for(int i=0; i<n; i++)
    {
        if(proc[i].CPU1<0)
        {
            for(int k=i; k>0; k--)
            {
                temp=proc[k];
                proc[k]=proc[k-1];
                proc[k-1]=temp;
            }
        }
    }
}
int terminate(int n)
{
    for(int i=0; i<n; i++)
    {
        if(proc[i].CPU1>=0)
        {
            return 0;
        }
    }
    return 1;
}
int least_AT(int n)
{
    int min=proc[0].AT;
    for(int i=0; i<n; i++)
    {
        if(proc[i].AT<=min)
        {
            min=proc[i].AT;
        }
    }
    return min;
}
void sort(int s,int n)
{
// Bubblesort by AT
    for(int i=s; i<n; i++)
    {
        for(int k=s; k<n-1; k++)
        {
            if(proc[k].AT>=proc[k+1].AT)
            {
                temp=proc[k];
                proc[k]=proc[k+1];
                proc[k+1]=temp;
            }
        }
    }
}
int inside_queue(int process){
    for(int i=0;i<rp;i++){
        if(ready[i]==process){
            return 1;
        }
    }
    return 0;
}
int next(int s,int n,int start,int end,int past){
//printf("past: %d :: start:%d :: end:%d :: i:%d\n",past,start,end,s);
//printf("%d",s);
    for(int i=s;i<n;i++){

          if(proc[i].AT>=start && proc[i].AT<=end && i!=past && proc[i].CPU1 >0){
              printf("\ni:%d :: AT:%d\n",i,proc[i].AT);
            if(inside_queue(i)==0){
                    queue[qp]=i;
                    qp++;
  //                  printf("\ni:%d\n",i);
            }
        }
    }
    printf("\n");
    for(int i=0;i<qp;i++){
        ready[rp]=queue[i];
        rp++;
    }
    if(proc[past].CPU1>0){
       ready[rp]=past;
       rp++;
    }

        printf("Ready: ");
    for(int u=0;u<rp;u++){
        printf("%d, ",ready[u]);
    }
       printf("queue: ");
    for(int y=0;y<qp;y++){
        printf("%d, ",queue[y]);
    }

    qp=0;
return ready[0];
}
int find_next_process(int start,int n){
    for(int i=0;i<n;i++){
        for(int k=0;k<proc[i].sp;k++){
            if(proc[i].s[k]== start){
                this_proc=i;
                return proc[i].e[k];
            }
        }
    }
    return 0;
}
void gantt(int n){
int traverse=0,next=0,now=start;
int max_end=cur_end,pin=start;
printf("\nCompletion Time: %d\n",max_end);
    while(traverse<=max_end){
        //draw line from 0 to start,start to end of one process, and breaks
        printf(" - ");
        if(traverse==now){
                if(traverse==start){
                   printf("%d|",now);
                }else{
                printf("P%d|%d",proc[this_proc].name,now);
                }

        next=find_next_process(traverse,n);
                while(next==0 && traverse<=max_end ){
                traverse++;
            next=find_next_process(traverse,n);
        }
            pin=now;
            now=next;
            if(pin<=0){
                pin=now;
            }
        }

        traverse++;
    }
    printf("|");
}
void view(int n){
// sort by name
    for(int i=0;i<n;i++){
        for(int k=0;k<n-1;k++){
            if(proc[k].name>proc[k+1].name){
                temp=proc[k];
                proc[k]=proc[k+1];
                proc[k+1]=temp;
            }
        }
    }
    //set CT TAT WT RT
    for(int i=0;i<n;i++){
        //CT
        proc[i].CT=proc[i].e[proc[i].ep-1];
        //TAT
        proc[i].TAT=proc[i].CT-proc[i].at[0];
        //WT
         proc[i].WT=proc[i].TAT-proc[i].orig_cpu;
        //RT
        proc[i].RT=proc[i].s[0]- proc[i].at[0];
    }

}
int main()
{
    int i=0,point=0,total=0,TQ=0,past=0;
//get nth processes
    printf("RR\n");
    printf("How many processes:");
    scanf("%d",&n);
    total=n;
    printf("Time Quantum:");
    scanf("%d",&TQ);
// get inputs
    for(int i=0; i<n; i++)
    {
        printf("P%d:\n",i+1);
        proc[i].name=i+1;
        printf("AT:");
        scanf("%d",&proc[i].AT);
        proc[i].at[0]=proc[i].AT;
        proc[i].ap++;
        printf("CPU:");
        scanf("%d",&proc[i].CPU1);
        proc[i].orig_cpu=proc[i].CPU1;
    }
    cur_start=temp_start=least_AT(n);
    sort(i,n);
// first put values in first process
//START:
proc[i].S=proc[i].AT;
cur_start=proc[i].S;
proc[i].AT=proc[i].E;
 proc[i].at[proc[i].ap]=proc[i].AT;
    proc[i].ap++;
    proc[point].s[proc[point].sp]=proc[point].S;
    proc[point].sp++;
//END:
if(proc[i].CPU1<= TQ){
    proc[i].E=proc[i].CPU1 + proc[i].S;
    cur_end=proc[i].E;
    proc[i].CPU1=-1;
}else{
    proc[i].E=proc[i].S + TQ;
    cur_end=proc[i].E;
    proc[i].CPU1-=TQ;
}
    proc[point].e[proc[point].ep]=proc[point].E;
    proc[point].ep++;
past=i;
//printf("past: %d",past);
ready[rp]=0;
rp++;
        printf("Ready: ");
    for(int u=0;u<rp;u++){
        printf("%d, ",ready[u]);
    }
       printf("queue: ");
    for(int u=0;u<qp;u++){
        printf("%d, ",queue[u]);
    }

    // printf("P%d\n",proc[point].name);
//printf("curend=%d :: i=%d\n",cur_end,i);
//MAIN CYCLE
    while(terminate(n)==0)
    {
//delete the value
        for(int k=0;k<rp;k++){
            ready[k]=ready[k+1];
        }
        rp-=1;
// main execution
        sort(i,n);
        point=next(i,n,temp_start,cur_end,past);
      //  printf("P%d\n",proc[point].name);
        //START:
        if(cur_end<proc[point].AT){
            proc[point].S=proc[point].AT;
        }else{
            proc[point].S=cur_end;
        }
    proc[point].at[proc[point].ap]=proc[point].E;
    proc[point].ap++;
    proc[point].s[proc[point].sp]=proc[point].S;
    proc[point].sp++;
        //END:
        if(proc[point].CPU1<= TQ){
            proc[point].E=proc[point].CPU1 + proc[point].S;
            cur_end=proc[point].E;
            proc[point].CPU1=-1;
        }else{
            proc[point].E=proc[point].S + TQ;
            cur_end=proc[point].E;
            proc[point].CPU1-=TQ;
        }
    proc[point].e[proc[point].ep]=proc[point].E;
    proc[point].ep++;
        past=point;
    }
    printf("\n\n\n");
    view(n);
system("cls");
printf("VIEW:\n\n");
    float ave_tat=0.0,ave_wt=0.0,ave_rt=0.0;
for(int i=0;i<total;i++){
    printf("P%d\n",proc[i].name);
    printf("AT: ");
    for(int k=0;k<proc[i].ap;k++){
        printf("%d, ",proc[i].at[k]);
    }
    printf("\n");
    printf("CPU1: %d\n",proc[i].orig_cpu);
    printf("Start: ");
    for(int k=0;k<proc[i].sp;k++){
        printf("%d, ",proc[i].s[k]);
    }
    printf("\n");
    printf("End: ");
    for(int k=0;k<proc[i].ep;k++){
        printf("%d,",proc[i].e[k]);
    }
    printf("\nCT: %d\n",proc[i].CT);
    printf("TAT: %d\n",proc[i].TAT);
    ave_tat+=proc[i].TAT;
    printf("WT: %d\n",proc[i].WT);
    ave_wt+=proc[i].WT;
    printf("RT: %d\n",proc[i].RT);
    ave_rt+=proc[i].RT;
    printf("\n");
}
printf("AVERAGE WT: %f\n",ave_wt/n);
printf("AVERAGE TAT: %f\n",ave_tat/n);
printf("AVERAGE RT: %f\n",ave_rt/n);

//get max n of array in start and end in specific process
    for(int i=0;i<n;i++){
        proc[i].nth=proc[i].ep;
    }
gantt(n);
    return 0;
}
/*
5
3
0
8
5
2
1
7
6
3
8
5

*/
