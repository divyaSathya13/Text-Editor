#include "DSproject.h"
//display from Start(s) line to End(e) line

int length_list()
{
    Node* temp=head;
    int count=0;
    while(temp!=NULL)
    {
        temp=temp->next;
        count++;
    }
    return count;
}
void display(int s,int e)
{
    int i;
    int c=length_list();
    if(c == 0)
    {
        printf("Empty File.\n");
        return;
    }
    if(s > c)
    {
        printf("Invalid.\n");
    }
    else if(s>c || e>c )
    {
        printf("Invalid.\n");
    }
    else
    {
        for(i=1,t=head;i<s;i++,t=t->next);
        for(;i<=e;i++,t=t->next)
        {
            //puts(t->data);
            printf("%d : %s",i,t->data);   
        }

    }
}

//CREATE a new line, as a new node in the doubly-linked list.
Node* getNode(char *str) 
{
    Node *temp=(Node *)malloc(sizeof(Node));
    if(temp==NULL)
    {
        exit(0);  //exit the program if malloc fails.
    }
    strcpy(temp->data,str);
    temp->next=NULL;
    temp->prev=NULL;
    return(temp);

}
void append()
{
    char line[MAX];
    char tline[MAX];

    printf("Enter Text(. to Quit)\n");
    if(fgets(line,MAX,stdin)==NULL)
    {
        printf("String length exceeds limit.\n");
    } 
//fgets() return NULL when the string entered exceeds MAX.

    strcpy(tline, line);
    if(head!= NULL)
    {
        for(t=head;t->next!=NULL;t=t->next);
    }
    
//fgets() has trailing '\n'
    line[strlen(line)-1]='\0';  
    while(strcmp(line,".")!=0)
    {
         if(head==NULL)
        {
            newNode=getNode(tline);
            head=t=newNode;
        }
        else
        {
            newNode=getNode(strcat(line,"\n"));
            t->next=newNode;
            newNode->prev=t;
            t=newNode;   
        }
        if(fgets(line,MAX,stdin)==NULL)
        {
            printf("String length exceeds limit.\n");
        }
        strcpy(tline,line);
        line[strlen(line)-1]='\0';
        changed=1;

    }
    printf("Lines Added.\n");
}

//to SAVE, open file with file name specified in write mode and write into file.
void save()
{
    FILE *fp1;
//returns NULL when unable to open the file.
    fp1=fopen(fileName,"w"); 
    if(!fp1) 
    {
        printf("File not saved.");
        exit(0);
    }
    else
    {
        for(t=head;t!=NULL;t=t->next)
        {
            fputs(t->data,fp1);
        }

    }
    printf("File saved successfully.\n");
    return;
    /*
    open file in the write mode, so all the previous contents are lost, 
    since head points to the first line, write everything back to the file.
    */
}

void delete_line(int s,int e)
{
    int i;
    Node *del;
    int count=length_list();
    if(s>count || e>count || (s==count && e>count) || s<=0 || e<=0)
    {
        printf("Invalid line number.\n");
        return;
    }
    else
    {

//deletes the first line.
        if(s==1 && e==1) 
        {
            del=head;
            head=head->next;
            if(head!=NULL)
            {
                head->prev=NULL; 
            }
            free(del);

        }
// deletes from the first line till e'th line.
        else if(s==1 && e>1) 
        {
            for(i=s;i<=e;i++)
            {
                del=head;
                head=head->next;
                if(head!=NULL)
                {
                    head->prev=NULL;

                }
                free(del);
            }
        }
//when s and e are same and are not equal to one, ie, when user gives equal START and END index and not equal to 1.
        else if(s==e && s!=1) 
        {
            for(i=1,t=head;i<s-1;i++,t=t->next); //traverse till said position.
            del=t->next;
            t->next=del->next;
            if(del->next!=NULL)
            {
                del->next->prev=t;

            }
            free(del);
        }
        else
        {
            for(i=1,t=head;i<s-1;i++,t=t->next); // move till s 
            for(;i<e;i++) //delete lines from s to e
            {
                del=t->next;
                t->next=del->next;
                if(del->next!=NULL)
                { 
                    del->next->prev=t;
                }
                free(del);
            }
        }
        changed=1;
    }
}
void insert(int lineno)
{
    char line[100];
    int count=0,i,j;
    for(t=head;t!=NULL;t=t->next,count++);
    if(lineno>count  || lineno<0)
    {
        printf("Invalid line number.\n");
        return;
    }
    else
    {

        if(lineno==0)
        {
            printf("Enter Text\n");
            fflush(stdin);
            fgets(line,MAX,stdin);
            newNode=getNode(line);
            newNode->next=head;
            head=newNode;
            head->prev=NULL;

        }
        else if(lineno==count)
        {
            printf("Enter Text\n");
            fflush(stdin);
            fgets(line,MAX,stdin);
            newNode=getNode(line);
            for(t=head;t->next!=NULL;t=t->next);
            t->next=newNode;
            newNode->prev=t;

        }
        else
        {
            printf("Enter Text\n");
            fflush(stdin);
            fgets(line,MAX,stdin);
            for(t=head,i=1 ;i<lineno;t=t->next,i++);
            newNode=getNode(line);
            newNode->next=t->next;
            t->next=newNode;
            newNode->prev=t;
            newNode->next->prev=newNode;
        }
        changed=1;

    }
}

void move(int s,int e)
{
    int i,count=0;
    Node *temp1,*temp2;

    for(t=head;t!=NULL;t=t->next,count++);
    if(s>0 && e>0 && e<=count && s<=count)
    {
        if(s==e)
        {

        }
        else if(s==1 && e!=s)
        {
            temp1=head;
            head=head->next;
            for(i=1,t=head;i<e-1;t=t->next,i++);
            temp1->next=t->next;
            temp1->prev=t;
            t->next=temp1;
            changed = 1;
        }
        else if(s!=1 && s!=e)
        {
            if(e==1)
            {
                for(i=1,t=head;i<s-1;i++,t=t->next);
                temp1=t->next;
                t->next=temp1->next; 
                if(temp1->next!=NULL)
                {
                    temp1->next->prev=t;

                }
                temp1->next=head;
                head->prev=temp1;
                head=temp1;
                changed = 1;
            }
            else if(e!=1)
            {
                for(i=1,t=head;i<s-1;i++,t=t->next);
                temp1=t->next;
                t->next=temp1->next;
                if(temp1->next!=NULL)
                {
                    temp1->next->prev=t;
                }
                for(i=1,t=head;i<e-1;t=t->next,i++);
                temp1->next=t->next;
                if(t->next!=NULL)
                {
                    t->next->prev=temp1;

                }
                t->next=temp1;
                t->next->prev=t;
                changed = 1;
            }
        }
    }
    else
    {
        if(e>count || e<0)
            printf("Invalid destination line.\n");

        if(s>count || s<0)
            printf("Invalid source line.\n");
    }
}

void copy(int s,int e)
{
    Node *temp,*temp1,*del;
    int i,count=0;
    int n;
    for(t=head;t!=NULL;t=t->next,count++);
    if(s<=0 || e>count || s>count)
    {
        printf("Invalid command.\n");
        return;
    }
    else
    {
        if( s>0 && s<=count && e>0 && e<=count)
        {
            for(i=1,t=head;i<s;i++,t=t->next);
            temp=getNode(t->data);
            if(e==1)
            {
                strcpy(head->data,temp->data);
            }
            else
            {
                for(i=1,t=head;i<e;i++,t=t->next);
                strcpy(t->data,temp->data);
            }
        }

        changed=1;   
    }

}
    
/* 
    char *strstr(const char *haystack, const char *needle) 
    function finds the first occurrence of the 
    substring needle in the string haystack.      
*/
void displayPattern(char *pat)
{
    int i;
    t = head;
    i = 1;
    while(t)
    {
        if(strstr(t->data,pat))
        {
            printf("%d: %s",i,t->data);
        }
        t=t->next;
        i++;
    }
}

void replace(char* fpat, char* rpat)
{
    int i, j, found, flag=0;
    char prefix[MAX];
    char suffix[MAX];
    char temp[MAX];
    int preLen, sufLen;
    int fpatLen = strlen(fpat); 
    int rpatLen = strlen(rpat);
    int stringLen;
    int fpatIndex = 0;
    int suffixIndex = 0;

    t = head;
    while(t)
    {
        if(strstr(t->data,fpat))
        {
            flag = 1;
            break;
        }
        t=t->next;
    }

    if(flag == 0)
    {
        printf("Substring does not exist.\n");
        return;
    }

    stringLen = strlen(t->data);

    char* string = t->data;
    char* substring = strstr(string, fpat);
    fpatIndex = substring - string;
    preLen = fpatIndex;
    sufLen = stringLen - suffixIndex;
    suffixIndex = preLen + fpatLen;

    for(i=0; i<fpatIndex; i++)
    {
        prefix[i] = t->data[i];
    }
    prefix[preLen] = '\0';

    for(i=0, j=suffixIndex; i<sufLen,j<=stringLen; i++, j++)
    {
        suffix[i] = t->data[j];
    }
    suffix[sufLen] = '\0';
    strcpy( temp, strcat(prefix, rpat));

    strcpy(t->data, strcat(temp, suffix));
    t->data[preLen + rpatLen + sufLen-1] = '\0';

    changed = 1;
}