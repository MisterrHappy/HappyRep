/**********************************************************************************************************/
 /* File: HighLevelFunctions.c */
 /* Made by: Andre Luis Raposo Marinho, Number 93687. */
 /* Description: High level functions used in the program. */
/**********************************************************************************************************/

#include "HighLevelFunctions.h" /* Functions used here are declared in this file. */
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

/***********************************************************************************/
/*           ERRORS AND CONTACT PRINT STRUCTURE USED IN THIS FILE                  */
/***********************************************************************************/

#define OVERCONTACT "Nome existente."  /* Error used when the contact to add is already in the schedule. */
#define NOCONTACT "Nome inexistente."  /* Error used when the contact to remove, to find or tho change does not exist. */
#define WRITECONTACT "%s %s@%s %s\n"   /* Contact print structure. */
#define DOMAIN "%s:%d\n"               /* Domain print structure. */

#define HASHS_SIZE 1001                /* Number of slots in the hash. */

/* Hash_Table_Node** + Hash_Table_Node** + schedule* + char*[];
   Creates and adds the contact with the given input in the schedule and in both hash tables. When the contact already exists prints an error. */
void add_contact(Hash_Table_Node** Hash_Names, Hash_Table_Node** Hash_Domains, schedule* s, char *input_elements[]) {
    int x = 2, index_names = hash(input_elements[0], HASHS_SIZE), index_domains = hash(input_elements[x], HASHS_SIZE), size = strlen(input_elements[0]), next_index; /* Both hashs positions to add the contact. */
    contact *new_c, *new_c2;  /* Creation of the contact. */
    if (!find_node_in_hash(Hash_Names, index_names, input_elements[0])) {
        new_c = new_contact(input_elements);
        add_contact_last_schedule(s, new_c);
        add_contact_in_hash(Hash_Names, index_names, new_c);
        add_contact_in_hash(Hash_Domains, index_domains, new_c); 
    }
    /* A ideia é se o contacto original já existir fazer um ciclo adicionando o sufixo _1 a cada iteração até encontrar o utlimo nó com o nome com todos os sufixos,
                     acrescentando nas duas hash tables e no schedule o contacto com todos os "_1". */
    while (1) {
    input_elements[0] = realloc(input_elements[0], sizeof(char) * (strlen(input_elements[0]) + 3));
    input_elements[0][++size] = "_";
    input_elements[0][++size] = "1";
    input_elements[0][++size] = "\0";
    next_index = hash(input_elements[0], HASHS_SIZE);
    if (find_node_in_hash(Hash_Names, next_index, input_elements[0]))
        continue;
    new_c2 = new_contact(input_elements);
    add_contact_last_schedule(s, new_c2);
    add_contact_in_hash(Hash_Names, next_index, new_c2);
    add_contact_in_hash(Hash_Domains, index_domains, new_c2); 
    break;
}   

/* schedule* --> void;
   Prints all the contacts in the schedule. */
void print_schedule(schedule* s) {
    contact* c_temp;
    for (c_temp = s->head; c_temp; c_temp = c_temp->next)
        printf(WRITECONTACT, c_temp->name, c_temp->email_local, c_temp->email_domain, c_temp->number);
}

/* Hash_Table_Node** + char*[] ---> void; 
   Prints the contact given in the input. When it does not exist prints an error. */
void find_contact(Hash_Table_Node** Hash, char* input_elements[]) {
    int x = 0, hash_index = hash(input_elements[x], HASHS_SIZE);
    Hash_Table_Node* node_to_search = find_node_in_hash(Hash, hash_index, input_elements[x]);  /* Finding the node of the contact given in the input. */
    if (!node_to_search) {
        puts(NOCONTACT);
        return;
    }
    printf(WRITECONTACT, node_to_search->c->name, node_to_search->c->email_local, node_to_search->c->email_domain, node_to_search->c->number);
}

/* Hash_Table_Node** + Hash_Table_Node** + schedule* + char*[]; 
   Removes the contact in the input from the schedule and from both hashs. When it does not exist prints an error. */
void remove_contact(Hash_Table_Node** Hash_Names, Hash_Table_Node** Hash_Domains, schedule* s, char *input_elements[]) {
    int x = 0, domains_index, names_index = hash(input_elements[x], HASHS_SIZE);  /* Contact position in hash names. */
    Hash_Table_Node *node_to_removeN = find_node_in_hash(Hash_Names, names_index, input_elements[x]), *node_to_removeD; /* The possible node which contains the contact pointer. */
    contact *c_to_rem; /* Variable to store the contact to remove. */
    if (!node_to_removeN) {
        puts(NOCONTACT);
        return;
    }
    c_to_rem = node_to_removeN->c;
    domains_index = hash(c_to_rem->email_domain, HASHS_SIZE);                             /* Contact position in hash domains. */
    node_to_removeD = find_node_in_hash(Hash_Domains, domains_index, input_elements[x]);  /* The node to remove in hash domains. */

    remove_hash_node(Hash_Names, names_index, node_to_removeN); 
    remove_hash_node(Hash_Domains, domains_index, node_to_removeD);
    remove_c_in_schedule(s, c_to_rem);
}

/* Hash_Table_Node** + Hash_Table_Node** + char*[] ---> void;
   Changes both parts of the contact email given in the input and relocates the node in hash_domains. If it does not exist prints an error. */
void change_c_email(Hash_Table_Node** Hash_Names, Hash_Table_Node** Hash_Domains, char* input_elements[]) {
    /* Int x is used to go through the elements of the input, index names is the position of the contact in hash names. */
    int x = 0, old_index, new_index, index_names = hash(input_elements[x], HASHS_SIZE);
    Hash_Table_Node *node_to_change, *node_names = find_node_in_hash(Hash_Names, index_names, input_elements[x]);  /* Node where the contact may be. */
    contact* c_changed;     /* Where the changed contact is stored. */
    if (!node_names) {
        puts(NOCONTACT);
        return;
    }

    old_index = hash(node_names->c->email_domain, HASHS_SIZE);  /* Contact position in hash domains. */
    node_to_change = find_node_in_hash(Hash_Domains, old_index, input_elements[x++]); /* Contact node of hash domains. */

    node_to_change->c->email_local = (char*) realloc(node_to_change->c->email_local, sizeof(char) * (strlen(input_elements[x]) + 1));
    strcpy(node_to_change->c->email_local, input_elements[x++]);
    
    node_to_change->c->email_domain = (char*) realloc(node_to_change->c->email_domain, sizeof(char) * (strlen(input_elements[x]) + 1));
    strcpy(node_to_change->c->email_domain, input_elements[x]);

    c_changed = node_to_change->c;

    remove_hash_node(Hash_Domains, old_index, node_to_change);
    new_index = hash(input_elements[x], HASHS_SIZE);           /* New position for the changed contact in hash domains. */
    add_contact_in_hash(Hash_Domains, new_index, c_changed);
} 

/* Hash_Table_Node** + char*[] ---> void;
   Prints the number of occurences of the domain given in the input with a counter (count_domain). */
void count_domain_occ(Hash_Table_Node** Hash_Domains, char* input_elements[]) {
    int count_domain = 0, x = 0, index_domains = hash(input_elements[x], HASHS_SIZE); /* Position of the contacts with the given domain in the input. */
    Hash_Table_Node* node_temp;
    for (node_temp = Hash_Domains[index_domains]; node_temp; node_temp = node_temp->next) {
       if (!strcmp(node_temp->c->email_domain, input_elements[x]))
        count_domain++;
    }
    printf(DOMAIN, input_elements[x], count_domain); /* Int x is to represent the element of the input. */
}

int pref(int size, contact* c, char* n) {
    int count;
    for (count = *(c->name); size; *(c->name)++) {
        if (count = *(n)++) {
            size--;
            continue;
        }
        return 0;
    }
    return 1;
}

void count_contacts(char* input_elements[], schedule* s) {
    int c = strlen(input_elements[0]), count = 0;
    contact* aux;
    for (aux = s->head; aux; aux = aux->next) { 
            if (pref) 
                count++;
    } 
    printf("%d", count);
}
