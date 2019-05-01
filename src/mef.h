/**
 * @file mef.h
 * @author Ricardo Martín Marcucci
 * @brief Logica de la maquina de estados implementada con punteros a funciones
 *
 * @copyright Copyright (c) 2019
 *
 * @defgroup mef Maquina de estado del proyecto
 * @ingroup TPF
 * @{
 */

#ifndef __MEF_H
#define __MEF_H

#ifdef __cplusplus
extern "C" {
#endif
/* ----------------------------------------------------------------------------------------------------------------
 * Funciones Publicas
 * ---------------------------------------------------------------------------------------------------------------- */

void mef_init(void);

void mef_process();

#ifdef __cplusplus
}
#endif
#endif /* __MEF_H */

/** @} Doxygen module end*/