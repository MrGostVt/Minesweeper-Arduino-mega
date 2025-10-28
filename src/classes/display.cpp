#include <Arduino.h>
#include <SPI.h>
#include <headers/display.h>
#include <headers/utils.h>

Display::Display(int cs, int dc, int rst, int width, int height): TFT_CS(cs), TFT_DC(dc), TFT_RST(rst), WIDTH(width), HEIGHT(height){}

void Display::initILI9341(){
    digitalWrite(TFT_RST, LOW);
    delay(50);
    digitalWrite(TFT_RST, HIGH);
    delay(120);
  
    writeCommand(0x01); // Software reset
    delay(120);
  
    writeCommand(0x28); // Display OFF
    writeCommand(0xCF);
    writeData(0x00); writeData(0x83); writeData(0x30);
  
    writeCommand(0xED);
    writeData(0x64); writeData(0x03); writeData(0x12); writeData(0x81);
  
    writeCommand(0xE8);
    writeData(0x85); writeData(0x01); writeData(0x79);
  
    writeCommand(0xCB);
    writeData(0x39); writeData(0x2C); writeData(0x00); writeData(0x34); writeData(0x02);
  
    writeCommand(0xF7);
    writeData(0x20);
  
    writeCommand(0xEA);
    writeData(0x00); writeData(0x00);
  
    writeCommand(0xC0); // Power control
    writeData(0x26);
  
    writeCommand(0xC1); // Power control
    writeData(0x11);
  
    writeCommand(0xC5); // VCM control
    writeData(0x35); writeData(0x3E);
  
    writeCommand(0xC7); // VCM control2
    writeData(0xBE);
  
    writeCommand(0x36); // Memory Access Control
    writeData(0x48);
  
    writeCommand(0x3A); // Pixel Format
    writeData(0x55);    // 16-bit color
  
    writeCommand(0xB1); // Frame Rate
    writeData(0x00); writeData(0x1B);
  
    writeCommand(0xB6); // Display Function Control
    writeData(0x0A); writeData(0xA2);
  
    writeCommand(0xF2); // 3Gamma Function Disable
    writeData(0x00);
  
    writeCommand(0x26); // Gamma curve selected
    writeData(0x01);
  
    writeCommand(0xE0); // Set Gamma
    writeData(0x0F); writeData(0x31); writeData(0x2B); writeData(0x0C);
    writeData(0x0E); writeData(0x08); writeData(0x4E); writeData(0xF1);
    writeData(0x37); writeData(0x07); writeData(0x10); writeData(0x03);
    writeData(0x0E); writeData(0x09); writeData(0x00);
  
    writeCommand(0xE1); // Set Gamma
    writeData(0x00); writeData(0x0E); writeData(0x14); writeData(0x03);
    writeData(0x11); writeData(0x07); writeData(0x31); writeData(0xC1);
    writeData(0x48); writeData(0x08); writeData(0x0F); writeData(0x0C);
    writeData(0x31); writeData(0x36); writeData(0x0F);
  
    writeCommand(0x11); // Sleep out
    delay(120);
    writeCommand(0x29); // Display ON
}

void Display::drawPixel(uint16_t x, uint16_t y, uint16_t color){
    if (x >= WIDTH || y >= HEIGHT) return;
    setAddressWindow(x, y, x, y);
    writeData16(color);
}

void Display::writeData(uint8_t data) {
    digitalWrite(TFT_DC, HIGH);
    digitalWrite(TFT_CS, LOW);
    spiWrite(data);
    digitalWrite(TFT_CS, HIGH);
}

void Display::spiWrite(uint8_t data) {
    SPI.transfer(data);
}

void Display::writeCommand(uint8_t cmd){
    digitalWrite(TFT_DC, LOW);
    digitalWrite(TFT_CS, LOW);
    spiWrite(cmd);
    digitalWrite(TFT_CS, HIGH);
}

void Display::writeData16(uint16_t data) {
    digitalWrite(TFT_DC, HIGH);
    digitalWrite(TFT_CS, LOW);
    spiWrite(data >> 8);
    spiWrite(data & 0xFF);
    digitalWrite(TFT_CS, HIGH);
}

void Display::setAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    writeCommand(0x2A); // Column addr set
    digitalWrite(TFT_DC, HIGH);
    digitalWrite(TFT_CS, LOW);
    spiWrite(x0 >> 8); spiWrite(x0 & 0xFF);
    spiWrite(x1 >> 8); spiWrite(x1 & 0xFF);
    digitalWrite(TFT_CS, HIGH);
  
    writeCommand(0x2B); // Row addr set
    digitalWrite(TFT_DC, HIGH);
    digitalWrite(TFT_CS, LOW);
    spiWrite(y0 >> 8); spiWrite(y0 & 0xFF);
    spiWrite(y1 >> 8); spiWrite(y1 & 0xFF);
    digitalWrite(TFT_CS, HIGH);
  
    writeCommand(0x2C); // Write to RAM
}

void Display::fillScreen(uint16_t color) {
    setAddressWindow(0, 0, WIDTH - 1, HEIGHT - 1);
    digitalWrite(TFT_DC, HIGH);
    digitalWrite(TFT_CS, LOW);
    for (uint32_t i = 0; i < (uint32_t)WIDTH * HEIGHT; i++) {
      spiWrite(color >> 8);
      spiWrite(color & 0xFF);
    }
    digitalWrite(TFT_CS, HIGH);
}

void Display::drawImage(const uint16_t *img, int img_len, int w, int h, int x, int y) {
    int pixel_size = 1;
    if(w == h){
      if(img_len != w){
        pixel_size = w / img_len;
      }
    }
  
    for(int j = 0; j < h; j++){
      for(int i = 0; i < w; i++){
        int index = j/pixel_size * img_len + i/pixel_size;
        drawPixel(i + x, j + y, img[index]);
      }
    }
}

void Display::drawFieldByImages(ImageBmp<100> *imgs, int cell_size,int imgs_count, int (&field)[20][20], int field_w, int field_h){
  for(int j = 0; j < field_h; j++){
    for(int i = 0; i < field_w; i++){
      int id = field[j][i];
      ImageBmp<100> currentCeil = imgs[id];
      if(id > 5){
        currentCeil = imgs[0];
      }
      
      drawImage(currentCeil.getImageData(), currentCeil.getWidth(), cell_size, cell_size, i * cell_size, j*cell_size);
      
      if(id > 5){
        drawImageOnUpperLayer(numberImages[id-5-1].getImageData(), numberImages[id-5-1].getWidth(), cell_size, cell_size, i * cell_size, j*cell_size);
      }
    }
  }
}

void Display::drawImageOnUpperLayer(const uint16_t *img, int img_len, int w, int h, int x, int y){
  int pixel_size = 1;
  if(w == h){
    if(img_len != w){
      pixel_size = w / img_len;
    }
  }

  for(int j = 0; j < h; j++){
    for(int i = 0; i < w; i++){
      int index = j/pixel_size * img_len + i/pixel_size;
      if(img[index] != 0xffff){
        drawPixel(i + x, j + y, img[index]);
      }
    }
  }
}
