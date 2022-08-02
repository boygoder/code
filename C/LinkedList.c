  #include <stdio.h>
  #include <conio.h>
  #include <stdlib.h>
struct node
{   
    int data;
    struct node *next;
};

struct node *head; //head pointer hold the address of the starting node of the linked list;

int createlinkedlist()
{
    struct node *newnode,*temp;
    newnode = (struct node*)malloc(sizeof(struct node));//creating of a newnode
    printf("\n\n\t Enter the data into the linkedlist:-");
    scanf("%d",&(newnode->data));
    newnode->next = NULL;
    if(head == NULL)
    {
        head = newnode;
        return 1;
    }
    else{
        temp = head;
        while(temp->next!=NULL)
        {
            temp = temp->next;
        }
        temp->next = newnode;
    }

}
void dispaly()
{
    struct node *temp;
    if(head!=NULL)
    {   
        for(temp = head;temp!=NULL;temp=temp->next)
        {
            printf("%d\t",temp->data);
        }
    }
    else{
        printf("\n\n\t The list is empty");
    }

}
int main()
{
    int ch;
    head = NULL; //tell that the list is empty
    do
    {
        /* code */
        printf("\n\n\t 1.create linkedlist");
        printf("\n\n\t 2.Display linkedlist");
        printf("\n\n\t 3.exit");
        printf("\n\n\t Enter our choice:- ");
        scanf("%d",&ch);
        switch(ch)
        {
        case 1:
            createlinkedlist();
            break;
        case 2:
            dispaly();
            break;
        case 3:
            exit(1);
            break;
        default:
            printf("\n\n\t Wrong entry try again……,");
        }
    } while (ch!=3);
    return 0;
};
