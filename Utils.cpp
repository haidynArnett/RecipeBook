#include <Utils.h>;
#include <Arduino.h>;
#include <stdio.h>

namespace CocktailMaker {
    char *Utils::ingredientToString(Ingredient i) {
        switch (i) {
            case Vodka:         return "Vodka";
            case WhiteRum:      return "White Rum";
            case DarkRum:       return "Dark Rum";
            case Tequila:       return "Tequila";
            case Bourbon:       return "Bourbon";
            case Water:         return "Water";
            case Bitters:       return "Bitters";
            case LemonJuice:    return "Lemon Juice";
            case LimeJuice:     return "Lime Juice";
            case SimpleSyrup:   return "Simple Syrup";
            case Mint:          return "Mint";

        }
        return "That is not an Ingredient";
    }

    char *Utils::doubleToString(double d) {
        char * buffer;
        sprintf(buffer, "%.2d", d);
        return buffer;
    }
}