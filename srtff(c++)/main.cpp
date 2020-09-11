# include<stdio.h>
# include<conio.h>
#include<iostream>

# define max1 10      //MAX PROCESSES
# define r 6          //MAX RESOURCES

using namespace std;
int pgant[max1];
void sort(int st,int a[],int b[],int pr[],int np)
{       int i,j,t,p,z;
for(i=0;i<np-1;i++)
{
for(j=st;j<np-i-1;j++)
{
if(a[j]>a[j+1])
{
    t=a[j];      z=b[j];        p=pr[j];
    a[j]=a[j+1]; b[j]=b[j+1]; pr[j]=pr[j+1];
    a[j+1]=t;  b[j+1]=z; pr[j+1]=p;
}
}
}
}
/* SHEDULING ALGO-SHORTEST REMAINING TIME FIRST-PREEMTIVE */

void srtf()
{
int p1[max1],t1[max1],i,ch,np;
int arr[max1];
int tat[max1];
int wt[max1];
int resp[max1];
float rdelay[max1];
float atat;
float awt;
float aresp;
float ardelay;
int tgant[max1];
int tex=0;
int j,k,count,c,a;
int trem[max1];
cout<<"\nEnter no. of processes  : ";
cin>>np;
for(i=0;i<np;i++)
{
cout<<"\nEnter the Process  :- "<<i+1<<" ";
p1[i]=i;
cout<<"\nExecution time : ";
cin>>t1[i];
cout<<"\nArrival time   : ";
cin>>arr[i];
}
cout<<"\nPROCESSES\t\tEXECUTION TIME\t\tARRIVAL TIME";
for(i=0;i<np;i++)
{
cout<<"\n p "<<p1[i]+1<<"  \t\t\t"<<t1[i]<<"  \t\t\t"<<arr[i];
}
for(i=0;i<np;i++)
{ tex=tex+t1[i];
trem[i]=t1[i];
}
sort(0,arr,p1,t1,np);
tgant[0]=0;
j=0,k=0,count=0,c=0;
while(count!=tex)
{
if(j!=np)
{       j=k;
for(i=k;i<np;i++)
{
if(arr[i]<=count)
j++;
else
break;
}
if((j-k)>1)
sort(k,trem,p1,arr,j);
}
while(trem[k]==0)
k++;
c++;
pgant[c-1]=p1[k];
if(j==np)
a=trem[k];
else
{ if(trem[k] < (arr[j]-tgant[c-1]) )
a=trem[k];
else
a=arr[j]-tgant[c-1];
}
tgant[c]=tgant[c-1]+a;
count=tgant[c];
trem[k]=trem[k]-(tgant[c]-tgant[c-1]);
if(c>1)
{
if(pgant[c-1]==pgant[c-2])
{ tgant[c-1]=tgant[c];
c--;
}
}
}
sort(0,arr,p1,trem,np);
for(i=0;i<np;i++)
{
wt[i]=0;
tat[i]=0;
resp[i]=-1;
}
for(i=0;i<c;i++)
{
for(j=0;j<np;j++)
{
if(pgant[i]==p1[j])
{
wt[j]=wt[j]+tgant[i]-tat[j];
if(resp[j]==-1)
resp[j]=tgant[i];
tat[j]=tgant[i+1] ;
break;
}
}
}
for(i=0;i<np;i++)
{
wt[i]=wt[i]-arr[i];
tat[i]=tat[i]-arr[i];
resp[i]=resp[i]-arr[i];
rdelay[i]=(float)tat[i]/t1[i];
}
atat=0;  awt=0;  aresp=0;  ardelay=0;
for(i=0;i<np;i++)
{
atat=atat+tat[i];
awt=awt+wt[i];
aresp=aresp+resp[i];
ardelay=ardelay+rdelay[i];
}
atat=atat/np;
awt=awt/np;
aresp=aresp/np;
ardelay=ardelay/np;

cout<<"\nGANTT CHART:- ";
for(i=0;i<c;i++){
cout<<"   P"<<pgant[i]+1<<"  ";
}
for(i=0;i<=c;i++)
cout<<"\n\nAverage waiting time      : "<<awt;
cout<<"\nAverage turn arround time : "<<atat;
cout<<"\nAverage response time     : "<<aresp;
cout<<"\nAverage relative delay    : "<<ardelay;
getch();
}

int main()
{
      srtf();
     getch();
}
