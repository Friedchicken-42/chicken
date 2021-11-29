#include "data.h"

#include <stdio.h>

Data data_int(int i) {
    Data d;
    d.type = INT;
    d.data.i = i;
    return d;
}

Data data_str(char *s) {
    Data d;
    d.type = STRING;
    d.data.s = s;
    return d;
}

int data_is_truthy(Data d) {
    switch (d.type) {
        case INT:
            return d.data.i != 0;
        case STRING:
            return d.data.s[0] != '\0';
    }
    return 0;
}

void data_print(Data d) {
    if (d.type == INT) {
        printf("%d ", d.data.i);
    } else {
        printf("\"%s\" ", d.data.s);
    }
}