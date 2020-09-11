#include <stdio.h>
#include <stdlib.h>
int cur_end=0,cur_start=0,min_burst=0,n=0,this_proc=0,start=0;
typedef struct Proc
{
    int name;
    int AT,CPU1,CPU2,IO,S,E;
    int at[200],s[200],e[200];
    int ap,sp,ep;
        //max n in array
    int nth,CT,WT,TAT,RT;
    //strorage for cpus
    int orig_cpu1,orig_cpu2,sum_cpu;
} process[200],temporary;
process proc;
temporary temp;

void checker(int n)
{
    for(int i=0; i<n; i++)
    {
        if(proc[i].CPU2<0)
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
        if(proc[i].CPU2>=0)
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
                        if(proc[k+1].name<proc[k].name){
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
int least_burst(int s,int n)
{
    int loc=s;
    for(int i=s+1; i<n; i++)
    {
        if(proc[i].AT>=cur_start && proc[i].AT<=cur_end)
        {
           // printf("in between %d : %d is %d\n",cur_start,cur_end,proc[i].AT);
            if(proc[i].CPU1<0)
            {
                if(proc[i].CPU2<proc[loc].CPU2 || proc[i].CPU2<proc[loc].CPU1 )
                {
                    loc=i;
                }
            }
            else
            {
                if(proc[i].CPU1<proc[loc].CPU1 || proc[i].CPU1<proc[loc].CPU2)
                {
                    loc=i;
                }
            }
        }
    }
    printf("min is:P%d value: %d\n",loc,min_burst);
    return loc;
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
         proc[i].WT=proc[i].TAT-proc[i].sum_cpu;
        //RT
        proc[i].RT=proc[i].s[0]- proc[i].at[0];
    }

}
int main()
{
    int i=0,point=0,total;
//get nth processes
    printf("sjf\n");
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
        proc[i].at[0]=proc[i].AT;
        proc[i].ap++;
        printf("I/0:");
        scanf("%d",&proc[i].IO);
        printf("CPU1:");
        scanf("%d",&proc[i].CPU1);
        proc[i].orig_cpu1=proc[i].CPU1;
        if(proc[i].orig_cpu1<0){
            proc[i].orig_cpu1=0;
        }
        printf("CPU2:");
        scanf("%d",&proc[i].CPU2);
        proc[i].orig_cpu2=proc[i].CPU2;
        if(proc[i].orig_cpu2<0){
            proc[i].orig_cpu2=0;
        }
        proc[i].sum_cpu=proc[i].orig_cpu1+proc[i].orig_cpu2+proc[i].IO;
    }
//set cur_end by least AT and cur_start by least_AT
    start=cur_start=least_AT(n);
    cur_end=least_AT(n);
//MAIN CYCLE
    while(terminate(n)==0)
    {
        checker(n);
        while(proc[i].CPU2<0)
        {
            i++;
        }
        //SORT BY AT
        sort(i,n);
       // printf("P%d, ",proc[i].name);
        if(proc[i].CPU1<0){
            min_burst=proc[i].CPU2;
        }else{
            min_burst=proc[i].CPU1;
        }
        point=least_burst(i,n);

   // printf("P%d,",proc[point].name);
    //Set Start
    if(cur_end>proc[point].AT){
    proc[point].S=cur_end;
    proc[point].s[proc[point].sp]=proc[point].S;
    proc[point].sp++;
    }else{
    proc[point].S=proc[point].AT;
    proc[point].s[proc[point].sp]=proc[point].S;
    proc[point].sp++;
    }
    //Set End
    if(proc[point].CPU1<0){
    proc[point].E=proc[point].S + proc[point].CPU2;
    proc[point].CPU2=-1;
    }else{
    proc[point].E=proc[point].S + proc[point].CPU1;
    proc[point].CPU1=-1;
    }
    proc[point].e[proc[point].ep]=proc[point].E;
    proc[point].ep++;
    //Set cur_end to End
    cur_end=proc[point].E;
    //Save AT to AT array
    proc[point].at[proc[point].ap]=proc[point].AT;
    proc[point].ap++;
    //set New AT by cur_end if CPU1 is >=0 only
    if(proc[point].IO>=0){
    proc[point].AT=cur_end + proc[point].IO;
    proc[point].IO=-1;
    }
    }
    system("cls");
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
    printf("CPU1: %d\n",proc[i].orig_cpu1);
    printf("CPU2: %d\n",proc[i].orig_cpu2);
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

5
2
0
-1
1
1
0
-1
5
4
0
-1
1
0
0
-1
6
2
0
-1
3

*/
