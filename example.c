#include <stdio.h>
#include "vector.h"

VEC_MAKE(int)

int main() {
  vec_int v;
  vec_init_int(&v);
  v.auto_shrink = true;

  vec_push_int(&v, 5);
  vec_push_int(&v, 8);
  vec_push_int(&v, 2);

  vec_remove_int(&v, 1);
  vec_insert_int(&v, 0, 123);

  vec_push_int(&v, 314);
  vec_push_int(&v, 73);

  vec_pop_int(&v);

  for (size_t i = 0; i < v.length; i++) {
    printf("%d ", v.data[i]);
  }
  putchar('\n');

  vec_free_int(&v);

  return 0;
}
