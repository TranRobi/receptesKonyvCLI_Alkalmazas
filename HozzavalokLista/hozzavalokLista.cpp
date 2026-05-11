#include "hozzavalokLista.h"
#include "../Ingridient/ingridient.h"

HozzavalokLista::HozzavalokLista() {}

HozzavalokLista::~HozzavalokLista() {}

void HozzavalokLista::addHozzavalo(int recipeID, int ingridientID, int amount) {
    for (auto& h : hozzavalok) {
        if (h.getRecipeID() == recipeID && h.getIngridientID() == ingridientID) {
            h.setAmount(h.getAmount() + amount);
            return;
        }
    }
    hozzavalok.push_back(HozzaValok(recipeID, ingridientID, amount));
}

void HozzavalokLista::removeHozzavalo(int recipeID, int ingridientID) {
    for (auto it = hozzavalok.begin(); it != hozzavalok.end(); ++it) {
        if (it->getRecipeID() == recipeID && it->getIngridientID() == ingridientID) {
            hozzavalok.erase(it);
            break;
        }
    }
}

void HozzavalokLista::removeAllForRecipe(int recipeID) {
    for (auto it = hozzavalok.begin(); it != hozzavalok.end(); ) {
        if (it->getRecipeID() == recipeID) {
            it = hozzavalok.erase(it);
        } else {
            ++it;
        }
    }
}

void HozzavalokLista::editAmount(int recipeID, int ingridientID, int newAmount) {
    for (auto& h : hozzavalok) {
        if (h.getRecipeID() == recipeID && h.getIngridientID() == ingridientID) {
            h.setAmount(newAmount);
            break;
        }
    }
}

vector<HozzaValok> HozzavalokLista::getForRecipe(int recipeID) const {
    vector<HozzaValok> result;
    for (const auto& h : hozzavalok) {
        if (h.getRecipeID() == recipeID) {
            result.push_back(h);
        }
    }
    return result;
}

const vector<HozzaValok>& HozzavalokLista::getHozzavalok() const {
    return hozzavalok;
}

void HozzavalokLista::setHozzavalok(const vector<HozzaValok>& h) {
    hozzavalok = h;
}

void HozzavalokLista::listForRecipe(int recipeID, const vector<Ingridient>& alapanyagok, ostream& os) const {
    vector<HozzaValok> items = getForRecipe(recipeID);
    if (items.empty()) {
        os << "  (Nincsenek hozzavalok)\n";
        return;
    }
    for (const auto& item : items) {
        // Alapanyag nev keresese
        const Ingridient* alap = nullptr;
        for (const auto& a : alapanyagok) {
            if (a.getId() == item.getIngridientID()) {
                alap = &a;
                break;
            }
        }
        if (alap) {
            os << "  - " << alap->getName() << ": " << item.getAmount() << " " << alap->getUnit() << "\n";
        } else {
            os << "  - [AlapanyagID=" << item.getIngridientID() << "]: " << item.getAmount() << "\n";
        }
    }
}
