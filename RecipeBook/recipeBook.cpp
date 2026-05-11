#include "recipeBook.h"

RecipeBook::RecipeBook() {}

RecipeBook::~RecipeBook() {}

int RecipeBook::nextId() const {
    int maxId = 0;
    for (const auto& r : receptek) {
        if (r.getId() > maxId) maxId = r.getId();
    }
    return maxId + 1;
}

void RecipeBook::addRecipe(const string& name, const string& desc,
                           Kategoria kat, int elkeszitesiIdo) {
    receptek.push_back(Recipe(nextId(), name, desc, kat, elkeszitesiIdo));
}

void RecipeBook::removeRecipe(int id) {
    for (auto it = receptek.begin(); it != receptek.end(); ++it) {
        if (it->getId() == id) {
            receptek.erase(it);
            break;
        }
    }
}

Recipe* RecipeBook::searchById(int id) {
    for (auto& r : receptek) {
        if (r.getId() == id) return &r;
    }
    return nullptr;
}

vector<Recipe*> RecipeBook::searchByName(const string& name) {
    vector<Recipe*> result;
    for (auto& r : receptek) {
        if (r.getName().find(name) != string::npos) {
            result.push_back(&r);
        }
    }
    return result;
}

vector<Recipe*> RecipeBook::searchByKategoria(Kategoria kat) {
    vector<Recipe*> result;
    for (auto& r : receptek) {
        if (r.getKategoria() == kat) {
            result.push_back(&r);
        }
    }
    return result;
}

void RecipeBook::editName(int id, const string& newName) {
    if (Recipe* r = searchById(id)) r->setName(newName);
}

void RecipeBook::editDescription(int id, const string& newDesc) {
    if (Recipe* r = searchById(id)) r->setDescription(newDesc);
}

void RecipeBook::editKategoria(int id, Kategoria newKat) {
    if (Recipe* r = searchById(id)) r->setKategoria(newKat);
}

void RecipeBook::editElkeszitesiIdo(int id, int newIdo) {
    if (Recipe* r = searchById(id)) r->setElkeszitesiIdo(newIdo);
}

const vector<Recipe>& RecipeBook::getReceptek() const {
    return receptek;
}

void RecipeBook::setReceptek(const vector<Recipe>& r) {
    receptek = r;
}

void RecipeBook::listReceptek(ostream& os) const {
    for (const auto& r : receptek) {
        r.print(os);
    }
}