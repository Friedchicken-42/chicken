#include <stdio.h>

#include "chicken.h"

int main(int argc, char *argv[]) {
    char *filename;
    char *input;

    switch (argc) {
        case 2:
            filename = argv[1];
            input = "";
            break;
        case 3:
            filename = argv[1];
            input = argv[2];
            break;
        default:
            printf("Usage: chicken <filename> <input>\n");
            return 1;
    }

    VM *vm = vm_create();
    stack_push_int(vm->stack, 0);
    stack_push_str(vm->stack, input);
    vm_push_code(vm, filename);
    stack_push_int(vm->stack, 0);
    stack_push_int(vm->stack, 0);
    stack_print(vm->stack);
    vm_execute(vm);
    data_print(stack_pop(vm->stack));
    vm_destroy(vm);

    return 0;
}