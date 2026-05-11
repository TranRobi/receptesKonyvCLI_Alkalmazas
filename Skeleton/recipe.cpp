#include "recipe.h"
#include "ingridient.h"

Recipe::Recipe(const string& name,Ingridient* Ingridients, const string& description){

}

Recipe::~Recipe(){

}
const string& Recipe::getName() const{
    return name;
}

const Ingridient* Recipe::getIngridients() const {
    return ingridients;
}

void Recipe::setName(const string& newName){

}

void Recipe::setIngridients(Ingridient* ing){

}

void Recipe::setDescription(const string& newDescription){
}
