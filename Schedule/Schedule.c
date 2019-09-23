/**********************************************************************************************************/
 /* File: Schedule.c */
 /* Made by:  Andre Luis Raposo Marinho, Number 93687. */
 /* Description: Functions to create, manage and destroy the contacts in the schedule and also do make and
    erase the schedule. */
/**********************************************************************************************************/

/**************************************/
/*   LIBRARIES AND OTHER FILES USED   */
/**************************************/

#include "Schedule.h"  /* Functions and structures used here are declared in this file. */
#include <stdlib.h>
#include <string.h>

/***********************************************************************************/
/*           ERRORS AND CONTACT PRINT STRUCTURE USED DURING PROGRAM                */
/***********************************************************************************/

#define OVERCONTACT "Nome existente."  /* Error used when the contact to add is already in schedule. */
#define NOCONTACT "Nome inexistente."  /* Error used when the contact to remove, to find or tho change does not exist. */
#define WRITECONTACT "%s %s@%s %s\n"   /* Contact print structure. */
#define DOMAIN "%s:%d\n"               /* Domain print structure. */

#define HASHS_SIZE 1001                /* Number of slots in the hash. */

/* void ---> schedule*;
   Creates and returns a schedule, starting head and last pointers with NULL (function given in class). */
schedule* create_schedule() {
    schedule *s = (schedule*) malloc(sizeof(schedule));
    s->head = s->last = NULL;
    return s;
}

/* char*[] ---> contact*;
   Creates and returns a new_contact with the information in *input_elements[] allocating memory according to the length of the string copied. */
contact* new_contact(char* input_elements[]) {
    int x = 0;                                            /* Int to go through all the elements of the input. */
    contact *new_c = (contact*) malloc(sizeof(contact));  /* Contact created. */

    new_c->name = (char*) malloc(sizeof(char) * (strlen(input_elements[x]) + 1));
    strcpy(new_c->name, input_elements[x++]);

    new_c->email_local = (char*) malloc(sizeof(char) * (strlen(input_elements[x]) + 1));
    strcpy(new_c->email_local, input_elements[x++]);

    new_c->email_domain = (char*) malloc(sizeof(char) * (strlen(input_elements[x]) + 1));
    strcpy(new_c->email_domain, input_elements[x++]);

    new_c->number = (char*) malloc(sizeof(char) * (strlen(input_elements[x]) + 1));
    strcpy(new_c->number, input_elements[x++]);
    return new_c;
}

/* contact* ---> void;
   Frees all memory associated to a contact. */
void free_contact(contact* c) {
    free(c->name);
    free(c->email_local);
    free(c->email_domain);
    free(c->number);
    free(c);
}

/* schedule* ---> void;
   Frees all memory associated to a schedule and respective contacts (function given in class). */
void erase_schedule(schedule* s) {
    while (s->head) {
        contact* c_temp = s->head->next;
        free_contact(s->head);
        s->head = c_temp;
    }
    free(s);
}

/* schedule* + char*[] --->  void; 
   Creates and adds the contact given in the input in the last position of schedule s (function given in class). */
void add_contact_last_schedule(schedule* s, contact* c_to_add) {
    c_to_add->next = NULL;
    c_to_add->previous = s->last;   
    
    if (!s->head)
        s->head = c_to_add;
    if (s->last)
        s->last->next = c_to_add;
    s->last = c_to_add;
}

/* schedule* + char*[] ---> void;
   Removes the contact given in the input from the schedule (function given in class). */
void remove_c_in_schedule(schedule* s, contact* c) {
    if (!c->previous)
        s->head = c->next;
    else
        c->previous->next = c->next;
    if (!c->next)
        s->last = c->previous;
    else
        c->next->previous = c->previous;
    free_contact(c);
}
