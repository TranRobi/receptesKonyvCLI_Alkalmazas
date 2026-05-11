#ifndef KATEGORIAIDOAJANLAT_H
#define KATEGORIAIDOAJANLAT_H

#include <vector>
#include "../ajanlat.h"

using namespace std;

// Kategoria es max elkeszitesi ido alapjan szelektaljuk a recepteket.
// A tiltott alapanyag szurest az ososztalytol kapjuk.
class KategoriaIdoAjanlat : public Ajanlat {
    private:
        int maxElkeszitesiIdo; // percben, ha 0 akkor nincs idobeli megkotes
    public:
        KategoriaIdoAjanlat();
        KategoriaIdoAjanlat(const vector<Recipe>&     receptek,
                            const vector<HozzaValok>& hozzavalok,
                            const vector<Ingridient>& alapanyagok,
                            Kategoria kat,
                            int maxIdo,
                            const vector<int>& elerhetoAlapanyagIds);
        ~KategoriaIdoAjanlat();

        void setMaxElkeszitesiIdo(int maxIdo);
        int  getMaxElkeszitesiIdo() const;

        vector<Recipe> ajanlatKeszit() const override;
};

#endif
