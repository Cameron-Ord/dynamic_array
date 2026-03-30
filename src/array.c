#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/array.h"

static void array_set_err(const char *str);
static size_t array_str_len(const char *str);
static Array *array_push(Array *self, void* data);
static Array *array_insert(Array *self, size_t index, void *data);
static Array *array_delete(Array *self, size_t index);
static Array *array_fill(Array *self, void *data);
static Array *array_resize(Array *self, size_t capacity);
static void array_free(void *ptr);
static void *array_malloc(size_t bytes);
static void *array_realloc(size_t bytes, void **data);
static void *array_calloc(size_t bytes, size_t nmemb);
static size_t capacity_to_nmemb(size_t capacity, size_t memb_bytes);

enum SIZES { ERR_BUF_MAX = 1024 };
char errbuf[ERR_BUF_MAX] = {0};
const char NULLCHAR = '\0';

static size_t array_str_len(const char *str){
  size_t count = 0;
  while((str && *str != NULLCHAR) && count < ERR_BUF_MAX){
    count++, str++;
  }
  return count;
}

static void array_set_err(const char *str){
  memcpy(errbuf, str, array_str_len(str));
}

static void array_free(void *ptr){
  if(ptr)
    free(ptr);
}

static void *array_malloc(size_t bytes) {
  void *mem = malloc(bytes);
  if(!mem){
    array_set_err("Failed to allocate!");
    return NULL;
  }
  return mem;
}

static void *array_realloc(size_t bytes, void **data){
  void *tmp = realloc(*data, bytes);
  if(!tmp){
    array_set_err("Failed to reallocate!");
    return NULL;
  }
  *data = tmp;
  return data;
}

static void *array_calloc(size_t bytes, size_t nmemb){
  void *mem = calloc(nmemb, bytes);
  if(!mem){
    array_set_err("Failed to allocate!");
    return NULL;
  }
  return mem;
}

static size_t capacity_to_nmemb(size_t capacity, size_t memb_bytes){
  return capacity / memb_bytes;
}

static Array *array_insert(Array *self, size_t index, void * data){

}

static Array *array_delete(Array *self, size_t index){

}

static Array *array_push(Array *self, void *data){
  if(self->elements >= capacity_to_nmemb(self->capacity, self->memb_bytes)){
    self->capacity = self->capacity * 2;
    self->data = array_realloc(self->capacity, &self->data);
    if(!self->data){
      destroy_array(self);
      return NULL;
    }
  }
  const size_t byte_offset = self->elements * self->memb_bytes;
  memcpy((char*)self->data + byte_offset, data, self->memb_bytes);
  self->elements++;
  return self;
}

static Array *array_fill(Array *self, void *data){

}

static Array *array_resize(Array *self, size_t capacity){

}

// === NON STATIC FUNCS === 
const char *array_last_error(void){
  return errbuf;
}

Array *create_array(size_t nmemb, size_t memb_bytes){
  if(nmemb == 0 || memb_bytes == 0){
    // Set error
    array_set_err("Passed invalid size parameters!");
    return NULL;
  }

  Array *container = array_malloc(sizeof(Array));
  if(!container){
    return NULL;
  }

  container->push = array_push;
  container->delete = array_delete;
  container->insert = array_insert;
  container->fill = array_fill;
  container->resize = array_resize;
  
  container->data = array_calloc(memb_bytes, nmemb);
  if(!container->data){
    array_free(container);
    return NULL;
  }


  container->memb_bytes = memb_bytes;
  container->elements = 0;
  container->capacity = nmemb * memb_bytes;
  
  return container;
}

void destroy_array(Array *array){
  if(array && array->data){
    array_free(array->data);
    array->data = NULL;
  }
  if(array){
    array_free(array);
    array = NULL;
  }
}
