#include <headers/minesweep.h>

Minesweep::Minesweep(int screen_width, int screen_height): screenWidth(screen_width), screenHeight(screen_height) {
    calculateFieldSizes();
}

Minesweep::Minesweep(int screen_width, int screen_height, Level lvl): screenWidth(screen_width), screenHeight(screen_height), gameLevel(lvl) {
    calculateFieldSizes();
}

void Minesweep::calculateFieldSizes(){
    switch (gameLevel)
    {
        case EASY: cellSize = 40; break;
        case MIDDLE: cellSize = 30; break;
        case HARD: cellSize = 20; break;
    }
    fieldWidth = screenWidth/cellSize;
    fieldHeight = screenHeight/cellSize;
    bombCount = fieldHeight * 2;
    
    field = Field(fieldWidth, fieldHeight);
    field.fillByGrass();
    fieldFillStatus = false;
}

void Minesweep::movePointer(int shift_x, int shift_y){
    if(pointer[0]+shift_x < fieldWidth && pointer[0]+shift_x >= 0){
        oldPointer[0] = pointer[0];
        pointer[0] = pointer[0] + shift_x;
    }
    if(pointer[1]+shift_y < fieldHeight && pointer[1]+shift_y >= 0){
        oldPointer[1] = pointer[1];
        pointer[1] = pointer[1] + shift_y;
    }
}

int Minesweep::getOldPointerData(){
    auto& fieldData = field.getField();
    return fieldData[oldPointer[1]][oldPointer[0]];
}