#include "Recipe.h"
#include "Step.h"
#include <Arduino.h>

namespace CocktailMaker {

  Recipe::Recipe(char *name) {
    this->name = name;
    this->currentStep = 0;
    this->numSteps = 0;
    this->steps = calloc(MAX_RECIPE_SIZE, sizeof(Step));
  }
  Recipe::~Recipe() {
    free(this->steps);
  }

  void Recipe::addStep(Step step) {
    if (this->numSteps < MAX_RECIPE_SIZE) {
      this->steps[this->numSteps].ingredient = step.ingredient;
      this->steps[this->numSteps].amount = step.amount;
      this->numSteps++;
    } else {
      Serial.println("Max Number of steps exceded");
      // throw 20;
    }
  }

  Step Recipe::getStep() {
    Step prevStep = this->steps[this->currentStep];
    this->currentStep = this->currentStep + 1;
    return prevStep;
  }

  bool Recipe::hasNextStep() {
    return this->currentStep != this->numSteps;
  }

  void Recipe::resetStepIterator() {
    this->currentStep = 0;
  }

  void Recipe::printRecipe() {
    Serial.println(this->name);
    for (int i = 0; i < this->numSteps; i++) {
      this->steps[i].printStep();
    }
    Serial.println();
  }
}