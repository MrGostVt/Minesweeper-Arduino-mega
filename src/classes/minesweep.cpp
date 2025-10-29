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
    // if(!isStarted && fieldFillStatus){
    //     return;
    // }
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

void Minesweep::dig(){
    Serial.println();
    Serial.write("DIG!: ");
    bool isBomb = field.dig(pointerX(true), pointerY(true));
    isStarted = !isBomb;
}

void Minesweep::flagAction(){
    int cell = field.checkCell(pointerX(true), pointerY(true));
    if(cell == FLAGONBOMB || cell == FLAG ){
        isStarted = !field.removeFlag(pointerX(true), pointerY(true));
        return;
    }
    if(cell == SAND){
        return;
    }

    isStarted = !field.placeFlag(pointerX(true), pointerY(true));

}

void Minesweep::start(int position_x, int position_y){
    field.fillFromStart(position_x,position_y,bombCount, gameLevel);
    fieldFillStatus = true;
    isStarted = true;
}

void Minesweep::start(){
    field.fillFromStart(pointerX(true),pointerY(true),bombCount, gameLevel);
    isStarted = true;
    fieldFillStatus = true;
}

bool Minesweep::checkGameComplection(){
    return !isStarted;
}

void Minesweep::restart(){
    field.reset();
    field.fillByGrass();
    pointer[0] = 0;
    pointer[1] = 0;
    oldPointer[0] = 0;
    oldPointer[1] = 0;
}

void Minesweep::setLevel(Level lvl){
    gameLevel = lvl;
    calculateFieldSizes();
}