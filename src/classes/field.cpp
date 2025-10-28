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
    fillBy(SAND);
}
void Field::reset(int size_w, int size_h){
    reset();
    width = size_w;
    height = size_h;
}
void Field::fillByGrass(){
    fillBy(GRASS);
}
//TODO: Добавить проверку на границы, и если выбрана крайняя клетка - сдвигать к центру квадрата.
void Field::fillFromStart(int start_x, int start_y, int bomb_count, Level lvl){
    bombCount = bomb_count;
    int safeZoneDefault;
    int safeZoneAdditional;
    int safeZoneCoords[4];

    switch(lvl){
        case EASY: safeZoneDefault = 3; safeZoneAdditional = 1; break;
        case MIDDLE: safeZoneDefault = 4; safeZoneAdditional = 2; break;
        case HARD: safeZoneDefault = 5; safeZoneAdditional = 3; break;
    }

    if(start_x - safeZoneDefault +1< 0){
        Serial.println();
        Serial.write("X ON LEFT ");
        Serial.print(start_x - safeZoneDefault);
        start_x = 0 + safeZoneDefault/2;
    }
    if (start_y - safeZoneDefault +1< 0)
    {
        Serial.println();
        Serial.write("Y ON TOP ");
        Serial.print(start_y - safeZoneDefault);
        start_y = 0 + safeZoneDefault/2;
    }
    if ( start_x + safeZoneDefault > width)
    {
        Serial.println();
        Serial.write("X ON RIGHT ");
        Serial.print(start_x + safeZoneDefault);
        start_x = width-1 - safeZoneDefault/2;
    }
    if (start_y + safeZoneDefault > height)
    {
        Serial.println();
        Serial.write("y on down ");
        Serial.print(start_y + safeZoneDefault);
        start_y = height-1 - safeZoneDefault/2;
    }
    
    // Serial.println();
    // Serial.write("START_X CHECK! ");
    // Serial.print(start_x);

    // Serial.println();
    // Serial.write("START_Y CHECK! ");
    // Serial.print(start_y);

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
                // Serial.println();
                // Serial.write("in Default zone! ");
                // Serial.print();
                field[j][i] = SAND;
            }
            else if(isBomb){
                field[j][i] = BOMB;
            }
        }
    }
    
    //numbers
    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            bool isInDefaultZone = field[j][i] == SAND;
            int bombAroundCount = 0;
            if(isInDefaultZone){
                for(int y = j - 1; y < j + 2; y++){
                    for(int x = i - 1; x < i + 2; x++){
                        if(field[y][x] == BOMB || field[y][x] == FLAGONBOMB){
                            bombAroundCount++;
                        }
                    }
                }
            }
            if(bombAroundCount != 0){
                // Serial.println();
                // Serial.write("Number check! j: ");
                // Serial.print(j);
                // Serial.write(" i: ");
                // Serial.print(i);
                field[j][i] = NUMBER + bombAroundCount;
            }
        }
    }
}
