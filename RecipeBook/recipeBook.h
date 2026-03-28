#ifndef RECIPEBOOK_H
#define RECIPEBOOK_H

#include <string>
#include "../Recipe/recipe.h"

class RecipeBook{
    Recipe* recipeBook;
    public:
        RecipeBook();
        Recipe& searchForRecipe(int id);
        Recipe& searchForRecipe(const string& name);
        
};
#endif