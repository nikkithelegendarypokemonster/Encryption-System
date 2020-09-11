#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
int cur_end=0,start=0,min_burst=0,n=0,running=0,max_at=0,cur_start=0,flag=1,this_proc=0;
int ready [200],qp=0,rp=0;
int queue[200];
typedef struct Proc
{
    int name;
    int AT,CPU1,S,E;
    int at[200],s[200],e[200];
    int ap,sp,ep;
    int prio;
    //max n in array
    int nth,CT,WT,TAT,RT;
    //strorage for cpus
    int orig_cpu;
    int complete;
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
void sort(int s,int n){
    for(int i=s;i<n;i++){
        for(int k=s;k<n-1;k++){
            if(proc[k].AT>=proc[k+1].AT){
                    if(proc[k].AT==proc[k+1].AT){
                        if(proc[k+1].CPU1<proc[k].CPU1){
                            temp=proc[k];
                            proc[k]=proc[k+1];
                            proc[k+1]=temp;
                        }
                    }else{
                    temp=proc[k];
                    proc[k]=proc[k+1];
                    proc[k+1]=temp;
                    }

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
void search(int n){
    for(int i=0;i<n;i++){
        if(inside_queue(i)==0){
            if(proc[i].AT>=start && proc[i].AT<=cur_end){
                // testing: printf("\ni:%d",i);
                ready[rp]=i;
                rp++;
            }
        }
    }
}
int ultra_least(int n,int running){
int min=ready[running],big=0,big_loc=0;
if(proc[running].CPU1<=0){
        proc[running].complete=1;
    //find the bidggest bt in queue once you find one exit the loop
    for(int i=0;i<rp;i++){
        if(proc[ready[i]].CPU1>big &&i!=running){
        big=proc[ready[i]].CPU1;
        big_loc=i;
        break;
        }
    }
    min=big_loc;
    printf("\n\n\n\n\nbigloc:%d\n\n\n\n",proc[min].name);
}

    for(int i=0;i<rp;i++){
            //change this if need to set the setting of greater than and less than
        if(proc[i].prio<proc[min].prio && proc[i].CPU1>0){
                min=i;
        }
    }
return min;
}
int highest_priority(int s,int n){
 int loc=s;
    for(int i=s; i<n; i++)
    {
        if(proc[i].AT>=cur_start && proc[i].AT<=cur_end && proc[i].prio<proc[loc].prio)
        {
            loc=i;
        }
    }
return loc;
}
void PP(int n){
int running=ready[0],least=0,trying=0,unit=0;
    while(cur_end<=max_at){
     least=ultra_least(n,running);
    //KEEP RUNNING= CUREND+1 RUNNING.CPU-1 dont save end cause it will still run
    //INITIAL: curstart=0 curend=1
    printf("LEAST: P%d\n",proc[least].name);
    printf("Running: P%d -> %d\n",proc[running].name,proc[running].CPU1);
    printf("curend: %d\n",cur_end);
    if(((least==running)&& proc[running].CPU1>0)){
        if(flag==1){
            proc[running].S=cur_start;
            cur_end+=1;
            if(trying==0){
            proc[running].s[proc[running].sp]=proc[running].S;
            proc[running].sp++;
            trying=1;
            }
        }else{
        cur_end+=1;
        //proc[running].CPU1-=1;
        }

    }else{
        flag=0;
    //CONTEXT SWITCH
    //first  work the running process one more and set start
        //printf("cpu of running:%d\n",proc[running].CPU1);
    //1->0,6->5,7->6
    //set the end of current running process to be terminated
    if(proc[running].CPU1<=proc[least].AT){
        proc[running].E=cur_end;
    }else{
    proc[running].E=proc[least].AT;
    }
    //set the start of the next process:least
    if(proc[running].CPU1<proc[least].AT && proc[running].CPU1>0){
        proc[least].S= proc[least].AT;
    }else{
        proc[least].S= cur_end;
    }
    proc[running].AT= proc[running].E;
    proc[running].at[proc[running].ap]=proc[running].E;
    proc[running].ap++;

   // printf("%d",proc[least].AT);
    //proc
    //ends: p1->1,p1->
    proc[running].e[proc[running].ep]=proc[running].E;
    proc[running].ep++;
    proc[least].s[proc[least].sp]=proc[least].S;
    proc[least].sp++;
    running=least;
    cur_end+=1;
    }
    search(n);
    if(cur_end<=max_at){
        proc[running].CPU1-=1;
        //printf("P%d->%d\n",proc[running].name,proc[running].CPU1);
    }
}
    //printf("P%d->%d\n",proc[running].name,proc[running].CPU1);
    //printf("proc[running].cpu:%d\n",proc[running].CPU1);
    proc[running].E=proc[running].CPU1+proc[running].S;
    proc[running].e[proc[running].ep]=proc[running].E;
    proc[running].ep++;
    proc[running].CPU1=-1;
    cur_end=proc[running].E;
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
        proc[i].RT=proc[i].s[0]-proc[i].at[0];
    }

}
int main()
{
   int i=0,total=0,point;
//get nth processes
    printf("PP\n");
    printf("How many processes:");
    scanf("%d",&n);
    total=n;
// get inputs
    for(int i=0; i<n; i++)
    {
        printf("P%d:\n",i+1);
        proc[i].name=i+1;
        printf("AT:");
        scanf("%d",&proc[i].AT);
        proc[i].at[proc[i].ap]=proc[i].AT;
        proc[i].ap++;
        printf("Priority:");
        scanf("%d",&proc[i].prio);
        printf("CPU1:");
        scanf("%d",&proc[i].CPU1);
        proc[i].orig_cpu=proc[i].CPU1;
        if(proc[i].AT>=max_at){
            max_at=proc[i].AT;
        }
    }

    sort(i,n);
    start=cur_start=proc[i].AT;
    cur_end=0;
    ready[0]=0;
    rp++;
    proc[ready[0]].S=start;
    PP(n);
    printf("\n\n\n\n");
       //clean the zeros to negative ones
    for(int i=0;i<n;i++){
        if(proc[i].CPU1<=0){
            proc[i].CPU1=-1;
        }
    }

    for(int i=0;i<total;i++){
    printf("P%d\n",proc[i].name);
    printf("AT: ");
    for(int k=0;k<proc[i].ap;k++){
        printf("%d, ",proc[i].at[k]);
    }
    printf("\n");
    printf("Priority: %d\n",proc[i].prio);
    printf("CPU1: %d\n",proc[i].CPU1);
    printf("Start: ");
    for(int k=0;k<proc[i].sp;k++){
        printf("%d, ",proc[i].s[k]);
    }
    printf("\n");
    printf("End: ");
    for(int k=0;k<proc[i].ep;k++){
        printf("%d,",proc[i].e[k]);
    }
    printf("\n");
}
getch();
   i=0;
   point=0;
//do a non preemtive priority
//set cur_start by least_AT and dont set the cur end
    cur_start=least_AT(n);
    while(terminate(n)==0)
    {
        checker(n);
        while(proc[i].CPU1<0)
        {
            i++;
        }
//SORT BY AT
        sort(i,n);
        point=highest_priority(i,n);
        printf("P%d : %d,",proc[point].name,proc[point].prio);
    if(cur_end>proc[point].AT){
    proc[point].S=cur_end;
    proc[point].s[proc[point].sp]=proc[point].S;
    proc[point].sp++;
    }else{
    proc[point].S=proc[point].AT;
    proc[point].s[proc[point].sp]=proc[point].S;
    proc[point].sp++;
    }
proc[point].AT= proc[point].S;
    //Set End
    proc[point].E=proc[point].S + proc[point].CPU1;
    proc[point].CPU1=-1;
    proc[point].e[proc[point].ep]=proc[point].E;
    proc[point].ep++;
    //Set cur_end to End
    cur_end=proc[point].E;
    //Save AT to AT array
    proc[point].at[proc[point].ap]=proc[point].AT;
    proc[point].ap++;
    }

    printf("\n\n\n");
    view(n);
//system("cls");
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

gantt(n);
}
/*
7
0
3
4
1
4
2
3
4
4
4
5
1
5
2
6
6
6
5
10
1
1
==========================================
7
0
3
8
1
4
2
3
4
4
4
5
1
5
2
6
6
6
5
10
1
1
======================================================
7
0
2
4
1
4
2
2
6
3
3
10
5
4
8
1
5
12
4
6
9
6
===========================================================
5
0
2
8
3
1
3
4
2
10
6
2
9
8
1
7

*/
