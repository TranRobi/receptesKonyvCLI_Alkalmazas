#ifndef INGRIDIENT_H
#define INGRIDIENT_H

#include <string>

using namespace std;
class Ingridient{
    private:
        string name;
        int amount;
        string unit;
    public:
        Ingridient(const string& name, int amount, const string& unit);
        ~Ingridient();
        const string& getName() const;
         const int getAmount() const;
        const string& getUnit() const;

        void setName(const string& newName);
        void setAmount(int newAmount);
        void setUnit(const string& newUnit);

};
#endif