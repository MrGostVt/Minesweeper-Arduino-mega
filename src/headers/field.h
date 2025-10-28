#pragma once
#include <headers/utils.h>

class Field{
    private:
    int width;
    int height;

    int field [20][20];
    int bombCount = 0;

    private:
    void fillBy(Cell item);

    public:
    Field(){};
    Field(int size_w, int size_h);
    void reset();
    void reset(int size_w, int size_h);
    void fillByGrass();
    void fillFromStart(int start_x, int start_y, int bomb_count, Level lvl);
    int (&getField())[20][20]{
        return field;
    }
};