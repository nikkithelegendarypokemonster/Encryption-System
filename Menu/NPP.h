#ifndef NPP_H_INCLUDED
#define NPP_H_INCLUDED
typedef struct proc5
{
    int name;
    int AT,CPU1,CPU2,IO,S,E;
    //priority
    int prio;
    int at[200],s[200],e[200];
    int ap,sp,ep;
    int nth,CT,WT,TAT,RT;
    //strorage for cpus
    int orig_cpu1,orig_cpu2,sum_cpu;
    int color;
} process5[200],temporary5;
process5 proc5;
temporary5 temp5;
int location2=0;
void checker5(int n)
{
    for(int i=0; i<n; i++)
    {
        if(proc5[i].CPU2<0)
        {
            for(int k=i; k>0; k--)
            {
                temp5=proc5[k];
                proc5[k]=proc5[k-1];
                proc5[k-1]=temp5;
            }
        }
    }
}
int terminate5(int n)
{
    for(int i=0; i<n; i++)
    {
        if(proc5[i].CPU2>=0)
        {
            return 0;
        }
    }
    return 1;
}

int least_AT5(int n)
{
    int min=proc5[0].AT;
    for(int i=0; i<n; i++)
    {
        if(proc5[i].AT<=min)
        {
            min=proc5[i].AT;
        }
    }
    return min;
}
void sort5(int s,int n){
    for(int i=s;i<n;i++){
        for(int k=s;k<n-1;k++){
            if(proc5[k].AT>=proc5[k+1].AT){
                    if(proc5[k].AT==proc5[k+1].AT){
                        if(proc5[k+1].name<proc5[k].name){
                            temp5=proc5[k];
                            proc5[k]=proc5[k+1];
                            proc5[k+1]=temp5;
                        }
                    }else{
                    temp5=proc5[k];
                    proc5[k]=proc5[k+1];
                    proc5[k+1]=temp5;
                    }

            }
        }
    }
}
int highest_priority5(int s,int n){
 int loc=s,max=s;
    for(int i=s; i<n; i++)
    {
        if(proc5[i].AT>=cur_start && proc5[i].AT<=cur_end && proc5[i].prio<=proc5[max].prio)
        {
         //if theres an equal on priorities
         if(proc5[i].prio==proc5[max].prio){
            if(proc5[i].AT<=proc5[max].AT){
                if(proc5[i].AT==proc5[i+1].AT){
                        if(proc5[i].name<proc5[i+1].name){
                            loc=i;
                        }
                    }
            }
         }else{
            loc=i;
         }
        }
    }
return loc;
}
int find_next_process5(int start,int n){
    for(int i=0;i<n;i++){
        for(int k=0;k<proc5[i].sp;k++){
            if(proc5[i].s[k]== start){
                this_proc5=i;
                location2=k;
                return proc5[i].e[k];
            }
        }
    }
    return 0;
}
void gantt5(int n){
int traverse=0,next=0,now=start;
int max_end=cur_end;
printf("\nCompletion Time: %d\n",max_end);
    while(traverse<=max_end){
        //draw line from 0 to start,start to end of one proc5ess, and breaks
                SetColor(proc5[this_proc5].color);
        printf(" - ");
        if(traverse==now){
                if(traverse==start){
                   printf("%d|",now);
                }else{
                SetColor(proc5[this_proc5].color);
                printf("P%d|%d",proc5[this_proc5].name,now);
                SetColor(15);
                }

        next=find_next_process5(traverse,n);
        //printf("\nlocation:%d\n",proc[this_proc5].s[location]);
        while(next==0 && traverse<=max_end ){
                traverse++;
            next=find_next_process5(traverse,n);
            if(traverse==proc5[this_proc5].s[location2]){
                printf("-IDLE|%d",proc5[this_proc5].s[location2]);
            }
        }
            now=next;
        }

        traverse++;
    }
    printf("|");
}
void view5(int n){
// sort5 by name
    for(int i=0;i<n;i++){
        for(int k=0;k<n-1;k++){
            if(proc5[k].name>proc5[k+1].name){
                temp5=proc5[k];
                proc5[k]=proc5[k+1];
                proc5[k+1]=temp5;
            }
        }
    }
    //set CT TAT WT RT
    for(int i=0;i<n;i++){
        //CT
        proc5[i].CT=proc5[i].e[proc5[i].ep-1];
        //TAT
        proc5[i].TAT=proc5[i].CT-proc5[i].at[0];
        //WT
         proc5[i].WT=proc5[i].TAT-proc5[i].sum_cpu;
        //RT
        proc5[i].RT=proc5[i].s[0]- proc5[i].at[0];
    }

}
void npp(void){
    int i=0,point=0,total;
//get nth proc5esses
    printf("NPP\n");
    printf("How many processes:");
    scanf("%d",&n);
    total=n;
// get inputs
    for(int i=0; i<n; i++)
    {
        printf("P%d:\n",i+1);
        proc5[i].name=i+1;
        printf("AT:");
        scanf("%d",&proc5[i].AT);
        if((proc2[i].AT>0 && i!=0)){
           proc2[i].at[0]=proc2[i].AT;
        proc2[i].ap++;
        }
        printf("Priority:");
        scanf("%d",&proc5[i].prio);
        printf("I/0:");
        scanf("%d",&proc5[i].IO);
        printf("CPU1:");
        scanf("%d",&proc5[i].CPU1);
        proc5[i].orig_cpu1=proc5[i].CPU1;
        if(proc5[i].orig_cpu1<0){
            proc5[i].orig_cpu1=0;
        }
        printf("CPU2:");
        scanf("%d",&proc5[i].CPU2);
        proc5[i].orig_cpu2=proc5[i].CPU2;
        if(proc5[i].orig_cpu2<0){
            proc5[i].orig_cpu2=0;
        }
            proc5[i].color=head_color;
         head_color++;
        if(head_color>14){
                    head_color=1;
        }
        proc5[i].sum_cpu=proc5[i].orig_cpu1+proc5[i].orig_cpu2+proc5[i].IO;
    }
           //clean the zeros to negative ones
    for(int i=0;i<n;i++){
        if(proc5[i].CPU1<=0){
            proc5[i].CPU1=-1;
        }
    }

//set cur_end by least AT and cur_start by least_AT5
    start=cur_start=least_AT5(n);
    cur_end=least_AT5(n);
//MAIN CYCLE
    while(terminate5(n)==0)
    {
        checker5(n);
        if(proc5[i].CPU2<0)
        {
            i++;
        }
//sort5 BY AT
        sort5(i,n);
        point=highest_priority5(i,n);
        printf("P%d : %d,",proc5[point].name,proc5[point].prio);
    if(cur_end>proc5[point].AT){
    proc5[point].S=cur_end;
    proc5[point].s[proc5[point].sp]=proc5[point].S;
    proc5[point].sp++;
    }else{
    proc5[point].S=proc5[point].AT;
    proc5[point].s[proc5[point].sp]=proc5[point].S;
    proc5[point].sp++;
    }

    //Set End
    if(proc5[point].CPU1<0){
    proc5[point].E=proc5[point].S + proc5[point].CPU2;
    proc5[point].CPU2=-1;
    }else{
    proc5[point].E=proc5[point].S + proc5[point].CPU1;
    proc5[point].CPU1=-1;
    }
    proc5[point].e[proc5[point].ep]=proc5[point].E;
    proc5[point].ep++;
    //Set cur_end to End
    cur_end=proc5[point].E;
    //Save AT to AT array
    proc5[point].at[proc5[point].ap]=proc5[point].AT;
    proc5[point].ap++;
    //set New AT by cur_end if CPU1 is >=0 only
    if(proc5[point].IO>=0){
    proc5[point].AT=cur_end + proc5[point].IO;
    proc5[point].IO=-1;
    }
    }

    view5(n);
    printf("\n\n\n");
    /*
   for(int i=0;i<total;i++){
    for(int k=0;k<proc2[i].sp;k++){
     proc2[i].at[proc2[i].ap]=proc2[i].e[k];
     proc2[i].ap++;
    }
   }*/
//system("cls");
printf("view:\n\n");
    float ave_tat=0.0,ave_wt=0.0,ave_rt=0.0;
for(int i=0;i<total;i++){
    SetColor(proc5[i].color);
    printf("P%d\n",proc5[i].name);
    SetColor(15);
    printf("AT: ");
    for(int k=0;k<proc5[i].ap;k++){
        printf("%d, ",proc5[i].at[k]);
    }
    printf("\n");
    printf("Priority:%d",proc5[i].prio);
    printf("\n");
    printf("CPU1: %d\n",proc5[i].orig_cpu1);
    printf("I/O: %d\n",proc5[i].sum_cpu - (proc5[i].orig_cpu1+proc5[i].orig_cpu2));
    printf("CPU2: %d\n",proc5[i].orig_cpu2);
    printf("Start: ");
    for(int k=0;k<proc5[i].sp;k++){
        printf("%d, ",proc5[i].s[k]);
    }
    printf("\n");
    printf("End: ");
    for(int k=0;k<proc5[i].ep;k++){
        printf("%d,",proc5[i].e[k]);
    }
    printf("\nCT: %d\n",proc5[i].CT);
    printf("TAT: %d\n",proc5[i].TAT);
    ave_tat+=proc5[i].TAT;
    printf("WT: %d\n",proc5[i].WT);
    ave_wt+=proc5[i].WT;
    printf("RT: %d\n",proc5[i].RT);
    ave_rt+=proc5[i].RT;
    printf("\n");
}
printf("AVERAGE WT: %f\n",ave_wt/n);
printf("AVERAGE TAT: %f\n",ave_tat/n);
printf("AVERAGE RT: %f\n",ave_rt/n);

gantt5(n);
printf("\n");
}
/*
1
5
5


*/
#endif // NPP_H_INCLUDED
