/* 
 * File:   eeprom.h
 * Author: ti
 *
 * Created on 12 de Janeiro de 2014, 04:36
 */

#ifndef EEPROM_H
#define	EEPROM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>

/*
//Estes s�o os endere�os da EEPROM onde ficam armazendas essas informa��es.
//Algumsa informa��es usam apenas 1 byte e outras usam 2 bytes.
//Nos 16 primeiros bytes (0x00 a 0x0F) ficam as configura��es e 
//a partir do endere�o 16 (0x10) ficar�o as amostras armazendas.
  
 * Aquisicao: � a aquisi��o de um valor da porta anal�gica.
 *  
 * Leitura: � a aquisi��o de v�rios valores da porta anal�gica, resultando no valor m�dio de leitura e que ser� considerado 
 * como o valor lido do sensor. Por exemplo, uma leitura de um sensor pode corresponder a aquisi��o de 10 valores.
 * 
 * Amostra: � um conjunto de leitura de todos os sensores atualmente configurados.
 * Por exemplo, se est� configurado para 4 sensores, ent�o uma amostra corresponde a 4 leituras.
 * Nesse caso, se cada leitura corresponde � m�dia da aquisi��o de 10 valores,
 * ent�o uma amostra corresponderia a aquisi��o de 40 valores (armazenamento de apenas 4 dados de leitura).
 * 
 * Sess�o de monitoramento: corresponde a uma sess�o onde s�o realizadas (lidas) v�rias amostras.
 * 
*/
#define END_QTDE_SENSORES_ATUAL       0x00    //1 byte: quantidade de sensores atual.
#define END_QTDE_SENSORES_AMOSTRADOS  0x01    //1 byte: quantidade de sensores utilizados no ultima sess�o de monitoramento.
#define END_TEMPO_AMOSTRAGEM          0x02    //2 bytes: tempo entre amostras.
#define END_LEITURA_MIN               0x04    //2 bytes: valor da menor leitura armazenada.
#define END_LEITURA_MAX               0x06    //2 bytes: valor da maior leitura armazenada.
#define END_QTDE_AMOSTRAS             0x08    //1 byte: quantidade de amostras atualmente armazenadas.
#define END_CHAVE_INICIALIZACAO       0x0c    //1 byte: 
//At� o endere�o 0x0F est� reservado.
#define END_INICIO_AMOSTRAS           0x10    //1 byte: endere�o inicial da EEPROM onde s�o armazenadas as amostras.



/**
 * Funcao para gravar dois bytes (big endian) na eeprom
 * @param end endereco dos dados
 * @param dado dado a ser gravado
 */
void eeprom_gravar_word(uint8_t end, uint16_t dado);

/**
 * Funcao que le dois bytes seguidos da eeprom
 * @param end endereco de memoria onde esta o dado a ser lido
 * @return valor de 16 bits (big endian)
 */
uint16_t eeprom_ler_word(uint8_t end);

#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_H */

