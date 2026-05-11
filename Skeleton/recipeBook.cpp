#include "recipeBook.h"

RecipeBook::RecipeBook(){

}
Recipe& RecipeBook::searchForRecipe(int id){
    return recipeBook[0];
}
Recipe& RecipeBook::searchForRecipe(const string& name){
    return recipeBook[0];
}
void RecipeBook::listRecipeBook(const RecipeBook&){}
void RecipeBook::editRecipeName(int id, string name){}
void RecipeBook::editRecipeIngridient(int id, Ingridient* ing){}
void RecipeBook::editRecipeDescription(int id, string description){}
void RecipeBook::deleteRecipe(int id){}
void RecipeBook::addRecipe(const string& name, Ingridient* ing, const string& desc){}