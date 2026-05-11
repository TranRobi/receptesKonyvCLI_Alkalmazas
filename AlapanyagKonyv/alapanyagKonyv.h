#ifndef ALAPANYAGKONYV_H
#define ALAPANYAGKONYV_H

#include <string>
#include <vector>
#include <ostream>
#include "ingridient.h"

using namespace std;

// Csak az alapanyagokat kezeli (CRUD)
class AlapanyagKonyv {
    private:
        vector<Ingridient> alapanyagok;
        int nextId() const;
    public:
        AlapanyagKonyv();
        ~AlapanyagKonyv();

        void addAlapanyag(const string& name, const string& unit);
        void removeAlapanyag(int id);

        Ingridient*         searchById(int id);
        vector<Ingridient*> searchByName(const string& name);

        void editName(int id, const string& newName);
        void editUnit(int id, const string& newUnit);

        const vector<Ingridient>& getAlapanyagok() const;
        void setAlapanyagok(const vector<Ingridient>& a);
        void listAlapanyagok(ostream& os) const;
};

#endif
