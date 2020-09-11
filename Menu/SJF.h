#ifndef SJF_H_INCLUDED
#define SJF_H_INCLUDED
typedef struct proc2
{
    int name;
    int AT,CPU1,CPU2,IO,S,E;
    int at[200],s[200],e[200];
    int ap,sp,ep;
        //max n in array
    int nth,CT,WT,TAT,RT;
    //strorage for cpus
    int orig_cpu1,orig_cpu2,sum_cpu;
    int color;
} process2[200],temporary2;
process2 proc2;
temporary2 temp2;
int location1=0;
void checker2(int n)
{
    for(int i=0; i<n; i++)
    {
        if(proc2[i].CPU2<0)
        {
            for(int k=i; k>0; k--)
            {
                temp2=proc2[k];
                proc2[k]=proc2[k-1];
                proc2[k-1]=temp2;
            }
        }
    }
}
int terminate2(int n)
{
    for(int i=0; i<n; i++)
    {
        if(proc2[i].CPU2>=0)
        {
            return 0;
        }
    }
    return 1;
}

int least_AT2(int n)
{
    int min=proc2[0].AT;
    for(int i=0; i<n; i++)
    {
        if(proc2[i].AT<=min)
        {
            min=proc2[i].AT;
        }
    }
    return min;
}
void sort2(int s,int n){
    for(int i=s;i<n;i++){
        for(int k=s;k<n-1;k++){
            if(proc2[k].AT>=proc2[k+1].AT){
                    if(proc2[k].AT==proc2[k+1].AT){
                        if(proc2[k+1].name<proc2[k].name){
                            temp2=proc2[k];
                            proc2[k]=proc2[k+1];
                            proc2[k+1]=temp2;
                        }
                    }else{
                    temp2=proc2[k];
                    proc2[k]=proc2[k+1];
                    proc2[k+1]=temp2;
                    }

            }
        }
    }
}
int least_burst(int s,int n)
{
    int loc=s;
    for(int i=s+1; i<n; i++)
    {
        if(proc2[i].AT>=cur_start && proc2[i].AT<=cur_end)
        {
           // printf("in between %d : %d is %d\n",cur_start,cur_end,proc2[i].AT);
            if(proc2[i].CPU1<0)
            {
                if(proc2[loc].CPU1<0){
                    if(proc2[i].CPU2<proc2[loc].CPU2){
                        loc=i;
                    }
                }else{
                    if(proc2[i].CPU2<proc2[loc].CPU1 )
                    {
                        loc=i;
                    }
                }

            }
            else
            {
                if(proc2[loc].CPU1<0){
                    if(proc2[i].CPU1<proc2[loc].CPU2){
                        loc=i;
                    }
                }else{
                    if(proc2[i].CPU1<proc2[loc].CPU1)
                    {
                        loc=i;
                    }
                }

            }
        }
    }
    //printf("min is:P%d value: %d\n",loc,min_burst);
    return loc;
}
int find_next_process2(int start,int n){
    for(int i=0;i<n;i++){
        for(int k=0;k<proc2[i].sp;k++){
            if(proc2[i].s[k]== start){
                this_proc2=i;
                location1=k;
                return proc2[i].e[k];
            }
        }
    }
    return 0;
}
void gantt2(int n){
int traverse=0,next=0,now=start;
int max_end=cur_end,pin=start;
printf("\nCompletion Time: %d\n",max_end);
    while(traverse<=max_end){
        //draw line from 0 to start,start to end of one proc2ess, and breaks
                SetColor(proc2[this_proc2].color);
        printf(" - ");
        if(traverse==now){
                if(traverse==start){
                   printf("%d|",now);
                }else{
                SetColor(proc2[this_proc2].color);
                printf("P%d|%d",proc2[this_proc2].name,now);
                SetColor(15);
                }

        next=find_next_process2(traverse,n);
                while(next==0 && traverse<=max_end ){
                traverse++;
            next=find_next_process2(traverse,n);
            if(traverse==proc2[this_proc2].s[location1]){
                printf("-IDLE|%d",proc2[this_proc2].s[location1]);
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
void view2(int n){
// sort2 by name
    for(int i=0;i<n;i++){
        for(int k=0;k<n-1;k++){
            if(proc2[k].name>proc2[k+1].name){
                temp2=proc2[k];
                proc2[k]=proc2[k+1];
                proc2[k+1]=temp2;
            }
        }
    }
    //set CT TAT WT RT
    for(int i=0;i<n;i++){
        //CT
        proc2[i].CT=proc2[i].e[proc2[i].ep-1];
        //TAT
        proc2[i].TAT=proc2[i].CT-proc2[i].at[0];
        //WT
         proc2[i].WT=proc2[i].TAT-proc2[i].sum_cpu;
        //RT
        proc2[i].RT=proc2[i].s[0]- proc2[i].at[0];
    }

}
void sjf(void){

    int i=0,point=0,total=0;
//get nth proc2esses
    printf("SJF\n");
    printf("How many processes:");
    scanf("%d",&n);
    total=n;
// get inputs
    for(int i=0; i<n; i++)
    {
        printf("P%d:\n",i+1);
        proc2[i].name=i+1;
        printf("AT:");
        scanf("%d",&proc2[i].AT);
        printf("I/0:");
        scanf("%d",&proc2[i].IO);
        printf("CPU1:");
        scanf("%d",&proc2[i].CPU1);
        proc2[i].orig_cpu1=proc2[i].CPU1;
        if(proc2[i].orig_cpu1<0){
            proc2[i].orig_cpu1=0;
        }
        printf("CPU2:");
        scanf("%d",&proc2[i].CPU2);
        proc2[i].orig_cpu2=proc2[i].CPU2;
        if(proc2[i].orig_cpu2<0){
            proc2[i].orig_cpu2=0;
        }
            proc2[i].color=head_color;
         head_color++;
        if(head_color>14){
                    head_color=1;
        }
        proc2[i].sum_cpu=proc2[i].orig_cpu1+proc2[i].orig_cpu2+proc2[i].IO;
    }
//set cur_end by least AT and cur_start by least_AT
    start=cur_start=least_AT2(n);
    cur_end=least_AT2(n);
//MAIN CYCLE
    while(terminate2(n)==0)
    {
        checker2(n);
        while(proc2[i].CPU2<0)
        {
            i++;
        }
        //sort2 BY AT
        sort2(i,n);
        printf("P%d, ",proc2[i].name);
        if(proc2[i].CPU1<0){
            min_burst=proc2[i].CPU2;
        }else{
            min_burst=proc2[i].CPU1;
        }
        point=least_burst(i,n);

    //printf("P%d,",proc2[point].name);
    //Set Start
    if(cur_end>proc2[point].AT){
    proc2[point].S=cur_end;
    proc2[point].s[proc2[point].sp]=proc2[point].S;
    proc2[point].sp++;
    }else{
    proc2[point].S=proc2[point].AT;
    proc2[point].s[proc2[point].sp]=proc2[point].S;
    proc2[point].sp++;
    }
    //Set End
    if(proc2[point].CPU1<0){
    proc2[point].E=proc2[point].S + proc2[point].CPU2;
    proc2[point].CPU2=-1;
    }else{
    proc2[point].E=proc2[point].S + proc2[point].CPU1;
    proc2[point].CPU1=-1;
    }
    proc2[point].e[proc2[point].ep]=proc2[point].E;
    proc2[point].ep++;
    //Set cur_end to End
    cur_end=proc2[point].E;
     //Save AT to AT array
    proc2[point].at[proc2[point].ap]=proc2[point].AT;
    proc2[point].ap++;
    //set New AT by cur_end if CPU1 is >=0 only
    if(proc2[point].IO>=0){
    proc2[point].AT=cur_end + proc2[point].IO;
    proc2[point].IO=-1;
    }
    }
    //system("cls");
   printf("\n\n\n");
    view2(n);
//system("cls");
printf("VIEW:\n\n");
    float ave_tat=0.0,ave_wt=0.0,ave_rt=0.0;
for(int i=0;i<total;i++){
    SetColor(proc2[i].color);
    printf("P%d\n",proc2[i].name);
    SetColor(15);
    printf("AT: ");
    for(int k=0;k<proc2[i].ap;k++){
        printf("%d, ",proc2[i].at[k]);
    }
    printf("\n");
    printf("CPU1: %d\n",proc2[i].orig_cpu1);
    printf("I/O: %d\n",proc2[i].sum_cpu - (proc2[i].orig_cpu1+proc2[i].orig_cpu2));
    printf("CPU2: %d\n",proc2[i].orig_cpu2);
    printf("Start: ");
    for(int k=0;k<proc2[i].sp;k++){
        printf("%d, ",proc2[i].s[k]);
    }
    printf("\n");
    printf("End: ");
    for(int k=0;k<proc2[i].ep;k++){
        printf("%d,",proc2[i].e[k]);
    }
    printf("\nCT: %d\n",proc2[i].CT);
    printf("TAT: %d\n",proc2[i].TAT);
    ave_tat+=proc2[i].TAT;
    printf("WT: %d\n",proc2[i].WT);
    ave_wt+=proc2[i].WT;
    printf("RT: %d\n",proc2[i].RT);
    ave_rt+=proc2[i].RT;
    printf("\n");
}
printf("AVERAGE WT: %f\n",ave_wt/n);
printf("AVERAGE TAT: %f\n",ave_tat/n);
printf("AVERAGE RT: %f\n",ave_rt/n);

//get max n of array in start and end in specific proc2ess
    for(int i=0;i<n;i++){
        proc2[i].nth=proc2[i].ep;
    }
gantt2(n);
printf("\n");
}
/*
1
2
5
0
6
5
7
0
2
4
3
0
3
2
4
0
2
5
7
0
2
3
4

2
2
2
5
0
6
5
7
3
2
4
3
4
3
2
4
7
2
5
7
14
2
3
4

1
2
5
0
6
5
7
0
2
4
3
0
3
2
4
0
2
5
7
0
2
3
4

*/
#endif // SJF_H_INCLUDED
