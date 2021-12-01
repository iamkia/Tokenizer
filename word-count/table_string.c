#include "table_string.h"
#include "str_cmp.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUCKETS

// Hash a character array to integer value between 0 and buckets-1.
// See here for more details: https://theartincode.stanis.me/008-djb2/
unsigned int djb2_word_to_bucket(char *word, int buckets) {
  if (!word) {
    printf("Invoked with null string");
    exit(EXIT_FAILURE);
  }
  unsigned long hash = 5381;
  uint32_t i;

  for (i = 0; i < strlen(word); i++)
    hash = ((hash << 5) + hash) + word[i];

  return hash & (buckets - 1);
}

/**
 * @brief Instantiate a table string
 *
 * @param buckets
 * @return table_string*
 */
table_string *table_string_allocate(unsigned int buckets) {
  table_string* ts = (table_string*) malloc(sizeof(table_string));
  ts->buckets = buckets;
  ts->heads = (vs_entry_t**)calloc(ts->buckets, sizeof(vs_entry_t*));
  for (int i = 0; i <ts->buckets; i++) {
    ts->heads[i] = NULL;
  }
  return ts;
}

/**
 * @brief Insert the string pointed to by word into the table string.
 *   If word is already found increment count.
 *   If word is not found insert at the end of the corresponding bucket
 * @param ts - Pointer to table_string datastructure
 * @param word - Pointer to string to search for
 * @return * Find*
 */
void table_string_insert_or_add(table_string *ts, char *word) {
  // Find the bucket for word. djb2 will return a value between 0-buckets-1.
  // Rule: buckets can only be power of 2.
  int bucket = djb2_word_to_bucket(word, ts->buckets);

  int count = 0;
  while (word[count] != '\0') {
    count++;
  }
  vs_entry_t* node;
  node = (vs_entry_t*)malloc(sizeof(vs_entry_t));
  node->value = malloc(sizeof(char) *(count + 1));
  int i;
  for(i = 0; word[i] != '\0'; i++) {
    node->value[i] = word[i];
  }
  node->value[i] = '\0';
  node->next = NULL;
  node->count = 1;

  // Case head == NULL: bucket hasn't been initialized yet
  if (ts->heads[bucket] == NULL) {
    ts->heads[bucket] = node;
  }
  else {
    // Case word already in list, increment count
    vs_entry_t* temp;
    temp = ts->heads[bucket];
    while (temp != NULL) {
      if (my_str_cmp(temp->value, word) == 0) {
        temp->count += 1;
        free(node->value);
        free(node);
        return;
      }
      temp = temp->next;
    }

    // Case word not found, insert word and return.
    vs_entry_t* lastNode = ts->heads[bucket];
    while (lastNode->next != NULL) {
      lastNode = lastNode->next;
    }
    lastNode->next = node;
  }
}

void table_string_deallocate(table_string *ts) {
  for (int i = 0; i < ts->buckets; i++) {
    vs_entry_t* temp; 
    while (ts->heads[i]!= NULL) {
      temp = ts->heads[i];
      ts->heads[i] = ts->heads[i]->next;
      free(temp->value);
      free(temp);
    }
  }
  free(ts->heads); 
  free(ts);
}

void table_string_print(table_string *ts) {
  vs_entry_t * node;
  if(ts->heads == NULL) {
    return;
  }
  for (int i = 0; i < ts->buckets; i++) {
    node = ts->heads[i];
    while(node != NULL) {
      printf("%s:%d\n", node->value, node->count);
      node = node->next;
    }
  }
}
