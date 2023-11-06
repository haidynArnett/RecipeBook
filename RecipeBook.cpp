#include "RecipeBook.h"
#include <IOController.h>
#include <Arduino.h>
#include <string.h>
using namespace std;

namespace CocktailMaker {
  RecipeBook::RecipeBook() :
    controller()
  {
    this->recipes = calloc(MAX_NUM_RECIPES, sizeof(Recipe *));
    this->numRecipes = 0;
  }

  RecipeBook::~RecipeBook() {
    free(this->recipes);
  }

  Mode RecipeBook::getMode() {
    return this->mode;
  }

  void RecipeBook::initializeRecipes() {
    // all recipes are here
    Recipe *vodkaSour = new Recipe("Vodka Sour");
    vodkaSour->addStep(Step(Vodka, 2));
    vodkaSour->addStep(Step(LemonJuice, 0.5));
    vodkaSour->addStep(Step(SimpleSyrup, 0.5));
    this->addRecipe(vodkaSour);

    Recipe *oldFashioned = new Recipe("Old Fashioned");
    oldFashioned->addStep(Step(SimpleSyrup, 1.0 / 3));
    oldFashioned->addStep(Step(Water, 1.0 / 6));
    oldFashioned->addStep(Step(Bitters, 0.01));
    oldFashioned->addStep(Step(Bourbon, 1.5));
    this->addRecipe(oldFashioned);

    Recipe *mojito = new Recipe("Mojito");
    mojito->addStep(Step(WhiteRum, 2));
    mojito->addStep(Step(LimeJuice, 1));
    mojito->addStep(Step(SimpleSyrup, 0.5));
    this->addRecipe(mojito);

  }

  void RecipeBook::printRecipes() {
    for (int i = 0; i < numRecipes; i++) {
      this->recipes[i]->printRecipe();
    }
  }

  void RecipeBook::addRecipe(Recipe *recipe) {
    if (this->numRecipes < MAX_NUM_RECIPES) {
      this->recipes[this->numRecipes] = recipe;
      this->numRecipes++;
    } else {
      Serial.println("Max Number of recipes exceded");
      // throw 20;
    }
  }

  void RecipeBook::showBrowsedRecipeName() {
    String name = this->recipes[this->recipeBrowseIndex]->name;
    controller.showLCD(name);
  }

  void RecipeBook::browse() {
    this->showBrowsedRecipeName();
    controller.readButtons();
    Action action = controller.getAction();
    while (action != SELECT) {
      if (action == RIGHT) {
        this->recipeBrowseIndex = (this->recipeBrowseIndex + 1) % this->numRecipes;
        this->showBrowsedRecipeName();
      } else if (action == LEFT) {
        this->recipeBrowseIndex = (this->recipeBrowseIndex - 1 + this->numRecipes) % this->numRecipes;
        this->showBrowsedRecipeName();
      }

      controller.readButtons();
      action = controller.getAction();
    }
     
    this->selectedRecipe = this->recipes[this->recipeBrowseIndex];
    this->controller.showLCD("Selected: ", this->selectedRecipe->name);
    delay(2000);
  }

  void RecipeBook::calibrate() {
    this->controller.showLCD("Place your cup", "then press []");
    this->controller.waitForButtonPress();
    this->controller.zeroScale();
  }

  void RecipeBook::execute() {
    // this->selectedRecipe->printRecipe();
    while (selectedRecipe->hasNextStep()) {
      Step currentStep = selectedRecipe->getStep();
      currentStep.printStep();

      controller.showLCD(Utils::ingredientToString(currentStep.ingredient));
      float currentReading = this->controller.readScale();
      while (currentReading < currentStep.amount) {
        controller.showLEDs(currentStep.getPercentComplete(currentReading), 0, 0, 50);
        currentReading = this->controller.readScale();
        // Serial.println(currentReading);
      }
      if (!selectedRecipe->hasNextStep()) {
        break;
      }
      this->controller.zeroScale();
      this->controller.blinkLEDs(3, 250, 0, 255, 0);
    }
    this->controller.showSuccess();
    selectedRecipe->resetStepIterator();
    selectedRecipe = NULL;
  }
}