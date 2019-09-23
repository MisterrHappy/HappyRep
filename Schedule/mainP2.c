/**********************************************************************************************************/
 /* File: mainP2.c */
 /* Made by: Andre Luis Raposo Marinho, Number 93687. */
 /* Description: Main function of a program developed to book and manage contacts with Schedule.c file 
    and reading input with ReadInputP2.c file. */
/**********************************************************************************************************/

/**************************************/
/*   LIBRARIES AND OTHER FILES USED   */
/**************************************/

#include <stdio.h>
#include <stdlib.h>
#include "ReadInputP2.h"
#include "Schedule.h"
#include "HashTable.h"
#include "HighLevelFunctions.h"

/********************************************************/
/*            CONSTANTS AND LOOP LIMITS USED            */
/********************************************************/

#define MAXNAME 1024   /* The maximum length of a contact name. */
#define MAXEMAIL 512   /* The maximum length of a contact e-mail (local + domain). */
#define MAXNUMBER 64   /* The maximum length of a contact number. */
#define MAXSPACES 2    /* Number of spaces that the input may have between strings. */
#define MAXELEMENTS 4  /* Maximum number of fragments in which the input can be split. */
#define MAXINPUT (MAXNAME + MAXEMAIL + MAXNUMBER + MAXSPACES) /* The sum of all parts of the input. */
#define HASHS_SIZE 1001   /* Number of slots in the hash. */

int main() { 
    char *input_elements[MAXELEMENTS], buffer[MAXINPUT];  /* Array of pointers to store the fragments of the input in the buffer. */  
    schedule *new_s = create_schedule();    /* Schedule to store the contacts in order of insertion. */
    
    /* Hash tables to perform quick searchs of contacts, one organized by contact names (hash_names) and other by email domains (hash_domains). */
    Hash_Table_Node **hash_names = init_hashtable(HASHS_SIZE), **hash_domains = init_hashtable(HASHS_SIZE); 
    while (1) {
        int command = getchar();
        if (getchar() != '\n') {
            fgets(buffer, MAXINPUT, stdin);
            split_input(buffer, input_elements);   /* In commands 'l' and 'x' there is no input. */
        }
        switch (command) {
            case 'a':
                add_contact(hash_names, hash_domains, new_s, input_elements);
                break;

            case 'l':
                print_schedule(new_s);
                break;

            case 'p':
                find_contact(hash_names, input_elements);
                break;

            case 'r':
                remove_contact(hash_names, hash_domains, new_s, input_elements);
                break;

            case 'e':
                change_c_email(hash_names, hash_domains, input_elements); 
                break;

            case 'c':
                count_domain_occ(hash_domains, input_elements); 
                break;

            case 'P':
                count_contacts(input_elements, new_s);
                break;

            case 'x':
                close_hashtable(hash_names, HASHS_SIZE);
                close_hashtable(hash_domains, HASHS_SIZE);
                erase_schedule(new_s);
                exit(0);
        }
    }
    return 0;
}
