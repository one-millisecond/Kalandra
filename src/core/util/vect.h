#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef VECT_H
#define VECT_H

typedef struct {
    void **data;
    size_t size;
    size_t capacity;
} Vector;

void vect_init(Vector *vec, size_t initial_capacity) {
    vec->data = malloc(sizeof(void *) * initial_capacity);
    vec->size = 0;
    vec->capacity = initial_capacity;
}
void vect_resize(Vector *vec, size_t new_capacity) {
    vec->data = realloc(vec->data, sizeof(void *) * new_capacity);
    vec->capacity = new_capacity;
}
void vect_push(Vector *vec, void *element) {
    if (vec->size == vec->capacity) {
        vect_resize(vec, vec->capacity * 2);
    }
    vec->data[vec->size] = element;
    vec->size++;
}
void *vect_get(Vector *vec, size_t index) {
    if (index >= vec->size) {
        return NULL;
    }
    return vec->data[index];
}
void vect_free(Vector *vec) {
    free(vec->data);
    vec->size = 0;
    vec->capacity = 0;
}

#endif