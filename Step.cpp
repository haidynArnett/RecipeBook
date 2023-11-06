#include "Step.h"
#include <string.h>
#include <Utils.h>
#include <Arduino.h>
using namespace std;

namespace CocktailMaker {
  // amount in grams
  Step::Step(Ingredient ingredient, double amount) {
    this->ingredient = ingredient;
    this->amount = amount * 29.5735;
  }

  float Step::getPercentComplete(float amount) {
    return amount / this->amount;
  }

  void Step::printStep() {
    char *s = Utils::ingredientToString(this->ingredient);
    Serial.print(s);
    Serial.print(", ");
    Serial.println(this->amount);
  }
}