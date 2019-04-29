


typedef struct {
    void(*fun_estado)(void);
    bool primeraVez;

} estado_t;




void mef_init(void);

void mef_process();

void mef_cambiar(void(*fun)(void));

