#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define true 1
#define false 0

//creating a struct
struct node
{
  char* value;
  int code;
  struct node* next;
};

struct node* head;

//functions
void print();
void insert(char* x,int code);
int find(struct node* head,int code);
void fileprocces();
void edit();
void writesorted();

void print()
{
    struct node* temp = head;

    while(temp != NULL)
    {
        printf("%d%s",temp->code,temp->value);
        temp = temp ->next;
    }
    printf("\n");
}

void insert(char* x, int code)
{
  if(find(head,code) == 0)//if there is no same code in linkedlist, we can add element
  {
    struct node* temp = (struct node*)malloc(sizeof(struct node)); //used malloc for opening space in memory
    temp -> value = x;
    temp -> code = code;
    temp -> next = NULL;
    if(head != NULL)
    {
      temp -> next = head;
    }
    head = temp;
  }
}

int find(struct node* head,int code)
{
  struct node* current = head;
  while(current != NULL)//searching for same code in our linkedlist
  {
    if((current -> code) == code)
    {
      return true;//if we find same course code in linkedlist, we won't add it again
    }
    current = current -> next;
  }
  return false;//if we can not find any same code then we add it to linkedlist
}

void fileprocces()
{
    FILE *filepointer = fopen("Data.dat","r");//opening file

    int lengthline = 255;
    char line[255];

    while(fgets(line,lengthline,filepointer))//reading file line by line
    {
        char *linetoken = strtok(line," ");
        char *tempname = malloc(sizeof(line));
        char *tempcode;
        int count = 0;

        strcpy(tempname,"\t");//tab for "code    course name"

        while(linetoken != NULL)
        {
          if(atoi(linetoken)==0)//if there is no number than atoi returns 0
          {
            
            strcat(tempname,linetoken);//append course name words to tempname 
            strcat(tempname," ");//space between two words
          }
          else
          {
            strcat(tempname,"\n");//\n for to move cursor to bottom line
            tempcode = linetoken;
          }
            linetoken = strtok(NULL, " "); //strtok() for to divide in each space
            count++;
        }
        int code = atoi(tempcode);//atoi() for changing string to int
        //end of taking course code and name

        insert(tempname,code);//inserting course name and code to linkedlist
    }
    fclose(filepointer);//closing file
}

void edit()
{
  struct node* current = head, *location = NULL;
  char *tempS;
  int tempI;

  while(current != NULL)
  {
    location = current -> next;

    while(location != NULL)
    { //making bubble sorting
      if(current -> code > location -> code)
      {
        tempI = current->code;
        tempS = current->value;

        current->code = location->code;
        current->value = location->value;

        location->code = tempI;
        location->value = tempS;
      }
      location = location -> next;
    }
    current = current -> next;
  }

}

void writesorted()
{
  FILE *filepointer = fopen("Sorted.dat","w");

  int lengthline = 255;
  char line[255];

  struct node* temp = head;

    while(temp != NULL)
    {
        fprintf(filepointer,"%d%s",temp->code,temp->value);
        temp = temp ->next;
    }
  fclose(filepointer);
}

//main function
int main()
{
    fileprocces();
    edit();
    writesorted();
    print();
    return 0;
}