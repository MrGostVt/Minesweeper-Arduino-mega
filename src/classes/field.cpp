#include <Arduino.h>
#include <SPI.h>
#include <headers/field.h>
#include <headers/utils.h>
#include <stdlib.h>

Field::Field(int size_w, int size_h): width(size_w), height(size_h){
    fillByGrass();
}

void Field::fillBy(Cell item){
    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            field[j][i] = item;
        }
    }
}

void Field::reset(){
    bombsOnField = 0;
    flagsOnBombs = 0;
    fillBy(SAND);
}
void Field::reset(int size_w, int size_h){
    reset();
    width = size_w;
    height = size_h;
}
void Field::fillByGrass(){
    bombsOnField = 0;
    flagsOnBombs = 0;
    fillBy(GRASS);
}

void Field::fillFromStart(int start_x, int start_y, int bomb_count, Level lvl){
    int safeZoneDefault;
    int safeZoneAdditional;
    int safeZoneCoords[4];

    switch(lvl){
        case EASY: safeZoneDefault = 3; safeZoneAdditional = 1; break;
        case MIDDLE: safeZoneDefault = 4; safeZoneAdditional = 2; break;
        case HARD: safeZoneDefault = 5; safeZoneAdditional = 3; break;
    }

    if(start_x - safeZoneDefault +1< 0){
        start_x = 0 + safeZoneDefault/2;
    }
    if (start_y - safeZoneDefault +1< 0)
    {
        start_y = 0 + safeZoneDefault/2;
    }
    if ( start_x + safeZoneDefault > width)
    {
        start_x = width-1 - safeZoneDefault/2;
    }
    if (start_y + safeZoneDefault > height)
    {
        start_y = height-1 - safeZoneDefault/2;
    }


    for(int i = 0; i < 2; i++){
        int safeZoneX = rand() % 2 - 1;
        int safeZoneY = rand() % 2 - 1;
        safeZoneCoords[i] = safeZoneX;
        safeZoneCoords[i+2] = safeZoneY;
    }

    int currentBombCount = bomb_count;
    for(int j = 0; j < height; j++){
        int lineBombsCount = currentBombCount % 2 == 0? bomb_count/height: bomb_count/height + 1;
        int bombsX[lineBombsCount];

        for(int b = 0; b < lineBombsCount; b++){
            bombsX[b] = rand() % width;
            // Serial.print(bombsX[b]);
            // Serial.write(" ");
        }

        for(int i = 0; i < width; i++){
            boolean isInDefaultZone = start_x-1 <= i && start_y-1 <=j && start_x+1 >= i && start_y+1 >= j ;

            // bool isInAdditionalZone; && 
            // for()
            bool isBomb = false;
            for(int b = 0; b < lineBombsCount; b++){
                isBomb = i == bombsX[b];
                if(isBomb){
                    break;
                }
            }
            if(isInDefaultZone){
                field[j][i] = SAND;
            }
            else if(isBomb){
                field[j][i] = BOMB;
                bombsOnField++;
            }
        }
    }
    
    //numbers
    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            bool isInDefaultZone = field[j][i] == SAND;
            int bombAroundCount = 0;
            if(isInDefaultZone){
                bombAroundCount = checkBombCount(i, j);
            }
            if(bombAroundCount != 0){
                field[j][i] = NUMBER + bombAroundCount;
            }
        }
    }
}

int Field::checkBombCount(int x, int y){
    int bombAroundCount = 0;

    for(int j = y - 1; j < y + 2; j++){
        for(int i = x - 1; i < x + 2; i++){
            if(field[j][i] == BOMB || field[j][i] == FLAGONBOMB || field[j][i] == OPENEDBOMB){
                bombAroundCount++;
            }
        }
    }
    return bombAroundCount;
}

bool Field::placeFlag(int x, int y){
        
    // Serial.println();
    // Serial.write("Flag count check! Flag on field: ");
    // Serial.print(flagsOnField);
    // Serial.write(" Flag on bomb: ");
    // Serial.print(flagsOnBombs);

    if(flagsOnField + flagsOnBombs >= bombsOnField){
        return false;
    }
    int cell = field[y][x];
    switch (cell)
    {
        case BOMB:
            field[y][x] = FLAGONBOMB;
            flagsOnBombs++;
            break;
        case SAND:
            return false;
        default:
            flagsOnField++;
            field[y][x] = FLAG;
            break;
    }

    if(flagsOnBombs == bombsOnField && flagsOnField == 0){
        return true;
    }
    return false;
}

bool Field::removeFlag(int x, int y){
    int cell = field[y][x];
    switch (cell)
    {
        case FLAGONBOMB:
            flagsOnBombs--;
            field[y][x] = BOMB;
            break;
        
        default:
            flagsOnField--;
            field[y][x] = GRASS;
            break;
    }

    if(flagsOnBombs == bombsOnField && flagsOnField == 0){
        return true;
    }
    return false;
}

bool Field::dig(int x, int y){
    int cell = field[y][x];
    switch (cell)
    {
        case BOMB:
            field[y][x] = OPENEDBOMB;
            return true;
        case GRASS:
            int bombAroundCount = checkBombCount(x, y);
            field[y][x] = NUMBER + bombAroundCount;
            return false;
        default:
            return false;
    }
}
