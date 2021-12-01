#include "vector_string.h"
#include "str_cmp.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
/////////////////////////////////////////

*/
/**
 * @brief Memory allocate a vector string so that we can start inserting entries
 * into it.
 *
 */
vector_string *vector_string_allocate() {
  vector_string* vs = (vector_string*) malloc(sizeof(vector_string));
  vs->head = NULL;
  vs->tail = NULL;
  return vs;
}

/**
 * @brief Search the vector string pointed to by vs and return true if the
 * vs_entry.value == key, else return false.
 * TODO:
 * @param vs - Pointer to vector_string datastructure
 * @param key - Pointer to string to search for
 * @return * Find*
 */
bool vector_string_find(vector_string *vs, char *key) { 
  vs_entry_t* temp;
  temp = vs->head;
  while (temp != NULL) {
    if (my_str_cmp(temp->value, key ) == 0) {
      return true;
    }
    temp = temp->next;
  }
  return false;
}

/**
 * @brief TODO: Insert the string pointed to by key into the vector string.
 *  char* is externally allocated. You do not have to allocate internally
 *
 * @param vs - Pointer to vector_string datastructure
 * @param key - Pointer to string to search for
 * @return * Find*
 */
void vector_string_insert(vector_string *vs, char *key) {
  int count = 0;
  while (key[count] != '\0') {
    count++;
  }
  vs_entry_t* node;
  node = (vs_entry_t*)malloc(sizeof(vs_entry_t));
  node->value = malloc(sizeof(char) *(count + 1));
  int i;
  for(i = 0; key[i] != '\0'; i++) {
    node->value[i] = key[i];
  }
  node->value[i] = '\0';
  node->next = NULL;

  if(vs->head == NULL) {
    vs->head = node;
    vs->tail = node;
  }
  else {
    vs->tail->next = node;
    vs->tail = vs->tail->next;
  }		
}

/**
 * @brief Remove all entries and cleanup vector string
 * TODO: Remove all entries. Remember head and tail are pointers.
 * Remember to remove vs as well; not just entries. or you will have memory
 * leaks.
 * @param vs: Pointer to vector_string struct
 */
void vector_string_deallocate(vector_string *vs) {
  vs_entry_t* temp;
  while (vs->head != NULL) {
    temp = vs->head;
    vs->head = vs->head->next;
    free(temp->value);
    free(temp); 
  }
  free(vs);
}

/**
 * @brief Print all value in each entry of the vector string, in the following
 * format. In this case hello and world are the unique words in the file.
 * 1. hello
 * 2. world
 * @param vs
 */
void vector_string_print(vector_string *vs) {
  vs_entry_t * node;
  if(vs->head == NULL) {
    return;
  }
  node = vs->head;
  int count = 1;
  while(node != NULL) {
    printf("%d. %s\n",count, node->value);
    node = node->next;
    count++;
  }
}
