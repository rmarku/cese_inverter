
typedef struct{
    uint8_t cant_mensajes;
    char *mensaje[];
} msg_t;

/** @brief Configura el terminal serial */
void terminal_configurar();

/**
 * @brief Escribe en la terminal
 * 
 * @param cadena Cadena de caracteres que se va a escribir
 */
void terminal_escribir(const char * cadena);

void terminal_escribirMsg(const msg_t *msg);


void terminal_process();
uint8_t terminal_getCommand(char *data);
