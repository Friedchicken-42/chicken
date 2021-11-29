#ifndef STACK_H
#define STACK_H

#include "data.h"

typedef struct {
    Data *data;
    int length;
    int size;
} Stack;

Stack *stack_create(int size);
void stack_destroy(Stack *stack);
void stack_push(Stack *stack, Data d);
void stack_push_int(Stack *stack, int i);
void stack_push_str(Stack *stack, char *s);
Data stack_pop(Stack *stack);
void stack_set(Stack *stack, int i, Data data);
int stack_get_int(Stack *stack, int i);
void stack_print(Stack *stack);

#endif