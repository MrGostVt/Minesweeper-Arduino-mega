#pragma once
#include <headers/utils.h>
#include <Arduino.h>
#include <SPI.h>

template <int count>
class Buttons{
    public:
    uint16_t colors[count];
    int selected = 0;

    public:
    Buttons(){}
    uint16_t getSelectedColor(){
        return colors[selected];
    }
    void selectNext(){
        selected = selected + 1 == count? 0: selected+1;
    }
    void selectLast(){
        selected = selected - 1 == 0? count-1: selected-1;
    }
    void setColor(int id, uint16_t color){
        colors[id] = color;
    }
    bool isSelected(int id){
        return id == selected;
    }
};