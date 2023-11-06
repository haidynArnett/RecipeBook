#ifndef RECIPE_H
#define RECIPE_H

#include <Arduino.h>
#include "Step.h"

namespace CocktailMaker {

  class Recipe {
    public:
      Recipe(char *name);
      ~Recipe();
      void addStep(Step step);
      char *name;
      Step getStep();
      bool hasNextStep();
      void resetStepIterator();
      void printRecipe();
    private:
      Step *steps;
      int numSteps = 0;
      int currentStep = 0;
  };
}

#endif