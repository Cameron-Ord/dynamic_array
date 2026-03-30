#include "../include/array.h"
#include <stdio.h>
int main(int argc, char **argv){
  Array *array = create_array(1024, sizeof(int));
  int value = 33; 
  array->push(array, &value)->push(array, &value);
  for(size_t i = 0; i < array->elements; i++){
    int *data = array->data;
    printf("%d\n", data[i]);
  }
  return 0;
}
