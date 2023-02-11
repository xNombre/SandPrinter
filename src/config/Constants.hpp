#pragma once

#include <stdint.h>

#include <hardware/i2c.h>
#include <hardware/spi.h>


// Ref: https://pico.pinout.xyz/
class Constants {
public:
    // ***************** GPIOs *********************************
    // Buttons
    static inline const uint8_t BUTTON_UP_GPIO = 20;
    static inline const uint8_t BUTTON_OK_GPIO = 21;
    static inline const uint8_t BUTTON_DOWN_GPIO = 22;

    // Motors
    static inline const uint8_t MOTOR_DIR_X_GPIO = 8;
    static inline const uint8_t MOTOR_STEP_X_GPIO = 9;

    static inline const uint8_t MOTOR_DIR_Y_GPIO = 10;
    static inline const uint8_t MOTOR_STEP_Y_GPIO = 11;

    static inline const uint8_t MOTOR_BRUSH1_GPIO = 12;
    static inline const uint8_t MOTOR_BRUSH2_GPIO = 13;
    static inline const uint8_t MOTOR_BRUSH3_GPIO = 14;
    static inline const uint8_t MOTOR_BRUSH4_GPIO = 15;

    // Leds
    static inline const uint8_t STATUS_LED_GPIO = 25;
    // *********************************************************

    // ***************** DISPLAY *******************************
    static inline const uint8_t DISPLAY_SDA_GPIO = 26;
    static inline const uint8_t DISPLAY_SCL_GPIO = 27;
    static inline const uint8_t DISPLAY_MAX_CHAR = 16;
    static inline const uint8_t DISPLAY_MAX_LINE = 2;
    static inline const uint8_t DISPLAY_I2C_ADDRESS = 0x27;
    static inline i2c_inst_t *const DISPLAY_I2C_PORT = i2c1;
    // *********************************************************

    // ***************** BUTTON *******************************
    static inline const uint8_t BUTTON_DEBOUNCE_MS = 150;
    // *********************************************************


    // ***************** Card Reader *******************************
    static inline const uint8_t CARD_READER_CS_GPIO = 17;
    static inline const uint8_t CARD_READER_MISO_GPIO = 16;
    static inline const uint8_t CARD_READER_MOSI_GPIO = 19;
    static inline const uint8_t CARD_READER_SCLK_GPIO = 18;
    static inline spi_inst_t *const CARD_READER_SPI_PORT = spi0;
    // *********************************************************

    // ***************** Limit Switches ************************
    static inline const uint8_t LIMIT_SWITCH_X_GPIO = 6;
    static inline const uint8_t LIMIT_SWITCH_Y_GPIO = 7;
    // *********************************************************
};