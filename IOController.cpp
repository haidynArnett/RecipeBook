#include "IOController.h"
#include <Utils.h>

namespace CocktailMaker {

    IOController::IOController()
        : lcd(rs, en, d4, d5, d6, d7),
        rightButton(6),
        middleButton(7),
        leftButton(8)
    {
        // lcd setup
        this->lcd.begin(16, 2);

        // LEDs setup
        FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);

        // scale setup
        scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
        scale.set_scale(calibration_factor);
    }

    void IOController::showLCD(String message) {
        lcd.clear();
        lcd.print(message);
    }

    void IOController::showLCD(String line1, String line2) {
        lcd.clear();
        lcd.print(line1);
        lcd.setCursor(0, 1);
        lcd.print(line2);
        lcd.setCursor(0, 0);
    }

    // percent is from 0 - 1
    void IOController::showLEDs(double percent, int r, int g, int b) {
        double litLEDs = (int)(percent * NUM_LEDS);
        for (int i = 0; i < NUM_LEDS; i++) {
            if (i < litLEDs) {
                leds[i] = CRGB(r, g, b);
            } else {
                leds[i] = CRGB(0, 0, 0);
            }
        }
        FastLED.show();
    }

    void IOController::blinkLEDs(int times, int d, int r, int g, int b) {
        for (int i = 0; i < times; i++) {
            for (int i = 0; i < 60; i++) {
                leds[i] = CRGB(r, g, b);
            }
            FastLED.show();
            delay(d);
            for (int i = 0; i < 60; i++) {
                leds[i] = CRGB (0, 0, 0);
            }
            FastLED.show();
            delay(d);
        }
    }

    void IOController::showSuccess() {
        this->showLCD("Drink",  "Responsibly");
        this->blinkLEDs(2, 400, 0, 255, 0);
        delay(5000);
    }

    void IOController::readButtons() {
        this->rightButton.takeReading();
        this->middleButton.takeReading();
        this->leftButton.takeReading();
    }

    void IOController::zeroScale() {
        scale.tare();
    }

    float IOController::readScale() {
        return scale.get_units() * 1000;
    }

    enum Action IOController::getAction() {
        if (this->middleButton.getPressed()) {
            return SELECT;
        }
        bool right = this->rightButton.getPressed();
        bool left = this->leftButton.getPressed();
        if (right && !left) {
            return RIGHT;
        } else if (!right && left) {
            return LEFT;
        } else {
            return NONE;
        }
    }

    void IOController::waitForButtonPress() {
        this->readButtons();
        while (this->getAction() == NONE) {
            this->readButtons();
        }
    }
}
