/* 
 * File:   menu.h
 * Author: ti
 *
 * Created on 30 de Dezembro de 2013, 23:59
 */

#ifndef MENU_PRINCIPAL_H
#define	MENU_PRINCIPAL_H

#ifdef	__cplusplus
extern "C" {
#endif

//#include <stdint.h>
#include "global.h"
#include "versao.h" //versao deve ser incluido por último
#include "menu.h"
#include "tempo_amostra.h"
    
#ifdef _ENVIA_DADOS_SERIAL_
  #define MENU_PRINCIPAL_TAM  8 // tamanho do menu inicial
#else
  #define MENU_PRINCIPAL_TAM  7 // tamanho do menu inicial
#endif

  TMenu menu_principal;
  
  const TMenuItem menu_principal_itens[MENU_PRINCIPAL_TAM] = {
        "1)Monitora",      0,
        "2)Monit/Grava",   1,
        "3)Ver Todos",     2,
        "4)Max/Min",       3,
        "5)Limpar",        4,
        "6)Tempo Amostra", 5,
        "7)Quant.Sensors", 6                 //não fechar virgula aqui
        #ifdef _ENVIA_DADOS_SERIAL_
         ,"8)Enviar Dados" 7
        #endif

  };

  #define SENS_TAM_MENU_QUANT_SENSORES  4 // tamanho do menu.
    
  TMenu sens_menu_quant_sensores;
      
  //const TSensMenuQuantSensores sens_menu_quant_sensores[SENS_TAM_MENU_QUANT_SENSORES] = {
  const TMenuItem sens_menu_itens_quant_sensores[SENS_TAM_MENU_QUANT_SENSORES] = {
        "1 sensor",   1,
        "2 sensores", 2,
        "3 sensores", 3,
        "4 sensores", 4
  };

  TMenu amo_menu_tempo_amostra;
 
  const TMenuItem amo_menu_itens_tempo_amostra[AMO_TAM_MENU_TEMPO_AMOSTRA] = {
        //"0.1 seg", TEMPO_01_SEGUNDO,
        //"0.5 seg", TEMPO_05_SEGUNDO,
        "1 seg",  TEMPO_AMOSTRA_1_SEGUNDO,
        "10 seg", TEMPO_AMOSTRA_10_SEGUNDOS,
        "30 seg", TEMPO_AMOSTRA_30_SEGUNDOS,
        "1 min",  TEMPO_AMOSTRA_1_MINUTO,
        "10 min", TEMPO_AMOSTRA_10_MINUTOS,
        "30 min", TEMPO_AMOSTRA_30_MINUTOS,
        "1 hora", TEMPO_AMOSTRA_1_HORA
  };
  
#ifdef	__cplusplus
}
#endif

#endif	/* MENU_PRINCIPAL_H */