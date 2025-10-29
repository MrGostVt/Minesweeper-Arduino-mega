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
    OPENEDBOMB,
    FLAGONBOMB,
    NUMBER,
};

extern ImageBmp numberImages[8];
extern ImageBmp grass;
extern ImageBmp grassFlag;
extern ImageBmp sand;
extern ImageBmp pointerImg;
extern ImageBmp images[7];