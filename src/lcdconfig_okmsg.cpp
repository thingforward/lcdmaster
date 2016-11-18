#include "Arduino.h"
#include "Wire.h"
#include "lcdconfig_okmsg.h"
#include "lcdconfig_common.h"


void slyft_lcdconfig_okmsg_init(struct slyft_lcdconfig_okmsg *obj, LiquidCrystal *lcd, DFR_Key *dfr_key, const char *line1, const char *line2) {
    strcpy(obj->msg_line1, line1);
    strcpy(obj->msg_line2, line2);
    obj->p_lcd = lcd;
    obj->p_dfr_key = dfr_key;
    obj->state = LCDCONFIG_STATE_NEW;
}

int slyft_lcdconfig_okmsg_handle(struct slyft_lcdconfig_okmsg *obj) {
    if (obj->state == LCDCONFIG_STATE_NEW) {
        obj->p_lcd->setCursor(0,0);
        obj->p_lcd->print(obj->msg_line1);
        obj->p_lcd->setCursor(0,1);
        obj->p_lcd->print(obj->msg_line2);
        obj->state = LCDCONFIG_STATE_INPROGRESS;
    } else if (obj->state == 1) {
        if(obj->p_dfr_key->getKey() == SELECT_KEY) {
            obj->p_lcd->clear();
            obj->p_lcd->setCursor(0,0);
            obj->state = LCDCONFIG_STATE_SELECTED;
        }
    }
    return obj->state;
}

void slyft_lcdconfig_okmsg_reset(struct slyft_lcdconfig_okmsg *obj) {
    obj->state = LCDCONFIG_STATE_NEW;
}
