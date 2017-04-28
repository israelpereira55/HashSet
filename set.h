#ifndef SET_H_
#define SET_H_

typedef struct set Set;

/* THE CLIENT SHOULD IMPLEMENT:
 * - A comparable function.
 *	This function should compare two keys and return an int as the strcmp function, which return:
 *		<0, if the first key are lower than the second key.
 *		 0, if the keys are equal.
 *		>0, if the first are higher than the second key.
 *
 * - A function to calculate the hash code.
 *	The parameters should be a void pointer to one key and the output will be an int which will 
 *	select where the element will be inserted in the HashSet.
 *	The info's index will be the hash code value % hash size.
 * 
 * - A function to clear their info to use the "set_complete_clear" function. 
 * 	This functions won't be used if the client don't call the function "set_complete_clear".
 *	Is possible to pass NULL on that parameter, however the "set_complete_clear" function
 * 	should not be used.
 *	The function "set_clear" will free all the memory used by the Set but the client info will remains.
 */


Set* set_create(int set_size, int(*comparable)(void* info1, void* info2), int (*hash_code)(void* key), void* (*info_clear)(void* info));


/* Output:
 * 	1, if the set is empty.
 * 	0, otherwise.
 */
int set_is_empty(Set* set);


/* Output:
 * 	1, if the insertion was made.
 * 	0, if the key is already used in the set and if so the element will NOT be inserted.
 */
int set_insert(Set* set, void* info, void* key);


/* Output:
 * 	1, if the element is on set.
 * 	0, otherwise.
 */
int set_contains(Set* set, void* key);


/* Output:
 * 	void pointer to the client info with the selected key.
 * 	NULL, otherwise.
 *
 * The client need to do the type cast to his info in purpose to use it.
 */
void* set_get(Set* set, void* key);


/* Output:
 * 	the info removed from the set if it was there.
 * 	NULL, otherwise.
 */
void* set_remove(Set* set, void* key);


/* Free all the memory allocated by set.
 * Output:
 * 	NULL (In purpose clear the client pointer).
 */
Set* set_clear(Set* set);


/* Free all the memory allocated by set and the client info.
 * Output:
 * 	NULL (In purpose clear the client pointer).
 */
Set* set_complete_clear(Set* set);

#endif /*SET_H_*/
