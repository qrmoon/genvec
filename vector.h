#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define VEC_MAKE(type) \
  typedef struct { \
    type *data; \
    size_t length; \
    size_t size; \
    bool auto_shrink; \
  } vec_##type; \
  \
  void vec_init_##type(vec_##type *v) { \
    v->data = NULL; \
    v->length = 0; \
    v->size = 0; \
  } \
  \
  void vec_free_##type(vec_##type *v) { \
    free(v->data); \
    v->data = NULL; \
    v->length = 0; \
    v->size = 0; \
    v->auto_shrink = false; \
  } \
  \
  void vec_shrink_##type(vec_##type *v) { \
    if (v->size == 0) return; \
    v->data = realloc(v->data, v->length*sizeof(type)); \
    v->size = v->length; \
  } \
  \
  void vec_push_##type(vec_##type *v, type val) { \
    if (v->data == NULL) { \
      v->data = malloc(sizeof(type)); \
      v->data[v->length] = val; \
    } else if (v->length < v->size) { \
      v->data[v->length] = val; \
    } else { \
      v->data = realloc(v->data, (v->size+1)*sizeof(type)); \
      v->data[v->length] = val; \
    } \
    v->length++; \
    v->size++; \
  } \
  \
  void vec_pop_##type(vec_##type *v) { \
    if (v->length > 0) \
      v->length--; \
    if (v->auto_shrink) vec_shrink_##type(v); \
  } \
  \
  void vec_remove_##type(vec_##type *v, size_t index) { \
    if (index == v->length-1) vec_pop_##type(v); \
    else if (index < v->length-1) { \
      memmove(v->data+index, v->data+index+1, (v->length-index)*sizeof(type)); \
      v->length--; \
    } \
    if (v->auto_shrink) vec_shrink_##type(v); \
  } \
  \
  void vec_insert_##type(vec_##type *v, size_t index, type val) { \
    if (index >= v->length-1) { \
      vec_push_##type(v, val); \
      return; \
    } \
    if (v->length == v->size) \
      v->data = realloc(v->data, ++v->size); \
    memmove(v->data+index+1, v->data+index, (v->length-index)*sizeof(type)); \
    v->data[index] = val; \
    v->length++; \
  } \

#endif
