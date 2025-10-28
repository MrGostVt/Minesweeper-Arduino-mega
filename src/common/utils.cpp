#include <Arduino.h>
#include <SPI.h>
#include <headers/image.h>
#include <headers/utils.h>
#include <headers/imagesBmp.h>

ImageBmp numberImages[8] = {
    ImageBmp(10,10, number1),
    ImageBmp(10,10, number2),
    ImageBmp(10,10, number3),
    ImageBmp(10,10, number4),
    ImageBmp(10,10, number5),
    ImageBmp(10,10, number6),
    ImageBmp(10,10, number7),
    ImageBmp(10,10, number8),
};
ImageBmp grass = ImageBmp(10,10, grassImage);
ImageBmp grassFlag = ImageBmp(10,10, grassFlagImage);
ImageBmp sand = ImageBmp(10,10, sandImage);
ImageBmp pointerImg = ImageBmp(10,10, pointerImage);
ImageBmp images[6] = {sand, grass, grassFlag, grassFlag, grass, sand};