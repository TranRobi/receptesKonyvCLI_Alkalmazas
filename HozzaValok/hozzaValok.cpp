#include <ostream>
#include "hozzaValok.h"
#include "../memtrace.h"
HozzaValok::HozzaValok() : recipeID(0), ingridientID(0), amount(0) {}

HozzaValok::HozzaValok(int recipeID, int ingridientID, int amount)
    : recipeID(recipeID), ingridientID(ingridientID), amount(amount) {}

HozzaValok::~HozzaValok() {}

int HozzaValok::getRecipeID() const {
    return recipeID;
}

int HozzaValok::getIngridientID() const {
    return ingridientID;
}

int HozzaValok::getAmount() const {
    return amount;
}

void HozzaValok::setRecipeID(int newRecipeID) {
    recipeID = newRecipeID;
}

void HozzaValok::setIngridientID(int newIngridientID) {
    ingridientID = newIngridientID;
}

void HozzaValok::setAmount(int newAmount) {
    amount = newAmount;
}

void HozzaValok::print(ostream& os) const {
    os << recipeID << "," << ingridientID << "," << amount << "\n";
}

bool HozzaValok::operator==(const HozzaValok& other) const {
    return recipeID == other.recipeID && ingridientID == other.ingridientID;
}