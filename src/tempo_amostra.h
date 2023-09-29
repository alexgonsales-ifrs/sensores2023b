/* 
 * File:   tempo_amostra.h
 * Author: ifrs
 *
 * Created on 16 de Abril de 2015, 16:47
 */

#ifndef MENU_TEMPO_AMOSTRA_H
#define	MENU_TEMPO_AMOSTRA_H

#ifdef	__cplusplus
extern "C" {
#endif

    #include "menu.h"
            
  // Valores de selecao do tempo de amostragem
  //#define     TEMPO_01_SEGUNDO    18/10
  //#define     TEMPO_05_SEGUNDO    9
  #define     TEMPO_AMOSTRA_1_SEGUNDO     18
  #define     TEMPO_AMOSTRA_10_SEGUNDOS   180
  #define     TEMPO_AMOSTRA_30_SEGUNDOS   540
  #define     TEMPO_AMOSTRA_1_MINUTO      1080
  #define     TEMPO_AMOSTRA_10_MINUTOS    10800
  #define     TEMPO_AMOSTRA_30_MINUTOS    32400
  #define     TEMPO_AMOSTRA_1_HORA        64800

  #define AMO_TAM_MENU_TEMPO_AMOSTRA   7 // tamanho do menu taxa de amostragem

  extern uint8_t amo_tempo_amostra_atual;
  
#ifdef	__cplusplus
}
#endif

#endif	/* MENU_TEMPO_AMOSTRA_H */

