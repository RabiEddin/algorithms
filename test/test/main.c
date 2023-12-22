//
//  main.c
//  test
//
//  Created by 김도윤 on 2022/09/06.
//

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct node
{
   char elem;
   struct node *prev;
   struct node* next;
}N;

N* getnode()
{
   N* newnode = NULL;
   newnode = (N*)malloc(sizeof(N));
   newnode->elem = '0';
   newnode->next = NULL;
   newnode->prev = NULL;
   return newnode;
}

void add(N* list, int r, char e)
{
   N* newnode = getnode();
   newnode->elem = e;

   N* R = list;
   for (int i = 1; i < r; i++)
   {
      R = R->next;
      if (R->next == NULL)
      {
         printf("invalid position\n");
         return;
      }
   }
   newnode->prev = R;
   newnode->next = R->next;
    R->next->prev = newnode;
    R->next = newnode;

}

void Delete(N* list, int r)
{
   N* R = list;
   for (int i = 1; i < r; i++)
   {
      R = R->next;
      if (R->next == NULL)
      {
         printf("invalid position\n");
         return;
      }
   }
   N* Next = R->next->next;
   N* Prev = R;
   free(R->next);
   Next->prev = Prev;
   Prev->next = Next;
   return;
}

void Get(N* list, int r)
{
   N* R = list;
   for (int i = 0; i < r; i++)
   {
      R = R->next;
      if (R->next == NULL)
      {
         printf("invalid position\n");
         return ;
      }
   }
   printf("%c\n", R->elem);
}

void print(N* list)
{
   N* R = list->next;
   while (R->next != NULL)
   {
      printf("%c", R->elem);
      R = R->next;
   }
   printf("\n");
   return;
}

int main()
{
   N* head,* tail;
   head = (N*)malloc(sizeof(N));
   head->prev = NULL;
   tail = (N*)malloc(sizeof(N));
   tail->next = NULL;
   head->next = tail;
   tail->prev = head;

   int count = 0;
   scanf("%d\n", &count);
   for (int i = 0; i < count; i++)
   {
       char order[10] = { 0 };
      gets(order);
      int Rank = 0;
      for (int j = 2; j < strlen(order) - 2; j++)
      {
         Rank *= 10;
         Rank += (order[j] - '0');
      }
       printf("%d\n", Rank);
      switch(order[0])
      {
      case('A'):
         add(head, Rank, order[strlen(order) - 1]);
         continue;
      case('D'):
         Delete(head , Rank);
         continue;
      case('G'):
         Get(head, Rank);
         continue;
      case('P'):
         print(head);
         continue;
      default:
         break;
      }
   }
   for (N* d = head; d != NULL; d = d->next)
   {
      N* D = d;
      free(D);
   }
}
