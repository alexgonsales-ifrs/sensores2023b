/* 
 * File:   botoes.h
 * Author: ti
 *
 * Created on 30 de Dezembro de 2013, 11:33
 */

#ifndef BOTOES_H

  #define	BOTOES_H

  #ifdef	__cplusplus
    extern "C" {
  #endif

  #include <stdint.h>
  #include "versao.h"

  typedef enum {
        BTN_NULL,
        BTN_START,
        BTN_STOP,
        BTN_UP,
        BTN_DOWN,
  } TBotao;
    
  //valores de retorno dos botoes
  //nao usar zero, pois a funcao btns_testa retorna 0 por default
  ///#define BTN_START     1
  //#define BTN_STOP      2
  //#define BTN_UP        3
  //#define BTN_DOWN      4

  /****************************************/
  #ifdef _MODULO_NOVO_
    #define BTN_START_PIN   RB4     //Bot�o Start/Select
    #define BTN_STOP_PIN    RB5    //Bot�o Stop/Esc
    #define BTN_UP_PIN      RB6    //Bot�o Up
    #define BTN_DOWN_PIN    RB7   //Bot�o Down

    #define BTN_START_TRIS  TRISB4
    #define BTN_STOP_TRIS   TRISB5
    #define BTN_UP_TRIS     TRISB6
    #define BTN_DOWN_TRIS   TRISB7
    
  #else 
    #ifdef _MODULO_ANTIGO_
      #define BTN_START_PIN           RC3
      #define BTN_START_TRIS      TRISC3

      #define BTN_STOP_PIN            RC2
      #define BTN_STOP_TRIS       TRISC2

      #define BTN_UP_PIN                  RC1
      #define BTN_UP_TRIS             TRISC1

      #define BTN_DOWN_PIN                RC0
      #define BTN_DOWN_TRIS           TRISC0
    #endif //_MODULO_ANTIGO_

    /**
     * Funcao que faz o debouncing do sinal dos botoes.
     * @return botao pressionado
     */
    uint8_t btns_testa(void);
    
  #endif //_MODULO_NOVO_ 

  /**
  * Funcao que inicializa a porta B, configurando para ativar as interrupcoes
  * conforme os pinos onde instalamos os botoes.
  */
  extern void    btns_init(void);
  
  /*
   Testa qual bot�o foi pressionado no equipamento e retorna P_START, P_STOP, P_UP, P_DWON
   * ou retorna zero se foi algum outro evento */
  extern TBotao btns_testa(void);
    
  #ifdef	__cplusplus
  }
  #endif

#endif	/* BOTOES_H */

