#ifndef RECIPE_H
#define RECIPE_H

#include <string>
#include "ingridient.h"
using namespace std;

class Recipe{
    static const int id;
    string name;
    Ingridient* ingridients;
    string description;
    public:
        Recipe(const string& name, Ingridient* Ingridients, const string& description);
        ~Recipe();
        const string& getName() const;
        const string& getDescription()const;
        const Ingridient* getIngridients() const;
        void setName(const string& newName);
        void setIngridients(Ingridient* ing);
        void setDescription(const string& newDescription);
};
#endif