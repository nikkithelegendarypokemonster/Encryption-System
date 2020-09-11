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
int main()
{
    int running=0,check=0,point=0,seeker=0;
    int i=0,total=0,max_at=0,min_cpu=0;
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
    cur_start=least_AT(n);
    cur_end=proc[i].AT+proc[i].CPU1;
    min_cpu=proc[i].CPU1;
    running=point;
    while(cur_start<=max_at){
            printf("P%d: I:%d\n",proc[running].name,i);
             checker(n);
         if(proc[i].CPU1<=0){
            i++;
            min_cpu=proc[i].CPU1;
            running=i;
         }
        for(check=i;check<n;check++){
            if(seeker==0){
             if((proc[check].AT>=cur_start && proc[check].AT<=cur_end) && check !=running && proc[check].CPU1>0){
                if(proc[check].CPU1<min_cpu){
                        min_cpu=proc[check].CPU1;
                        point=check;
                    printf("%d\n",proc[check].AT);
                }
             }
            }else{
             if((proc[check].AT>=cur_start && proc[check].AT<=cur_end) && proc[check].CPU1>0){
                if(proc[check].CPU1<min_cpu){
                        min_cpu=proc[check].CPU1;
                        point=check;
                    printf("%d\n",proc[check].AT);
                }
             }
             seeker=0;
            }
        }
        //START
            proc[running].S=cur_start;
            proc[running].s[proc[running].sp]=proc[running].S;
            proc[running].sp++;
        if(point!=running && proc[running].CPU1>proc[point].AT){
            //END
            proc[running].E=proc[point].AT;
            cur_end=proc[running].E;
            proc[running].CPU1=(proc[running].CPU1 + proc[running].S)-proc[point].AT;

        }else{
        proc[running].E=proc[running].S+proc[running].CPU1;
        cur_end=proc[running].E;
        seeker=1;

        proc[running].CPU1=-1;
        }
        proc[running].e[proc[running].ep]=proc[running].E;
        proc[running].ep++;
        cur_start=cur_end;
        running=point;
    }

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
        printf("running: %d point: %d\n",running,point);
                //START
            proc[running].S=cur_start;
            proc[running].s[proc[running].sp]=proc[running].S;
            proc[running].sp++;
        if(point!=running && proc[running].CPU1>proc[point].AT){
            //END
            proc[running].E=proc[point].AT;
            cur_end=proc[running].E;
            proc[running].CPU1=(proc[running].CPU1 + proc[running].S)-proc[point].AT;
        }else{
        proc[running].E=proc[running].S+proc[running].CPU1;
        cur_end=proc[running].E;
        proc[running].CPU1=-1;
        }
        proc[running].e[proc[running].ep]=proc[running].E;
        proc[running].ep++;
        cur_start=cur_end;


                    if(proc[check].AT>=cur_start && proc[check].AT<=cur_end && check !=running && proc[check].CPU1>0){
                    printf("Hi");
                if(proc[check].CPU1<proc[point].CPU1){
                    point=check;
                }
            }

         checker(n);
         if(proc[i].CPU1<=0){
            i++;
         }
         sort(i,n);
*/
