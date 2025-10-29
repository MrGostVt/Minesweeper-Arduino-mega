#pragma once
#include <headers/utils.h>
#include <Arduino.h>
#include <SPI.h>

class Field{
    private:
    int width;
    int height;

    uint8_t field [20][20];
    int bombsOnField = 0;
    int flagsOnBombs = 0;
    int flagsOnField = 0;

    private:
    void fillBy(Cell item);

    public:
    Field(){};
    Field(int size_w, int size_h);
    void reset();
    void reset(int size_w, int size_h);
    void fillByGrass();
    void fillFromStart(int start_x, int start_y, int bomb_count, Level lvl);
    uint8_t (&getField())[20][20]{
        return field;
    }
    bool placeFlag(int x, int y);
    bool removeFlag(int x, int y);
    int checkBombCount(int x, int y);
    bool dig(int x, int y);
    int checkCell(int x, int y){
        return field[y][x];
    }
};