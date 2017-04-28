#ifndef SET_H_
#define SET_H_

typedef struct set Set;

/* THE CLIENT SHOULD IMPLEMENT:
 * -A comparable function.
 *	This function should compare two keys and answer as the strcmp function, which says:
 *		<0 if the first key are lower than the second key.
 *		0 if the keys are equal.
 *		>0 if the first are higher than the second key.
 *
 * -A function to calculate the hash code.
 *	The parameters should be a void pointer to one key and the output will be an int which will select where the element will be inserted in the HashSet.
 *	A simple choose is to use any criteria to get a int by one key and use the rest of a division ( the operator: %) of the hash size.
 * 
 * -A function to clear their info.
 * 	This functions don't will be used if the client don't call the function "set_complete_clear".
 *	The function "set_clear" will free all the memory used by the HashSet but the client info will remains.
 *
 */


Set* set_create(int set_size, int(*comparable)(void* info1, void* info2), int (*hash_code)(void* key), void* (*info_clear)(void* info));

int set_is_empty(Set* set);


/* Returns 1 if the insertion was done.
 * Returns 0 if the key is already used in the set and if so the element do NOT will be inserted.
 */
int set_insert(Set* set, void* info, void* key);

int set_contains(Set* set, void* key);

void* set_get(Set* set, void* key);

void* set_remove(Set* set, void* key);

Set* set_clear(Set* set);

Set* set_complete_clear(Set* set);

#endif /*SET_H_*/
