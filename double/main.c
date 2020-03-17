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

  node->next = NULL;
  if(!tail->next && !tail->prev){
		strcpy(node->data, data);
	  strcpy(node->hash, data);
    node->prev = tail;
    tail->next = node;
    return 0;
  }
  while(tail->next){
    tail = tail->next;
  }
	strcpy(node->data, data);
	strcpy(node->hash, data);
  node->prev = tail;
  tail->next = node;
  table->tail = node;
  return 0;
}

int head_add(table_t *table, char *data){
  table_entry_t *head = table->head;
  table_entry_t *node = calloc(1, sizeof(table_entry_t));
  if(!head->next && !head->prev){
    strcpy(node->data, data);
    strcpy(node->hash, data);
    node->next = head;
    node->prev= NULL;
    head->prev = node;
    return 0;
  }

  strcpy(node->data, data);
  strcpy(node->hash, data);
  node->next = head;
  node->prev = NULL;
  head->prev = node;
	table->head = node;
  return 0;
}

void head_show(table_t *table){
  table_entry_t *head = table->head;
  while(head){
    printf("%s -> ", head->data);
    head = head->next;
  }
	printf("NULL\n");
}

void tail_show(table_t *table){
	table_entry_t *tail = table->tail;
	while(tail){
		printf("%s -> ", tail->data);
		tail = tail->prev;
	}
	printf("NULL\n");
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

  if(!head->next && !head->prev){
		if(!strcmp(head->data, entry->data)){
				free(head);
				return 0;
		}
		else{
			printf("not found\n");
			return -1;
		}
	}
	while(head){
		if(!strcmp(head->data, entry->data)){
			head->prev->next = head->next;
			head->next->prev = head->prev;
			free(head);
			return 0;
		}
		head = head->next;
	}
  printf("not found\n");
  return -1;
}

/* int insertB4(table_t *table, char* data, table_entry_t *entry) //insert data before entry*/

/* int insertAfter(table_t *table, char* data, table_entry_t *entry) //insert data after entry*/

int main (int argc, char **argv){

  table = init();
  tail_add(table, "ali");
  head_add(table, "reza");
  tail_add(table, "mohsen");
  head_add(table, "benyamin");
  tail_add(table, "mehrnaz");
  tail_add(table, "yashan");
  head_add(table, "fatemeh");
  tail_add(table, "elnaz");
  head_add(table, "shahram");
  tail_add(table, "farideh");

	head_show(table);
  table_entry_t *node = find(table, "benyamin");
  del(table, node);
	head_show(table);
	
  free(table);
  return 0;
}
