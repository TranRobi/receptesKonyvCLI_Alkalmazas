#ifndef RECIPE_H
#define RECIPE_H

#include <string>
#include "../Ingridient/ingridient.h"
using namespace std;

class Recipe{
    static const int id;
    string name;
    Ingridient* ingridients;
    string description;
    public:
        Recipe(const string& name, Ingridient* Ingridients, const string& description);
        ~Recipe();
        string& getName();
        string& getDescription();
        Ingridient* getIngridients();
        void setName(const string& newName);
        void setIngridients(Ingridient* ing);
        void setDescription(const string& newDescription);
};
#endif