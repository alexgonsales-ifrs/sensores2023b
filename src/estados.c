/*
 * Este m�dulo implementa a m�quina de estados para o menu da interface do usu�rio.
 * 
 * A sequ�ncia de chamadas de fun��es � a seguinte:
 * 1) Chama a fun��o est_maquina(botao) que verifica o estado atual e 
 * 2) chama a fun��o espec�fica do estado, que executa a a��o de sa�da de transi��o do estado e
 * 3) chama a fun��o est_executa(novo_estado), que executa a a��o de entrada do novo estado e troca o estado.
 *  
 * est_maquina(TBotao) - � a funcao de entrada da m�quina de estados.
 * Toda transi��o de estado come�a por esta fun��o, que � chamada pela interrup��o que foi gerada pelo bot�o.
 * O bot�o que foi pressionado � passado como par�metro para a fun��o.
 * Esta fun��o somente verifica o estado atual da m�quina de estados e chama a fun��o espec�fica para tratar o estado,
 * passando adiante o bot�o que foi pressionado.
 * 
 * Fun��es espec�ficas de cada estado:
 * Cada estado possui uma fun��o espec�fica que executa as a��es de transi��o que ocorrem no estado.
 * As a��es executadas durante uma transi��o est�o implementadas nessas fun��es espec�ficas (origem da transi��o).
 * Por exemplo: a a��o "decrementar item menu" ao clicar no bot�o UP enquanto no estado EST_CONF_QUANT_SENSORES
 * est� implementada na fun��o est_estado_menu_conf_quant_sensores(). As a��es espec�ficas de cada estado
 * s�o listadas a seguir:
 * 
 * est_estado_inicial(TBotao);
 * est_estado_menu_principal(TBotao botao);
 * est_estado_monitora(TBotao botao);
 * est_estado_ver_todos(TBotao botao);
 * est_estado_max_min(TBotao botao);
 * est_estado_menu_limpar(TBotao opt);
 * est_estado_menu_conf_tempo_amostra(TBotao botao);
 * est_estado_menu_conf_quant_sensores(TBotao botao);
 * est_estado_enviar_dados(TBotao botao);
 * 
 * est_executa(Estado) -
 * Esta fun��o executa as a��es "do" de cada estado e tamb�m a troca de estado.
 *  
 */

#include <xc.h>
#include <stdio.h>

#include "adcon.h"
#include "botoes.h"
#include "eeprom.h"
#include "lcd.h"
#include "menu_principal.h"
#include "sensores.h"
#include "tempo_amostra.h"
#include "estados.h" //adicionado em 21/08/23 para acessar o tipo Estados.

#include "versao.h"

/*********************************************************************
******************** Defini��es P�blicas do M�dulo *******************
*********************************************************************/

//Vari�vel global que matem o estado atual da m�quina de estados.  
TEstado est_estado_atual = EST_ESTADO_INICIAL;

/*********************************************************************
**************** Defini��es Privadas do M�dulo ***********************
*********************************************************************/

/******************** Variaveis Privadas ****************************/

//Mantem o indice da amostra que est� sendo mostrada no display quando
//estiver no estado EST_VER_TODOS.
static uint8_t est_ver_todos_index_amostra = 0;

/******************* Fun��es Privadas ******************************/

//Fun��es espec�ficas de cada estado.
static void est_estado_inicial(TBotao botao);
static void est_estado_menu_principal(TBotao botao);
static void est_estado_monitora(TBotao botao);
static void est_estado_monitora_grava(TBotao botao);
static void est_estado_ver_todos(TBotao botao);
static void est_estado_mostra_max_min(TBotao botao);
static void est_estado_menu_limpar(TBotao opt);
static void est_estado_menu_conf_tempo_amostra(TBotao botao);
static void est_estado_menu_conf_quant_sensores(TBotao botao);
static void est_estado_enviar_dados(TBotao botao);

//Fun��o que executa a a��o "do" dos estados.
//o par�metro novo_estado � o estado que ser� executada a a��o "do".
static void est_executa(TEstado novo_estado);

/*********************************************************************
********** Defini��es (implementa��o) das Fun��es P�blicas **********
*********************************************************************/ 

/**
 * Esta � a funcao de entrada da m�quina de estado. Toda transi��o de estado
 * come�a por esta fun��o.
 * Verifica o estado atual da m�quina e chama a fun��o espec�fica do estado.
 *  * @param botao eh o botao do equipamento que foi pressionado.
 */
void est_maquina(TBotao botao) {

    switch (est_estado_atual) {
        case EST_ESTADO_INICIAL:
             est_estado_inicial(botao);
        break;//EST_INICIO

        case EST_ESTADO_MENU_PRINCIPAL:
            est_estado_menu_principal(botao);
        break;//EST_MENU_PRINCIPAL:

        case EST_ESTADO_MONITORA:
            est_estado_monitora(botao);
        break; //EST_CAPTURA_E_MOSTRA

        case EST_ESTADO_MONITORA_GRAVA:
            //usando o timer 0, a funcao somente testa o stop e para o timer:

            //    if (opt == BTN_STOP) {
            //        INTCONbits.T0IE = 0;
            //        muda_estado(EST_MENU_PRINCIPAL);
            //    }
            est_estado_monitora(botao);
        break; //EST_CAPTURA_E_GRAVA

        case EST_ESTADO_MOSTRA_TODOS:
            est_estado_ver_todos(botao);
        break; //EST_MOSTRA_TODOS

        case EST_ESTADO_MOSTRA_MAX_MIN:
            est_estado_mostra_max_min(botao);
        break; //EST_MOSTRA_MAX_MIN

        case EST_ESTADO_LIMPAR:
            est_estado_menu_limpar(botao);
        break; //EST_LIMPAR

        case EST_ESTADO_MENU_CONF_TEMPO_AMOSTRA:
            est_estado_menu_conf_tempo_amostra(botao);
        break; //EST_MENU_CONF_TEMPO_AMOSTRA

        case EST_ESTADO_MENU_CONF_QUANT_SENSORES:
            est_estado_menu_conf_quant_sensores(botao);
        break; //EST_MENU_CONF_QUANT_SENSORES
        
        #ifdef _ENVIA_DADOS_SERIAL_
        case EST_ENVIAR_DADOS:
            est_estado_enviar_dados(botao);
        break; //EST_ENVIAR_DADOS
        #endif

        default:
            break;

    }//switch(gl_estado)
    
}//est_maquina()

/*********************************************************************
********* Defini��es (implementa��o) das Fun��es Privadas  ***********
*********************************************************************/

/**
 * A partir do estado inicial, muda para o estado menu principal
 * @param botao o bot�o que foi pressionado.
 */
static void est_estado_inicial(TBotao botao) {
    est_executa(EST_ESTADO_MENU_PRINCIPAL);
}//est_estado_inicial()

/**
 * Funcao que trata as transi��es do estado EST_MENU_PRINCIPAL.
 * @param botao o bot�o que foi pressionado.
 */
static void est_estado_menu_principal(TBotao botao) {
  uint8_t index;

  switch (botao) {
    case BTN_UP:
      if (menu_dec_index(&menu_principal) >= 0) {
         est_executa(EST_ESTADO_MENU_PRINCIPAL);
      }
    break;

    case BTN_DOWN:
      if ( menu_inc_index(&menu_principal) >= 0 ) {
        est_executa(EST_ESTADO_MENU_PRINCIPAL);
      }
    break;

    case BTN_START:
      index = menu_get_index_nav(&menu_principal);
      menu_confirma_index(&menu_principal);
      switch (index) {
        case 0: //"Monitora"
          adcon_le_amostra();
          est_executa(EST_ESTADO_MONITORA);
          break;

        case 1: //"Monitora/Grava"
          adcon_le_amostra_grava();
          est_executa(EST_ESTADO_MONITORA_GRAVA);
          break;

        case 2: //"Ver Todos"
          est_executa(EST_ESTADO_MOSTRA_TODOS);
          break;

        case 3: //"Max/Min"
          est_executa(EST_ESTADO_MOSTRA_MAX_MIN);
          break;

        case 4: //"Limpar"
          est_executa(EST_ESTADO_LIMPAR);
          break;

        case 5: //"Tempo Amostra"
          est_executa(EST_ESTADO_MENU_CONF_TEMPO_AMOSTRA);
          break;

        case 6: //"Quant Sensores"
          est_executa(EST_ESTADO_MENU_CONF_QUANT_SENSORES);
          break;
          #ifdef _ENVIA_DADOS_SERIAL_
          case 7: //"Enviar Dados"
            est_executa(EST_ENVIAR_DADOS);
            break;
          #endif
      }//switch (index)
    break; //BTN_START
    
    default:
      break;

  } //switch (botao)

}//est_estado_menu_principal()

/**
 * Funcao que trata as transi��es do estado EST_MENU_LIMPAR.
  * @param botao o bot�o que foi pressionado.
 */
static void est_estado_menu_limpar(TBotao botao) {
  if (botao == BTN_STOP) {
    est_executa(EST_ESTADO_MENU_PRINCIPAL);
  }
}//est_estado_menu_limpar()

/* Funcao que trata as transi��es do estado EST_MONITORA.
 * @param botao o bot�o que foi pressionado.
 */
static void est_estado_monitora(TBotao botao) {
  if (botao == BTN_STOP) {
    INTCONbits.T0IE = 0;
    est_executa(EST_ESTADO_MENU_PRINCIPAL);
  }
}//est_estado_monitora()

/**
 * Funcao que trata as transi��es do estado EST_MONITORA_GRAVA.
 * @param botao o bot�o que foi pressionado.
 */
static void est_estado_monitora_grava(TBotao botao) {
  if (botao == BTN_STOP) {
    INTCONbits.T0IE = 0;
    est_executa(EST_ESTADO_MENU_PRINCIPAL);
  }
}//est_estado_monitora()

/**
 * Funcao que trata as transi��es do estado EST_VER_TODOS.
 * Controla a navegacao por todos os valores ja gravados na EEPROM.
 * @param botao o bot�o que foi pressionado.
 */
static void est_estado_ver_todos(TBotao botao) {
  switch (botao) {
    case BTN_UP:
      if (est_ver_todos_index_amostra > 0) {
        est_ver_todos_index_amostra--;
        est_executa(EST_ESTADO_MOSTRA_TODOS);
      }
      break;
    case BTN_DOWN:
      if (est_ver_todos_index_amostra < adcon_quant_amostras - 1) {
        est_ver_todos_index_amostra++;
        est_executa(EST_ESTADO_MOSTRA_TODOS);
      }
      break;
    case BTN_STOP:
      est_executa(EST_ESTADO_MENU_PRINCIPAL);
      break;
    default:
      break;
  }//switch
}//est_estado_ver_todos()

/**
 * Funcao que trata as transi��es do estado EST_MOSTRA_MAX_MIN.
 * @param botao o bot�o que foi pressionado.
 */
static void est_estado_mostra_max_min(TBotao botao) {
  if (botao == BTN_STOP) {
    est_executa(EST_ESTADO_MENU_PRINCIPAL);
  }
}//est_estado_mostra_max_min()

/**
 * Funcao que trata as transi��es do estado EST_MENU_CONF_TEMPO_AMOSTRA.
 * @param botao o bot�o que foi pressionado.
 */
static void est_estado_menu_conf_tempo_amostra(TBotao botao) {
  switch (botao) {
    case BTN_UP:
      if (menu_dec_index(&amo_menu_tempo_amostra) >= 0) {
        est_executa(EST_ESTADO_MENU_CONF_TEMPO_AMOSTRA);
      }
      break;
    case BTN_DOWN:
      if ( menu_inc_index(&amo_menu_tempo_amostra) >= 0 ) {
        est_executa(EST_ESTADO_MENU_CONF_TEMPO_AMOSTRA);
      }
      break;
    case BTN_STOP:
      menu_restore_index(&amo_menu_tempo_amostra);
      est_executa(EST_ESTADO_MENU_PRINCIPAL);
      break;
    case BTN_START:
      menu_confirma_index(&amo_menu_tempo_amostra);
      amo_tempo_amostra_atual = (uint8_t)(menu_get_value_active(&amo_menu_tempo_amostra));
      eeprom_gravar_word(END_TEMPO_AMOSTRAGEM, amo_tempo_amostra_atual);
      est_executa(EST_ESTADO_MENU_PRINCIPAL);
      break;
    default:
      break;
  }//switch
   
}//est_estado_menu_conf_tempo_amostra()

/**
 * Funcao que trata as transi��es do estado EST_MENU_CONF_QUANT_SENSORES.
 * @param botao o bot�o que foi pressionado.
 */
static void est_estado_menu_conf_quant_sensores(TBotao botao) {
  uint8_t quant_sens;
    switch (botao) {
      case BTN_UP:
        //vetor que guarda a quantidade de sensores inicia em 1:
        if (menu_dec_index(&sens_menu_quant_sensores) >= 0) {
          est_executa(EST_ESTADO_MENU_CONF_QUANT_SENSORES);
        }
        break;
      case BTN_DOWN:
        //vetor que guarda a quantidade de sensores inicia em 1:
        if ( menu_inc_index(&sens_menu_quant_sensores) >= 0 ) {
          est_executa(EST_ESTADO_MENU_CONF_QUANT_SENSORES);
        }
        break;
      case BTN_STOP:
        menu_restore_index(&sens_menu_quant_sensores);
        est_executa(EST_ESTADO_MENU_PRINCIPAL);
        break;
      case BTN_START:
        menu_confirma_index(&sens_menu_quant_sensores);
        sens_quant_sensores_atual = (uint8_t)(menu_get_value_active(&sens_menu_quant_sensores));
        eeprom_write(END_QTDE_SENSORES_ATUAL, sens_quant_sensores_atual);
        est_executa(EST_ESTADO_MENU_PRINCIPAL);
        break;
      default:
        break;
    }//switch
}//est_estado_menu_conf_quant_sensores()

/**
 * Funcao que trata as transi��es do estado EST_ENVIAR_DADOS.
 * @param botao o bot�o que foi pressionado.
 */
static void est_estado_enviar_dados(TBotao botao) {
  if (botao == BTN_STOP) {
    est_executa(EST_ESTADO_MENU_PRINCIPAL);
  }
}//est_estado_enviar_dados()

/**
 * Executa a a��o "do" dos estados.
 * o par�metro novo_estado � o estado que ser� executada a a��o "do".
 * Atualiza a variavel est_estado_atual = novo_estado.
 * @param novo_estado o proximo estado para a m�quina de estados.
 */
static void est_executa(TEstado novo_estado) {
  //uint16_t maior, menor, temp_int, pos_taxa;
  uint16_t maior, menor, temp_int;
  uint8_t endereco, qtd_val, qtd_sens;
  uint8_t index;
  //uint8_t posicao;
  #ifdef _ENVIA_DADOS_SERIAL_
    uint8_t bytes_tx;
  #endif
  char tmp[17] = {0}; //warning do compilador
  uint8_t tmp8;
  
  //pos_taxa = eeprom_ler_word(END_TX_AMOSTRA);
  switch (novo_estado) {
      
    case EST_ESTADO_MENU_PRINCIPAL:
      //Limpa o LCD e imprime o novo item de menu principal.
      lcd_clear();
      index = menu_get_index_nav(&menu_principal);
      lcd_puts(menu_principal.itens[index].str_text);
      break; //EST_MENU_PRINCIPAL
      
    case EST_ESTADO_MONITORA:
      //Habilita a interrup��o do Timer0 para iniciar o monitoramento.
      INTCONbits.T0IE = 1;
      break; //EST_CAPTURA_E_MOSTRA
      
    case EST_ESTADO_MONITORA_GRAVA:
      //Habilita a interrup��o do Timer0 para iniciar o monitoramento.
      INTCONbits.T0IE = 1;
      break; //EST_CAPTURA_E_GRAVA
      
    case EST_ESTADO_MOSTRA_TODOS:
      //A cada entrada neste estado mostra o pr�ximo conjunto de dados armazenados na EEPROM.
      //Se n�o tiver nenhum dado, finaliza.
      lcd_clear();
      if (adcon_quant_amostras == 0) {
        lcd_puts("Nenhum Dado");
      }
      else {
        //qtd_sens = menu_get_quant(&sens_menu_quant_sensores);
        qtd_sens = sens_quant_sensores_atual;
        endereco = END_INICIO_AMOSTRAS + (est_ver_todos_index_amostra * qtd_sens * 2);
        //Mostrar no LCD os valores gravados na EEPROM:
        for (uint8_t i = 0; i < qtd_sens; i++) {
            temp_int = eeprom_ler_word(endereco);
            sprintf(tmp, "%d=%d.%d", i + 1, temp_int / 10, temp_int % 10);
            lcd_goto(LCD_POSICAO[i].y, LCD_POSICAO[i].x);
            lcd_puts(tmp);
            endereco = endereco + 2; //enderecos de 2 bytes
        }//for
      }//else
    break; //EST_MOSTRA_TODOS
    
    case EST_ESTADO_MOSTRA_MAX_MIN:
      //Mostra o valor m�ximo e m�nimo armazenados na EEPROM.
      lcd_clear();
      maior = eeprom_ler_word(END_LEITURA_MAX);
      menor = eeprom_ler_word(END_LEITURA_MIN);
      if (menor == ADCON_VALOR_MAXIMO_LEITURA) {
            lcd_puts("Nenhum Dado");
      }
      else {
        sprintf(tmp, "Max=%d.%d", maior / 10, maior % 10);
        lcd_puts(tmp);
        lcd_goto(2, 0);
        sprintf(tmp, "Min=%d.%d", menor / 10, menor % 10);
        lcd_puts(tmp);
      }//else
      break; //EST_MOSTRA_MAX_MIN
      
    case EST_ESTADO_LIMPAR:
      lcd_clear();
      lcd_puts("Limpando...");
      //Inicializa toda a EEPROM com os valores default.
      eeprom_write(END_QTDE_SENSORES_ATUAL, 1);
      eeprom_write(END_QTDE_AMOSTRAS, 0);
      eeprom_gravar_word(END_TEMPO_AMOSTRAGEM, TEMPO_AMOSTRA_1_SEGUNDO);
      eeprom_gravar_word(END_LEITURA_MIN, ADCON_VALOR_MAXIMO_LEITURA);
      eeprom_gravar_word(END_LEITURA_MAX, ADCON_VALOR_MINIMO_LEITURA);
      for (uint8_t i = 0; i < ADCON_QTD_MAX_LEITURAS * 2; i++) {
        eeprom_write(i + END_INICIO_AMOSTRAS, 0);
      }
      lcd_clear();
      lcd_puts("Tudo Limpo.");
      break; //EST_LIMPAR
      
    case EST_ESTADO_MENU_CONF_TEMPO_AMOSTRA:
      //Entra no menu Conf. Tempo Amostra.
      index = menu_get_index_nav(&amo_menu_tempo_amostra);
      lcd_clear();
      lcd_puts(amo_menu_tempo_amostra.itens[index].str_text);
      break; //EST_MENU_CONF_TEMPO_AMOSTRA

    case EST_ESTADO_MENU_CONF_QUANT_SENSORES:
      //Entra no menu Conf. Quant. de Sensores.
      lcd_clear();
      index = menu_get_index_nav(&sens_menu_quant_sensores);
      lcd_puts(sens_menu_quant_sensores.itens[index].str_text);
      break; //EST_MENU_CONF_QUANT_SENSORES
      
      #ifdef _ENVIA_DADOS_SERIAL_
      case EST_ENVIAR_DADOS:
        bytes_tx = rs232_transmite();
        lcd_clear();
        sprintf(tmp, "%d bytes transmitidos", bytes_tx);
        lcd_puts(tmp);
        break; //EST_ENVIAR_DADOS
      #endif

    default:
      break;

    }//switch (novo_estado)
  
    //Atualiza o novo Estado.
    est_estado_atual = novo_estado;
    
}//est_executa()
