#ifndef ARRAY_H
#define ARRAY_H
#include <stddef.h>
typedef struct Array Array;

struct Array {
  void *data;
  size_t memb_bytes;
  size_t elements;
  size_t capacity;

  // Push an element from the last element
  Array *(*push)(Array *, void *);
  // Delete an element at given index
  Array *(*delete)(Array *, size_t);
  // Insert an element at given index
  Array *(*insert)(Array *, size_t, void*);
  // Fill to capacity with given value
  Array *(*fill)(Array *, void*);
  // Resize the capacity of the array
  Array *(*resize)(Array *, size_t);
};

const char *array_last_error(void);
Array *create_array(size_t nmemb, size_t memb_bytes);
void destroy_array(Array *array);

#endif
