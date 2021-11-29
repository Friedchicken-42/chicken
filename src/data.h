#ifndef DATA_H
#define DATA_H

typedef struct {
    enum { INT, STRING } type;
    union {
        int i;
        char *s;
    } data;
} Data;

Data data_str(char *s);
Data data_int(int i);
int data_is_truthy(Data d);
void data_print(Data d);

#endif