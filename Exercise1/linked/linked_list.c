#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"


list_t list_create()
{
	list_t temp = malloc(sizeof(struct node));
	temp->head = NULL;
	temp->tail = NULL;
	temp->length = 0;

	return temp;
}

void list_delete(list_t list)
{
	struct node *curr = list->head;
	struct node *next = curr->next;
	struct node *temp;

	while(next){
		temp = curr;
		curr = next;

		free(temp->next);
		free(temp->prev);
		free(temp);

		temp = NULL; 
	}	

	//free(list->head);
	free(list);

}

void list_insert(list_t list, int index, int data)
{
	struct node *curr = list->head;
	int i;
	for(i = 0 ; i < index - 1 ; i++){
		curr = curr->next;
	}

	struct node *temp = malloc(sizeof(struct node));

	temp->prev = curr;
	temp->next = curr->next;

	curr->next->prev = temp;
	curr->next = temp;

	temp->data = data;

	list->length = list->length + 1;
}

void list_append(list_t list, int data)
{
	struct node *temp = malloc(sizeof(struct node));
	if(list->head == NULL){
		temp->prev = NULL;
		temp->next = NULL;
		temp->data = data;
		list->head = temp;
	}else if(list->tail == NULL){
		temp->prev = list->head;
		temp->next = NULL;
		list->tail = temp;
		temp->data = data;
		list->head->next = list->tail;
	}else{
		temp->next = NULL;
		temp->prev = list->tail;
		list->tail->next = temp;
		temp->data = data;
		list->tail = temp;
	}

	list->length = list->length + 1;
}

void list_print(list_t list)
{
	if(list->length == 0){
		printf("\n");
		return;
	}
	struct node *curr = list->head;
	while(curr->next){
		printf("%i ", curr->data);
		curr = curr->next;
	}
	printf("%i \n", curr->data);
}

long list_sum(list_t list)
{
	int sum = 0;
	struct node *curr = list->head;
	while(curr->next){
		sum = sum + curr->data;
		curr = curr->next;
	}
	sum = sum + curr->data;
	
	return sum;
}

int list_get(list_t list, int index)
{
	struct node *curr = list->head;
	int i;
	for(i = 0 ; i <= index - 1 ; i++){
		curr = curr->next;
	}
	
	return curr->data;
}

int list_extract(list_t list, int index)
{
	struct node *curr = list->head;
	if(curr->next){
	}
	int i;
	if(index!=0){
		for(i = 0 ; i < index ; i++){
			curr = curr->next;
		}
		
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;
	}else{
		if(list->length == 1){
			list->head->next = NULL;
		}else{
			list->head = curr->next;
			list->head->prev = NULL;
		}
	}

	int result = curr->data;

	free(curr);

	list->length = list->length - 1;

	return result;
}
