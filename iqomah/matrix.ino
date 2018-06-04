/* ===================================
 * KONFIGURASI PIN ARDUINO UNO
 * ===================================
 * LED MATRIX 32 x 8
 * 
 * vcc    -> +5v
 * gnd    -> -5v
 * din    -> 11
 * cs/ss  -> 10
 * clk    -> 13
 * buzzer -> 2
 * push   -> 7  //push button harus konek pin 7 dan satunya ke vcc
 *              //pin 7 harus disambung ke ground dengan menggunakan 
 *              // resistor 10khm
 */
 
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

/* Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI ) */
/* Pin SS */
int pinCS = 10;

/* ROW */ 
int numberOfHorizontalDisplays = 1;

/* COLUMN */
int numberOfVerticalDisplays = 4;

/* Set max72xx panel library */
Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

/* init string messages */
String tape = ""; // Pesan yang ditampilkan  

/* kecepatan running-text ukuran miliseconds */
int wait = 100;        // Kecepatan text berjalan

/* jarak antar font */
int spacer = 1;
int width = 5 + spacer; // The font width is 5 pixels

void matrixSetup() {
  /* Atur kecerahan LED */
  matrix.setIntensity(1); // Use a value between 0 and 15 for brightness

  /* Pengaturan yang lebih spesifik */
  //  matrix.setPosition(0, 0, 0); // The first display is at <0, 0>
  //  matrix.setPosition(1, 1, 0); // The second display is at <1, 0>
  //  matrix.setPosition(2, 2, 0); // The third display is at <2, 0>
  //  matrix.setPosition(3, 3, 0); // And the last display is at <3, 0>
  //  ...
  //  matrix.setRotation(0, 2);    // The first display is position upside down
  //  matrix.setRotation(3, 2);    // The same hold for the last display
  
  matrix.setRotation(3); // set rotasi agar tidak vertical
}

/* Konfigurasi text diam */
void parkedText() {
  matrix.fillScreen(LOW);

  int i = matrix.width() - 1 - spacer;

  int letter = i / width; 
  int x = (matrix.width() - 1) - i % width;
  int y = (matrix.height() - 8) / 2; // center the text vertically

  while ( x + width - spacer >= 0 && letter >= 0 ) {
    if ( letter < tape.length() ) {
      matrix.drawChar(x, y, tape[letter], HIGH, LOW, 1);
    }

    letter--;
    x -= width;
  }
  matrix.write(); // Send bitmap to display

  delay(wait);
}

/* Konfigurasi text berjalan */
void runningText() {
  for ( int i = 0 ; i < width * tape.length() + matrix.width() - 1 - spacer; i++ ) {
  
    matrix.fillScreen(LOW);
  
    int letter = i / width;
    int x = (matrix.width() - 1) - i % width;
    int y = (matrix.height() - 8) / 2; // center the text vertically
  
    while ( x + width - spacer >= 0 && letter >= 0 ) {
      if ( letter < tape.length() ) {
        matrix.drawChar(x, y, tape[letter], HIGH, LOW, 1);
      }
  
      letter--;
      x -= width;
    }
    
    matrix.write();
    delay(wait);
  }  
}

void showMatrix(String msg, int mode) {
  tape = msg;
  if(mode == 0) parkedText();
  if(mode == 1) runningText();
}

void showMatrix(String msg) {
  tape = msg;
  parkedText();
}
