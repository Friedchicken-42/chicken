#ifndef CHICKEN_H
#define CHICKEN_H

#include <stdio.h>

#include "stack.h"

typedef struct {
    Stack *stack;
    int ip;
} VM;

enum {
    AXE,
    CHICKEN,
    ADD,
    FOX,
    ROOSTER,
    COMPARE,
    PICK,
    PECK,
    FR,
    BBQ,
} Commands;

void vm_read_chicken(FILE *f);
int vm_read_op(VM *vm);
void vm_push_code(VM *vm, char *filename);
void vm_command_push(VM *vm, int command);
void vm_command_add(VM *vm);
void vm_command_sub(VM *vm);
void vm_command_mux(VM *vm);
void vm_command_cmp(VM *vm);
void vm_command_pick(VM *vm);
void vm_command_peck(VM *vm);
void vm_command_fr(VM *vm);
void vm_command_bbq(VM *vm);
int vm_step(VM *vm);
void vm_execute(VM *vm);
VM *vm_create();
void vm_destroy(VM *vm);

#endif