#pragma once
#include <Arduino.h>
#include <SPI.h>
#include <headers/field.h>
#include <headers/utils.h>
#include <stdlib.h>

Field::Field(int size_w, int size_h): width(size_w), height(size_h){
    fillByGrass();
}

void Field::fillBy(Ceil item){
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
            // bombsX[b] = (rand() % (width*100))/100; // в случае если часто налаживаются
            bombsX[b] = rand() % width;
        }
        for(int i = 0; i < width; i++){
            // boolean isInDefaultZone = start_x-1 >= i && start_y-1 >=i && start_x+1 <= i && start_y+1 <= i;
            // boolean isInDefaultZone = start_x-1 >= i && start_y-1 >=j ;
            boolean isInDefaultZone = start_x-1 <= i && start_y-1 <=j && start_x+1 >= i && start_y+1 >= j ;

            // bool isInAdditionalZone; && 
            // for()
            Serial.println();
            Serial.write("On the crossroads! ");
            Serial.print(start_x-1 >= i && start_y-1 >=i );
            bool isBomb;
            for(int b = 0; b < lineBombsCount; b++){
                isBomb = i == bombsX[b];
            }
            if(isInDefaultZone){
                Serial.println();
                Serial.write("in Default zone! ");
                // Serial.print();
                field[j][i] = SAND;
            }
            else if(isBomb){
                field[j][i] = BOMB;
            }
        }
    }
    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            bool isInDefaultZone = field[j][i] == SAND;
            int bombAroundCount = 0;
            for(int y = j - 1; y < j + 2; y++){
                for(int x = i - 1; x < i + 2; x++){
                    if(field[j][x] == BOMB){
                        bombAroundCount++;
                    }
                }
            }
            if(isInDefaultZone && bombAroundCount != 0){
                field[j][i] = NUMBER + bombAroundCount;
            }
        }
    }
}
