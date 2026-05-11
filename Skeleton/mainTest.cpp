#include <iostream>
#include <string>
#include "fileManager.h"
#include "menuSystem.h"
#include "recipe.h"
#include "recipeBook.h"

#include "memtrace.h"


int main() {
    MenuSystem menu;
    menu.printMenu();

    Ingridient* tesztIng = new Ingridient("Cukor", 200, "g");

    Recipe* tesztRecipe = new Recipe("Teszt Suti", tesztIng, "Keverd ossze es susd meg.");

    RecipeBook myBook;
    myBook.addRecipe("Gulyas", tesztIng, "Hagyomanyos recept");
    
    FileManager fm;
    fm.readFile("recipes.txt");
    fm.writeFile("recipes.txt");

    menu.exitMenu();

    delete tesztRecipe;

    std::cout << "A Skeleton tesztprogram sikeresen lefutott." << std::endl;

    return 0;
}