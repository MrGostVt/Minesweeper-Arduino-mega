#include <Arduino.h>
#include <SPI.h>
#include <math.h>
#include <headers/display.h>
#include <headers/image.h>
#include <headers/minesweep.h>
#include <headers/button.h>
#include <stdlib.h>

//display pins
#define TFT_CS   10
#define TFT_DC   9
#define TFT_RST  8

#define TFT_WIDTH  240
#define TFT_HEIGHT 320

//Joystick pins
#define VRX_PIN A0
#define VRY_PIN A1
#define SW_PIN  A2

//rgb565 macros
  #define COLOR565(r, g, b) ((((r) & 0xF8) << 8) | (((g) & 0xFC) << 3) | ((b) >> 3))

Display displayController(0,0,0,0,0);
Minesweep game;
GameState state;
Buttons<3> buttons;



void drawField(){
  int cell = game.getCellSize();
  auto& field = game.getField();
  displayController.drawFieldByImages(
    cell, field, game.getFieldWidth(), game.getFieldHeight() 
  );

  int x = game.pointerX(true) * cell;
  int y = game.pointerY(true) * cell;

  if(state == GAME){
    displayController.drawImageOnUpperLayer(pointerImg, cell, cell, x, y);
  }
}

void movePointer(int shiftX, int shiftY){
  game.movePointer(shiftX, shiftY);
  int oldCellData = game.getOldPointerData();
  int cellSize = game.getCellSize();
  int oldCellX = game.pointerX(false)*cellSize;
  int oldCellY = game.pointerY(false)*cellSize;
  int id = oldCellData;
  if(oldCellData > 6){
    id = 6;
  }
  // Serial.println();
  // Serial.write("Cell data: ");
  // Serial.print(oldCellData-5-1);
  displayController.drawImage(images[id], cellSize, cellSize, oldCellX, oldCellY);
  if(oldCellData > 6){
    displayController.drawImageOnUpperLayer(numberImages[oldCellData-7], cellSize, cellSize, oldCellX, oldCellY);
  }
  displayController.drawImageOnUpperLayer(pointerImg,game.getCellSize(), game.getCellSize(),
    game.pointerX(true)*game.getCellSize(), game.pointerY(true)*game.getCellSize()
  );
}

void prepareGame(){
  state = LEVELSCREEN;
  game = Minesweep(TFT_WIDTH, TFT_HEIGHT);
  game.setLevel(static_cast<Level>(buttons.selected));
  // game.start(2,3);
  drawField();

  displayController.drawButtons<3>(buttons);
}

void setup() {
  Serial.begin(9600);
  srand(analogRead(micros()));  
  pinMode(TFT_CS, OUTPUT);
  pinMode(TFT_DC, OUTPUT);
  pinMode(TFT_RST, OUTPUT);
  
  pinMode(SW_PIN, INPUT_PULLUP); // кнопка подтянута к VCC

  SPI.begin();
  SPI.beginTransaction(SPISettings(40000000, MSBFIRST, SPI_MODE0));

  displayController = Display(TFT_CS, TFT_DC, TFT_RST, TFT_WIDTH, TFT_HEIGHT);

  displayController.initILI9341();

  displayController.fillScreen(COLOR565(30, 144, 52));  // очистка

  buttons.setColor(0, COLOR565(0, 255,0));
  buttons.setColor(1, COLOR565(255, 255,0));
  buttons.setColor(2, COLOR565(255, 0,0));
  
  prepareGame();
}

void processGame(int shiftX, int shiftY){
  if(!game.isFieldLoaded()){
      game.start();
      Serial.println();
      Serial.write("game started: ");
      // Serial.print(oldCellData-5-1);
      drawField();
  }

  delay(500);
  int newestButtonInfo = digitalRead(SW_PIN);
  if(newestButtonInfo == 0){
    game.flagAction();
  }
  else{
    game.dig();        
  }
  drawField();
  delay(500);

  bool isGameFinished = game.checkGameComplection();
  if(isGameFinished){
    prepareGame();
  }
}

void loop() {
  int yValue = analogRead(VRX_PIN); // 0–1023
  int xValue = analogRead(VRY_PIN); // 0–1023
  int buttonInfo = digitalRead(SW_PIN); // 0 или 1


  int shiftX = xValue > 512? -1: xValue < 512? 1: 0;
  int shiftY = yValue > 512? -1: yValue < 512? 1: 0;

  if(shiftY != 0 && state == LEVELSCREEN){
    switch(shiftY){
      case -1:
        buttons.selectLast();
        break;
      case 1: 
        buttons.selectNext();
        break;
    }
    drawField();
    displayController.drawButtons<3>(buttons);
  }

  if((shiftX != 0 || shiftY != 0) && state == GAME){
    movePointer(shiftX, shiftY);
  }

  if(buttonInfo == 0){
    switch(state){
      case LEVELSCREEN: 
        // game.start();
        // processGame()
        game.setLevel(static_cast<Level>(buttons.selected));
        state = GAME;
        drawField();
        break;
      case GAME:
        processGame(shiftX, shiftY);
        break;
    }
  }
  delay(50);
}
