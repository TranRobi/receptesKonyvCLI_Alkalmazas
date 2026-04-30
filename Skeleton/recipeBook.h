#ifndef RECIPEBOOK_H
#define RECIPEBOOK_H

#include <string>
#include "recipe.h"

class RecipeBook{
    Recipe* recipeBook;
    public:
        RecipeBook();
        Recipe& searchForRecipe(int);
        Recipe& searchForRecipe(const string&);
        void listRecipeBook(const RecipeBook&);
        void editRecipeName(int id, string name);
        void editRecipeIngridient(int id, Ingridient* ing);
        void editRecipeDescription(int id, string description);
        void deleteRecipe(int id);
        void addRecipe(const string& name, Ingridient* ing, const string& desc);
    };
#endif