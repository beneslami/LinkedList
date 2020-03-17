#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct table_entry_{
	char data[32];
	char hash[32];
	struct table_entry_ *next;
  struct table_entry_ *prev;
}table_entry_t;

typedef struct table_{
	table_entry_t *head;
  table_entry_t *tail;
}table_t;

table_t *table;


table_t *init(){
  table = calloc(1, sizeof(table_t));
  table_entry_t *node = calloc(1, sizeof(table_entry_t));
  node->next = NULL;
  node->prev = NULL;
  table->head = node;
  table->tail = node;
  return table;
}

int tail_add(table_t *table, char *data){
  table_entry_t *tail = table->tail;
  table_entry_t *node = calloc(1, sizeof(table_entry_t));
  strcpy(node->data, data);
  strcpy(node->hash, data);
  node->next = NULL;
  if(!tail->next && !tail->prev){
    node->prev = table->tail;
    table->tail->next = node;
    return 0;
  }
  while(tail->next){
    tail = tail->next;
  }
  node->prev = tail;
  tail->next = node;
  return 0;
}

int head_add(table_t *table, char *data){
  table_entry_t *head = table->head;
  table_entry_t *node = calloc(1, sizeof(table_entry_t));
  if(!head->next && !head->prev){
    strcpy(node->data, data);
    strcpy(node->hash, data);
    node->next = NULL;
    node->prev= NULL;
    table->head->prev = node;
    return 0;
  }
  strcpy(node->data, data);
  strcpy(node->hash, data);
  node->next = head;
  node->prev = NULL;
  head->prev = node;
  return 0;
}

void show(table_t *table){
  table_entry_t *head = table->head;
  while(head){
    printf("%s\t\t%s\n", head->data, head->hash);
    head = head->next;
  }
}
table_entry_t *find(table_t *table, char* data){
  table_entry_t *head = table->head;
  while(head){
    if(!strcmp(head->data, data)){
      return head;
    }
    else{
      head = head->next;
    }
  }
  return NULL;
}
int del(table_t *table, table_entry_t *entry){
  table_entry_t *head = table->head;
  table_entry_t *temp, *current, *previous;
  current = head;
  previous = head;

  if(!head->next){
    free(head);
    return 0;
  }
  while(current){
    if(!strcmp(current->data, entry->data)){
      previous->next = current->next;
      free(current);
      return 0;
    }
    previous = current;
    current = current->next;
  }
  return 0;
}

int main (int argc, char **argv){

  table = init();
  //tail_add(table, "ali");
  head_add(table, "reza");
  //tail_add(table, "mohsen");
  //add(table, "benyamin");
  //tail_add(table, "mehrnaz");
  //tail_add(table, "yashan");
  head_add(table, "fatemeh");
  //tail_add(table, "elnaz");
  //add(table, "shahram");
  //tail_add(table, "farideh");

  //table_entry_t *node = find(table, "benyamin");
  // Call any function
  show(table);

  free(table);
  return 0;
}
