#include <stdbool.h>

#define MAX_ITEMS 10
typedef struct circularQueue_s {
    int inicio;
    int fin;
    int cantidad;
    char data[MAX_ITEMS];
} bufferc_t;

void initializeQueue(bufferc_t *bc);

bool isEmpty(bufferc_t *bc);

int putItem(bufferc_t *bc, char dato);

int getItem(bufferc_t *bc, char *dato);

void printQueue(bufferc_t *bc);