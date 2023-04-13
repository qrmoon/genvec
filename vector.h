#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define VEC_MAKE_SUFFIX(type, suffix) \
  typedef struct { \
    type *data; \
    size_t length; \
    size_t size; \
    bool auto_shrink; \
  } vec_##suffix; \
  \
  void vec_init_##suffix(vec_##suffix *v) { \
    v->data = NULL; \
    v->length = 0; \
    v->size = 0; \
  } \
  \
  void vec_free_##suffix(vec_##suffix *v) { \
    free(v->data); \
    v->data = NULL; \
    v->length = 0; \
    v->size = 0; \
    v->auto_shrink = false; \
  } \
  \
  void vec_shrink_##suffix(vec_##suffix *v) { \
    if (v->size == 0) return; \
    v->data = realloc(v->data, v->length*sizeof(type)); \
    v->size = v->length; \
  } \
  \
  void vec_push_##suffix(vec_##suffix *v, type val) { \
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
  void vec_pop_##suffix(vec_##suffix *v) { \
    if (v->length > 0) \
      v->length--; \
    if (v->auto_shrink) vec_shrink_##suffix(v); \
  } \
  \
  void vec_remove_##suffix(vec_##suffix *v, size_t index) { \
    if (index == v->length-1) vec_pop_##suffix(v); \
    else if (index < v->length-1) { \
      memmove(v->data+index, v->data+index+1, (v->length-index)*sizeof(type)); \
      v->length--; \
    } \
    if (v->auto_shrink) vec_shrink_##suffix(v); \
  } \
  \
  void vec_insert_##suffix(vec_##suffix *v, size_t index, type val) { \
    if (index >= v->length-1) { \
      vec_push_##suffix(v, val); \
      return; \
    } \
    if (v->length == v->size) \
      v->data = realloc(v->data, ++v->size); \
    memmove(v->data+index+1, v->data+index, (v->length-index)*sizeof(type)); \
    v->data[index] = val; \
    v->length++; \
  } \

#define VEC_MAKE(type) VEC_MAKE_SUFFIX(type, type)

#endif
