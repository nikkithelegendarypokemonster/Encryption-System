#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include "GENERAL.h"
#include "FCFS.h"
#include "SJF.h"
#include "SRTF.h"
#include "PP.h"
#include "NPP.h"
#include "RR.h"

void reset(void){
cur_end=0,this_proc=0,start=0;
this_proc2=0;
cur_start=0,min_burst=0,n=0;
running=0,max_at=0,flag=1,this_proc3=0;
this_proc4=0;
this_proc6=0,temp_start=0;
this_proc5=0;
type_color=1,head_color=31;
}
int main(){
int choice[200],comparison=0;
printf("CPU SCHEDULING SYSTEM:\n");
printf("How many Comparison:");
scanf("%d",&comparison);

printf("[1]FCFS\n[2]SJF\n[3]SRTF\n[4]PP\n[5]NPP\n[6]RR\n");
printf("Choice:\n");
for(int i=0;i<comparison;i++){
    printf("Pick %d:",i+1);
    scanf("%d",&choice[i]);
}
for(int i=0;i<comparison;i++){
    switch(choice[i]){
    case 1:
        fcfs();
        break;
    case 2:
        sjf();
        break;
    case 3:
        SSRTFF();
        break;
    case 4:
        pp();
        break;
    case 5:
        npp();
        break;
    case 6:
        rr();
        break;
    default:
        reset();
        printf("Wrong Input");
        reset();
        break;
    }
}
getch();
return 0;
}
