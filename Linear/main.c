#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct table_entry_{
	char data[32];
	char hash[32];
	struct table_entry_ *next;
}table_entry_t;

typedef struct table_{
	table_entry_t *next;
}table_t;

table_t *table;


table_t *init(){
  table = calloc(1, sizeof(table_t));
  table_entry_t *node = calloc(1, sizeof(table_entry_t));
  node->next = NULL;
  table->next = node;
  return table;
}
int add(table_t *table, char *data){
  table_entry_t *head = table->next;
  table_entry_t *node = calloc(1, sizeof(table_entry_t));
  if(!head->next){
    strcpy(node->data, data);
    strcpy(node->hash, data);
    node->next = NULL;
    head->next = node;
    return 0;
  }
  while(head->next){
    head = head->next;
  }
  strcpy(node->data, data);
  strcpy(node->hash, data);
  node->next = NULL;
  head->next = node;
  return 0;
}
void show(table_t *table){
  table_entry_t *head = table->next;
  while(head){
    printf("%s\t\t%s\n", head->data, head->hash);
    head = head->next;
  }
}
table_entry_t *find(table_t *table, char* data){
  table_entry_t *head = table->next;
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
  table_entry_t *head = table->next;
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
    }
    previous = current;
    current = current->next;
  }
  return 0;
}

int main (int argc, char **argv){

  table = init();
  add(table, "ali");
  add(table, "reza");
  add(table, "mohsen");
  add(table, "benyamin");
  add(table, "mehrnaz");
  add(table, "yashan");
  add(table, "fatemeh");
  add(table, "elnaz");
  add(table, "shahram");
  add(table, "farideh");

  table_entry_t *node = find(table, "benyamin");
  // Call any function
  show(table);

  free(table);
  return 0;
}
