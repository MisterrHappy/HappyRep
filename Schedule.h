/**********************************************************************************************************/
 /* File: Schedule.h */
 /* Made by:  Andre Luis Raposo Marinho, Number 93687. */
 /* Description: Declaration of the functions and structs Contact and schedule used in Schedule.c. */
/**********************************************************************************************************/

#ifndef SCHEDULE_H
#define SCHEDULE_H

typedef struct Contact {
    struct Contact * previous, * next;
    char * name, * email_local, * email_domain, * number;
} contact;

typedef struct Contact_List {
    contact * head, * last;
} schedule;

schedule* create_schedule();
contact* new_contact(char* input_elements[]);
void free_contact(contact* c);
void erase_schedule(schedule* s);
void add_contact_last_schedule(schedule* s, contact* c_to_add);
void remove_c_in_schedule(schedule* s, contact* c);

#endif