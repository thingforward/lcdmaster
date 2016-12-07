//
// Created by c018 on 17.11.16.
//

#include "Arduino.h"
#include "Wire.h"
#include "LiquidCrystal.h"
#include "DFR_Key.h"
#include "lcdconfig_common.h"
#include "lcdconfig_okmsg.h"
#include "lcdconfig_select5.h"
#include "lcdconfig_simplepin.h"
#include "lcdconfig_slider16.h"

LiquidCrystal   lcd(8, 13, 9, 4, 5, 6, 7);
DFR_Key         keys;

struct slyft_lcdconfig_okmsg e;
struct slyft_lcdconfig_select5 m;
struct slyft_lcdconfig_slider16 s;
struct slyft_lcdconfig_simplepin simplepin;

void setup()
{
    lcd.clear();
    lcd.begin(16, 2);
    //keys.setRate(100);

    slyft_lcdconfig_okmsg_init(&e, &lcd, &keys, "Hit return", "");

    slyft_lcdconfig_simplepin_init(&simplepin, &lcd, &keys, "Enter PIN");
    slyft_lcdconfig_simplepin_set_options(&simplepin, 7, "000", true, false);

    slyft_lcdconfig_select5_init(&m, &lcd, &keys, "Choose one");
    m.b_allow_up = true;
    slyft_lcdconfig_select5_add(&m, "First");
    slyft_lcdconfig_select5_add(&m, "Second");
    slyft_lcdconfig_select5_add(&m, "Third");
    slyft_lcdconfig_select5_add(&m, "Fourth");
    slyft_lcdconfig_select5_add(&m, "Fifth");
    slyft_lcdconfig_select5_add(&m, "OneTooMuch");

    slyft_lcdconfig_slider16_init(&s, &lcd, &keys, "How much?", 5);
    s.b_allow_up = true;
}

enum cur_e {
    in_msg = 1,
    in_select5,
    in_slider16
};

cur_e cur = in_msg;

void loop()
{
    slyft_lcdconfig_simplepin_handle(&simplepin);

/*
    if (cur == in_msg) {
        if ( slyft_lcdconfig_okmsg_handle(&e) == LCDCONFIG_STATE_SELECTED) {
            cur = in_select5;
            slyft_lcdconfig_okmsg_reset(&e);
            delay(500);
        }
    }
    if ( cur == in_select5) {
        int s = slyft_lcdconfig_select5_handle(&m);
        if ( s == LCDCONFIG_STATE_SELECTED) {
            cur = in_slider16;
            slyft_lcdconfig_select5_reset(&m);
            delay(500);
        }
        if ( s == LCDCONFIG_STATE_UP) {
            cur = in_msg;
            slyft_lcdconfig_select5_reset(&m);
            delay(500);
        }
    }
    if ( cur == in_slider16) {
        int st = slyft_lcdconfig_slider16_handle(&s);
        if ( st == LCDCONFIG_STATE_SELECTED ) {
            cur = in_select5;
            slyft_lcdconfig_slider16_reset(&s);
            delay(500);
        } else if ( st == LCDCONFIG_STATE_UP ) {
            cur = in_msg;
            slyft_lcdconfig_slider16_reset(&s);
            delay(500);
        }
    }
*/
}