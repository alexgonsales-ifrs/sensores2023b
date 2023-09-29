#include <stdint.h>
#include <xc.h>

#include "lcd.h"
#include "versao.h"
#include "xtal.h" //usado por __delay_us())

//void lcd_write(uint8_t c);

/**
 * Envia o comando para o display separando cada bit
 * @param c comando a ser enviado
 */
static void lcd_write(uint8_t c) {
    if (c & 0b00000001) {
        LCD_D4 = 1;
    } else {
        LCD_D4 = 0;
    }
    if (c & 0b00000010) {
        LCD_D5 = 1;
    } else {
        LCD_D5 = 0;
    }
    if (c & 0b00000100) {
        LCD_D6 = 1;
    } else {
        LCD_D6 = 0;
    }
    if (c & 0b00001000) {
        LCD_D7 = 1;
    } else {
        LCD_D7 = 0;
    }
    __delay_us(40);
    LCD_E = 1;
    LCD_E = 0;
}//lcd_write())

void lcd_clear(void) {
    LCD_RS = 0;
    lcd_write(0);
    lcd_write(1);
    __delay_ms(2);
}//lcd_clear())

void lcd_goto(uint8_t y, uint8_t x) {
    LCD_RS = 0;
    switch (y) {
        case 1:
            lcd_write(8);
            break;
        case 2:
            lcd_write(0xc);
            break;
    }
    lcd_write(x);
    __delay_us(40);
}//lcd_goto())

/**
 * Envia uma string para o LCD. Se estiver em modo __DEBUG, envia também para a UART.
 * @param *str string a ser enviada.
 */
void lcd_puts(const char *str) {
  uint8_t cmd; //comando a ser enviado ao LCD.
  LCD_RS = 1;

  while (*str) {
    //Desloca 4 bits para a direita para enviar os 4 bits mais significativos do caractere.
    cmd = *str >> 4;
    lcd_write(cmd);
    __delay_us(40);
        
    //Envia os 4 bits menos sigificativos do caractere.
    lcd_write(*str);
    __delay_us(40);

    //Se o MPLABx IDE estiver em modo __DEBUG então envia o print do LCD também para a UART,
    //para imprimir na janela "UART1 Output" da IDE.
    #ifdef __DEBUG
      #ifdef _DEBUG_LCD_CMD_
        //Desloca 4 bits para a direita para enviar os 4 bits mais significativos do caractere.
        cmd = *str >> 4;
        while (!TXIF) {
          continue;
        }
        TXREG = cmd;
        
        while (!TXIF) {
          continue;
        }      
        //Envia os 4 bits menos significativos do caractere.
        cmd = (*str) & 0b00001111;
        TXREG = cmd;
      #else
        cmd = *str;
        while (!TXIF) {
          continue;
        }
        TXREG = cmd;
        
      #endif
    #endif      

    str++;
        
  }//while
  
  //Se estiver em modo __DEBUG então envia um comando para troca de linha.
  #ifdef __DEBUG
    while (!TXIF) {
      continue;
    }      
    TXREG = '\n';
  #endif

}//lcd_puts()

void lcd_init(void) {
    LCD_RS_TRIS = LCD_E_TRIS = LCD_D4_TRIS = LCD_D5_TRIS = LCD_D6_TRIS = LCD_D7_TRIS = 0;
    LCD_RS = LCD_E = LCD_D4 = LCD_D5 = LCD_D6 = LCD_D7 = 0; // display, 0 = saida
    lcd_write(2);
    lcd_write(8);
    lcd_write(0);
    lcd_write(0);
    lcd_write(0xc);
    lcd_write(0);
    lcd_write(6);
}//lcd_init())