#ifndef STEP_H
#define STEP_H
#include <Utils.h>
#include <Arduino.h>

using namespace std;

namespace CocktailMaker {

  class Step {
    public:
      Step(Ingredient ingredient, double amount);
      void printStep();
      float getPercentComplete(float amount); // amount in grams
      Ingredient ingredient;
      double amount; // in grams

    private:
  };
}

#endif