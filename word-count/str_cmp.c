#include "str_cmp.h"

/**
 * @brief Compare two strings
 *
 * @param s1
 * @param s2
 * @return int
 */
int my_str_cmp(const char *s1, const char *s2) {
  int i = 0;
  while (s1[i] == s2[i]) {
    if (s1[i] == '\0' || s2[i] == '\0') {
      break;
    }
    i++;
  }

  if (s1[i] == '\0' && s2[i] == '\0') {
    return 0;
  }
  else {
    return 1;
  }
}
