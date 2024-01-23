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
    //just in case, set SDA/SCL pins
    Wire.setSDA(PIN_MPU6050_I2C_SDA);
    Wire.setSCL(PIN_MPU6050_I2C_SCL);
    Wire.begin(address);
    Wire.onRequest(i2c_request_event);
    Wire.onReceive(i2c_receive_event);
}

void i2c_request_event(){
    Wire.write((char *)REGBANK+request_address, MAX_TRANSMIT_SIZE);
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
                flag_enable=true;
                break;
            /*case REG_ENC_RESET:
                flag_enc_reset=true;
                break; */
            case REG_POWER1:
            case REG_POWER2:
                flag_motor_power=true;
        }
    } else {
        // this was a request to read data from registers
        request_address=reg_address; //save for request handler
    }
}
