#include "buffercircular.h"
void bc_init(bufferc_t *bc) {
    int i;
    bc->cantidad = 0;
    bc->inicio = 0;
    bc->fin = 0;
    for (i = 0; i < MAX_ITEMS; i++) {
        bc->data[i] = 0;
    }
    return;
}

bool bc_isEmpty(bufferc_t *bc) {
    return (bool)( bc->cantidad == 0);
}

bool bc_isFull(bufferc_t *bc) {
    return (bool) (bc->cantidad == MAX_ITEMS);
}

int bc_putItem(bufferc_t *bc, char dato) {
    if (bc_isFull(bc))
        return -1;

    bc->cantidad++;
    bc->data[bc->fin] = dato;
    bc->fin = (bc->fin + 1) % MAX_ITEMS;
    return 0;
}

int bc_getItem(bufferc_t *bc, char *dato) {
    if (bc_isEmpty(bc))
        return -1;

    *dato = bc->data[bc->inicio];
    bc->inicio = (bc->inicio + 1) % MAX_ITEMS;
    bc->cantidad--;
    return 0;
}