
#include "buffercircular.h"
void initializeQueue(bufferc_t *bc) {
    int i;
    bc->cantidad = 0;
    bc->inicio = 0;
    bc->fin = 0;
    for (i = 0; i < MAX_ITEMS; i++) {
        bc->data[i] = 0;
    }
    return;
}

bool isEmpty(bufferc_t *bc) {  return (bool) bc->cantidad == 0; }

int bufferc_put(bufferc_t *bc, char dato) {
    if (bc->cantidad >= MAX_ITEMS)
        return -1;

    bc->cantidad++;
    bc->data[bc->fin] = dato;
    bc->fin = (bc->fin + 1) % MAX_ITEMS;
    return 0;
}

int bufferc_pop(bufferc_t *bc, char *dato) {
    if (isEmpty(bc))
        return -1;

    *dato = bc->data[bc->inicio];
    bc->inicio = (bc->inicio + 1) % MAX_ITEMS;
    bc->cantidad--;
    return 0;
}