#include "ingridient.h"
#include <ostream>

Ingridient::Ingridient() : id(0), name(""), unit("") {}

Ingridient::Ingridient(int id, const string& name, const string& unit)
    : id(id), name(name), unit(unit) {}

Ingridient::~Ingridient() {}

int Ingridient::getId() const {
    return id;
}

const string& Ingridient::getName() const {
    return name;
}

const string& Ingridient::getUnit() const {
    return unit;
}

void Ingridient::setId(int newId) {
    id = newId;
}

void Ingridient::setName(const string& newName) {
    name = newName;
}

void Ingridient::setUnit(const string& newUnit) {
    unit = newUnit;
}

void Ingridient::print(ostream& os) const {
    os << "[" << id << "] " << name << " (" << unit << ")\n";
}

bool Ingridient::operator==(const Ingridient& other) const {
    return id == other.id;
}