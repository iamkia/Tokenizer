#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <table_string.h>
#include <vector_char.h>
int main(int argc, char **argv) {
  char *source = NULL;

  if (argc != 2) {
    printf("./grade_tokenize.bin [FILE PATH]");
    exit(1);
  }
  /**
   * @brief Read file into source.
   * source is a character array with file contents
   * It is null terminated
   */
  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL) { /* Error */
    printf("Error reading file");
    exit(1);
  }
  if (fp != NULL) {
    /* Go to the end of the file. */
    if (fseek(fp, 0L, SEEK_END) == 0) {
      /* Get the size of the file. */
      long bufsize = ftell(fp);
      if (bufsize == -1) { /* Error */
        printf("Error reading file");
      }
      /* Allocate our buffer to that size. */
      source = malloc(sizeof(char) * (bufsize + 1));
      /* Go back to the start of the file. */
      if (fseek(fp, 0L, SEEK_SET) != 0) { /* Error */
      }
      /* Read the entire file into memory. */
      size_t newLen = fread(source, sizeof(char), bufsize, fp);
      if (ferror(fp) != 0) {
        printf("Error reading file");
      } else {
        source[newLen++] = '\0'; /* Just to be safe. */
      }
    }
  }
  fclose(fp);

  /** Start processing file and separate into words */
  // TODO: Write wordcount

  table_string *ts = table_string_allocate(8);
  
  for (int i = 0; source[i] != '\0'; i++) {

    vector_char_t* word = vector_char_allocate();
    
    if ( (source[i] > 47 && source[i] < 58) || 
    (source[i] > 96 && source[i] < 123) || 
    (source[i] > 64 && source[i] < 91) ) {
      while ( (source[i] > 47 && source[i] < 58) || 
      (source[i] > 96 && source[i] < 123) || 
      (source[i] > 64 && source[i] < 91) ) {
        vector_char_add(word, source[i]);
        if (source [i + 1] == '\0') {
          break;
        }
        i++; 
      } 
    }

    if (word->data != NULL) {
      vector_char_add(word, '\0');
      table_string_insert_or_add(ts, word->data);
    }

    vector_char_delete(word);

  }

  table_string_print(ts);
  table_string_deallocate(ts);

  free(source);

  return 0;
}
