#include "ingridient.h"

Ingridient::Ingridient(const string& name, int amount, const string& unit) : name(name), amount(amount), unit(unit){
}
Ingridient::~Ingridient(){
}
const string& Ingridient::getName() const{
    return name;
}
const string& Ingridient::getUnit() const{
    return unit;
}

const int Ingridient::getAmount() const{
    return amount;
}
void Ingridient::setAmount(int newAmount){
    amount = newAmount;
}
void Ingridient::setName(const string& newName){
    name = newName;
}
void Ingridient::setUnit(const string& newUnit){
    unit = newUnit;
}