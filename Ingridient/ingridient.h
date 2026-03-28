#ifndef INGRIDIENT_H
#define INGRIDIENT_H

#include <string>

using namespace std;
class Ingridient{
        string name;
        int amount;
        string unit;
    public:
        Ingridient(string& name, int amount, string& unit);
        ~Ingridient();
        string& getName() const;
        int getAmount() const;
        string& getUnit() const;

        void setName(const string& newName);
        void setAmount(int newAmount);
        void setUnit(const string& newUnit);

};
#endif