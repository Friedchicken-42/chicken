#include "chicken.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void vm_read_chicken(FILE *f) {
    if (!(fgetc(f) == 'h' && fgetc(f) == 'i' && fgetc(f) == 'c' && fgetc(f) == 'k' && fgetc(f) == 'e' && fgetc(f) == 'n')) {
        printf("error: not a chicken\n");
        exit(1);
    };
}

int vm_read_op(VM *vm) {
    int command = stack_get_int(vm->stack, vm->ip);
    vm->ip++;
    return command;
}

void vm_push_code(VM *vm, char *filename) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("file not found\n");
        return;
    }

    int count = 0;

    while (1) {
        char c = fgetc(f);
        if (c == EOF) {
            stack_push_int(vm->stack, count);
            break;
        } else if (c == '\n') {
            stack_push_int(vm->stack, count);
            count = 0;
        } else if (c == ' ') {
            ;
        } else if (c == 'c') {
            vm_read_chicken(f);
            count++;
        } else {
            printf("unknow character: %c \n", c);
        }
    }
}

void vm_command_push(VM *vm, int command) {
    int number = command - 10;
    stack_push_int(vm->stack, number);
}

void vm_command_add(VM *vm) {
    Data d1 = stack_pop(vm->stack);
    Data d2 = stack_pop(vm->stack);
    if (d1.type == INT && d2.type == INT) {
        stack_push_int(vm->stack, d1.data.i + d2.data.i);
    } else if (d1.type == STRING && d2.type == STRING) {
        char *s1 = d1.data.s;
        char *s2 = d2.data.s;
        int length = strlen(s1) + strlen(s2) + 1;
        char *s = malloc(length);
        strcpy(s, s2);
        strcpy(s + strlen(s2), s1);
        stack_push_str(vm->stack, s);
    } else {
        printf("error: add\n");
        exit(1);
    }
}

void vm_command_sub(VM *vm) {
    Data d1 = stack_pop(vm->stack);
    Data d2 = stack_pop(vm->stack);
    if (d1.type == INT && d2.type == INT) {
        stack_push_int(vm->stack, d2.data.i - d1.data.i);
    } else {
        printf("error: sub\n");
        exit(1);
    }
}

void vm_command_mux(VM *vm) {
    Data d1 = stack_pop(vm->stack);
    Data d2 = stack_pop(vm->stack);
    if (d1.type == INT && d2.type == INT) {
        stack_push_int(vm->stack, d1.data.i * d2.data.i);
    } else {
        printf("error: mux\n");
        exit(1);
    }
}

void vm_command_cmp(VM *vm) {
    Data d1 = stack_pop(vm->stack);
    Data d2 = stack_pop(vm->stack);
    if (d1.type == INT && d2.type == INT) {
        if (d1.data.i == d2.data.i) {
            stack_push_int(vm->stack, 1);
        } else {
            stack_push_int(vm->stack, 0);
        }
    } else if (d1.type == STRING && d2.type == STRING) {
        stack_push_int(vm->stack, strcmp(d1.data.s, d2.data.s) == 0 ? 1 : 0);
    } else {
        stack_push_int(vm->stack, 0);
    }
}

void vm_command_pick(VM *vm) {
    int source = vm_read_op(vm);
    int index = stack_pop(vm->stack).data.i;

    if (source == 0) {
        stack_push(vm->stack, vm->stack->data[index]);
    } else if (source == 1) {
        stack_push(vm->stack, vm->stack->data[1]);
    } else {
        printf("error: pick\n");
        exit(1);
    }
}

void vm_command_peck(VM *vm) {
    int addr = stack_pop(vm->stack).data.i;
    Data d = stack_pop(vm->stack);
    stack_set(vm->stack, addr, d);
}

void vm_command_fr(VM *vm) {
    int offset = stack_pop(vm->stack).data.i;
    Data d = stack_pop(vm->stack);
    if (data_is_truthy(d)) {
        vm->ip += offset;
    }
}

void vm_command_bbq(VM *vm) {
    int data = stack_pop(vm->stack).data.i;
    char *s = malloc(2);
    sprintf(s, "%c", data);
    stack_push_str(vm->stack, s);
}

int vm_step(VM *vm) {
    int command = vm_read_op(vm);
    switch (command) {
        case AXE:
            return 1;
        case CHICKEN:
            stack_push_str(vm->stack, "chicken");
            break;
        case ADD:
            vm_command_add(vm);
            break;
        case FOX:
            vm_command_sub(vm);
            break;
        case ROOSTER:
            vm_command_mux(vm);
            break;
        case COMPARE:
            vm_command_cmp(vm);
            break;
        case PICK:
            vm_command_pick(vm);
            break;
        case PECK:
            vm_command_peck(vm);
            break;
        case FR:
            vm_command_fr(vm);
            break;
        case BBQ:
            vm_command_bbq(vm);
            break;
        default:
            vm_command_push(vm, command);
            break;
    }
    return 0;
}

void vm_execute(VM *vm) {
    while (1) {
        int status = vm_step(vm);

        if (status != 0) {
            return;
        }
    }
}

VM *vm_create() {
    VM *vm = malloc(sizeof(VM));
    vm->stack = stack_create(64);
    vm->ip = 2;
    return vm;
}

void vm_destroy(VM *vm) {
    stack_destroy(vm->stack);
    free(vm);
}