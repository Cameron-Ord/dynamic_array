#include "../include/array.h"
#include <stdio.h>
int main(int argc, char **argv){
  Array *array = create_array(0, 0);
  printf("%s\n", array_last_error());
  destroy_array(array);
  return 0;
}
