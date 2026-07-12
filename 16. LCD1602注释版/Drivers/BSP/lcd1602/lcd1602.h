#ifndef __LCD1602_H__
#define __LCD1602_H__

#include <stdint.h>


void lcd1602_init(void);
void lcd1602_write_cmd(char cmd);
void lcd1602_write_data(char dataShow);
void lcd1602_show_line(char row, char col, char *string);
void lcd1602_right_move(void);


#endif
