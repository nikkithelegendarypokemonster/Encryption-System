#ifndef GENERAL_H_INCLUDED
#define GENERAL_H_INCLUDED
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
int cur_end=0,this_proc=0,start=0;
int this_proc2=0;
int cur_start=0,min_burst=0,n=0;
int running=0,max_at=0,flag=1,this_proc3=0;
int this_proc4=0;
int this_proc6=0,temp_start=0;
int this_proc5=0;
int type_color=1,head_color=1;
 void SetColor(int ForgC)
 {
     WORD wColor;

      HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
      CONSOLE_SCREEN_BUFFER_INFO csbi;

                       //We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
                 //Mask out all but the background attribute, and add in the forgournd     color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
 }
#endif // GENERAL_H_INCLUDED
