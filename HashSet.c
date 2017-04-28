#include <stdlib.h>

#include "linkedlist.h"
#include "set.h"

typedef struct container Cell;

struct container {
	void* info;
	void* key;
	int key_value;
};

struct set {
	List** vector;
	int size;
	int number_of_elements;
	int (*comparable)(void* info1, void* info2);
	int (*hash_code)(void* key);
	void* (*info_clear)(void* info);
};

Set* set_create(int set_size, int(*comparable)(void* info1, void* info2), int (*hash_code)(void* key), void* (*info_clear)(void* info)) {
	Set* HashSet = (Set*) malloc (sizeof(Set));
	
	HashSet->vector = (List**) malloc(set_size * sizeof(List*));
	
	int i = 0;
	while(i < set_size) {
		HashSet->vector[i] = NULL;
		i++;
	}

	HashSet->comparable = comparable;
	HashSet->hash_code = hash_code;
	HashSet->info_clear = info_clear;
	HashSet->size = set_size;
	HashSet->number_of_elements = 0;
	return HashSet;
}

int set_is_empty(Set* set) {
	return set->number_of_elements;
}

int set_contains(Set* set, void* key){
	int hash_key = set->hash_code(key);
	
	int lenght = list_size( set->vector[hash_key % set->size] );
	if(lenght == 0 || lenght == -1){
		return 0;
	}
	
	//Case the HashSet are working well, every cell will have approximately one item. Thus before construct an iterator, this function looks the first item.
	List* current_list = set->vector[hash_key % set->size];
	Cell* current_item = list_get_first( current_list );
	if( !set->comparable(current_item->key, key) ) {
		return 1;
	}
	
	Iterator* iterator = iterator_create(current_list);
	
	int i = 1;
	while(i < lenght){
		iterator = iterator_next(iterator);
		current_item = iterator_get_current(iterator);
		
		if( !set->comparable(current_item->key, key) ) {
			return 1;
		}
		i++;
	}
	
	return 0;
}

int set_insert(Set* set, void* info, void* key){
	
	if( set_contains(set, key) ) {
		return 0;
	}

	set->number_of_elements++;
	Cell* new = (Cell*) malloc (sizeof(Cell));

	new->info = info;
	new->key = key;
	
	int key_value = set->hash_code(info);
	new->key_value = key_value;

	List* current_list = set->vector[key_value % set->size];
	if(current_list == NULL){
		set->vector[key_value % set->size] = list_create();
	}

	list_insert_last(set->vector[key_value % set->size], new);
	return 1;
}

void* set_get(Set* set, void* key){
	int hash_key = set->hash_code(key);
	
	List* current_list = set->vector[hash_key % set->size];
	
	int lenght = list_size( current_list );
	if(lenght == 0){
		return NULL;
	}
	
	Cell* current_item = list_get_first( current_list );
	if( !set->comparable(current_item->key, key) ) {
		return current_item->info;
	}
	
	Iterator* iterator = iterator_create(current_list);
	
	int i = 1;
	while(i < lenght){
		iterator = iterator_next(iterator);
		current_item = iterator_get_current(iterator);
		
		if( !set->comparable(current_item->key, key) ) {
			return current_item->info;
		}
		i++;
	}
	
	return NULL;
}

void* cell_clear(void* cell){
	free( (Cell*)cell);
	return NULL;
}

void* set_remove(Set* set, void* key){
	int hash_key = set->hash_code(key);
	
	List* current_list = set->vector[hash_key % set->size];
	
	int lenght = list_size( current_list );
	if(lenght == 0){
		return NULL;
	}
	
	void* info = NULL;
	Cell* old = NULL;
	Cell* current_item = list_get_first( current_list );
	if( !set->comparable(current_item->key, key) ) {
		info = current_item->info;
		old = list_remove_first(current_list);
		cell_clear(old);
		return info;
	}
	
	Iterator* iterator = iterator_create(current_list);
	
	int i = 1;
	while(i < lenght){
		iterator = iterator_next(iterator);
		current_item = iterator_get_current(iterator);
		
		if( !set->comparable(current_item->key, key) ) {
			info = current_item->info;
			old = list_remove(current_list, i);
			cell_clear(old);
			return info;
		}
		i++;
	}
	
	return NULL;
}

Set* set_clear(Set* set){	
	
	if(set->number_of_elements == 0){
		free(set->vector);
		free(set);
		return NULL;
	}
	
	int lenght = set->size;
	int freed = 0;
	int max = set->number_of_elements;
	int i = 0;
	while(freed < max && i < lenght){
		if(set->vector[i] != NULL){
			set->vector[i] = list_complete_clear(set->vector[i], cell_clear);
			freed++;
		}
		i++;
	}
	
	free(set->vector);
	free(set);
	return NULL;
}

void* cell_complete_clear(void* cell, void*(*info_clear)(void* info)){
	Cell* c = (Cell*) cell;
	
	c->info = info_clear(c->info);
	cell_clear(cell);
	return NULL;
}
/*	
Set* set_complete_clear(Set* set){

	if(set->number_of_elements == 0){
		free(set->vector);
		free(set);
		return NULL;
	}
	
	int lenght = set->size;
	int freed = 0;
	int max = set->number_of_elements;
	int i = 0;
	while(freed < max && i < lenght){
		if(set->vector[i] != NULL){
			set->vector[i] = list_complete_clear2(set->vector[i], cell_complete_clear, set->info_clear);
			freed++;
		}
		i++;
	}
			
	free(set->vector);
	free(set);
	return NULL;
}*/

