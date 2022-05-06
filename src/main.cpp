#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_GC9A01A.h"
#include <Adafruit_I2CDevice.h>

#define TFT_CS 5
#define TFT_DC 27
#define TFT_MOSI 15
#define TFT_SCLK 14
#define TFT_RST 33

Adafruit_GC9A01A tft(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
// Adafruit_GC9A01A tft(&SPI, TFT_CS, TFT_DC, TFT_RST);

// Adafruit_GC9A01A(_CS, _DC, _MOSI, _SCLK,  _RST = -1);

class FrameBuffer : public Adafruit_GFX
{
public:
  uint16_t *buffer;
  FrameBuffer(int16_t w, int16_t h) : Adafruit_GFX(w, h)
  {
    buffer = (uint16_t *)malloc(2 * h * w);
    for (int i = 0; i < h * w; i++)
      buffer[i] = 0;

    tft.fillScreen(GC9A01A_BLACK);
  }
  void drawPixel(int16_t x, int16_t y, uint16_t color)
  {
    buffer[((int16_t)y * 240) + x] = color;
  }

  void display()
  {
    tft.setAddrWindow(0, 0, 240, 240);
    tft.writePixels(buffer, 57600);
    // for (uint16_t i = 0; i < 57600; i++)
    // {
    //   int x = i / 240;
    //   int y = i % 240;
    //   tft.writePixel(x,y,buffer[i]);
    // }
    // tft.drawRGBBitmap(0,0,buffer,240,240);
  }
};

FrameBuffer frame(240, 240);

// uint16_t *framebuffer[2];

#define SIZE_X 240
#define RAD 80

const int ORIGIN_X = SIZE_X / 2;
const int ORIGIN_Y = SIZE_X / 2;
const float TAU = 2 * PI;
const uint32_t buffer_size = 57600;

void setup()
{
  Serial.begin(115200);
  // tft.spi
  //  framebuffer[0] = (uint16_t *)malloc(buffer_size);
  //  framebuffer[1] = (uint16_t *)malloc(buffer_size);
  //  memset(framebuffer[0], GC9A01A_BLACK, buffer_size);
  //  memset(framebuffer[1], GC9A01A_BLACK, buffer_size);

  // tft.fillScreen(GC9A01A_BLACK);

  tft.begin();
  tft.startWrite();
  // tft.startWrite();
  // tft.setAddrWindow(0, 0, 240, 240);
}

void writePixel(int flip, int16_t x, int16_t y, uint16_t color)
{
  // framebuffer[flip][((int16_t)y * 240) + x] = color;
}

void loop()
{
  for (int y = 0; y < 240; y++)
    for (int x = 0; x < 240; x++)
    {
      int rad = sqrtf(powf(x - RAD, 2) + powf(y - RAD, 2));
      if (rad > RAD)
        continue;
      frame.drawPixel(x, y, random(65535));
    }
  frame.display();

  // static int flip = 0;
  // static float value;
  // static float value1;
  // static float value2;
  // static float distance;
  // static int norm_value;
  // static unsigned int i;

  // static unsigned short x;
  // static unsigned short y;

  // static float _time = 1;
  // static unsigned int rad = 0;

  // flip = flip ? 0 : 1;

  // if (_time > TAU * 100)
  //   _time = 1;

  // _time = _time + 0.01;

  // for (y = 0; y < SIZE_X; ++y)
  // {
  //   for (x = 0; x < SIZE_X; ++x)
  //   {

  //     rad = sqrtf(powf(x - RAD, 2) + powf(y - RAD, 2));
  //     if (rad > RAD)
  //       continue;

  //     value1 = sinf((x * sinf(_time / 2) + y * cosf(_time / 3)) / 40.74f + _time * 2);
  //     distance = sqrtf(((ORIGIN_X - x) * (ORIGIN_X - x)) + ((ORIGIN_Y - y) * (ORIGIN_Y - y))) + 1;
  //     value2 = (sinf(distance / 40.74f)) + _time;
  //     value = value1 + value2;
  //     // norm_value = ((value1 + value2) * 8) + 128;

  //     writePixel(flip, x, y, tft.color565(128 + sinf(value) + 128, 108 + cosf(value) * 128, 128 + sinf(value) * 128));
  //   }
  // }

  // tft.setAddrWindow(0, 0, 240, 240);
  // digitalWrite(TFT_DC, HIGH);
  // digitalWrite(TFT_CS, LOW);
  // SPI.beginTransaction(SPISettings(80000000, MSBFIRST, SPI_MODE3));
  // for (uint16_t i = 0; i < buffer_size; i++)
  // {
  //   SPI.write16(framebuffer[flip][i]);
  // }
  // SPI.endTransaction();
  // digitalWrite(TFT_CS, HIGH);
}