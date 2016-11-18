//
// Created by c018 on 17.11.16.
//

#ifndef ARDUINO_LCD_LCDCONFIG_SLIDER16_H
#define ARDUINO_LCD_LCDCONFIG_SLIDER16_H

#include "LiquidCrystal.h"
#include "DFR_Key.h"

struct slyft_lcdconfig_slider16 {
    LiquidCrystal   *p_lcd;
    DFR_Key         *p_dfr_key;
    char    msg_line1[16];

    bool    b_allow_up;

    int     state;      // 0=NEW, 1=SELECTING, 2=SELECTED, 3=UP (if b_allow_up)
    int     cur_value;
};

void    slyft_lcdconfig_slider16_init(struct slyft_lcdconfig_slider16 *obj, LiquidCrystal *lcd, DFR_Key *dfr_key,const char *line1, int starting_value);
int     slyft_lcdconfig_slider16_handle(struct slyft_lcdconfig_slider16 *obj);
int     slyft_lcdconfig_slider16_get_result(struct slyft_lcdconfig_slider16 *obj);
void    slyft_lcdconfig_slider16_reset(struct slyft_lcdconfig_slider16 *obj);


#endif
