#include "vector_string.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define BUCKETS

vector_string *vector_string_allocate() {
  vector_string *vs = (vector_string *)malloc(sizeof(vector_string));
  vs->head = NULL;
  return vs;
}

vs_entry_t *vector_string_find(vector_string *vs, char *key) {
  if (vs->head == NULL)
    return NULL;
  vs_entry_t *cursor = vs->head;
  vs_entry_t *prev = cursor;
  while (cursor != NULL) {
    prev = cursor;
    cursor = cursor->next;
    if (strcmp(cursor, key) == 0) {
    }
  }
}

/**
 * @brief Insert the string pointed to by key into the vector string.
 *
 * @param vs - Pointer to vector_string datastructure
 * @param key - Pointer to string to search for
 * @return * Find*
 */
void vector_string_insert(vector_string *vs, char *key);
void vector_string_deallocate(vector_string *vs);
void vector_string_print()

    vector_string_entry_t *vector_string_constructor() {
  if (!size)
    return NULL;
  if (!hash_fn)
    return NULL;
  if (!key_len_fn)
    return NULL;
  vector_string *vector_string = malloc(sizeof(vector_string));
  if (!vector_string)
    return NULL;

  vector_string->key_len_fn = key_len_fn;
  vector_string->hash_fn = hash_fn;
  vector_string->size = size;

  vector_string->table = malloc(vector_string->size * sizeof(hash_bucket_t *));
  if (!vector_string->table) {
    free(vector_string);
    return NULL;
  }

  uint32_t i;

  for (i = 0; i < vector_string->size; i++)
    vector_string->table[i] = NULL;

  return vector_string;
}

void vector_string_destructor(vector_string *vector_string) {
  if (!vector_string)
    return;
  if (!vector_string->table)
    goto adt_free;

  uint32_t i;
  hash_bucket_t *cursor, *_cursor;

  for (i = 0; i < vector_string->size; i++) {
    cursor = vector_string->table[i];

    while (cursor) {
      _cursor = cursor->next;
      free(cursor);
      cursor = _cursor;
    }
  }

  free(vector_string->table);

adt_free:
  free(vector_string);
}

/* self adjusting hash-table strategy */
void *vector_string_find(vector_string *vector_string, void *key) {
  if (!vector_string)
    return NULL;
  uint32_t hash = vector_string->hash_fn(key, vector_string->key_len_fn(key)) &
                  (vector_string->size - 1);

  hash_bucket_t *bucket, *front, *_bucket;
  bucket = front = vector_string->table[hash];

  while (bucket && memcmp(bucket->key, key, vector_string->key_len_fn(key))) {
    _bucket = bucket;
    bucket = bucket->next;
  }

  if (!bucket)
    return NULL;

  if (bucket != front) {
    _bucket->next = bucket->next;
    bucket->next = front;
    vector_string->table[hash] = bucket;
  }

  return bucket->val;
}

void vector_string_insert(vector_string *vector_string, void *key, void *val) {
  if (!vector_string)
    return;
  uint32_t hash = vector_string->hash_fn(key, vector_string->key_len_fn(key)) &
                  (vector_string->size - 1);

  hash_bucket_t *bucket = vector_string->table[hash];

  vector_string->table[hash] = malloc(sizeof(hash_bucket_t));
  vector_string->table[hash]->next = bucket;
  vector_string->table[hash]->key = key;
  vector_string->table[hash]->val = val;
}

void vector_string_delete(vector_string *vector_string, void *key) {
  if (!vector_string)
    return;
  uint32_t hash = vector_string->hash_fn(key, vector_string->key_len_fn(key)) &
                  (vector_string->size - 1);

  hash_bucket_t *bucket = vector_string->table[hash];

  if (!bucket)
    return;

  if (!memcmp(bucket->key, key, vector_string->key_len_fn(key))) {
    vector_string->table[hash] = bucket->next;
    free(bucket);
    return;
  }

  while (bucket->next &&
         memcmp(bucket->next->key, key, vector_string->key_len_fn(key)))
    bucket = bucket->next;

  if (!bucket)
    return;

  hash_bucket_t *_bucket = bucket->next;
  bucket->next = _bucket->next;

  free(_bucket);
}