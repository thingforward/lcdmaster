//
// Created by c018 on 17.11.16.
//

#ifndef ARDUINO_LCD_LCDCONFIG_OKMSG_H
#define ARDUINO_LCD_LCDCONFIG_OKMSG_H

#include "LiquidCrystal.h"
#include "DFR_Key.h"
#include "lcdconfig_common.h"

struct slyft_lcdconfig_okmsg {
    LiquidCrystal   *p_lcd;
    DFR_Key   *p_dfr_key;
    char    msg_line1[16];
    char    msg_line2[16];
    int     state;      // 0=NEW, 1=DISPLAYING, 2=OK'ed
};

void slyft_lcdconfig_okmsg_init(struct slyft_lcdconfig_okmsg *obj, LiquidCrystal *lcd, DFR_Key *dfr_key, const char *line1, const char *line2);
int slyft_lcdconfig_okmsg_handle(struct slyft_lcdconfig_okmsg *obj);
void slyft_lcdconfig_okmsg_reset(struct slyft_lcdconfig_okmsg *obj);

#endif //ARDUINO_LCD_LCDCONFIG_OKMSG_H
