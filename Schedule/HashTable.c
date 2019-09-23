/**********************************************************************************************************/
 /* File: HashTable.c */
 /* Made by:  Andre Luis Raposo Marinho, Number 93687. */
 /* Description: Functions to create, manage and destroy hash tables. */
/**********************************************************************************************************/

#include "HashTable.h" /* Functions used here are declared in this file. */
#include "stdlib.h"
#include "string.h"

/* int ---> Hash_Table_Node** ;
   Creates and returns an array of pointers to the struct Hash_Table_Node with the size given in the input. */
Hash_Table_Node **init_hashtable(int size) {
    int x;
    Hash_Table_Node** Hash = (Hash_Table_Node**) malloc(sizeof(Hash_Table_Node*) * size);
    for (x = 0; x < size; x++) 
        Hash[x] = NULL;
    return Hash;
}

/* Hash_Table_Node** + int + const char* ---> Hash_Table_Node*;
   Finds and returns the pointer of the node (with the given string in the input) in the hash table. If it does not exist returns NULL. */
Hash_Table_Node* find_node_in_hash(Hash_Table_Node** Hash, int index, const char* string) {
    Hash_Table_Node* node;
    for (node = Hash[index]; node; node = node->next) {
        if (!strcmp(string, node->c->name))
            return node;
    }
    return NULL;
}

/* Hash_Table_Node** + int + contact* ---> void;
   Creates a node for the hash table with the pointer of the contact given in the input. */
void add_contact_in_hash(Hash_Table_Node** Hash, int index, contact* c_to_add) {
    Hash_Table_Node* node_to_add = (Hash_Table_Node*) malloc(sizeof(Hash_Table_Node));

    node_to_add->c = c_to_add;
    node_to_add->previous = NULL;
    node_to_add->next = Hash[index]; 

    if (Hash[index]) 
        Hash[index]->previous = node_to_add; 

    Hash[index] = node_to_add;
}

/* Hash_Table_Node** + int + Hash_Table_Node* ---> void;
   Removes a node from the hash knowing the head of the nodes in a certain position. */
void remove_hash_node(Hash_Table_Node** Hash, int index, Hash_Table_Node* Node_to_remove) {
    if (Node_to_remove->previous) 
        Node_to_remove->previous->next = Node_to_remove->next;

    else 
        Hash[index] = Node_to_remove->next;
    
    if (Node_to_remove->next) 
        Node_to_remove->next->previous = Node_to_remove->previous;
    
    free(Node_to_remove);
}

/* char* + int ---> int;
   With the given string and size calculates the position for the hash table (function djb2 given in exercise 3 in lab 10). */
int hash(const char * string, int size) {
    unsigned long hash = 5381;
    int c;
    while ((c = *string++))
        hash = ((hash << 5) + hash) + c;
    return hash % size;
}

/* Hash_Table_Node** + int ---> void;
   Frees all memory associated with the Hash received. */
void close_hashtable(Hash_Table_Node** Hash, int size) {
    int x;
    for (x = 0; x < size; x++) {
        while (Hash[x]) {
        Hash_Table_Node* node_temp = Hash[x]->next;
        free(Hash[x]);
        Hash[x] = node_temp;
        }
    }
    free(Hash);
}
