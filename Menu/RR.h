#ifndef RR_H_INCLUDED
#define RR_H_INCLUDED
int ready3 [200];
int queue3[200];
int qp3=0,rp3=0;
int location6=0;
typedef struct proc6
{
    int name;
    int AT,CPU1,S,E;
    int at[200],s[200],e[200];
    int ap,sp,ep;
    int nth,CT,WT,TAT,RT;
    //strorage for cpus
    int orig_cpu;
    int color;
} process6[200],temporary6;
process6 proc6;
temporary6 temp6;


void checker6(int n)
{
    for(int i=0; i<n; i++)
    {
        if(proc6[i].CPU1<0)
        {
            for(int k=i; k>0; k--)
            {
                temp6=proc6[k];
                proc6[k]=proc6[k-1];
                proc6[k-1]=temp6;
            }
        }
    }
}
int terminate6(int n)
{
    for(int i=0; i<n; i++)
    {
        if(proc6[i].CPU1>=0)
        {
            return 0;
        }
    }
    return 1;
}
int least_AT6(int n)
{
    int min=proc6[0].AT;
    for(int i=0; i<n; i++)
    {
        if(proc6[i].AT<=min)
        {
            min=proc6[i].AT;
        }
    }
    return min;
}
void sort6(int s,int n)
{
// Bubblesort6 by AT
    for(int i=s; i<n; i++)
    {
        for(int k=s; k<n-1; k++)
        {
            if(proc6[k].AT>=proc6[k+1].AT)
            {
                temp6=proc6[k];
                proc6[k]=proc6[k+1];
                proc6[k+1]=temp6;
            }
        }
    }
}
int inside_queue36(int proc6ess){
    for(int i=0;i<rp3;i++){
        if(ready3[i]==proc6ess){
            return 1;
        }
    }
    return 0;
}
int next6(int s,int n,int start,int end,int past){
//printf("past: %d :: start:%d :: end:%d :: i:%d\n",past,start,end,s);
//printf("%d",s);
    for(int i=s;i<n;i++){

          if(proc6[i].AT>=start && proc6[i].AT<=end && i!=past && proc6[i].CPU1 >0){
              //printf("\ni:%d :: AT:%d\n",i,proc6[i].AT);
            if(inside_queue36(i)==0){
                    queue3[qp3]=i;
                    qp3++;
  //                  printf("\ni:%d\n",i);
            }
        }
    }
    printf("\n");
    for(int i=0;i<qp3;i++){
        ready3[rp3]=queue3[i];
        rp3++;
    }
    if(proc6[past].CPU1>0){
       ready3[rp3]=past;
       rp3++;
    }

        printf("ready3: ");
    for(int u=0;u<rp3;u++){
        //printf("%d, ",ready3[u]);
    }
       printf("queue3: ");
    for(int y=0;y<qp3;y++){
        //printf("%d, ",queue3[y]);
    }

    qp3=0;
return ready3[0];
}
int find_next_process6(int start,int n){
    for(int i=0;i<n;i++){
        for(int k=0;k<proc6[i].sp;k++){
            if(proc6[i].s[k]== start){
                this_proc6=i;
                location6=k;
                return proc6[i].e[k];
            }
        }
    }
    return 0;
}
void gantt6(int n){
int traverse=0,next6=0,now=start;
int max_end=cur_end,pin=start;
printf("\nCompletion Time: %d\n",max_end);
    while(traverse<=max_end){
        //draw line from 0 to start,start to end of one proc6ess, and breaks
                SetColor(proc6[this_proc6].color);
        printf(" - ");
        if(traverse==now){
                if(traverse==start){
                   printf("%d|",now);
                }else{
                SetColor(proc6[this_proc6].color);
                printf("P%d|%d",proc6[this_proc6].name,now);
                SetColor(15);
                }

        next6=find_next_process6(traverse,n);
                while(next6==0 && traverse<=max_end ){
                traverse++;
            next6=find_next_process6(traverse,n);
            if(traverse==proc6[this_proc6].s[location6]){
                printf("-IDLE|%d",proc6[this_proc6].s[location6]);
            }
        }
            pin=now;
            now=next6;
            if(pin<=0){
                pin=now;
            }
        }

        traverse++;
    }
    printf("|");
}
void view6(int n){
// sort6 by name
    for(int i=0;i<n;i++){
        for(int k=0;k<n-1;k++){
            if(proc6[k].name>proc6[k+1].name){
                temp6=proc6[k];
                proc6[k]=proc6[k+1];
                proc6[k+1]=temp6;
            }
        }
    }
    //set CT TAT WT RT
    for(int i=0;i<n;i++){
        //CT
        proc6[i].CT=proc6[i].e[proc6[i].ep-1];
        //TAT
        proc6[i].TAT=proc6[i].CT-proc6[i].at[0];
        //WT
         proc6[i].WT=proc6[i].TAT-proc6[i].orig_cpu;
        //RT
        proc6[i].RT=proc6[i].s[0]- proc6[i].at[0];
    }

}
void rr(void){
    int i=0,point=0,total=0,TQ=0,past=0;
//get nth proc6esses
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
        proc6[i].name=i+1;
        printf("AT:");
        scanf("%d",&proc6[i].AT);
        proc6[i].at[0]=proc6[i].AT;
        proc6[i].ap++;
        printf("CPU:");
        scanf("%d",&proc6[i].CPU1);
        proc6[i].orig_cpu=proc6[i].CPU1;
            proc6[i].color=head_color;
         head_color++;
        if(head_color>14){
                    head_color=1;
        }
    }
    cur_start=temp_start=least_AT6(n);
    sort6(i,n);
// first put values in first proc6ess
//START:
proc6[i].S=proc6[i].AT;
cur_start=proc6[i].S;
proc6[i].AT=proc6[i].E;
    proc6[point].s[proc6[point].sp]=proc6[point].S;
    proc6[point].sp++;
//END:
if(proc6[i].CPU1<= TQ){
    proc6[i].E=proc6[i].CPU1 + proc6[i].S;
    cur_end=proc6[i].E;
    proc6[i].CPU1=-1;
}else{
    proc6[i].E=proc6[i].S + TQ;
    cur_end=proc6[i].E;
    proc6[i].CPU1-=TQ;
}
    proc6[point].e[proc6[point].ep]=proc6[point].E;
    proc6[point].ep++;
past=i;
//printf("past: %d",past);
ready3[rp3]=0;
rp3++;
        printf("ready3: ");
    for(int u=0;u<rp3;u++){
        //printf("%d, ",ready3[u]);
    }
       printf("queue3: ");
    for(int u=0;u<qp3;u++){
        //printf("%d, ",queue3[u]);
    }

    // printf("P%d\n",proc6[point].name);
//printf("curend=%d :: i=%d\n",cur_end,i);
//MAIN CYCLE
    while(terminate6(n)==0)
    {
//delete the value
        for(int k=0;k<rp3;k++){
            ready3[k]=ready3[k+1];
        }
        rp3-=1;
// main execution
        sort6(i,n);
        point=next6(i,n,temp_start,cur_end,past);
      //  printf("P%d\n",proc6[point].name);
        //START:
        if(cur_end<proc6[point].AT){
            proc6[point].S=proc6[point].AT;
        }else{
            proc6[point].S=cur_end;
        }
    proc6[point].s[proc6[point].sp]=proc6[point].S;
    proc6[point].sp++;
        //END:
        if(proc6[point].CPU1<= TQ){
            proc6[point].E=proc6[point].CPU1 + proc6[point].S;
            cur_end=proc6[point].E;
            proc6[point].CPU1=-1;
        }else{
            proc6[point].E=proc6[point].S + TQ;
            cur_end=proc6[point].E;
            proc6[point].CPU1-=TQ;
        }
    proc6[point].e[proc6[point].ep]=proc6[point].E;
    proc6[point].ep++;
        past=point;
    }
    //printf("\n\n\n");
for(int i=0;i<total;i++){
    for(int k=0;k<proc6[i].ep-1;k++){
     proc6[i].at[proc6[i].ap]=proc6[i].e[k];
     proc6[i].ap++;
    }
   }
    view6(n);
//system("cls");
printf("view:\n\n");
    float ave_tat=0.0,ave_wt=0.0,ave_rt=0.0;
for(int i=0;i<total;i++){
    SetColor(proc6[i].color);
    printf("P%d\n",proc6[i].name);
    SetColor(15);
    printf("AT: ");
    for(int k=0;k<proc6[i].ap;k++){
        printf("%d, ",proc6[i].at[k]);
    }
    printf("\n");
    printf("CPU1: %d\n",proc6[i].orig_cpu);
    printf("Start: ");
    for(int k=0;k<proc6[i].sp;k++){
        printf("%d, ",proc6[i].s[k]);
    }
    printf("\n");
    printf("End: ");
    for(int k=0;k<proc6[i].ep;k++){
        printf("%d,",proc6[i].e[k]);
    }
    printf("\nCT: %d\n",proc6[i].CT);
    printf("TAT: %d\n",proc6[i].TAT);
    ave_tat+=proc6[i].TAT;
    printf("WT: %d\n",proc6[i].WT);
    ave_wt+=proc6[i].WT;
    printf("RT: %d\n",proc6[i].RT);
    ave_rt+=proc6[i].RT;
    printf("\n");
}
printf("AVERAGE WT: %f\n",ave_wt/n);
printf("AVERAGE TAT: %f\n",ave_tat/n);
printf("AVERAGE RT: %f\n",ave_rt/n);

//get max n of array in start and end in specific proc6ess
    for(int i=0;i<n;i++){
        proc6[i].nth=proc6[i].ep;
    }
gantt6(n);
printf("\n");
}

#endif // RR_H_INCLUDED
