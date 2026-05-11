#ifndef INGRIDIENT_H
#define INGRIDIENT_H

#include <string>
#include <ostream>

using namespace std;

class Ingridient {
    private:
        int id;
        string name;
        string unit;
    public:
        Ingridient();
        Ingridient(int id, const string& name, const string& unit);
        ~Ingridient();

        int getId() const;
        const string& getName() const;
        const string& getUnit() const;

        void setId(int newId);
        void setName(const string& newName);
        void setUnit(const string& newUnit);

        // Kiiratas: "id,nev,unit"
        void print(ostream& os) const;
        bool operator==(const Ingridient& other) const;
};

#endif