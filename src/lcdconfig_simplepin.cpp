#include "Arduino.h"
#include "Wire.h"
#include "lcdconfig_simplepin.h"
#include "lcdconfig_common.h"


int     slyft_lcdconfig_simplepin_get_result(slyft_lcdconfig_simplepin *obj) {
    switch(obj->state) {
        case LCDCONFIG_STATE_NEW : {
            return -1;
        }
        case LCDCONFIG_STATE_INPROGRESS : {
            return -1;
        }
        case LCDCONFIG_STATE_SELECTED : {
            return obj->idx_cur_sel;
        }
        case LCDCONFIG_STATE_UP : {
            return -2;
        }
    }
    return -3;
}

void slyft_lcdconfig_simplepin_init(slyft_lcdconfig_simplepin *obj, LiquidCrystal *lcd, DFR_Key *dfr_key, const char *line1) {
    strncpy(obj->msg_line1, line1, sizeof(obj->msg_line1));
    obj->p_lcd = lcd;
    obj->p_dfr_key = dfr_key;
    obj->state = LCDCONFIG_STATE_NEW;
    obj->idx_cur_sel = 0;
}

void    slyft_lcdconfig_simplepin_set_options(struct slyft_lcdconfig_simplepin *obj, int pin_len, const char *initialPin, bool allow_rolling_number, bool blinking) {
    obj->b_allow_rolling_numbers = allow_rolling_number;
    obj->b_blinking = blinking;
    obj->n_pin_len = (pin_len > 16)?16:pin_len;
    strncpy(obj->pin, initialPin, sizeof(obj->pin));
    int k = strlen(obj->pin);

    // does the initial pin carry more chars than pin_len? wipe out?
    char *p = obj->pin+obj->n_pin_len;
    int n = 16-obj->n_pin_len;
    while(n-- > 0)
        *p++ = ' ';
    // does the initial pin carry less chars than pin_len? fill with 0s.
    p = obj->pin+k;
    n = obj->n_pin_len-k;
    while(n-- > 0)
        *p++ = '0';
}

void slyft_lcdconfig_simplepin__show_cur(slyft_lcdconfig_simplepin *obj) {
    obj->p_lcd->setCursor(0, 1);
    obj->p_lcd->print("                ");
    obj->p_lcd->setCursor(0, 1);
    obj->p_lcd->print(obj->pin);
    obj->p_lcd->setCursor(obj->idx_cur_sel,1);
}

int slyft_lcdconfig_simplepin_handle(slyft_lcdconfig_simplepin *obj) {
    if (obj->state == LCDCONFIG_STATE_NEW) {
        obj->p_lcd->setCursor(0,0);
        obj->p_lcd->print(obj->msg_line1);
        slyft_lcdconfig_simplepin__show_cur(obj);
        obj->p_lcd->cursor();
        if ( obj->b_blinking) {
            obj->p_lcd->blink();
        }

        obj->state = 1;
        obj->idx_cur_sel = 0;
    } else if (obj->state == LCDCONFIG_STATE_INPROGRESS) {
        int k = obj->p_dfr_key->getKey();
        if( k == SELECT_KEY) {
            obj->p_lcd->noCursor();
            if ( obj->b_blinking) {
                obj->p_lcd->noBlink();
            }
            obj->p_lcd->clear();
            obj->p_lcd->setCursor(0,0);
            obj->state = LCDCONFIG_STATE_SELECTED;
            return obj->state;
        }
        if( k == UP_KEY) {
            obj->pin[obj->idx_cur_sel]++;

            if (obj->pin[obj->idx_cur_sel] > '9') {
                if ( obj->b_allow_rolling_numbers) {
                    obj->pin[obj->idx_cur_sel] = '0';
                } else {
                    obj->pin[obj->idx_cur_sel] = '9';
                }
            }

            obj->p_lcd->setCursor(0,0);
            slyft_lcdconfig_simplepin__show_cur(obj);
            delay(200);

            return obj->state;
        }
        if( k == DOWN_KEY) {
            obj->pin[obj->idx_cur_sel]--;
            if (obj->pin[obj->idx_cur_sel] < '0') {
                if ( obj->b_allow_rolling_numbers) {
                    obj->pin[obj->idx_cur_sel] = '9';
                } else {
                    obj->pin[obj->idx_cur_sel] = '0';
                }
            }

            obj->p_lcd->setCursor(0,0);
            slyft_lcdconfig_simplepin__show_cur(obj);
            delay(200);

            return obj->state;
        }
        if( k == LEFT_KEY && obj->idx_cur_sel > 0) {
            obj->idx_cur_sel--;
            slyft_lcdconfig_simplepin__show_cur(obj);
            delay(200);
            //obj->p_lcd->setCursor(14, 0);
        }
        if(k == RIGHT_KEY && obj->idx_cur_sel < obj->n_pin_len-1) {
            obj->idx_cur_sel++;
            slyft_lcdconfig_simplepin__show_cur(obj);
            delay(200);
        }
    }
    return obj->state;
}


void    slyft_lcdconfig_simplepin_reset(struct slyft_lcdconfig_simplepin *obj) {
    obj->state = LCDCONFIG_STATE_NEW;
    memset(obj->pin, 0, sizeof(obj->pin));
}
