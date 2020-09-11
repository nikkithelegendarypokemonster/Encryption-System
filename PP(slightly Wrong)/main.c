#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
int cur_end=0,cur_start=0,min_burst=0,n=0;
typedef struct Proc
{
    int name;
    int AT,CPU1,CPU2,IO,S,E;
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
            if(proc[k].AT>=proc[k+1].AT)
            {
                temp=proc[k];
                proc[k]=proc[k+1];
                proc[k+1]=temp;
            }
        }
}
}
int find_next(int cur,int n,int start,int end){
/*cases
current proc BT < next proc AT
no next proc remain in current proc
theres a next process and current BT is > next proc AT
last process needs to be included even the current end is exceeding max AT
*/
    for(int i=cur;i<n;i++){
    if(proc[i].prio<proc[cur].prio && (proc[i].AT>=start && proc[i].AT<=end)){
                return i;
        }
    }
    return cur;
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
    int i=0,point=0,temp_point=0,temp_start=0,max_at=0,total=0,check=0;
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
        printf("Priority:");
        scanf("%d",&proc[i].prio);
        printf("CPU1:");
        scanf("%d",&proc[i].CPU1);
        if(proc[i].AT>=max_at){
            max_at=proc[i].AT;
        }
    }
//MAIN CYCLE
//do preemtive version first
/*cases
current proc BT < next proc AT :: finish the process and cancel it out the list
no next proc remain in current proc :: finish the process and cancel it out the list then move to next process with least priority
theres a next process and current BT is > next proc AT
last process needs to be included even the current end is exceeding max AT
need to fucking pass start and end of current process to be analyzed in find_next function

NORMAL PROCESS:
greater AT than Next
there is a next proc
*/
    //sort first the AT's then compute the start and end o the first process
    sort(i,n);
    temp_start=cur_start=proc[i].AT;
    cur_end=proc[i].CPU1+proc[i].AT;
//======================================================
int s=0;
while(cur_end<=max_at){
        printf("cur_start:%d, cur_end:%d\n",cur_start,cur_end);
    //compute for current process start and next and store current end
        point=find_next(i,n,temp_start,cur_end);
        printf("i:%d ,point:%d",i,point);
             if(i==point){
                        proc[i].S=cur_start;
                        proc[i].s[proc[i].sp]=proc[i].S;
                        proc[i].sp++;
                        cur_start=proc[i].S;
                        temp_point=find_next(i,n,temp_start,cur_start+proc[i].CPU1);
                        printf(", temppoint:%d, ",temp_point);
                        if(temp_point!=i){
                            //has value
                        proc[i].E=proc[temp_point].AT;
                        cur_end=proc[i].E;
                        }else{
                        proc[i].E=cur_start + proc[i].CPU1;
                        cur_end=proc[i].E;
                        }
                        proc[i].e[proc[i].ep]=proc[i].E;
                        proc[i].ep++;
                              //      printf("P%d : S=%d : E=%d : curend=%d : curstart=%d : Temppoint=%d\n",proc[i].name,proc[i].S,proc[i].E,cur_end,cur_start,temp_point);
                        proc[i].CPU1=((cur_start+proc[i].CPU1)-proc[i].E);
                        i++;
                        check=1;
                        point=i;
                        cur_start=cur_end;
            }else{
                if(check==1){
                   i--;
                   check=0;
                }
                if(proc[i].CPU1<proc[point].AT){
                    if(proc[i].S>0 &&proc[i].E>0){
                    // has a value
                    i=point;
                    proc[i].S=cur_start;
                    proc[i].s[proc[i].sp]=proc[i].S;
                    proc[i].sp++;
                    cur_start=proc[i].S;
                    temp_point=find_next(i,n,temp_start,cur_start+proc[i].CPU1);
                    printf(", temppoint:%d, ",temp_point);
                        if(temp_point!=i){
                            //has value
                        proc[i].E=proc[temp_point].AT;
                        cur_end=proc[i].E;
                        }else{
                        proc[i].E=cur_start + proc[i].CPU1;
                        cur_end=proc[i].E;
                        }
                        proc[i].e[proc[i].ep]=proc[i].E;
                        proc[i].ep++;
                        proc[i].CPU1=((cur_start+proc[i].CPU1)-proc[i].E);
                              //      printf("P%d : S=%d : E=%d : curend=%d : curstart=%d : Temppoint=%d\n",proc[i].name,proc[i].S,proc[i].E,cur_end,cur_start,temp_point);
                        cur_start=cur_end;
                    }else{
                    //no value yet
                    proc[i].S=cur_start;
                    proc[i].s[proc[i].sp]=proc[i].S;
                    proc[i].sp++;
                    cur_start=proc[i].S;
                    temp_point=find_next(i,n,temp_start,cur_start+proc[i].CPU1);
                    printf(", temppoint:%d, ",temp_point);
                        if(temp_point!=i){
                            //has value
                        proc[i].E=proc[temp_point].AT;
                        cur_end=proc[i].E;
                        }else{
                        proc[i].E=cur_start + proc[i].CPU1;
                        cur_end=proc[i].E;
                        }
                        proc[i].e[proc[i].ep]=proc[i].E;
                        proc[i].ep++;
                        proc[i].CPU1=((cur_start+proc[i].CPU1)-proc[i].E);
                               //     printf("P%d : S=%d : E=%d : curend=%d : curstart=%d : Temppoint=%d\n",proc[i].name,proc[i].S,proc[i].E,cur_end,cur_start,temp_point);
                        cur_start=cur_end;
                        i=point;
                    }
                }else{
                    if(proc[i].S>0 &&proc[i].E>0){
                    // has a value
                    i=point;
                    proc[i].S=cur_start;
                    proc[i].s[proc[i].sp]=proc[i].S;
                    proc[i].sp++;
                    cur_start=proc[i].S;
                    temp_point=find_next(i,n,temp_start,cur_start+proc[i].CPU1);
                    printf(", temppoint:%d, ",temp_point);
                        if(temp_point!=i){
                            //has value
                        proc[i].E=proc[temp_point].AT;
                        cur_end=proc[i].E;
                        }else{
                        proc[i].E=cur_start + proc[i].CPU1;
                        cur_end=proc[i].E;
                        }
                        proc[i].e[proc[i].ep]=proc[i].E;
                        proc[i].ep++;
                        proc[i].CPU1=((cur_start+proc[i].CPU1)-proc[i].E);
                               //     printf("P%d : S=%d : E=%d : curend=%d : curstart=%d : Temppoint=%d\n",proc[i].name,proc[i].S,proc[i].E,cur_end,cur_start,temp_point);
                        cur_start=cur_end;
                    }else{
                    //no value yet
                    proc[i].S=cur_start;
                    proc[i].s[proc[i].sp]=proc[i].S;
                    proc[i].sp++;
                    cur_start=proc[i].S;
                    temp_point=find_next(i,n,temp_start,cur_start+proc[i].CPU1);
                    printf(", temppoint:%d, ",temp_point);
                        if(temp_point!=i){
                            //has value
                        proc[i].E=proc[temp_point].AT;
                        cur_end=proc[i].E;
                        }else{
                        proc[i].E=cur_start + proc[i].CPU1;
                        cur_end=proc[i].E;
                        }
                        proc[i].e[proc[i].ep]=proc[i].E;
                        proc[i].ep++;
                        proc[i].CPU1=((cur_start+proc[i].CPU1)-proc[i].E);
                                //    printf("P%d : S=%d : E=%d : curend=%d : curstart=%d : Temppoint=%d\n",proc[i].name,proc[i].S,proc[i].E,cur_end,cur_start,temp_point);
                        cur_start=cur_end;
                        i=point;
                    }
                }
            }
            s++;
        }
getch();


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



  system("cls");
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

/*
7
0
3
4
1
4
2
3
4
4
4
5
1
5
2
6
6
6
5
10
1
1
==========================================
7
0
3
8
1
4
2
3
4
4
4
5
1
5
2
6
6
6
5
10
1
1

*/
