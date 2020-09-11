#ifndef FCFS_H_INCLUDED
#define FCFS_H_INCLUDED
#include <windows.h>
typedef struct Proc{
    int name;
    int AT,CPU1,CPU2,IO,S,E;
    int at[200],s[200],e[200];
    int ap,sp,ep;
    int nth,CT,WT,TAT,RT;
    //strorage for cpus
    int orig_cpu1,orig_cpu2,sum_cpu;
    int color;
}process[200],temporary;
process proc;
temporary temp;
int location=0;

int terminate(int n){
    for(int i=0;i<n;i++){
        if(proc[i].CPU2>=0){
            return 0;
        }
    }
return 1;
}
int least_AT(int n){
    int min=proc[0].AT;
    for(int i=0;i<n;i++){
        if(proc[i].AT<=min){
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

int find_next_process(int start,int n){
    for(int i=0;i<n;i++){
        for(int k=0;k<proc[i].sp;k++){
            if(proc[i].s[k]== start){
                this_proc=i;
                location=k;
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
    SetColor(proc[this_proc].color);
        printf(" - ");
        if(traverse==now){
                if(traverse==start){
                   printf("%d|",now);
                }else{
                SetColor(proc[this_proc].color);
                printf("P%d|%d",proc[this_proc].name,now);
                SetColor(15);
                }

        next=find_next_process(traverse,n);
        while(next==0 && traverse<=max_end ){
                traverse++;
            next=find_next_process(traverse,n);
            if(traverse==proc[this_proc].s[location]){
                printf("-IDLE|%d",proc[this_proc].s[location]);
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

void fcfs(void){

    int n=0,i=0,total=0;
 //get nth processes
    printf("FCFS\n");
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
        //proc[i].at[0]=proc[i].AT;
        //proc[i].ap++;
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
            proc[i].color=head_color;
         head_color++;
        if(head_color>14){
                    head_color=1;
        }
        proc[i].sum_cpu=proc[i].orig_cpu1+proc[i].orig_cpu2+proc[i].IO;
    }
//set cur_end by least AT
        start=cur_end=least_AT(n);
//MAIN CYCLE
while(terminate(n)==0)
{
    //check starting cpu2 if <0
    if(proc[i].CPU2<0){
        i++;
    }
    //SORT PROCESSES
        sort(i,n);
    //Set Start
    if(cur_end>proc[i].AT){
    proc[i].S=cur_end;
    proc[i].s[proc[i].sp]=proc[i].S;
    proc[i].sp++;
    }else{
    proc[i].S=proc[i].AT;
    proc[i].s[proc[i].sp]=proc[i].S;
    proc[i].sp++;
    }
    //Set End
    if(proc[i].CPU1<0){
    proc[i].E=proc[i].S + proc[i].CPU2;
    proc[i].CPU2=-1;
    }else{
    proc[i].E=proc[i].S + proc[i].CPU1;
    proc[i].CPU1=-1;
    }
    proc[i].e[proc[i].ep]=proc[i].E;
    proc[i].ep++;
    //Set cur_end to End
    cur_end=proc[i].E;
    //Save AT to AT array
    proc[i].at[proc[i].ap]=proc[i].AT;
    proc[i].ap++;
    //set New AT by cur_end if CPU1 is >=0 only
    if(proc[i].IO>=0){
    proc[i].AT=cur_end + proc[i].IO;
    proc[i].IO=-1;
    }
}
   printf("\n\n\n");
    view(n);
printf("VIEW:\n\n");
    float ave_tat=0.0,ave_wt=0.0,ave_rt=0.0;
for(int i=0;i<total;i++){
    SetColor(proc[i].color);
    printf("P%d\n",proc[i].name);
    SetColor(15);
    printf("AT: ");
    for(int k=0;k<proc[i].ap;k++){
        printf("%d, ",proc[i].at[k]);
    }
    printf("\n");
    printf("CPU1: %d\n",proc[i].orig_cpu1);
    printf("I/O: %d\n",proc[i].sum_cpu - (proc[i].orig_cpu1+proc[i].orig_cpu2));
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


gantt(n);
printf("\n");
}

#endif // FCFS_H_INCLUDED
