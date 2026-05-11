#ifndef AJANLAT_H
#define AJANLAT_H

#include <vector>
#include <ostream>
#include "recipe.h"
#include "hozzaValok.h"
#include "ingridient.h"

using namespace std;

class Ajanlat {
    protected:
        vector<Recipe>     receptek;
        vector<HozzaValok> hozzavalok;
        vector<Ingridient> alapanyagok;

        // szuresi feltetelek - mindket leszarmazott hasznalhatja
        Kategoria      preferaltKategoria;
        vector<int>    elerhetoAlapanyagIds; // amit a felhasznalo megadott
        vector<int>    tiltottAlapanyagIds;  // ezeket kizarjuk

        // segitseggel ellenorizzuk hogy a recept megfelel-e
        bool containsTiltott(int recipeID) const;
        bool hasElerhetoAlapanyagok(int recipeID) const;

    public:
        Ajanlat();
        Ajanlat(const vector<Recipe>&     receptek,
                const vector<HozzaValok>& hozzavalok,
                const vector<Ingridient>& alapanyagok);
        virtual ~Ajanlat();

        void setReceptek(const vector<Recipe>& receptek);
        void setHozzavalok(const vector<HozzaValok>& hozzavalok);
        void setAlapanyagok(const vector<Ingridient>& alapanyagok);

        void setPreferaltKategoria(Kategoria kat);
        Kategoria getPreferaltKategoria() const;

        void addElerhetoAlapanyag(int ingridientID);
        void removeElerhetoAlapanyag(int ingridientID);
        const vector<int>& getElerhetoAlapanyagIds() const;

        void addTiltott(int ingridientID);
        void removeTiltott(int ingridientID);
        bool isTiltott(int ingridientID) const;

        // minden leszarmazott osztaly sajat modon csinalja meg az ajanlatot
        virtual vector<Recipe> ajanlatKeszit() const = 0;

        void listAjanlatok(ostream& os) const;
};

#endif
