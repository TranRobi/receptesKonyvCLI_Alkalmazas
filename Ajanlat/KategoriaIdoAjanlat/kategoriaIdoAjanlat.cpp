#include "kategoriaIdoAjanlat.h"

KategoriaIdoAjanlat::KategoriaIdoAjanlat() : maxElkeszitesiIdo(0) {}

KategoriaIdoAjanlat::KategoriaIdoAjanlat(
    const vector<Recipe>&     receptek,
    const vector<HozzaValok>& hozzavalok,
    const vector<Ingridient>& alapanyagok,
    Kategoria kat,
    int maxIdo,
    const vector<int>& elerhetoAlapanyagIds)
    : Ajanlat(receptek, hozzavalok, alapanyagok),
      maxElkeszitesiIdo(maxIdo)
{
    preferaltKategoria      = kat;
    this->elerhetoAlapanyagIds = elerhetoAlapanyagIds;
}

KategoriaIdoAjanlat::~KategoriaIdoAjanlat() {}

void KategoriaIdoAjanlat::setMaxElkeszitesiIdo(int maxIdo) {
    maxElkeszitesiIdo = maxIdo;
}

int KategoriaIdoAjanlat::getMaxElkeszitesiIdo() const {
    return maxElkeszitesiIdo;
}

// vegigmegy a recepteken es kiszuri azokat amelyek megfelelenek a feltételeknek
vector<Recipe> KategoriaIdoAjanlat::ajanlatKeszit() const {
    vector<Recipe> result;
    for (const auto& r : receptek) {
        if (preferaltKategoria != Kategoria::ISMERETLEN && r.getKategoria() != preferaltKategoria) {
            continue;
        }

        if (maxElkeszitesiIdo > 0 && r.getElkeszitesiIdo() > maxElkeszitesiIdo) {
            continue;
        }

        if (containsTiltott(r.getId())) {
            continue;
        }

        if (!hasElerhetoAlapanyagok(r.getId())) {
            continue;
        }

        result.push_back(r);
    }
    return result;
}
