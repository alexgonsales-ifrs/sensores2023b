/* 
 * File:   versao.h
 * Author: ifrs
 *
 * Created on 5 de Maio de 2014, 16:00
 */

#ifndef VERSAO_H
#define	VERSAO_H

#ifdef	__cplusplus
extern "C" {
#endif

#define _MODULO_NOVO_ //PIC16F886 (n�o esquecer de configurar o modelo nas propriedades do projeto).

//Esta diretiva ser� configurada pela IDE quando configuramos o modelo de PIC nas op��es de projeto.
//No entanto, � interessante defin�-la aqui tamb�m (de forma correta) para que o compilador reconhe�a as vari�veis definidas nesse modelo de PIC.
//#define _PIC16F886_H_
    
//#define _MODULO_ANTIGO_ //PIC16F876A (n�o esquecer de configurar o modelo nas propriedades do projeto).
    
//Habilita a fun��o "Enviar Dados" que envia pela serial os dados que est�o gravados na mem�ria RAM.
//Esta diretiva se chamava _DEBUG_ e foi modificada para _ENVIA_DADOS_SERIAL_.
//Antes de habilitar esta diretiva, verificar qual modelo de PIC est� sendo usado para enviar dados pela serial.
//#define _ENVIA_DADOS_SERIAL_

//Esta diretiva � definida pelo compilador quando o projeto � executado em modo DEBUG.
//� interessante tamb�m habilit�-la aqui quando o projeto for executado em modo DEBUG,
//pois assim a IDE mostra o c�digo que ser� compilado.
//#define __DEBUG
    
//Esta diretiva somente ser� usada quando o projeto estiver em modo __DEBUG.
//Nessa caso, se esta diretiva estiver ativada, ent�o os comandos de escrita no LCD
//ser�o enviadas por nibble (4 bits) ao inv�s do byte inteiro.
//#define _DEBUG_LCD_CMD_

//#define _MQ_
#define _LM35_

#ifdef	__cplusplus
}
#endif

#endif	/* VERSAO_H */

