//
// Created by c018 on 17.11.16.
//

#ifndef ARDUINO_LCD_LCDCONFIG_SIMPLEPIN_H
#define ARDUINO_LCD_LCDCONFIG_SIMPLEPIN_H

#include "LiquidCrystal.h"
#include "DFR_Key.h"

struct slyft_lcdconfig_simplepin {
    LiquidCrystal   *p_lcd;
    DFR_Key         *p_dfr_key;
    char    msg_line1[16];

    bool    b_allow_rolling_numbers;
    bool    b_blinking;
    int     n_pin_len;

    char    pin[16];

    int     state;      // 0=NEW, 1=SELECTING, 2=SELECTED, 3=UP (if b_allow_up)
    int     idx_cur_sel;
};

void    slyft_lcdconfig_simplepin_init(struct slyft_lcdconfig_simplepin *obj, LiquidCrystal *lcd, DFR_Key *dfr_key,const char *line1);
void    slyft_lcdconfig_simplepin_set_options(struct slyft_lcdconfig_simplepin *obj, int pin_len, const char *initialPin, bool allow_rolling_number, bool blinking);
int     slyft_lcdconfig_simplepin_handle(struct slyft_lcdconfig_simplepin *obj);
int     slyft_lcdconfig_simplepin_get_result(struct slyft_lcdconfig_simplepin *obj);
void    slyft_lcdconfig_simplepin_reset(struct slyft_lcdconfig_simplepin *obj);

#endif //ARDUINO_LCD_LCDCONFIG_SIMPLEPIN_H
