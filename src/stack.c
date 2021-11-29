#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

Stack *stack_create(int size) {
    Stack *stack = malloc(sizeof(Stack));
    stack->data = malloc(sizeof(Data) * size);
    stack->length = 0;
    stack->size = size;
    return stack;
}

void stack_destroy(Stack *stack) {
    free(stack->data);
    free(stack);
}

void stack_push(Stack *stack, Data data) {
    if (stack->length == stack->size) {
        stack->size *= 2;
        stack->data = realloc(stack->data, sizeof(Data) * stack->size);
    }
    stack->data[stack->length++] = data;
}

void stack_push_int(Stack *stack, int i) {
    ;
    stack_push(stack, data_int(i));
}

void stack_push_str(Stack *stack, char *s) {
    ;
    stack_push(stack, data_str(s));
}

Data stack_pop(Stack *stack) {
    if (stack->length == 0) {
        Data data;
        data.type = INT;
        data.data.i = 0;
        return data;
    }
    return stack->data[--stack->length];
}

void stack_set(Stack *stack, int i, Data data) {
    if (i >= stack->size) {
        stack->size = i + 1;
        stack->data = realloc(stack->data, sizeof(Data) * stack->size);
    }
    stack->data[i] = data;
}

int stack_get_int(Stack *stack, int i) {
    ;
    return stack->data[i].data.i;
}

void stack_print(Stack *stack) {
    for (int i = 0; i < stack->length; i++) {
        data_print(stack->data[i]);
    }
    printf("\n");
}