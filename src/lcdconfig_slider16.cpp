#include "Arduino.h"
#include "Wire.h"
#include "lcdconfig_slider16.h"
#include "lcdconfig_common.h"

int     slyft_lcdconfig_slider16_get_result(slyft_lcdconfig_slider16 *obj) {
    if (obj->state < 2) {
        return -1;
    }
    if (obj->state == 3) {
        return 0;
    }
    if (obj->state > 3) {
        return -1;
    }
    return obj->cur_value;
}

void slyft_lcdconfig_slider16_init(slyft_lcdconfig_slider16 *obj, LiquidCrystal *lcd, DFR_Key *dfr_key, const char *line1, int starting_value) {
    strcpy(obj->msg_line1, line1);
    obj->cur_value = starting_value;
    obj->p_lcd = lcd;
    obj->p_dfr_key = dfr_key;
    obj->state = 0;
}

void slyft_lcdconfig_slider16__show_cur(slyft_lcdconfig_slider16 *obj) {
    obj->p_lcd->setCursor(0, 1);
    obj->p_lcd->print("                ");
    for( int i = 0; i < obj->cur_value; i++) {
        obj->p_lcd->setCursor(i, 1);
        obj->p_lcd->print("*");
    }

}

int slyft_lcdconfig_slider16_handle(slyft_lcdconfig_slider16 *obj) {
    int k = obj->p_dfr_key->getKey();
    if (obj->state == 0) {
        obj->p_lcd->setCursor(0,0);
        obj->p_lcd->print(obj->msg_line1);
        slyft_lcdconfig_slider16__show_cur(obj);

        if (obj->b_allow_up) {
            obj->p_lcd->setCursor(15,0);
            obj->p_lcd->print("^");
        }

        obj->state = 1;
    } else if (obj->state == 1) {
        if( k == SELECT_KEY) {
            obj->p_lcd->clear();
            obj->p_lcd->setCursor(0,0);
            obj->state = 2;
            return obj->state;
        }
        if( k == UP_KEY && obj->b_allow_up) {
            obj->p_lcd->clear();
            obj->p_lcd->setCursor(0,0);
            obj->state = 3;
            return obj->state;
        }
        if( k == LEFT_KEY && obj->cur_value > 0) {
            obj->cur_value--;
            slyft_lcdconfig_slider16__show_cur(obj);
            delay(50);
        }
        if(k == RIGHT_KEY && obj->cur_value < 15) {
            obj->cur_value++;
            slyft_lcdconfig_slider16__show_cur(obj);
            delay(50);
        }
    }
    return obj->state;
}

void    slyft_lcdconfig_slider16_reset(struct slyft_lcdconfig_slider16 *obj) {
    obj->state = 0;
}
