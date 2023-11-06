#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

namespace CocktailMaker {
    static const int MAX_NUM_RECIPES = 20;
    static const int MAX_RECIPE_SIZE = 10;
    enum Action { NONE, LEFT, SELECT, RIGHT };
    enum Mode {BROWSE, CALIBRATE, EXECUTE};

    enum Ingredient {
        Vodka,
        WhiteRum,
        DarkRum,
        Tequila,
        Bourbon,
        Water,
        Bitters,
        LemonJuice,
        LimeJuice,
        SimpleSyrup,
        Mint
    };

    class Utils {
        public:
            static char *ingredientToString(Ingredient i);
            static char *doubleToString(double d);
    };

}

#endif