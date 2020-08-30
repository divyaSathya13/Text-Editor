#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 100

//Initiating variables
typedef struct node
{
    char data[MAX];
    struct node *next;
    struct node *prev;
}Node;
Node *head,*newNode, *t;
int changed;
char fileName[MAX];

void display(int, int );
Node* getNode(char* );
void append();
void save();
void delete_line(int, int );
void insert(int);
void move(int, int);
void copy(int, int);
void displayPattern(char* );
void replace(char*, char*);
int length_list();