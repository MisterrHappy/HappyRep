/**********************************************************************************************************/
 /* File: HashTable.h */
 /* Made by:  Andre Luis Raposo Marinho, Number 93687. */
 /* Description: Declaration of the functions and structs Hash_Node used in HashTable.c. */
/**********************************************************************************************************/

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Schedule.h"

typedef struct Hash_Node {
    struct Hash_Node * previous, * next;
    contact * c;
} Hash_Table_Node;

Hash_Table_Node** init_hashtable(int size);
Hash_Table_Node* find_node_in_hash(Hash_Table_Node** Hash, int index, const char* string);
void add_contact_in_hash(Hash_Table_Node** Hash, int index, contact* c_to_add);
void remove_hash_node(Hash_Table_Node** Hash, int index, Hash_Table_Node* Node_to_remove);
int hash(const char* string, int size);
void close_hashtable(Hash_Table_Node** Hash, int size);

#endif
