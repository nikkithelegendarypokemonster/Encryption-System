#include <stdio.h>
#include <stdlib.h>
int cur_end=0,cur_start=0,min_burst=0,n=0;
typedef struct Proc
{
    int name;
    int AT,CPU1,CPU2,IO,S,E;
    int at[200],s[200],e[200];
    int ap,sp,ep;
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
int least_burst(int s,int n)
{
    int loc=s;
    for(int i=s; i<n; i++)
    {
        if(proc[i].AT>=cur_start && proc[i].AT<=cur_end)
        {
            if(proc[i].CPU1<0)
            {
                if( proc[i].CPU2<=min_burst && proc[loc].CPU1 != proc[i].CPU2 && proc[loc].CPU2 != proc[i].CPU2)
                {
                    min_burst=proc[i].CPU2;
                    loc=i;
                }
            }
            else
            {
                if(proc[i].CPU1<=min_burst && proc[loc].CPU2 != proc[i].CPU1 && proc[loc].CPU1 != proc[i].CPU1)
                {
                    min_burst=proc[i].CPU1;
                    loc=i;
                }
            }
        }
    }
    return loc;
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
        printf("I/0:");
        scanf("%d",&proc[i].IO);
        printf("CPU1:");
        scanf("%d",&proc[i].CPU1);
        printf("CPU2:");
        scanf("%d",&proc[i].CPU2);
    }
//set cur_end by least AT and cur_start by least_AT
    cur_start=least_AT(n);
    cur_end=least_AT(n);
//MAIN CYCLE
    while(terminate(n)==0)
    {
        checker(n);
        if(proc[i].CPU2<0)
        {
            // printf("Yes");
            i++;
        }
        //SORT BY AT
        sort(i,n);
        //set min_burst to starting cpu burst
        if(proc[i].CPU1<0)
        {

            min_burst=proc[i].CPU2;
        }
        else
        {
            min_burst=proc[i].CPU1;
        }
        //printf("%d, ",min_burst);
        point=least_burst(i,n);
        // printf("%d, ",min_burst);
       // printf("%d, ",proc[point].name);

        //Set Start
            proc[i].S=cur_end;
            proc[i].s[proc[i].sp]=proc[i].S;
            proc[i].sp++;
        //Set End
        if(proc[point].CPU1<0)
        {
            proc[point].E=proc[point].S + proc[point].CPU2;
            proc[point].CPU2=-1;
        }
        else
        {
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
        if(proc[point].IO>=0)
        {
            proc[point].AT=cur_end + proc[point].IO;
            proc[point].IO=-1;
        }
    }

    system("cls");
    for(int i=0; i<total; i++)
    {
        printf("P%d\n",proc[i].name);
        printf("AT: ");
        for(int k=0; k<proc[i].ap; k++)
        {
            printf("%d, ",proc[i].at[k]);
        }
        printf("\n");
        printf("CPU1: %d\n",proc[i].CPU1);
        printf("CPU2: %d\n",proc[i].CPU2);
        printf("Start: ");
        for(int k=0; k<proc[i].sp; k++)
        {
            printf("%d, ",proc[i].s[k]);
        }
        printf("\n");
        printf("End: ");
        for(int k=0; k<proc[i].ep; k++)
        {
            printf("%d,",proc[i].e[k]);
        }
        printf("\n");
    }

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
*/
