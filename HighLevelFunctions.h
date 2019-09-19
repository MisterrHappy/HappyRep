/**********************************************************************************************************/
 /* File: HighLevelFunctions.h */
 /* Made by:  Andre Luis Raposo Marinho, Number 93687. */
 /* Description: Declaration of the functions used in HighLevelFunctions.c. */
/**********************************************************************************************************/

#ifndef HIGHLEVELFUNCTIONS_H
#define HIGHLEVELFUNCTIONS_H

#include "Schedule.h"
#include "HashTable.h"

void add_contact(Hash_Table_Node** Hash_Names, Hash_Table_Node** Hash_Domains, schedule *s, char *input_elements[]);
void print_schedule(schedule* s);
void find_contact(Hash_Table_Node** Hash, char* input_elements[]);
void remove_contact(Hash_Table_Node** Hash_Names, Hash_Table_Node** Hash_Domains, schedule* s, char *input_elements[]);
void change_c_email(Hash_Table_Node** Hash_Names, Hash_Table_Node** Hash_Domains, char* input_elements[]);
void count_domain_occ(Hash_Table_Node** Hash_Domains, char* input_elements[]);
int pref(int size, contact* c, char* n);
void count_contacts(char* input_elements[], schedule* s);

#endif