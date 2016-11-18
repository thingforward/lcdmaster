//
// Created by c018 on 17.11.16.
//

#ifndef ARDUINO_LCD_LCDCONFIG_SELECT5_H
#define ARDUINO_LCD_LCDCONFIG_SELECT5_H

#include "LiquidCrystal.h"
#include "DFR_Key.h"

struct slyft_lcdconfig_select5 {
    LiquidCrystal   *p_lcd;
    DFR_Key         *p_dfr_key;
    char    msg_line1[16];

    bool    b_allow_up;

    int     n_selections;
    char    sel1[16];
    char    sel2[16];
    char    sel3[16];
    char    sel4[16];
    char    sel5[16];

    int     state;      // 0=NEW, 1=SELECTING, 2=SELECTED, 3=UP (if b_allow_up)
    int     idx_cur_sel;
};

void    slyft_lcdconfig_select5_init(struct slyft_lcdconfig_select5 *obj, LiquidCrystal *lcd, DFR_Key *dfr_key,const char *line1);
int     slyft_lcdconfig_select5_handle(struct slyft_lcdconfig_select5 *obj);
bool    slyft_lcdconfig_select5_add(struct slyft_lcdconfig_select5 *obj, const char *selection);
int     slyft_lcdconfig_select5_get_result(struct slyft_lcdconfig_select5 *obj);
void    slyft_lcdconfig_select5_reset(struct slyft_lcdconfig_select5 *obj);

#endif //ARDUINO_LCD_LCDCONFIG_SELECT5_H
