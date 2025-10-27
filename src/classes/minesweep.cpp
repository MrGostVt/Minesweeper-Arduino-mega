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
        case EASY: ceilSize = 40; break;
        case MIDDLE: ceilSize = 30; break;
        case HARD: ceilSize = 20; break;
    }
    fieldWidth = screenWidth/ceilSize;
    fieldHeight = screenHeight/ceilSize;
    bombCount = fieldHeight * 2;
    
    field = Field(fieldWidth, fieldHeight);
    field.fillByGrass();
}

