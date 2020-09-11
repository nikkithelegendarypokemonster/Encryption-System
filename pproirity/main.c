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
            if(proc[i].AT>=start && proc[i].AT<=cur_end &&proc[i].CPU1>0){
                // testing: printf("\ni:%d",i);
                ready[rp]=i;
                rp++;
            }
        }
    }
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
}
    for(int i=0;i<rp;i++){
            //change this if need to set the setting of greater than and less than
        if(proc[i].prio<proc[min].prio){
                min=i;
        }
    }
return min;
}
void PP(int n){
int running=ready[0],least=0,trying=0,unit=0;
int i=0;
    while(cur_end<=max_at){

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
       //clean the zeros to negative ones
    for(int i=0;i<n;i++){
        if(proc[i].CPU1<=0){
            proc[i].CPU1=-1;
        }
    }
    return 0;
}
