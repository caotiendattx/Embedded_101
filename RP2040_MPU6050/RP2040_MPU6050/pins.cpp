#include <Arduino.h>
#include "pins.h"

void pins_init(){
    pinMode(PIN_JMP0, INPUT_PULLUP);
    pinMode(PIN_JMP1, INPUT_PULLUP);
    pinMode(PIN_JMP2, INPUT_PULLUP);
}
