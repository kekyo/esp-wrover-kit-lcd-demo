// This is a minimalist demonstration for using Ucglib on ESP-WROVER-KIT V1.4 with PlatformIO.
// Copyright (c) Kouji Matsui, License under MIT
// https://github.com/kekyo/esp-wrover-kit-lcd-demo/
//
// ESP-WROVER-KIT: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/hw-reference/esp32/get-started-wrover-kit.html
// Ucglib: https://github.com/olikraus/ucglib

//////////////////////////////////////////////////////////////////

// Comments out when required software-based SPI.
#define LCD_SPI_HW

// (Optional, drive with LED)
#define WITH_LED

//////////////////////////////////////////////////////////////////

#include <Arduino.h>
#include <SPI.h>
#include <Ucglib.h>

//////////////////////////////////////////////////////////////////

// ESP-WROVER-KIT aasignment       LCD (ILI9341)
#define LCD_RST   18   // RST  --> RESET
#define LCD_SCLK  19   // SCLK --> SCL
#define LCD_DC    21   // DC   --> D/C
#define LCD_CS    22   // CS   --> CS
#define LCD_MOSI  23   // MOSI --> SDA
#define LCD_MISO  25   // MISO <-- SDO
#define LCD_BL    5    // BL   --> LEDK

#if defined(WITH_LED)
#define LED_RED 0     // Onboard Red LED
#define LED_GREEN 2   // Onboard Green LED
#define LED_BLUE 4    // Onboard Blue LED
#endif

//////////////////////////////////////////////////////////////////

#if defined(LCD_SPI_HW)
static Ucglib_ILI9341_18x240x320_HWSPI ucg(LCD_DC, LCD_CS, LCD_RST);
#else
static Ucglib_ILI9341_18x240x320_SWSPI ucg(LCD_SCLK, LCD_MOSI, LCD_DC, LCD_CS, LCD_RST);
#endif

//////////////////////////////////////////////////////////////////

void setup(void) {
  delay(1000);

#if defined(WITH_LED)
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, LOW);
#endif

  // Enable backlight.
  pinMode(LCD_BL, OUTPUT);
  digitalWrite(LCD_BL, LOW);

#if defined(LCD_SPI_HW)
  // Initialize hardware-based SPI, assigned using ESP32 VSPI.
  SPI.begin(LCD_SCLK, LCD_MISO, LCD_MOSI, LCD_CS);
#endif

  // Initialize Ucglib
  ucg.begin(UCG_FONT_MODE_TRANSPARENT);
  ucg.clearScreen();
  ucg.setRotate90();
  ucg.setFont(ucg_font_8x13_tf);
}

//////////////////////////////////////////////////////////////////

static int colorIndex = 0;

void loop(void) {

  switch (colorIndex) {
    // Red
    case 0:
#if defined(WITH_LED)
      digitalWrite(LED_RED, HIGH);
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_BLUE, LOW);
#endif
      ucg.setColor(255, 0, 0);
      ucg.setPrintPos(50,50);
      ucg.print("Hello World!");
      break;

    // Green
    case 1:
#if defined(WITH_LED)
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_GREEN, HIGH);
      digitalWrite(LED_BLUE, LOW);
#endif
      ucg.setColor(0, 255, 0);
      ucg.setPrintPos(50,50);
      ucg.print("Hello World!");
      break;

    // Blue
    case 2:
#if defined(WITH_LED)
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_BLUE, HIGH);
#endif
      ucg.setColor(0, 0, 255);
      ucg.setPrintPos(50,50);
      ucg.print("Hello World!");
      break;
  }

  colorIndex = (colorIndex + 1) % 3;
  delay(500);
}
