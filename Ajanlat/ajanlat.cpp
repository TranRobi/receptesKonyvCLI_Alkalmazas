#include "ajanlat.h"
#include <iostream>

Ajanlat::Ajanlat() : preferaltKategoria(Kategoria::ISMERETLEN) {}

Ajanlat::Ajanlat(const vector<Recipe>&     receptek,
                 const vector<HozzaValok>& hozzavalok,
                 const vector<Ingridient>& alapanyagok)
    : receptek(receptek), hozzavalok(hozzavalok), alapanyagok(alapanyagok),
      preferaltKategoria(Kategoria::ISMERETLEN) {}

Ajanlat::~Ajanlat() {}

void Ajanlat::setReceptek(const vector<Recipe>& receptek) {
    this->receptek = receptek;
}

void Ajanlat::setHozzavalok(const vector<HozzaValok>& hozzavalok) {
    this->hozzavalok = hozzavalok;
}

void Ajanlat::setAlapanyagok(const vector<Ingridient>& alapanyagok) {
    this->alapanyagok = alapanyagok;
}

void Ajanlat::setPreferaltKategoria(Kategoria kat) {
    preferaltKategoria = kat;
}

Kategoria Ajanlat::getPreferaltKategoria() const {
    return preferaltKategoria;
}

void Ajanlat::addElerhetoAlapanyag(int ingridientID) {
    for (int id : elerhetoAlapanyagIds) {
        if (id == ingridientID) return;
    }
    elerhetoAlapanyagIds.push_back(ingridientID);
}

void Ajanlat::removeElerhetoAlapanyag(int ingridientID) {
    for (auto it = elerhetoAlapanyagIds.begin(); it != elerhetoAlapanyagIds.end(); ++it) {
        if (*it == ingridientID) {
            elerhetoAlapanyagIds.erase(it);
            break;
        }
    }
}

const vector<int>& Ajanlat::getElerhetoAlapanyagIds() const {
    return elerhetoAlapanyagIds;
}

void Ajanlat::addTiltott(int ingridientID) {
    for (int id : tiltottAlapanyagIds) {
        if (id == ingridientID) return;
    }
    tiltottAlapanyagIds.push_back(ingridientID);
}

void Ajanlat::removeTiltott(int ingridientID) {
    for (auto it = tiltottAlapanyagIds.begin(); it != tiltottAlapanyagIds.end(); ++it) {
        if (*it == ingridientID) {
            tiltottAlapanyagIds.erase(it);
            break;
        }
    }
}

bool Ajanlat::isTiltott(int ingridientID) const {
    for (int id : tiltottAlapanyagIds) {
        if (id == ingridientID) return true;
    }
    return false;
}

bool Ajanlat::containsTiltott(int recipeID) const {
    for (const auto& h : hozzavalok) {
        if (h.getRecipeID() == recipeID) {
            if (isTiltott(h.getIngridientID())) {
                return true;
            }
        }
    }
    return false;
}

bool Ajanlat::hasElerhetoAlapanyagok(int recipeID) const {
    if (elerhetoAlapanyagIds.empty()) return true;

    // Minden felhasznalo altal megadott alapanyagnak benne kell lennie a receptben.
    // Ha a recept mas hozzavalot is hasznal, az nem szamit - csak azt nezuk amit a user megadott.
    for (int userId : elerhetoAlapanyagIds) {
        bool talalt = false;
        for (const auto& h : hozzavalok) {
            if (h.getRecipeID() == recipeID && h.getIngridientID() == userId) {
                talalt = true;
                break;
            }
        }
        if (!talalt) return false; // ez az alapanyag nincs a receptben
    }
    return true;
}

void Ajanlat::listAjanlatok(ostream& os) const {
    vector<Recipe> ajanlott = ajanlatKeszit();
    if (ajanlott.empty()) {
        os << "Nincs a felteteleknek megfelelo ajanlat.\n";
        return;
    }
    for (const auto& r : ajanlott) {
        r.print(os);
    }
}
