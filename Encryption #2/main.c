#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include<conio.h>
#define SIZE 2000
// 256 BIT KEYS
int key_1[]= {123, 253, 214, 30, 3, 137, 1, 106, 239, 149, 179, 22, 232, 240, 13, 10, 71, 100
              , 64, 3, 227, 59, 0, 57, 38, 1, 53, 63, 103, 140, 243, 42, 115, 58, 172, 245, 109, 122, 164
              , 36, 217, 142, 166, 168, 243, 143, 246, 3, 69, 177, 134, 172, 120, 200, 108, 181, 107, 11, 148
              , 171, 130, 24, 178, 190, 65, 57, 123, 33, 25, 230, 21, 180, 129, 139, 204, 225, 73, 139, 6, 195
              , 43, 132, 121, 142, 164, 213, 155, 43, 2, 93, 90, 34, 189, 134, 14, 189, 10, 130, 172, 107, 174
              , 213, 60, 98, 16, 20, 141, 136, 147, 236, 39, 148, 34, 101, 129, 112, 13, 104, 116, 226, 19, 128
              , 240, 108, 192, 221, 238, 113, 249, 158, 165, 152, 213, 80, 1, 118, 174, 177, 81, 103, 120, 186, 64
              , 188, 82, 221, 6, 28, 91, 140, 223, 36, 199, 250, 188, 81, 50, 37, 57, 32, 51, 20, 208, 115, 53, 93
              , 76, 55, 130, 235, 128, 68, 161, 254, 56, 132, 226, 115, 112, 88, 55, 70, 196, 55, 69, 85, 40, 153, 187
              , 103, 217, 19, 227, 108, 148, 195, 119, 7, 5, 238, 181, 73, 130, 232, 181, 192, 249, 52, 251, 176, 39, 237
              , 73, 160, 11, 100, 182, 24, 155, 11, 4, 170, 181, 146, 47, 47, 88
              , 79, 66, 83, 20, 227, 110, 84, 191, 27, 93, 6, 106, 20, 196, 27, 147, 163, 56, 161, 157, 243, 66, 204, 125, 112, 181, 246, 181, 228, 63
             };
int key_2[]= {1, 1, 0, 5, 7, 7, 3, 4, 0, 8, 2, 0, 3, 8, 2, 1, 1, 8, 0, 2, 0, 0, 4, 0
              , 6, 5, 1, 2, 3, 7, 5, 4, 5, 5, 4, 7, 6, 8, 0, 8, 0, 0, 0, 3, 6, 0, 5, 6, 7, 6, 0
              , 8, 8, 6, 8, 1, 5, 7, 4, 2, 7, 6, 8, 0, 5, 4, 3, 5, 5, 7, 1, 3, 4, 4, 2, 2, 3, 0
              , 3, 2, 8, 8, 0, 0, 7, 5, 4, 8, 8, 5, 4, 3, 6, 2, 1, 1, 7, 6, 4, 1, 4, 2, 1, 8, 7, 3
              , 0, 2, 0, 2, 8, 6, 6, 0, 3, 7, 4, 2, 3, 2, 2, 3, 8, 6, 5, 5, 7, 5, 8, 6, 5, 1, 4, 4
              , 0, 7, 1, 4, 2, 6, 5, 1, 7, 0, 0, 3, 3, 8, 1, 4, 2, 8, 3, 4, 0, 1, 5, 5, 8, 6, 2, 6
              , 5, 4, 4, 5, 1, 8, 5, 1, 8, 1, 3, 3, 5, 6, 6, 1, 4, 2, 7, 7, 4, 6, 2, 6, 6, 4, 0, 6
              , 7, 4, 0, 5, 2, 6, 6, 1, 6, 3, 5, 6, 8, 6, 4, 7, 6, 6, 2, 7, 7, 0, 2, 6, 5, 1, 4, 0
              , 7, 4, 5, 1, 6, 5, 2, 5, 4, 2, 6, 6, 1, 6, 7, 5, 4, 4, 2, 4, 5, 3, 0, 5, 1, 3, 5, 6
              , 2, 7, 4, 8, 4, 5, 8, 5, 1, 6, 3
             };
int key_3[]= {1, 0, 2, 8, 5, 2, 8, 4, 4, 2, 4, 6, 8, 2, 0, 8, 0, 1, 1, 1, 2, 8,
              2, 5, 1, 4, 7, 8, 1, 5, 2, 2, 6, 7, 0, 6, 7, 2, 8, 0, 8, 6, 5, 4, 5, 8, 8,
              5, 6, 4, 2, 0, 7, 5, 4, 2, 1, 5, 1, 5, 4, 5, 5, 8, 4, 6, 7, 1, 2, 2, 4, 6,
              3, 0, 0, 6, 3, 5, 0, 5, 5, 6, 8, 2, 5, 3, 0, 3, 6, 3, 6, 5, 1, 3, 6, 2, 3,
              5, 8, 7, 4, 3, 1, 8, 6, 4, 6, 1, 2, 6, 8, 7, 6, 1, 8, 2, 6, 7, 3, 7, 5, 5, 0,
              1, 4, 7, 8, 4, 3, 8, 8, 7, 6, 4, 1, 8, 5, 7, 5, 6, 0, 8, 7, 5, 8, 3, 7,
              3, 5, 7, 4, 0, 4, 1, 7, 0, 4, 1, 3, 5, 2, 1, 6, 7, 6, 5, 4, 3, 2, 0, 0,
              8, 6, 1, 7, 0, 2, 8, 7, 3, 8, 6, 4, 2, 2, 7, 8, 5, 5, 2, 6, 5, 2, 6,
              4, 3, 6, 2, 7, 0, 7, 4, 6, 7, 4, 0, 5, 0, 6, 7, 0, 6, 5, 8, 4, 2, 7, 2,
              5, 3, 8, 4, 1, 8, 1, 5, 8, 3, 4, 2, 6, 5, 8, 2, 6, 0, 0, 2, 0, 7, 2, 4,
              3, 6, 5, 8, 4, 3, 8, 0, 6, 7, 7, 1, 8, 1, 8
             };
//=========================================================
typedef struct Node
{
    char data;
    struct Node *left,*right;
} node;
node *Queue[SIZE];
node* list[SIZE];
int top=-1;
void tree(int);
node* Create(char data)
{
    node *temp;
    temp=(node*)malloc(sizeof(node));
    temp->data=data;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}
void disp(char MSG[],int n)
{
    int i=0;
    for(; i<n; i++)
    {
        printf("%c",MSG[i]);
    }
    printf("\n");
    return;
}
void cipher(char MSG[],int n)
{
    //disp(MSG,n);
    int key_logger=0;
    time_t now;
    struct tm *now_tm;
    int hour,min;
    int k=0;
    int temp,i;
    now=time(NULL);
    now_tm = localtime(&now);
    hour = now_tm->tm_hour;
    min=now_tm->tm_min;
    key_logger=hour%3;
    printf("hour is: %d\nmin is: %d\nKey Logger is: %d\n",hour,min,key_logger);
    switch(key_logger)
    {
    case 0:
        if(min>=0&&min<40)
        {
            printf("Shifting 50 times...\n");
            while(k<50)
            {
                temp=key_2[0];
                for(i=0; i<257; i++)
                {
                    key_2[i]=key_2[i+1];
                }
                key_2[257-1]=temp;
                k++;
            }
        }
        for(int x=0, y=0; x<n; x++,y++)
        {
            if(y==256)
            {
                y=0;
            }
            if(MSG[x]==' ')
            {
                x++;
            }
            MSG[x]=MSG[x]+key_2[y];
        }
        break;
    case 1:
        if(min>=30&&min<40)
        {
            printf("Shifting 30 times...\n");
            while(k<30)
            {
                temp=key_1[0];
                for(i=0; i<257; i++)
                {
                    key_1[i]=key_1[i+1];
                }
                key_1[257-1]=temp;
                k++;
            }
        }
        else
        {
            printf("Shifting 1 time...\n");
            temp=key_1[0];
            for(i=0; i<257; i++)
            {
                key_1[i]=key_1[i+1];
            }
            key_1[257-1]=temp;
            k++;
        }
        for(int x=0, y=0; x<n; x++,y++)
        {
            if(y==256)
            {
                y=0;
            }
            if(MSG[x]==' ')
            {
                x++;
            }
            MSG[x]=MSG[x]+key_1[y];
        }
        break;
    case 2:
        for(i=0; i<257; i++)
        {
            printf("%d ",key_3[i]);
        }
        if(min>=3&&min<20)
        {
            printf("Shifting 20 times...\n");
            while(k<20)
            {
                temp=key_3[0];
                for(i=0; i<257; i++)
                {
                    key_3[i]=key_3[i+1];
                }
                key_3[257-1]=temp;
                k++;
            }
        }
        else
        {
            printf("Shifting 2 time...\n");
            while(k<2)
            {
                temp=key_3[0];
                for(i=0; i<257; i++)
                {
                    key_3[i]=key_3[i+1];
                }
                key_3[257-1]=temp;
                k++;
            }
        }
        printf("\nNew array after rotating by one postion in the left direction\n");
        for(i=0; i<257; i++)
        {
            printf("%d ",key_3[i]);
        }
        for(int x=0, y=0; x<n; x++,y++)
        {
            if(y==256)
            {
                y=0;
            }
            if(MSG[x]==' ')
            {
                x++;
            }
            MSG[x]=MSG[x]+key_3[y];
        }
        break;
    }
    printf("Encrypted Message: \n");
    disp(MSG,n);
}
void push(struct Node *node);
void pop(struct Node *node);
void level (struct Node *root)
{
    char A_MSG[SIZE];
    int i=0;
    if(root->data=='\0')
    {
        return;
    }
    push(root);
    while(Queue[top]!=NULL)
    {
        root=Queue[0];
        pop(Queue[0]);
        //printf(" %c ",root->data);
        A_MSG[i]=root->data;
        //printf(" %c ",A_MSG[i]);
        if(root->right!=NULL)
        {
            push(root->right);
        }
        if(root->left!=NULL)
        {
            push(root->left);
        }
        i++;
    }
    cipher(A_MSG,i);
}
void block(char msg[SIZE],int n)
{
    for(int i=0; i<n; i++)
    {
        list[i]=Create(msg[i]);
    }
}
int main()
{
    char msg[SIZE];
    printf("ENTER MSG: ");
    scanf("%[^\n]s",&msg[0]);
    int n=strlen(msg);
    printf("MSG=> ");
    for(int i=0; i<n; i++)
    {
        printf("%c",msg[i]);
    }
    printf("\n");
    strcat(msg,"UsG");
    n=strlen(msg);
    block(msg,n);
    tree(n);
    _getch();
    return 0;
}
void push(struct Node *node)
{
    if(top==(SIZE-1))
    {
        printf("Stack Overflow....");
        return;
    }
    //printf("%c",node->data);
    top++;
    Queue[top]=node;
}
void pop(struct Node *node)
{
    for(int i=0; i<top; i++)
    {
        Queue[i]=Queue[i+1];
        //printf("%c",Queue[i]->data);
    }
    top--;
}
void tree(int n)
{
    int i=0;
    node *root;
    while(i<n)
    {
        //printf("Left of %c:%p is %c:%p\n",list[i]->data,list[i],list[2*i+1]->data,list[i]->left);
        if(list[2*i+1]!='\0')
        {
            list[i]->left=list[2*i+1];
        }
        if(list[2*i+2]!='\0')
        {
            list[i]->right=list[2*i+2];
        }
        //printf("Right of %c:%p is %c:%p\n",list[i]->data,list[i],list[2*i+2]->data,list[i]->right);
        i++;
    }
    root=list[0];
    level(root);
}
/*
h e l l o w o r l d
hleowoldlr
                                                h
                                        e               l
                                    L          o       w       o
                                r       l    d
*/














