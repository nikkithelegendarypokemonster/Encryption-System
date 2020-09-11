#include <stdio.h>
#include <stdlib.h>
int cur_end=0,cur_start=0,min_burst=0,n=0,running=0;
int ready [200],qp=0,rp=0;
int queue[200];
typedef struct Proc
{
    int name;
    int AT,CPU1,S,E;
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
int traverse(int s,int n,int start,int end,int running){
int min=proc[running].CPU1,minloc=running,unit=0;
        for(int i=s;i<n;i++){
            unit=unit+(proc[i].AT-unit);
            if((proc[i].AT>=start && proc[i].AT<=end)&&i!=running){
                if(proc[i].CPU1<(min-unit)){
                    return i;
                }
            }
        }
    return running;
}
int main()
{
    int i=0,point=0,total=0,max_at=0,start=0,seeker=0;
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
        printf("CPU1:");
        scanf("%d",&proc[i].CPU1);
        if(proc[i].AT>=max_at){
            max_at=proc[i].AT;
        }
    }
    sort(i,n);
    start=cur_start=least_AT(n);
    cur_end=proc[i].CPU1 + proc[i].AT;
    if(cur_end>max_at){
        cur_end=max_at;
    }
    running=0;
    //while(cur_end<=max_at){
        checker(n);
        if(proc[i].CPU1<0){
            i++;
            running=i;
        }
        sort(i,n);
        point=traverse(i,n,start,cur_end+proc[i].CPU1,running);
        if(point==running){
            proc[running].S=cur_start;
            if(proc[running].E>=max_at){
                proc[running].E=max_at;
            }else{
            proc[running].E=proc[running].CPU1+proc[running].S;
            proc[running].CPU1=-1;
            }
        }else{
            if(proc[running].CPU1>proc[point].AT){
                proc[running].S=cur_start;
                proc[running].E=proc[point].AT;
                proc[running].CPU1=cur_end-(proc[running].AT+proc[running].CPU1);
                running=point;
            }else{
            proc[running].S=cur_start;
            proc[running].E=proc[running].CPU1+proc[running].S;
            proc[running].CPU1=-1;
            }
        }
   // }
for(int i=0;i<total;i++){
    printf("P%d\n",proc[i].name);
    printf("AT: ");
    for(int k=0;k<proc[i].ap;k++){
        printf("%d, ",proc[i].at[k]);
    }
    printf("\n");
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
/*
5
2
1
1
5
4
1
0
6
2
3

6
0
7
1
5
2
3
3
1
4
2
5
1

*/
