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
//Estes são os endereços da EEPROM onde ficam armazendas essas informações.
//Algumsa informações usam apenas 1 byte e outras usam 2 bytes.
//Nos 16 primeiros bytes (0x00 a 0x0F) ficam as configurações e 
//a partir do endereço 16 (0x10) ficarão as amostras armazendas.
  
 * Aquisicao: é a aquisição de um valor da porta analógica.
 *  
 * Leitura: é a aquisição de vários valores da porta analógica, resultando no valor médio de leitura e que será considerado 
 * como o valor lido do sensor. Por exemplo, uma leitura de um sensor pode corresponder a aquisição de 10 valores.
 * 
 * Amostra: é um conjunto de leitura de todos os sensores atualmente configurados.
 * Por exemplo, se está configurado para 4 sensores, então uma amostra corresponde a 4 leituras.
 * Nesse caso, se cada leitura corresponde à média da aquisição de 10 valores,
 * então uma amostra corresponderia a aquisição de 40 valores (armazenamento de apenas 4 dados de leitura).
 * 
 * Sessão de monitoramento: corresponde a uma sessão onde são realizadas (lidas) várias amostras.
 * 
*/
#define END_QTDE_SENSORES_ATUAL       0x00    //1 byte: quantidade de sensores atual.
#define END_QTDE_SENSORES_AMOSTRADOS  0x01    //1 byte: quantidade de sensores utilizados no ultima sessão de monitoramento.
#define END_TEMPO_AMOSTRAGEM          0x02    //2 bytes: tempo entre amostras.
#define END_LEITURA_MIN               0x04    //2 bytes: valor da menor leitura armazenada.
#define END_LEITURA_MAX               0x06    //2 bytes: valor da maior leitura armazenada.
#define END_QTDE_AMOSTRAS             0x08    //1 byte: quantidade de amostras atualmente armazenadas.
#define END_CHAVE_INICIALIZACAO       0x0c    //1 byte: 
//Até o endereço 0x0F está reservado.
#define END_INICIO_AMOSTRAS           0x10    //1 byte: endereço inicial da EEPROM onde são armazenadas as amostras.



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

