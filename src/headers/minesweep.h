#pragma once
#include <headers/utils.h>
#include <headers/field.h>

class Minesweep{
    private:
    int screenWidth;
    int screenHeight;
    int ceilSize;
    int fieldWidth;
    int fieldHeight;
    int bombCount;
    Level gameLevel = EASY;
    Field field;

    public:
    Minesweep(int screen_width, int screen_height);
    Minesweep(int screen_width, int screen_height, Level lvl);
    
    private:
    void calculateFieldSizes();
    public:
    int (&getField())[20][20]{
        return field.getField();
    }
    int getCeilSize(){
        return ceilSize;
    }
    int getFieldWidth(){
        return fieldWidth;
    }
    int getFieldHeight(){
        return fieldHeight;
    }
    void start(int position_x, int position_y){
        return field.fillFromStart(position_x,position_y,bombCount, gameLevel);
    }
};