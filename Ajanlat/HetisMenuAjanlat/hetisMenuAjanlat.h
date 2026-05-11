#ifndef HETISMENUAJANLAT_H
#define HETISMENUAJANLAT_H

#include <vector>
#include "../ajanlat.h"

using namespace std;

// Azokat a recepteket ajanlj, amelyeket a felhasznalo meg nem evett ezen a heten.
// Szurheto kategoria, elerheto alapanyagok es tiltott alapanyagok szerint is.
// (a tiltott szurest az ososztalytol kapjuk)
class HetisMenuAjanlat : public Ajanlat {
    private:
        vector<int> hetbenEvettIds; // ezeket mar ette a heten, nem ajanlunk ujra
    public:
        HetisMenuAjanlat();
        HetisMenuAjanlat(const vector<Recipe>&     receptek,
                         const vector<HozzaValok>& hozzavalok,
                         const vector<Ingridient>& alapanyagok,
                         Kategoria kat,
                         const vector<int>& elerhetoAlapanyagIds);
        ~HetisMenuAjanlat();

        // bekeri a felhasznalotol hogy mit evett mar ezen a heten
        void bekerHetesMenu();

        void addHetbenEvett(int recipeID);
        void removeHetbenEvett(int recipeID);
        bool wasEatenThisWeek(int recipeID) const;
        const vector<int>& getHetbenEvettIds() const;

        vector<Recipe> ajanlatKeszit() const override;
};

#endif
