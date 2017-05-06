
#ifndef MBED_PINNAMES_H
#define MBED_PINNAMES_H

#include "cmsis.h"
#include "PinNamesTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    PA_0  = 0x00,
    PA_1  = 0x01,
    PA_2  = 0x02,
    PA_3  = 0x03,
    PA_4  = 0x04,
    PA_5  = 0x05,
    PA_6  = 0x06,
    PA_7  = 0x07,
    PA_8  = 0x08,
    PA_9  = 0x09,
    PA_10 = 0x0A,
    PA_11 = 0x0B,
    PA_12 = 0x0C,
    PA_13 = 0x0D,
    PA_14 = 0x0E,
    PA_15 = 0x0F,

    PB_0  = 0x10,
    PB_1  = 0x11,
    PB_2  = 0x12,
    PB_3  = 0x13,
    PB_4  = 0x14,
    PB_5  = 0x15,
    PB_6  = 0x16,
    PB_7  = 0x17,
    PB_8  = 0x18,
    PB_9  = 0x19,
    PB_10 = 0x1A,
    PB_11 = 0x1B,
    PB_12 = 0x1C,
    PB_13 = 0x1D,
    PB_14 = 0x1E,
    PB_15 = 0x1F,

    PC_0  = 0x20,
    PC_1  = 0x21,
    PC_2  = 0x22,
    PC_3  = 0x23,
    PC_4  = 0x24,
    PC_5  = 0x25,
    PC_6  = 0x26,
    PC_7  = 0x27,
    PC_8  = 0x28,
    PC_9  = 0x29,
    PC_10 = 0x2A,
    PC_11 = 0x2B,
    PC_12 = 0x2C,
    PC_13 = 0x2D,
    PC_14 = 0x2E,
    PC_15 = 0x2F,

    PD_2  = 0x32,

    // ADC internal channels
    ADC_TEMP = 0xF0,
    ADC_VREF = 0xF1,


    // PCB printout
    A0          = PA_0,
    A1          = PA_1,
    A2          = PA_2,
    A3          = PA_3,
    A4          = PA_4,
    A5          = PA_5,
    A6          = PA_6,
    A7          = PA_7,
    A8          = PA_8,
    A9          = PA_9,
    A10         = PA_10,
    A11         = PA_11,
    A12         = PA_12,
    A15         = PA_15,

    B0          = PB_0,
    B1          = PB_1,
    B2          = PB_2,
    B3          = PB_3,
    B4          = PB_4,
    B5          = PB_5,
    B6          = PB_6,
    B7          = PB_7,
    B8          = PB_8,
    B9          = PB_9,
    B10         = PB_10,
    B11         = PB_11,
    B12         = PB_12,
    B13         = PB_13,
    B14         = PB_14,
    B15         = PB_15,

    C13         = PC_13,
    C14         = PC_14,
    C15         = PC_15,

    // Generic signals namings
    LED1        = PC_13,
    LED2        = PC_13,
    LED3        = PC_13,
    LED4        = PC_13,
    SERIAL_TX   = PA_9,
    SERIAL_RX   = PA_10,
    UART2_TX    = PA_2,
    UART2_RX    = PA_3,
    USBTX       = PA_9,
    USBRX       = PA_10,
    I2C_SCL     = PB_6,
    I2C_SDA     = PB_7,
    I2C_SCL_S     = PB_10,
    I2C_SDA_S     = PB_11,
    SPI_MOSI    = PA_7,
    SPI_MISO    = PA_6,
    SPI_SCK     = PA_5,
    SPI_CS      = PA_4,
    PWM_OUT     = PB_5,

    // Not connected
    NC = (int)0xFFFFFFFF
} PinName;

#ifdef __cplusplus
}
#endif

#endif