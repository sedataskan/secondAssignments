//Seda Nur TASKAN 201180004
#include <stdio.h>

#define SIZE 10

typedef struct
{
  int value;
} element;

element queue[SIZE];
int front = -1;
int rear = -1;

element temporaryqueue[SIZE];
int tFront = -1;
int tRear = -1;

int dequeue();
char *enqueue();
void print_queue();
int tDequeue();

int dequeue()
{
    if(rear == -1 && front == -1)
    {
        return;
    }
    else if(front == rear)
    {
        front = -1;
        rear = -1;
    }
    else
    {
        int deleted = queue[front].value; //deleted for returning. we use it at the enqueue().
        front++;
        return deleted;
    }
}

int tDequeue()
{
    if(tRear == -1 && tFront == -1)
    {
        return;
    }
    else if(tFront == tRear)
    {
        tFront = -1;
        tRear = -1;
    }
    else
    {
        int deleted = temporaryqueue[tFront].value; //we use it at the enqueue()
        tFront++;
        return deleted;
    }
} 

char *enqueue()
{
    int addValue;
    printf("Enter a value to add: ");
    scanf("%d",&addValue);
    if(rear == SIZE)
    {
        return "false"; // if our queue size is equal to SIZE then we can not add any items anymore
    }
    else if(rear == -1 && front == -1)
    {
        front = 0;
        rear = 0;  // if our queue is empty, we add it directly
        queue[rear].value = addValue;
        rear++;
    }
    else if(queue[front].value>= addValue)
    //(if front element is bigger than our addValue) in that case we want to add our addValue to beggining.   
    //so we made a temporary queue and add all of our elements from queue to temporary queue.
    //and then add our addValue to queue then all elements of temporary queue to queue.
    {                                      
        for(int i = front ; i< rear ; i++)
        {
            if(tRear == -1 && tFront == -1)
            {
                tRear = 0;
                tFront = 0;
            }
            temporaryqueue[tRear].value = dequeue();
            tRear++;
        }
        queue[rear].value = addValue;
        rear++;
        for(int i = tFront ; i<tRear ; i++){
            if(rear == -1 && front == -1)
            {
                rear = 0;
                front = 0;
            }
            queue[rear].value = tDequeue();
            rear++;
        }
    }
    else if(queue[rear-1].value <= addValue)
    //in that case we want to add our element at end.
    //we add it directly at the end of queue.
    {
        queue[rear].value = addValue;
        rear++;
    }
    else
    //in that case we want to add our addValue at the somewhere not end or beggining.
    //for this case we controlled the all elements of queue and when we find a bigger one, we add all elements smaller than addValue to temporary queue
    //and then we add our addValue to temporary queue too. then add all elements from queue to temporary queue until queue is empty.
    //and then we add all elements of temporary queue to queue and it is done.
    {
        for(int i = front ; i < rear ; i++)
        {
            if(queue[i].value <= addValue)
            {
                if(tRear == -1 && tFront == -1)
                {
                    tRear = 0;
                    tFront = 0;
                }
                temporaryqueue[tRear].value = dequeue();
                tRear++;
            }
        }
        temporaryqueue[tRear].value = addValue;
        tRear++;
        for(int i = front ; i < rear ; i++)
        {
            if(tRear == -1 && tFront == -1)
            {

                tRear = 0;
                tFront = 0;
            }
            temporaryqueue[tRear].value = dequeue();
            tRear++;
        }
        for(int i = tFront ; i < tRear ; i++){
            if(rear == -1 && front == -1)
            {
                rear = 0;
                front = 0;
            }
            queue[rear].value = tDequeue();
            rear++;
        }
    }
    //returning true so we succesfly add item to queue
    return "true";
}

void print_queue()
{
    if(front == -1 && rear == -1)
    {
        printf("Queue is empty."); //if our queue is empty, system will print queue is empty.
    }
    else
    {
        for(int i = front ; i < rear ; i++){
            printf("%d ",queue[i].value); // if queue is not empty print all elements
        }
        printf("\n\n");
    }
}

int Options()
{
  int option;
  printf("---------OPTIONS---------\n0- Print all elements of the queue\n1- Add an element into the queue\n2- Remove an element from the queue\n3- Exit\n");
  printf("Select (0-3)? : ");
  scanf("%d", &option);
  return option;
}

int main(void)
{
  int input = Options();

  switch (input)
  {
  case 0:
    print_queue();
    main();
    break;
  case 1:
    if (enqueue() == "true")
    { //we compared result and "true". if result is equal to "true" it returns 0.
      printf("-The element has been successfully added\n\n");
    }
    else
    {
      printf("-The element adding is failed\n\n");
    }
    main();
    break;
  case 2:
    dequeue();
    main();
    break;
  case 3:
    return 0; //using 0 for exit from system
  }
  return 0;
}