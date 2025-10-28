#pragma once
#include <Arduino.h>
#include <SPI.h>
#include <headers/image.h>

enum Level {
    EASY,
    MIDDLE,
    HARD,
};

enum Cell {
    SAND,
    GRASS,
    FLAG,
    BOMB,
    FLAGONBOMB,
    NUMBER,
};

extern uint16_t number8[100];
extern uint16_t number7[100];
extern uint16_t number6[100];
extern uint16_t number5[100];
extern uint16_t number4[100];
extern uint16_t number3[100];
extern uint16_t number2[100];
extern uint16_t number1[100];
extern ImageBmp<100> numberImages[8];

extern uint16_t pointer[100];
extern uint16_t grassImage[100];
extern uint16_t grassFlagImage[100];
extern uint16_t sandImage[100];

extern ImageBmp<100> grass;
extern ImageBmp<100> grassFlag;
extern ImageBmp<100> sand;
extern ImageBmp<100> images[6];
extern ImageBmp<100> pointerImg;
