#ifndef CONFIG_H
#define CONFIG_H

#define STEPS 4320 // 360 * 12

#define A_STEP PB13 // f(scx)
#define A_DIR PB12 // CW/CCW
#define B_STEP PA9 // f(scx)
#define B_DIR PA8 // CW/CCW

#define C_STEP PB0 // f(scx)
#define C_DIR PB1 // CW/CCW
#define D_STEP PA2 // f(scx)
#define D_DIR PA3 // CW/CCW

#define E_STEP PB10 // f(scx)
#define E_DIR PB11 // CW/CCW
#define F_STEP PA0 // f(scx)
#define F_DIR PA1 // CW/CCW

// I2C address
#define ADDR_1 PB4
#define ADDR_2 PB3
#define ADDR_3 PA15
#define ADDR_4 PA12

#define WIRE_SDA PB7 // Alreaday defined
#define WIRE_SCL PB6

//#define RESET 

#endif