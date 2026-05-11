#include "alapanyagKonyv.h"

AlapanyagKonyv::AlapanyagKonyv() {}

AlapanyagKonyv::~AlapanyagKonyv() {}

int AlapanyagKonyv::nextId() const {
    int maxId = 0;
    for (const auto& a : alapanyagok) {
        if (a.getId() > maxId) maxId = a.getId();
    }
    return maxId + 1;
}

void AlapanyagKonyv::addAlapanyag(const string& name, const string& unit) {
    alapanyagok.push_back(Ingridient(nextId(), name, unit));
}

void AlapanyagKonyv::removeAlapanyag(int id) {
    for (auto it = alapanyagok.begin(); it != alapanyagok.end(); ++it) {
        if (it->getId() == id) {
            alapanyagok.erase(it);
            break;
        }
    }
}

Ingridient* AlapanyagKonyv::searchById(int id) {
    for (auto& a : alapanyagok) {
        if (a.getId() == id) return &a;
    }
    return nullptr;
}

vector<Ingridient*> AlapanyagKonyv::searchByName(const string& name) {
    vector<Ingridient*> result;
    for (auto& a : alapanyagok) {
        if (a.getName().find(name) != string::npos) {
            result.push_back(&a);
        }
    }
    return result;
}

void AlapanyagKonyv::editName(int id, const string& newName) {
    if (Ingridient* a = searchById(id)) a->setName(newName);
}

void AlapanyagKonyv::editUnit(int id, const string& newUnit) {
    if (Ingridient* a = searchById(id)) a->setUnit(newUnit);
}

const vector<Ingridient>& AlapanyagKonyv::getAlapanyagok() const {
    return alapanyagok;
}

void AlapanyagKonyv::setAlapanyagok(const vector<Ingridient>& a) {
    alapanyagok = a;
}

void AlapanyagKonyv::listAlapanyagok(ostream& os) const {
    for (const auto& a : alapanyagok) {
        a.print(os);
    }
}
