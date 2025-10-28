#pragma once
#include <headers/utils.h>
#include <headers/field.h>

class Minesweep{
    private:
    int screenWidth;
    int screenHeight;
    int cellSize;
    int fieldWidth;
    int fieldHeight;
    int bombCount;
    int pointer[2] = {0,0};
    int oldPointer[2] = {0,0};
    Level gameLevel = EASY;
    Field field;
    bool fieldFillStatus = false;


    public:
    Minesweep(){}
    Minesweep(int screen_width, int screen_height);
    Minesweep(int screen_width, int screen_height, Level lvl);
    
    private:
    void calculateFieldSizes();
    public:
    int (&getField())[20][20]{
        return field.getField();
    }
    int getCellSize(){
        return cellSize;
    }
    int getFieldWidth(){
        return fieldWidth;
    }
    int getFieldHeight(){
        return fieldHeight;
    }
    void start(int position_x, int position_y){
        field.fillFromStart(position_x,position_y,bombCount, gameLevel);
        fieldFillStatus = true;
    }
    void start(){
        field.fillFromStart(pointerX(true),pointerY(true),bombCount, gameLevel);
        fieldFillStatus = true;
    }
    void movePointer(int x, int y);
    //Old - false, current - true;
    int pointerX(bool type){
        if(type){
            return pointer[0];
        }
        return oldPointer[0];
    }
    int pointerY(bool type){
        if(type){
            return pointer[1];
        }
        return oldPointer[1];
    }
    int getOldPointerData();
    bool isFieldLoaded(){
        return fieldFillStatus;
    }
};