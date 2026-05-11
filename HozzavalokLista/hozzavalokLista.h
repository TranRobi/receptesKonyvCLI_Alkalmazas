#ifndef HOZZAVALOK_LISTA_H
#define HOZZAVALOK_LISTA_H

#include <vector>
#include <ostream>
#include "hozzaValok.h"
#include "../Ingridient/ingridient.h"

using namespace std;

// ez az osztaly tartja nyilvan hogy melyik recepthez mi kell (recept-alapanyag kapcsolat)
class HozzavalokLista {
    private:
        vector<HozzaValok> hozzavalok;
    public:
        HozzavalokLista();
        ~HozzavalokLista();

        void addHozzavalo(int recipeID, int ingridientID, int amount);
        void removeHozzavalo(int recipeID, int ingridientID);
        void removeAllForRecipe(int recipeID);

        void editAmount(int recipeID, int ingridientID, int newAmount);

        vector<HozzaValok> getForRecipe(int recipeID) const;
        const vector<HozzaValok>& getHozzavalok() const;
        void setHozzavalok(const vector<HozzaValok>& h);
        void listForRecipe(int recipeID, const vector<Ingridient>& alapanyagok, ostream& os) const;
};

#endif
