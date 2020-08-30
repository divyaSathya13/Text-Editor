#include "DSproject.h"
int main(int argc,char *argv[])
{
    changed = 0;
    system("clear"); // clears screen.

    FILE *fp;
    int i,tokens,len=0;
    char ch,line[MAX],command[10],t1[MAX],t2[MAX],t3[MAX],t4[MAX];
    char ch2[MAX];

//If filename has not been entered along with executable, request file name.

    //head = NULL;

                if(argc!=2)
                {
                    while(1)
                    {
                        printf("Create new file or open existing file?(c:Create, o:Open, man:Manpage, v: View Directory)\n");
                        fflush(stdin);
                        fgets(ch2,MAX,stdin);
                        if(strcmp(ch2,"man\n")==0)
                        {
                            system("gedit man.txt");
                            fflush(stdin);
                            continue;
                        }

                        else if(strcmp(ch2,"q\n")==0)
                        {
                            fflush(stdin);
                            exit(0);
                        }

                        else if((strcmp(ch2,"c\n")==0) || (strcmp(ch2,"o\n")==0))
                        {
                    
                            printf("Enter File Name:\n");
                            scanf("%s", fileName); 
                            //system("clear"); 
                            break;
                        }  
                        
                        else if(strcmp(ch2,"v\n")==0)
                        {
                            system("ls");
                        }

                        else
                        {
                            printf("Invalid Command.\n");
                        } 

                    }
                    
                }
                else
                {
                    strcpy(fileName,argv[1]);

                }
                ch=ch2[0];
                switch(ch)
                {
                    case 'c': 
                                {  
                                    fp=fopen(fileName,"w");
                                    if(fp==NULL)
                                    {
                                        printf("Unable to open the file.\n");
                                        exit(0);
                                    }
                                    break;
                                }

                    case 'o':   
                                {
                                
                                    fp=fopen(fileName,"r");

                                    if(fp==NULL)
                                    {
                                        printf("File does not exist.\n");
                                        exit(0);

                                    }
                                    
                                    // system("clear"); 
                        
                                    break;
                                }

                    default: 
                                {
                                    fp=fopen(fileName,"r");
                                    if(fp == NULL)
                                        {
                                            printf("File does not exist.\n");
                                            exit(0);
                                        }
                                }

                } 
//If file name was entered as a main() argument, extract file name.
head = NULL;

//Parse through file and print contents on opening file
    while(fgets(line,MAX,fp))
    {
        //line[strlen(fileName)-1]='\0';
        newNode=(Node *)malloc(sizeof(Node));
        if(newNode==NULL)
        {
            exit(0);
        }
        strcpy(newNode->data,line);
        newNode->next=NULL;
        newNode->prev=NULL;
        if(head==NULL)
        {
            head=t=newNode;
        }
        else
        {
            t->next=newNode;
            newNode->prev=t;
            t=t->next;
        }

    }
    for(t=head,i=1;t!=NULL;t=t->next,i++)
        printf("%d : %s",i,t->data);    

    while(1)
    {
        if(tokens != -1)
            printf(">> ");
        fflush(stdin);
        fgets(command,MAX,stdin);
        tokens=sscanf(command,"%s%s%s%s",t1,t2,t3,t4); // sscanf - formatted input
        //printf("Tokens = %d\n",tokens);
        switch(tokens)
        {
            case -1:
                break;
            case 0:
                break;

        // for PRINT, display() all lines from line 1.
            case 1:
                    if(strcmp(t1,"p")==0)
                    {
                        len=0;
                        for(t=head;t!=NULL;t=t->next)
                            len++;

                        display(1,len);
                    }
            //for APPEND, append().
                    else if(strcmp("a",t1)==0)
                        append();
                    else if(strcmp("man",t1)==0)
                    {
                        system("gedit man.txt");
                    }
            
            //for QUIT, ask to save if edited, then quit.
                    else if(strcmp("q",t1)==0)
                    {
                        if(changed==1)
                        {
                            printf("Save?(y/n)");
                            ch=getchar();
                            if(ch=='y' || ch=='Y')
                                save();
                            else
                                exit(0);
                        }
                        exit(0);
                    }
                    else if(strcmp("i",t1)==0)
                    {
                        insert(0);   
                    }

            //for HELP, display legend.
                    else if(strcmp("h",t1)==0)
                        printf("man:ManPage\na: Append\ni: Insert\nm: Move\nc: Copy\np: Print\ns: Save \nq: Quit\n");

            //for SAVE, save().
                    else if(strcmp("s",t1)==0)
                        save();  
                    else if(strcmp("v",t1)==0)
                        system("ls");

            //for unidentified command, print remark.                
                    else    
                        printf("Invalid Command.\n");
                    break;


            case 2:
            //if PRINT is followed by line number, print specified line.
                    if(strcmp("p",t1)==0)
                    {
                        display(atoi(t2),atoi(t2));
                    }
            
            //if DELETE is followed by line number, delete specified line.
                    else if(strcmp("d",t1)==0)
                    {
                        delete_line(atoi(t2),atoi(t2));
                    }
            
            //if INSERT is followed by line number, insert after specified line.
                    else if(strcmp("i",t1)==0)
                        insert(atoi(t2));
            
            //if FIND is followed by substring, find substring occurance in string and display containing  line.
                    else if(strcmp(t1,"f")==0)
                        displayPattern(t2);
                    else
                        printf("Invalid Command.\n");
                    break;

            case 3:
            //PRINT from line a to line b.
                    if(strcmp("p",t1)==0)
                    {
                        if(atoi(t2)>atoi(t3))
                        {
                            display(atoi(t3),atoi(t2));
                        }
                        else
                            display(atoi(t2),atoi(t3));
                    }
            
                    else if(strcmp("r",t1)==0)
                    {
                        replace(t2, t3);
                    }
            //DELETE from line a to line b.
                    else if(strcmp("d",t1)==0)
                    {
                        delete_line(atoi(t2),atoi(t3));
                    }
                    else if(strcmp("m",t1)==0)
                        move(atoi(t2),atoi(t3));

                    else if(strcmp("c",t1)==0)
                        copy(atoi(t2),atoi(t3));
                    else
                        printf("Invalid command.\n");
                    break;

            default: printf("Invalid  Command. \n");
        }    

    }
}