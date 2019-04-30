#include <stdbool.h>

#define MAX_ITEMS 100
typedef struct circularQueue_s {
    int inicio;
    int fin;
    int cantidad;
    char data[MAX_ITEMS];
} bufferc_t;

void bc_init(bufferc_t *bc);

bool bc_isEmpty(bufferc_t *bc);
bool bc_isFull(bufferc_t *bc);

int bc_put(bufferc_t *bc, char dato);

int bc_get(bufferc_t *bc, char *dato);
int bc_peekLast(bufferc_t *bc, char *dato);
int bc_peekFirst(bufferc_t *bc, char *dato);
