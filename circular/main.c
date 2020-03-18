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
  node->next = node;
  node->prev = node;
  table->head = node;
  table->tail = node;
  return table;
}

int add(table_t *table, char *data){
  table_entry_t *head = table->head;
  table_entry_t *tail = table->tail;
  table_entry_t *node = calloc(1, sizeof(table_entry_t));

  if(head == tail){
    strcpy(node->data, data);
  	strcpy(node->hash, data);
    head->next = node;
    node->prev = head;
    head->prev = node;
    node->next = head;
    table->tail = node;
    return 0;
  }
  strcpy(node->data, data);
  strcpy(node->hash, data);
  node->prev = tail;
  tail->next = node;
  node->next = head;
  head->prev = node;
  table->tail = node;
  return 0;
}

void head_show(table_t *table){
  table_entry_t *head = table->head;
  while(head){
    printf("%s -> ", head->data);
    head = head->next;
    if(head == table->tail){
      printf("%s ->", head->data);
      break;
    }
  }
  printf("\n");
}

void tail_show(table_t *table){
	table_entry_t *tail = table->tail;
	while(tail){
		printf("%s -> ", tail->data);
		tail = tail->prev;
    if(tail == table->head){
      printf("%s ->", tail->data);
      break;
    }
	}
  printf("\n");
}

table_entry_t *find(table_t *table, char* data){
  table_entry_t *head = table->head;
  while(head){
    if(!strcmp(head->data, data)){
      return head;
    }
    else{
      head = head->next;
      if(head == table->tail){
        printf("not found\n");
        return NULL;
      }
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
    if(head == table->tail){
      printf("not found\n");
      return -1;
    }
	}
  printf("not found\n");
  return -1;
}

int insertB4(table_t *table, char* data, table_entry_t *entry){ //insert data before entry
	table_entry_t *head = table->head;
	table_entry_t *node = calloc(1, sizeof(table_entry_t));
	while(head){
		if(!strcmp(head->data, entry->data)){
			strcpy(node->data, data);
			strcpy(node->hash, data);
			head->prev->next = node;
			node->prev = head->prev;
			node->next = head;
			head->prev = node;
			return 0;
		}
		head = head->next;
	}
	add(table, data);
	return 0;
}

int insertAfter(table_t *table, char* data, table_entry_t *entry) {//insert data after entry
	table_entry_t *head = table->head;
	table_entry_t *node = calloc(1, sizeof(table_entry_t));
	while(head){
		if(!strcmp(head->data, entry->data)){
			strcpy(node->data, data);
			strcpy(node->hash, data);
			head->next->prev = node;
			node->next = head->next;
			head->next = node;
			node->prev = head;
			return 0;
		}
		head = head->next;
	}
	add(table, data);
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

	tail_show(table);
  table_entry_t *node = find(table, "benyamin");
  insertAfter(table, "eslami", node);
	tail_show(table);

  free(table);
  return 0;
}
