/**********************************************************************************************************/
 /* File:  ReadInputP2.c */
 /* Made by:  Andre Luis Raposo Marinho, Number 93687. */
 /* Description: Function used to split the input. */
/**********************************************************************************************************/

/**************************************/
/*   LIBRARIES AND OTHER FILES USED   */
/**************************************/

#include "ReadInputP2.h" /* Functions used here are declared in this file. */
#include <stdlib.h>
#include <string.h>

#define MAXELEMENTS 4 /* Maximum number of fragments in which the input can be split. */

/* char[] + char*[] ---> void;
   Splits strings in buffer in chars " " and "@", '\n' is replaced with '\0'; each fragment goes to a pointer in *input_elements[]. */
void split_input(char buffer[], char *input_elements[]) {
    char *fragment = strtok(buffer, " @\n");
    int x;
    for (x = 0; x < MAXELEMENTS; x++) {
        if (!fragment) {
            input_elements[x] = NULL;  /* When an input fragment is NULL the pointer in elements is also NULL. */
            continue;
        }
        input_elements[x] = fragment;
        fragment = strtok(NULL, " @\n");
    }
}
