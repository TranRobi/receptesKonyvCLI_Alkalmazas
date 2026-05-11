#include "recipe.h"
#include <ostream>

Recipe::Recipe()
    : id(0), name(""), description(""), kategoria(Kategoria::ISMERETLEN), elkeszitesiIdo(0) {}

Recipe::Recipe(int id, const string& name, const string& description,
               Kategoria kategoria, int elkeszitesiIdo)
    : id(id), name(name), description(description),
      kategoria(kategoria), elkeszitesiIdo(elkeszitesiIdo) {}

Recipe::~Recipe() {}

int Recipe::getId() const {
    return id;
}

const string& Recipe::getName() const {
    return name;
}

const string& Recipe::getDescription() const {
    return description;
}

Kategoria Recipe::getKategoria() const {
    return kategoria;
}

int Recipe::getElkeszitesiIdo() const {
    return elkeszitesiIdo;
}

void Recipe::setId(int newId) {
    id = newId;
}

void Recipe::setName(const string& newName) {
    name = newName;
}

void Recipe::setDescription(const string& newDescription) {
    description = newDescription;
}

void Recipe::setKategoria(Kategoria newKategoria) {
    kategoria = newKategoria;
}

void Recipe::setElkeszitesiIdo(int newIdo) {
    elkeszitesiIdo = newIdo;
}

string Recipe::kategoriaToString(Kategoria k) {
    switch (k) {
        case Kategoria::REGGELI: return "REGGELI";
        case Kategoria::EBED: return "EBED";
        case Kategoria::VACSORA: return "VACSORA";
        default: return "ISMERETLEN";
    }
}

Kategoria Recipe::stringToKategoria(const string& s) {
    if (s == "REGGELI") return Kategoria::REGGELI;
    if (s == "EBED") return Kategoria::EBED;
    if (s == "VACSORA") return Kategoria::VACSORA;
    return Kategoria::ISMERETLEN;
}

void Recipe::print(ostream& os) const {
    os << "[" << id << "] " << name << "\n"
       << "  Leiras: " << description << "\n"
       << "  Kategoria: " << kategoriaToString(kategoria) << "\n"
       << "  Elkeszitesi ido: " << elkeszitesiIdo << " perc\n";
}

bool Recipe::operator==(const Recipe& other) const {
    return id == other.id;
}
