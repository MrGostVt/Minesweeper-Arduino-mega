#include <Arduino.h>
#include <SPI.h>
#include <headers/image.h>
#include <headers/utils.h>
#include <headers/imagesBmp.h>

ImageBmp numberImages[8] = {
    ImageBmp(10,10, number1, 1),
    ImageBmp(10,10, number2, 2),
    ImageBmp(10,10, number3, 3),
    ImageBmp(10,10, number4, 4),
    ImageBmp(10,10, number5, 5),
    ImageBmp(10,10, number6, 6),
    ImageBmp(10,10, number7, 7),
    ImageBmp(10,10, number8, 8),
};
ImageBmp grass = ImageBmp(10,10, grassImage, 9);
ImageBmp grassFlag = ImageBmp(10,10, grassFlagImage, 10);
ImageBmp sand = ImageBmp(10,10, sandImage, 11);
ImageBmp pointerImg = ImageBmp(10,10, pointerImage, 12);
ImageBmp openedBombImg = ImageBmp(10,10, openedBombImage, 13);
ImageBmp images[7] = {sand, grass, grassFlag, grassFlag, openedBombImg, grassFlag, sand};