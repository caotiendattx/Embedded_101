#include "i2c.h"
#include <Wire.h>
#include "wiring_private.h"
#include "pins.h"
#include "globals.h"
volatile uint8_t request_address;
// Flags


void i2c_begin(){
    uint8_t address = DEFAULT_I2C_ADDRESS;
    //check teh solder bridge jumpers and determine address
    if (digitalRead(PIN_JMP0) == LOW ) address +=1;
    if (digitalRead(PIN_JMP1) == LOW ) address +=2;
    if (digitalRead(PIN_JMP2) == LOW ) address +=4;
    Wire.setPins(PIN_MPU6050_I2C_SDA, PIN_MPU6050_I2C_SCL);
    Wire.begin(address);
    Wire.onRequest(i2c_request_event);
    Wire.onReceive(i2c_receive_event);
}

void i2c_request_event(){
    //put maximum possible number of bytes in the buffer - the master will stop transimssion
    //after reading as many as it needs
    //start at offset requestAddress - the one received from master at last transimssion

    Wire.write((uint8_t *)(REGBANK+request_address), MAX_TRANSMIT_SIZE);
    //Serial.print("Sent bytes starting at offset "); Serial.println(request_address);
}

void i2c_receive_event(int bytes_received){
    uint8_t reg_address=Wire.read();//get the register offset, always first byte sent
    if ((bytes_received>1) && (reg_address<RW_REGISTERS)) {
        //this was to write data to register
        have_i2c = true;
        for (int i=0; i<bytes_received-1; i++){
            REGBANK[reg_address+i]=Wire.read();
        }
        //if necessary, set some flags for future processing
        switch (reg_address) {
            case REG_ENABLE:
                // flag_enable=true;
                break;
        }
    } else {
        // this was a request to read data from registers
        request_address=reg_address; //save for request handler
    }
}

