#pragma once
#include <Arduino.h>
#include <SPI.h>

// template <int size>
class ImageBmp{
    private:
    int width;
    int height;
    const uint16_t* imageData;

    public:
    ImageBmp(){};
    ImageBmp(int img_width, int img_height, const uint16_t* image_data)
        : width(img_width), height(img_height), imageData(image_data)
    {}
    boolean isSquare(){
        return width == height;
    }
    int getWidth(){
        return width;
    }
    int getHeight(){
        return height;
    }
    const uint16_t* getImageData(){
        return imageData;
    }
    uint16_t getPixel(uint16_t index) const {
        return pgm_read_word(&imageData[index]);
    }
};