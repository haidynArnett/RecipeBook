#ifndef RECIPE_BOOK_H
#define RECIPE_BOOK_H

#include "Recipe.h"
#include <IOController.h>
#include <Utils.h>

namespace CocktailMaker {

  class RecipeBook {
    public:
      RecipeBook();
      ~RecipeBook();
      int recipeBrowseIndex;
      Recipe **recipes;
      Mode getMode();
      void initializeRecipes();
      void printRecipes();
      void browse();
      void calibrate();
      void execute();

    private:
      Mode mode = BROWSE;
      IOController controller;
      int numRecipes;
      Recipe *selectedRecipe;
      void addRecipe(Recipe *recipe);
      void showBrowsedRecipeName();

  };
}

#endif