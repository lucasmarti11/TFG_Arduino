#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include <stdint.h>

#include <FastLED.h>

typedef enum {RGB_LOOP, FADEINOUT, STROBE, CYLONBOUNCE, NEWKITT, TWINKLE} Led_Effect_t;

class Led {
  public:
    // Initializations

    Led(uint8_t pin_led_, uint8_t num_led_, Led_Effect_t current_eff_);

    // Les inicialitzacions dels pins s'han de fer dins el setup(), poden donar problemes si es fan al constructor ja que s'executarà abans del setup()
    void begin();

    void selectEffect(Led_Effect_t current_effect_);

  private:

    uint8_t   pin_led;
    uint8_t   num_led;
    Led_Effect_t current_eff;
    CRGB *leds;

    byte bright = 50;
    byte baza = 0;


    void RGBLoop();

    void FadeInOut(byte red, byte green, byte blue);

    void Strobe(byte red, byte green, byte blue, int StrobeCount, int FlashDelay, int EndPause);

    void CylonBounce(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);

    void NewKITT(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);

    void CenterToOutside(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);

    void OutsideToCenter(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);

    void LeftToRight(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);

    void RightToLeft(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);

    void Twinkle(byte red, byte green, byte blue, int Count, int SpeedDelay, boolean OnlyOne);

    void showStrip();

    void setPixel(int Pixel, byte red, byte green, byte blue);

    void setAll(byte red, byte green, byte blue);

};

#endif
