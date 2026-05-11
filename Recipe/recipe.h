#ifndef RECIPE_H
#define RECIPE_H

#include <string>
#include <ostream>

using namespace std;

enum class Kategoria {
    REGGELI,
    EBED,
    VACSORA,
    ISMERETLEN
};

class Recipe {
    private:
        int id;
        string name;
        string description;
        Kategoria kategoria;
        int elkeszitesiIdo; // percben
    public:
        Recipe();
        Recipe(int id, const string& name, const string& description,
               Kategoria kategoria, int elkeszitesiIdo);
        ~Recipe();

        int getId() const;
        const string& getName() const;
        const string& getDescription() const;
        Kategoria getKategoria() const;
        int getElkeszitesiIdo() const;

        void setId(int newId);
        void setName(const string& newName);
        void setDescription(const string& newDescription);
        void setKategoria(Kategoria newKategoria);
        void setElkeszitesiIdo(int newIdo);

        // Segedfu"ggvenyek a kategoriahoz
        static string kategoriaToString(Kategoria k);
        static Kategoria stringToKategoria(const string& s);

        // Kiiratas: "id,nev,leiras,kategoria,ido"
        void print(ostream& os) const;
        bool operator==(const Recipe& other) const;
};

#endif