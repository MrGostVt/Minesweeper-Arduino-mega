#pragma once
#include <Arduino.h>
#include <SPI.h>

template <int size>
class ImageBmp{
    private:
    int width;
    int height;
    uint16_t imageData[size];

    public:
    ImageBmp(int img_width, int img_height, const uint16_t (&image_data)[size])
        : width(img_width), height(img_height) 
    {
        // копируем данные вручную
        for (int i = 0; i < size; ++i) {
            imageData[i] = image_data[i];
        }
    }
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
};