#include "Arduino.h"
#include "Wire.h"
#include "lcdconfig_select5.h"
#include "lcdconfig_common.h"


int     slyft_lcdconfig_select5_get_result(slyft_lcdconfig_select5 *obj) {
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

void slyft_lcdconfig_select5_init(slyft_lcdconfig_select5 *obj, LiquidCrystal *lcd, DFR_Key *dfr_key, const char *line1) {
    strcpy(obj->msg_line1, line1);
    obj->n_selections = 0;
    obj->p_lcd = lcd;
    obj->p_dfr_key = dfr_key;
    obj->state = LCDCONFIG_STATE_NEW;
    obj->idx_cur_sel = 0;
}

void slyft_lcdconfig_select5__show_cur(slyft_lcdconfig_select5 *obj) {
    obj->p_lcd->setCursor(0, 1);
    obj->p_lcd->print("                ");
    obj->p_lcd->setCursor(1, 1);
    switch (obj->idx_cur_sel) {
        case 1: { obj->p_lcd->print(obj->sel1); }
            break;
        case 2: { obj->p_lcd->print(obj->sel2); }
            break;
        case 3: { obj->p_lcd->print(obj->sel3); }
            break;
        case 4: { obj->p_lcd->print(obj->sel4); }
            break;
        case 5: { obj->p_lcd->print(obj->sel5); }
            break;
    }
}

int slyft_lcdconfig_select5_handle(slyft_lcdconfig_select5 *obj) {
    if (obj->state == LCDCONFIG_STATE_NEW) {
        obj->p_lcd->setCursor(0,0);
        obj->p_lcd->print(obj->msg_line1);
        obj->p_lcd->setCursor(0,1);
        obj->p_lcd->print(obj->sel1);

        if (obj->b_allow_up) {
            obj->p_lcd->setCursor(15,0);
            obj->p_lcd->print("^");
        }

        obj->state = 1;
        obj->idx_cur_sel = 1;
    } else if (obj->state == LCDCONFIG_STATE_INPROGRESS) {
        int k = obj->p_dfr_key->getKey();
        if( k == SELECT_KEY) {
            obj->p_lcd->clear();
            obj->p_lcd->setCursor(0,0);
            obj->state = LCDCONFIG_STATE_SELECTED;
            return obj->state;
        }
        if( k == UP_KEY && obj->b_allow_up) {
            obj->p_lcd->clear();
            obj->p_lcd->setCursor(0,0);
            obj->state = LCDCONFIG_STATE_UP;
            return obj->state;
        }
        if( k == LEFT_KEY && obj->idx_cur_sel > 1) {
            obj->idx_cur_sel--;
            slyft_lcdconfig_select5__show_cur(obj);
            delay(200);
            //obj->p_lcd->setCursor(14, 0);
        }
        if(k == RIGHT_KEY && obj->idx_cur_sel < obj->n_selections) {
            obj->idx_cur_sel++;
            slyft_lcdconfig_select5__show_cur(obj);
            delay(200);
        }
        if ( obj->idx_cur_sel > 1) {
            obj->p_lcd->setCursor(0, 1);
            obj->p_lcd->print("<");
        }
        if ( obj->idx_cur_sel < obj->n_selections && obj->n_selections > 1) {
            obj->p_lcd->setCursor(15, 1);
            obj->p_lcd->print(">");
        }
    }
    return obj->state;
}


bool slyft_lcdconfig_select5_add(slyft_lcdconfig_select5 *obj, const char *selection) {
    if (obj->n_selections >= 5)
        return false;
    obj->n_selections++;
    switch (obj->n_selections) {
        case 1: { strcpy(obj->sel1, selection); }
            break;
        case 2: { strcpy(obj->sel2, selection); }
            break;
        case 3: { strcpy(obj->sel3, selection); }
            break;
        case 4: { strcpy(obj->sel4, selection); }
            break;
        case 5: { strcpy(obj->sel5, selection); }
            break;
        default:
            break;
    }
    return true;
}

void    slyft_lcdconfig_select5_reset(struct slyft_lcdconfig_select5 *obj) {
    obj->state = LCDCONFIG_STATE_NEW;
}
