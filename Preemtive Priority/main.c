#include <stdio.h>
#include <stdlib.h>
int cur_end=0,cur_start=0,n=0,max_at=0;
int ready [200],qp=0,rp=0;
int queue[200];
typedef struct Proc
{
    int name;
    int AT,CPU1,S,E;
    //priority
    int prio;
    int at[200],s[200],e[200];
    int ap,sp,ep;
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
            if(proc[k].AT>proc[k+1].AT)
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
void find_next(int s,int n,int start,int end){
int min=proc[s].prio,loc=0,chance=0;
if(end>=max_at){
        end=end-(end-max_at);
    chance=1;
}
        for(int i=s;i<n;i++){
             if(proc[i].AT>=start && proc[i].AT<=end && proc[i].CPU1 >0){
                        queue[qp]=i;
                        qp++;
             }
        }

    //find queue lowest priority
        for(int i=0;i<qp;i++){
            if(proc[queue[i]].prio<min || queue[i]==s){
                loc=queue[i];
            }
        } printf("min:%d\n",min);
        printf("loc:%d,s:%d, end:%d",loc,s,end);
        if(loc == s ){
            if(inside_queue(loc)==0){
            ready[rp]=loc;
            rp++;
            }
            s++;
            if(chance==0){
                    qp=0;
                   // printf("cpu:%d :: end:%d\n",proc[loc].CPU1,end);
              find_next(s,n,start,proc[loc].CPU1+ end);
            }else{
            return;
            }

        }else{
            if(inside_queue(loc)==0){
            ready[rp]=loc;
            rp++;
            }
            if(chance==0){
                    qp=0;
              find_next(s,n,start,proc[loc].CPU1+end);
            }else{
            return;
            }
        }

}
int highest_priority(int s,int n){
 int loc=s;
    for(int i=s+1; i<n; i++)
    {
        if(proc[i].AT>=cur_start && proc[i].AT<=cur_end && proc[i].prio<=proc[s].prio)
        {
         //if theres an equal on priorities
         if(proc[i].prio==proc[s].prio){
            if(proc[i].AT< proc[s].AT){
                loc=i;
            }
         }else{
            loc=i;
         }
        }
    }
return loc;
}
int main()
{
    int i=0,temp_start=0,total=0,point=0;
//get nth processes
    printf("Preemptive Priority\n");
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
        printf("Priority:");
        scanf("%d",&proc[i].prio);
        printf("CPU1:");
        scanf("%d",&proc[i].CPU1);
        if(proc[i].AT>=max_at){
            max_at=proc[i].AT;
        }
    }
    sort(i,n);
    temp_start=cur_start=proc[i].AT;
    cur_end=proc[i].CPU1+proc[i].AT;
    ready[rp]=0;
    rp++;
         find_next(i,n,temp_start,cur_end);
         cur_end=0;
    for(int i=0;i<rp;i++){
        printf("%d, ",ready[i]);
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

// next loop
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
    return 0;
}
