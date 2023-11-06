#ifndef IOCONTROLLER_H
#define IOCONTROLLER_H

#include <Arduino.h>
#include <FastLED.h>
#include <LiquidCrystal.h>
#include <DebouncedButton.h>
#include <Utils.h>
#include "HX711.h"


#define LED_PIN   9
#define NUM_LEDS  60

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

#define LOADCELL_DOUT_PIN  A2
#define LOADCELL_SCK_PIN  A1
const float calibration_factor = 463700;

namespace CocktailMaker {
    class IOController {
        public:
            IOController();
            void showLCD(String message);
            void showLCD(String line1, String line2);
            void showLEDs(double percent, int r, int g, int b);
            void blinkLEDs(int times, int d, int r, int g, int b);
            void showSuccess();
            void readButtons();
            void zeroScale();
            float readScale(); // returns scale reading in grams
            enum Action getAction();
            void waitForButtonPress();
        private:
            LiquidCrystal lcd;
            CRGB leds[NUM_LEDS];
            HX711 scale;
            DebouncedButton rightButton;
            DebouncedButton middleButton;
            DebouncedButton leftButton;
    };
}

#endif