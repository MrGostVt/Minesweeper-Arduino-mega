#pragma once
#include <Arduino.h>
#include <SPI.h>
#include <headers/image.h>
#include <headers/button.h>

class Display{
    private:
    int TFT_CS;
    int TFT_DC;
    int TFT_RST;
    int WIDTH;
    int HEIGHT;
    int buttonWidth = 180;
    int buttonHeight = 40;
    int buttonSpace = 20;
    int lastFrameCell;
    
    uint8_t lastFrame[20][20];
    private:
    void setAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
    void writeData16(uint16_t data);
    void writeData(uint8_t data);
    void writeCommand(uint8_t cmd);
    void spiWrite(uint8_t data);

    public:
    Display() : TFT_CS(0), TFT_DC(0), TFT_RST(0), WIDTH(0), HEIGHT(0) {}
    Display(int cs, int dc, int rst, int width, int height);
    void initILI9341();
    void drawPixel(uint16_t x, uint16_t y, uint16_t color);
    void fillScreen(uint16_t color);
    void drawImage(ImageBmp img, int w, int h, int x, int y);
    void drawFieldByImages(int cell_size, uint8_t (&field)[20][20], int field_w, int field_h);
    void drawImageOnUpperLayer(ImageBmp img, int w, int h, int x, int y);
    void saveLastFrame(int j, int i, int pixelData);
    bool readLastFrame(int j, int i, int pixelData);
    template<int count>
    void drawButtons(Buttons<count> buttons){
        int startY = (HEIGHT - buttonHeight * count) / 2;
        for(int i = 0; i < count; i++){
          drawButton(buttons.isSelected(i), startY + i * buttonHeight + i * buttonSpace, buttons.colors[i]);
        }
      };
    void drawButton(bool isSelected, int y, uint16_t color);
    void redrawButtons();
};