#include "hetisMenuAjanlat.h"
#include <iostream>

HetisMenuAjanlat::HetisMenuAjanlat() {}

HetisMenuAjanlat::HetisMenuAjanlat(
    const vector<Recipe>&     receptek,
    const vector<HozzaValok>& hozzavalok,
    const vector<Ingridient>& alapanyagok,
    Kategoria kat,
    const vector<int>& elerhetoAlapanyagIds)
    : Ajanlat(receptek, hozzavalok, alapanyagok)
{
    preferaltKategoria         = kat;
    this->elerhetoAlapanyagIds = elerhetoAlapanyagIds;
}

HetisMenuAjanlat::~HetisMenuAjanlat() {}

// beolvassuk a heten evett recepteket a felhasznalotol (0-ra all meg)
void HetisMenuAjanlat::bekerHetesMenu() {
    hetbenEvettIds.clear();
    cout << "Kerek add meg a heten evett receptek ID-jait! (0 - befejezes)\n";
    int id;
    while (true) {
        cout << "Recept ID: ";
        cin >> id;
        if (id == 0) break;
        addHetbenEvett(id);
    }
}

void HetisMenuAjanlat::addHetbenEvett(int recipeID) {
    for (int id : hetbenEvettIds) {
        if (id == recipeID) return;
    }
    hetbenEvettIds.push_back(recipeID);
}

void HetisMenuAjanlat::removeHetbenEvett(int recipeID) {
    for (auto it = hetbenEvettIds.begin(); it != hetbenEvettIds.end(); ++it) {
        if (*it == recipeID) {
            hetbenEvettIds.erase(it);
            break;
        }
    }
}

bool HetisMenuAjanlat::wasEatenThisWeek(int recipeID) const {
    for (int id : hetbenEvettIds) {
        if (id == recipeID) return true;
    }
    return false;
}

const vector<int>& HetisMenuAjanlat::getHetbenEvettIds() const {
    return hetbenEvettIds;
}

// ez a fo szuresi logika: kizarjuk amit mar evett, nem megfelelo kategoriat, tiltottat es amit nem tud elkesziteni
vector<Recipe> HetisMenuAjanlat::ajanlatKeszit() const {
    vector<Recipe> result;
    for (const auto& r : receptek) {
        if (wasEatenThisWeek(r.getId())) {
            continue;
        }

        if (preferaltKategoria != Kategoria::ISMERETLEN && r.getKategoria() != preferaltKategoria) {
            continue;
        }

        if (containsTiltott(r.getId())) {
            continue;
        }

        if (!hasElerhetoAlapanyagok(r.getId())) {
            continue;
        }

        result.push_back(r);
    }
    return result;
}
