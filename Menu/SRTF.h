#ifndef SRTF_H_INCLUDED
#define SRTF_H_INCLUDED
#include<conio.h>
int ready1 [200];
int queue1[200];
int qp1=0,rp1=0;
typedef struct proc3
{
    int name;
    int AT,CPU1,S,E;
    int at[200],s[200],e[200];
    int ap,sp,ep;
    //max n in array
    int nth,CT,WT,TAT,RT;
    //strorage for cpus
    int orig_cpu;
    int complete;
    int color;
} process3[200],temporary3;
process3 proc3;
temporary3 temp3;
int location3=0;
void checker3(int n)
{
    for(int i=0; i<n; i++)
    {
        if(proc3[i].CPU1<0)
        {
            for(int k=i; k>0; k--)
            {
                temp3=proc3[k];
                proc3[k]=proc3[k-1];
                proc3[k-1]=temp3;
            }
        }
    }
}
int terminate3(int n)
{
    for(int i=0; i<n; i++)
    {
        if(proc3[i].CPU1>=0)
        {
            return 0;
        }
    }
    return 1;
}

int least_AT3(int n)
{
    int min=proc3[0].AT;
    for(int i=0; i<n; i++)
    {
        if(proc3[i].AT<=min)
        {
            min=proc3[i].AT;
        }
    }
    return min;
}
void sort3(int s,int n){
    for(int i=s;i<n;i++){
        for(int k=s;k<n-1;k++){
            if(proc3[k].AT>=proc3[k+1].AT){
                    if(proc3[k].AT==proc3[k+1].AT){
                        if(proc3[k+1].CPU1<proc3[k].CPU1){
                            temp3=proc3[k];
                            proc3[k]=proc3[k+1];
                            proc3[k+1]=temp3;
                        }
                    }else{
                    temp3=proc3[k];
                    proc3[k]=proc3[k+1];
                    proc3[k+1]=temp3;
                    }

            }
        }
    }

}
int inside_queue13(int proc3ess){
    for(int i=0;i<rp1;i++){
        if(ready1[i]==proc3ess){
            return 1;
        }
    }
    return 0;
}
void search3(int n){
    for(int i=0;i<n;i++){
        if(inside_queue13(i)==0){
            if(proc3[i].AT>=start && proc3[i].AT<=cur_end){
                // testing: printf("\ni:%d",i);
                ready1[rp1]=i;
                rp1++;
            }
        }
    }
}
int ultra_least3(int n,int running){
int min=ready1[running],big=0,big_loc=0;
if(proc3[running].CPU1<=0){
        proc3[running].complete=1;
    //find the bidggest bt in queue1 once you find one exit the loop
    for(int i=0;i<rp1;i++){
        if(proc3[ready1[i]].CPU1>big &&i!=running){
        big=proc3[ready1[i]].CPU1;
        big_loc=i;
        break;
        }
    }
    min=big_loc;
}
    for(int i=0;i<rp1;i++){
        if(proc3[i].CPU1< proc3[min].CPU1 && proc3[i].CPU1>0  ){
                min=i;
        }
    }
return min;
}
void srtf(int n){
int running=ready1[0],least=0,trying=0;
    while(cur_end<max_at){
     least=ultra_least3(n,running);
    //KEEP RUNNING= CUREND+1 RUNNING.CPU-1 dont save end cause it will still run
    //INITIAL: curstart=0 curend=1
    //printf("Least:%d curstart:%d curend:%d running_cpu:P%d->%d \n",proc3[least].name,cur_start,cur_end,proc3[running].name,proc3[running].CPU1);
    if(((least==running) && proc3[running].CPU1>0 )){
        if(flag==1){
            proc3[running].S=cur_start;
            proc3[running].AT= proc3[running].S;
            cur_end+=1;
            if(trying==0){
            proc3[running].s[proc3[running].sp]=proc3[running].S;
            proc3[running].sp++;
            trying=1;
            }
        }else{
        cur_end+=1;
        //proc3[running].CPU1-=1;
        }

    }else{
        flag=0;
    //CONTEXT SWITCH
    //first  work the running proc3ess one more and set start
        printf("cpu of running:%d\n",proc3[running].CPU1);
    //1->0,6->5,7->6
    //set the end of current running proc3ess to be terminate3d
    if(proc3[running].CPU1<=proc3[least].AT){
        proc3[running].E=cur_end;
    }else{
    proc3[running].E=proc3[least].AT;
    }
    printf("end of running:%d\n",proc3[running].E);
    proc3[running].e[proc3[running].ep]=proc3[running].E;
    proc3[running].ep++;
    //set the start of the next proc3ess:least
    if(proc3[running].CPU1<proc3[least].AT && proc3[running].CPU1>0){
        proc3[least].S= proc3[least].AT;

    }else{
        proc3[least].S= cur_end;
    }
    printf("%d",proc3[least].AT);
    //proc3
    //ends: p1->1,p1->
    proc3[least].s[proc3[least].sp]=proc3[least].S;
    proc3[least].sp++;
    running=least;
    cur_end+=1;
    }
    //work the running cpu
    proc3[running].CPU1-=1;
    //========================
    search3(n);
    }
    if(cur_end!=0){
        proc3[running].E=cur_end;
        proc3[running].e[proc3[running].ep]=proc3[running].E;
        proc3[running].ep++;
    }

}
int least_burst3(int s,int n)
{
    int loc=s;
    for(int i=s+1; i<n; i++)
    {
        if(proc3[i].AT>=cur_start && proc3[i].AT<=cur_end)
        {
                if(proc3[i].CPU1<proc3[loc].CPU1)
                {
                    loc=i;
                }
        }
    }
    return loc;
}
void sjf3(int n){
int i=0,point=0;
//MAIN CYCLE
    while(terminate3(n)==0)
    {
        checker3(n);
        while(proc3[i].CPU1<0)
        {
            i++;
        }
        //sort3 BY AT
        sort3(i,n);
        //printf("P%d, ",proc3[i].name);
        min_burst=proc3[i].CPU1;
        point=least_burst3(i,n);
    //printf("P%d,",proc3[point].name);
    //Set Start
    if(cur_end>proc3[point].AT){
    proc3[point].S=cur_end;
    proc3[point].s[proc3[point].sp]=proc3[point].S;
    proc3[point].sp++;
    }else{
    proc3[point].S=proc3[point].AT;
    proc3[point].s[proc3[point].sp]=proc3[point].S;
    proc3[point].sp++;
    }

    proc3[point].AT= proc3[point].S;
    //Set End
    proc3[point].E=proc3[point].S + proc3[point].CPU1;
    proc3[point].CPU1=-1;
    proc3[point].e[proc3[point].ep]=proc3[point].E;
    proc3[point].ep++;
    //Set cur_end to End
    cur_end=proc3[point].E;
    }

}

int find_next_process3(int start,int n){
    for(int i=0;i<n;i++){
        for(int k=0;k<proc3[i].sp;k++){
            if(proc3[i].s[k]== start){
                this_proc3=i;
                location3=k;
                return proc3[i].e[k];
            }
        }
    }
    return 0;
}
void gantt3(int n){
int traverse=0,next=0,now=start;
int max_end=cur_end,pin=start;
printf("\nCompletion Time: %d\n",max_end);
    while(traverse<=max_end){
        //draw line from 0 to start,start to end of one proc3ess, and breaks
                SetColor(proc3[this_proc3].color);
        printf(" - ");
        if(traverse==now){
            if(traverse==start){
                   printf("%d|",now);
                }else{
                SetColor(proc3[this_proc3].color);
                printf("P%d|%d",proc3[this_proc3].name,now);
                SetColor(15);
                }
        next=find_next_process3(traverse,n);
                while(next==0 && traverse<=max_end ){
                traverse++;
            next=find_next_process3(traverse,n);
            if(traverse==proc3[this_proc3].s[location3]){
                printf("-IDLE|%d",proc3[this_proc3].s[location3]);
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
void view3(int n){
// sort3 by name
    for(int i=0;i<n;i++){
        for(int k=0;k<n-1;k++){
            if(proc3[k].name>proc3[k+1].name){
                temp3=proc3[k];
                proc3[k]=proc3[k+1];
                proc3[k+1]=temp3;
            }
        }
    }
    //set CT TAT WT RT
    for(int i=0;i<n;i++){
        //CT
        proc3[i].CT=proc3[i].e[proc3[i].ep-1];
        //TAT
        proc3[i].TAT=proc3[i].CT-proc3[i].at[0];
        //WT
        proc3[i].WT=proc3[i].TAT-proc3[i].orig_cpu;
        //RT
        proc3[i].RT=proc3[i].s[0]-proc3[i].at[0];
    }

}
void SSRTFF(void){
       int i=0,total=0;
//get nth proc3esses
    printf("SRTF\n");
    printf("How many processes:");
    scanf("%d",&n);
    total=n;
// get inputs
    for(int i=0; i<n; i++)
    {
        printf("P%d:\n",i+1);
        proc3[i].name=i+1;
        printf("AT:");
        scanf("%d",&proc3[i].AT);
        proc3[i].at[0]=proc3[i].AT;
        proc3[i].ap++;
        printf("CPU1:");
        scanf("%d",&proc3[i].CPU1);
        proc3[i].orig_cpu=proc3[i].CPU1;
        if(proc3[i].AT>=max_at){
            max_at=proc3[i].AT;
        }
            proc3[i].color=head_color;
         head_color++;
        if(head_color>14){
                    head_color=1;
        }
    }

    sort3(i,n);
    start=cur_start=proc3[i].AT;
    cur_end=0;
    ready1[0]=0;
    rp1++;
    proc3[ready1[0]].S=start;
    srtf(n);
    //clean the zeros to negative ones
    for(int i=0;i<n;i++){
        if(proc3[i].CPU1<=0){
            proc3[i].CPU1=-1;
        }
    }

    sjf3(n);
    printf("\n\n\n");
    for(int i=0;i<total;i++){
    for(int k=0;k<proc3[i].ep-1;k++){
     proc3[i].at[proc3[i].ap]=proc3[i].e[k];
     proc3[i].ap++;
    }
   }
    view3(n);
//system("cls");
printf("view:\n\n");
    float ave_tat=0.0,ave_wt=0.0,ave_rt=0.0;
for(int i=0;i<total;i++){
    SetColor(proc3[i].color);
    printf("P%d\n",proc3[i].name);
    SetColor(15);
    printf("AT: ");
    for(int k=0;k<proc3[i].ap;k++){
        printf("%d, ",proc3[i].at[k]);
    }
    printf("\n");
    printf("CPU1: %d\n",proc3[i].orig_cpu);
    printf("Start: ");
    for(int k=0;k<proc3[i].sp;k++){
        printf("%d, ",proc3[i].s[k]);
    }
    printf("\n");
    printf("End: ");
    for(int k=0;k<proc3[i].ep;k++){
        printf("%d,",proc3[i].e[k]);
    }
    printf("\nCT: %d\n",proc3[i].CT);
    printf("TAT: %d\n",proc3[i].TAT);
    ave_tat+=proc3[i].TAT;
    printf("WT: %d\n",proc3[i].WT);
    ave_wt+=proc3[i].WT;
    printf("RT: %d\n",proc3[i].RT);
    ave_rt+=proc3[i].RT;
    printf("\n");
}
printf("AVERAGE WT: %f\n",ave_wt/n);
printf("AVERAGE TAT: %f\n",ave_tat/n);
printf("AVERAGE RT: %f\n",ave_rt/n);

//get max n of array in start and end in specific proc3ess
    for(int i=0;i<n;i++){
        proc3[i].nth=proc3[i].ep;
    }
gantt3(n);
printf("\n");
}

#endif // SRTF_H_INCLUDED
