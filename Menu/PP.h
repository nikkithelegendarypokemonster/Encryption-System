#ifndef PP_H_INCLUDED
#define PP_H_INCLUDED
int ready2 [200];
int queue2[200];
int qp2=0,rp2=0;
typedef struct proc4
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
    int color;
} process4[200],temp4orary4;
process4 proc4;
temp4orary4 temp4;
int location4=0;
void checker4(int n)
{
    for(int i=0; i<n; i++)
    {
        if(proc4[i].CPU1<0)
        {
            for(int k=i; k>0; k--)
            {
                temp4=proc4[k];
                proc4[k]=proc4[k-1];
                proc4[k-1]=temp4;
            }
        }
    }
}
int terminate4(int n)
{
    for(int i=0; i<n; i++)
    {
        if(proc4[i].CPU1>=0)
        {
            return 0;
        }
    }
    return 1;
}

int least_AT4(int n)
{
    int min=proc4[0].AT;
    for(int i=0; i<n; i++)
    {
        if(proc4[i].AT<=min)
        {
            min=proc4[i].AT;
        }
    }
    return min;
}
void sort4(int s,int n){
    for(int i=s;i<n;i++){
        for(int k=s;k<n-1;k++){
            if(proc4[k].AT>=proc4[k+1].AT){
                    if(proc4[k].AT==proc4[k+1].AT){
                        if(proc4[k+1].CPU1<proc4[k].CPU1){
                            temp4=proc4[k];
                            proc4[k]=proc4[k+1];
                            proc4[k+1]=temp4;
                        }
                    }else{
                    temp4=proc4[k];
                    proc4[k]=proc4[k+1];
                    proc4[k+1]=temp4;
                    }

            }
        }
    }

}
int inside_queue24(int proc4ess){
    for(int i=0;i<rp2;i++){
        if(ready2[i]==proc4ess){
            return 1;
        }
    }
    return 0;
}
void search4(int n){
    for(int i=0;i<n;i++){
        if(inside_queue24(i)==0){
            if(proc4[i].AT>=start && proc4[i].AT<=cur_end){
                // testing: printf("\ni:%d",i);
                ready2[rp2]=i;
                rp2++;
            }
        }
    }
}
int ultra_least4(int n,int running){
int min=ready2[running],big=0,big_loc=0;
if(proc4[running].CPU1<=0){
        proc4[running].complete=1;
    //find the bidggest bt in queue2 once you find one exit the loop
    for(int i=0;i<rp2;i++){
        if(proc4[ready2[i]].CPU1>big &&i!=running){
        big=proc4[ready2[i]].CPU1;
        big_loc=i;
        break;
        }
    }
    min=big_loc;
    //printf("\n\n\n\n\nbigloc:%d\n\n\n\n",proc4[min].name);
}

    for(int i=0;i<rp2;i++){
            //change this if need to set the setting of greater than and less than
        if(proc4[i].prio<proc4[min].prio && proc4[i].CPU1>0){
                min=i;
        }
    }
return min;
}
int highest_priority4(int s,int n){
 int loc=s;
    for(int i=s; i<n; i++)
    {
        if(proc4[i].AT>=cur_start && proc4[i].AT<=cur_end && proc4[i].prio<proc4[loc].prio)
        {
            loc=i;
        }
    }
return loc;
}
void PP4(int n){
int running=ready2[0],least=0,trying=0;
    while(cur_end<=max_at){
     least=ultra_least4(n,running);
    //KEEP RUNNING= CUREND+1 RUNNING.CPU-1 dont save end cause it will still run
    //INITIAL: curstart=0 curend=1
   // printf("LEAST: P%d\n",proc4[least].name);
    //printf("Running: P%d -> %d\n",proc4[running].name,proc4[running].CPU1);
    //printf("curend: %d\n",cur_end);
    if(((least==running)&& proc4[running].CPU1>0)){
        if(flag==1){
            proc4[running].S=cur_start;
            cur_end+=1;
            if(trying==0){
            proc4[running].s[proc4[running].sp]=proc4[running].S;
            proc4[running].sp++;
            trying=1;
            }
        }else{
        cur_end+=1;
        //proc4[running].CPU1-=1;
        }

    }else{
        flag=0;
    //CONTEXT SWITCH
    //first  work the running proc4ess one more and set start
        //printf("cpu of running:%d\n",proc4[running].CPU1);
    //1->0,6->5,7->6
    //set the end of current running proc4ess to be terminate4d
    if(proc4[running].CPU1<=proc4[least].AT){
        proc4[running].E=cur_end;
    }else{
    proc4[running].E=proc4[least].AT;
    }
    //set the start of the next proc4ess:least
    if(proc4[running].CPU1<proc4[least].AT && proc4[running].CPU1>0){
        proc4[least].S= proc4[least].AT;
    }else{
        proc4[least].S= cur_end;
    }
    proc4[running].AT= proc4[running].E;

   // printf("%d",proc4[least].AT);
    //proc4
    //ends: p1->1,p1->
    proc4[running].e[proc4[running].ep]=proc4[running].E;
    proc4[running].ep++;
    proc4[least].s[proc4[least].sp]=proc4[least].S;
    proc4[least].sp++;
    running=least;
    cur_end+=1;
    }
    search4(n);
    if(cur_end<=max_at){
        proc4[running].CPU1-=1;
        //printf("P%d->%d\n",proc4[running].name,proc4[running].CPU1);
    }
}
    //printf("P%d->%d\n",proc4[running].name,proc4[running].CPU1);
    //printf("proc4[running].cpu:%d\n",proc4[running].CPU1);
    proc4[running].E=proc4[running].CPU1+proc4[running].S;
    proc4[running].e[proc4[running].ep]=proc4[running].E;
    proc4[running].ep++;
    proc4[running].CPU1=-1;
    cur_end=proc4[running].E;
}

int find_next_process4(int start,int n){
    for(int i=0;i<n;i++){
        for(int k=0;k<proc4[i].sp;k++){
            if(proc4[i].s[k]== start){
                this_proc4=i;
                location4=k;
                return proc4[i].e[k];
            }
        }
    }
    return 0;
}
void gantt4(int n){
int traverse=0,next=0,now=start;
int max_end=cur_end,pin=start;
printf("\nCompletion Time: %d\n",max_end);
    while(traverse<=max_end){
        //draw line from 0 to start,start to end of one proc4ess, and breaks
                SetColor(proc4[this_proc4].color);
        printf(" - ");
        if(traverse==now){
            if(traverse==start){
                   printf("%d|",now);
                }else{
                SetColor(proc4[this_proc4].color);
                printf("P%d|%d",proc4[this_proc4].name,now);
                SetColor(15);
                }
        next=find_next_process4(traverse,n);
                while(next==0 && traverse<=max_end ){
                traverse++;
            next=find_next_process4(traverse,n);
            if(traverse==proc4[this_proc4].s[location4]){
                printf("-IDLE|%d",proc4[this_proc4].s[location4]);
            }
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
void view4(int n){
// sort4 by name
    for(int i=0;i<n;i++){
        for(int k=0;k<n-1;k++){
            if(proc4[k].name>proc4[k+1].name){
                temp4=proc4[k];
                proc4[k]=proc4[k+1];
                proc4[k+1]=temp4;
            }
        }
    }
    //set CT TAT WT RT
    for(int i=0;i<n;i++){
        //CT
        proc4[i].CT=proc4[i].e[proc4[i].ep-1];
        //TAT
        proc4[i].TAT=proc4[i].CT-proc4[i].at[0];
        //WT
        proc4[i].WT=proc4[i].TAT-proc4[i].orig_cpu;
        //RT
        proc4[i].RT=proc4[i].s[0]-proc4[i].at[0];
    }

}
void pp(void){
   int i=0,total=0,point;
//get nth proc4esses
    printf("PP\n");
    printf("How many processes:");
    scanf("%d",&n);
    total=n;
// get inputs
    for(int i=0; i<n; i++)
    {
        printf("P%d:\n",i+1);
        proc4[i].name=i+1;
        printf("AT:");
        scanf("%d",&proc4[i].AT);
        proc4[i].at[proc4[i].ap]=proc4[i].AT;
        proc4[i].ap++;
        printf("Priority:");
        scanf("%d",&proc4[i].prio);
        printf("CPU1:");
        scanf("%d",&proc4[i].CPU1);
        proc4[i].orig_cpu=proc4[i].CPU1;
        if(proc4[i].AT>=max_at){
            max_at=proc4[i].AT;
        }
        proc4[i].color=head_color;
         head_color++;
        if(head_color>14){
                    head_color=1;
        }
    }

    sort4(i,n);
    start=cur_start=proc4[i].AT;
    cur_end=0;
    ready2[0]=0;
    rp2++;
    proc4[ready2[0]].S=start;
    PP4(n);
    printf("\n\n\n\n");
       //clean the zeros to negative ones
    for(int i=0;i<n;i++){
        if(proc4[i].CPU1<=0){
            proc4[i].CPU1=-1;
        }
    }
   i=0;
   point=0;
//do a non preemtive priority
//set cur_start by least_AT4 and dont set the cur end
    cur_start=least_AT4(n);
    while(terminate4(n)==0)
    {
        checker4(n);
        while(proc4[i].CPU1<0)
        {
            i++;
        }
//sort4 BY AT
        sort4(i,n);
        point=highest_priority4(i,n);
        printf("P%d : %d,",proc4[point].name,proc4[point].prio);
    if(cur_end>proc4[point].AT){
    proc4[point].S=cur_end;
    proc4[point].s[proc4[point].sp]=proc4[point].S;
    proc4[point].sp++;
    }else{
    proc4[point].S=proc4[point].AT;
    proc4[point].s[proc4[point].sp]=proc4[point].S;
    proc4[point].sp++;
    }
proc4[point].AT= proc4[point].S;
    //Set End
    proc4[point].E=proc4[point].S + proc4[point].CPU1;
    proc4[point].CPU1=-1;
    proc4[point].e[proc4[point].ep]=proc4[point].E;
    proc4[point].ep++;
    //Set cur_end to End
    cur_end=proc4[point].E;
    }

    printf("\n\n\n");
        for(int i=0;i<total;i++){
    for(int k=0;k<proc4[i].ep-1;k++){
     proc4[i].at[proc4[i].ap]=proc4[i].e[k];
     proc4[i].ap++;
    }
   }
    view4(n);
printf("view:\n\n");
    float ave_tat=0.0,ave_wt=0.0,ave_rt=0.0;
for(int i=0;i<total;i++){
    SetColor(proc4[i].color);
    printf("P%d\n",proc4[i].name);
    SetColor(15);
    printf("AT: ");
    for(int k=0;k<proc4[i].ap;k++){
        printf("%d, ",proc4[i].at[k]);
    }
    printf("\n");
    printf("Priority:%d",proc4[i].prio);
    printf("\n");
    printf("CPU1: %d\n",proc4[i].orig_cpu);
    printf("Start: ");
    for(int k=0;k<proc4[i].sp;k++){
        printf("%d, ",proc4[i].s[k]);
    }
    printf("\n");
    printf("End: ");
    for(int k=0;k<proc4[i].ep;k++){
        printf("%d,",proc4[i].e[k]);
    }
    printf("\nCT: %d\n",proc4[i].CT);
    printf("TAT: %d\n",proc4[i].TAT);
    ave_tat+=proc4[i].TAT;
    printf("WT: %d\n",proc4[i].WT);
    ave_wt+=proc4[i].WT;
    printf("RT: %d\n",proc4[i].RT);
    ave_rt+=proc4[i].RT;
    printf("\n");
}
printf("AVERAGE WT: %f\n",ave_wt/n);
printf("AVERAGE TAT: %f\n",ave_tat/n);
printf("AVERAGE RT: %f\n",ave_rt/n);

gantt4(n);
printf("\n");
}

#endif // PP_H_INCLUDED
