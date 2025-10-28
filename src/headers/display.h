#pragma once
#include <Arduino.h>
#include <SPI.h>
#include <headers/image.h>

class Display{
    private:
    int TFT_CS;
    int TFT_DC;
    int TFT_RST;
    int WIDTH;
    int HEIGHT;
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
    void drawImage(const uint16_t *img, int img_len, int w, int h, int x, int y);
    void drawFieldByImages(ImageBmp<100> *imgs, int cell_size,int imgs_count, int (&field)[20][20], int field_w, int field_h);
    void drawImageOnUpperLayer(const uint16_t *img, int img_len, int w, int h, int x, int y);
};