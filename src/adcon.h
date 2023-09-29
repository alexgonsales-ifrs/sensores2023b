/* 
 * File:   adcon.h
 * Author: ti
 *
 * Created on 5 de Janeiro de 2014, 03:38
 */

#ifndef ADCON_H
#define	ADCON_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdint.h>

//Quantidade máxima de leituras permitidas (gravadas na EEPROM). Cada leitura ocupa 2 bytes.
#define ADCON_QTD_MAX_LEITURAS              120 
    
#define ADCON_VALOR_MAXIMO_LEITURA          0xFFFF
#define ADCON_VALOR_MINIMO_LEITURA          0

extern uint8_t adcon_quant_amostras;

extern void adcon_init(void);

extern void adcon_le_amostra(void);

extern void adcon_le_amostra_grava(void);

extern void adcon_print(uint16_t t_int, uint8_t i);

#ifdef	__cplusplus
}
#endif

#endif	/* ADCON_H */
