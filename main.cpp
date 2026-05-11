#include <iostream>
#include <string>
#include <limits>

#include "./menuSystem/menuSystem.h"
#include "./RecipeBook/recipeBook.h"
#include "./AlapanyagKonyv/alapanyagKonyv.h"
#include "./HozzavalokLista/hozzavalokLista.h"
#include "./fileManager/fileManager.h"
#include "./Ajanlat/KategoriaIdoAjanlat/kategoriaIdoAjanlat.h"
#include "./Ajanlat/HetisMenuAjanlat/hetisMenuAjanlat.h"

using namespace std;

// cin utan marad egy '\n' a bufferben, ezt kell tisztitani getline elott
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// beolvas hozzavalokat egy recepthez (ID + mennyiseg paronkent, 0-ra all meg)
void bekerHozzavalok(int receptId, AlapanyagKonyv& alapanyagKonyv, HozzavalokLista& hozzavalokLista) {
    cout << "Elerheto alapanyagok:\n";
    alapanyagKonyv.listAlapanyagok(cout);
    cout << "Add meg a hozzavalokat (Alapanyag ID es Mennyiseg, 0 = kesz):\n";
    int hId, hAmount;
    while (true) {
        cout << "  Alapanyag ID: "; cin >> hId;
        if (hId == 0) break;
        if (!alapanyagKonyv.searchById(hId)) {
            cout << "  Nincs ilyen alapanyag, proba ujra.\n";
            continue;
        }
        cout << "  Mennyiseg: "; cin >> hAmount;
        hozzavalokLista.addHozzavalo(receptId, hId, hAmount);
    }
}

// bekeri a tiltott alapanyag ID-kat az ajanlat szureshez (-1 = nincs tiltott)
void bekerTiltottAlapanyagok(Ajanlat& ajanlat) {
    cout << "Tiltott alapanyagok ID-jai (0 = kesz, -1 = nincs tiltott):\n";
    int tId; cin >> tId;
    if (tId == -1) return;
    while (tId != 0) {
        ajanlat.addTiltott(tId);
        cin >> tId;
    }
}

// kiirja az ajanlott recepteket a hozzavalokkal egyutt
void printAjanlottak(const vector<Recipe>& ajanlottak, HozzavalokLista& hozzavalokLista, AlapanyagKonyv& alapanyagKonyv) {
    cout << "\n--- AJANLOTT RECEPTEK ---\n";
    if (ajanlottak.empty()) {
        cout << "Nincs a felteteleknek megfelelo ajanlat.\n";
        return;
    }
    for (const auto& r : ajanlottak) {
        r.print(cout);
        cout << "  Hozzavalok:\n";
        hozzavalokLista.listForRecipe(r.getId(), alapanyagKonyv.getAlapanyagok(), cout);
    }
}

// --- RECEPT MUVELETEK ---

void receptHozzaadas(RecipeBook& receptKonyv, AlapanyagKonyv& alapanyagKonyv, HozzavalokLista& hozzavalokLista) {
    string name, desc, katStr;
    int ido;
    cout << "Nev: "; clearInput(); getline(cin, name);
    cout << "Leiras: "; getline(cin, desc);
    cout << "Kategoria (REGGELI/EBED/VACSORA): "; cin >> katStr;
    cout << "Elkeszitesi ido (perc): "; cin >> ido;
    receptKonyv.addRecipe(name, desc, Recipe::stringToKategoria(katStr), ido);
    int ujId = receptKonyv.getReceptek().back().getId(); // az uj recept mindig utolso
    bekerHozzavalok(ujId, alapanyagKonyv, hozzavalokLista);
    cout << "Recept hozzaadva!\n";
}

void receptListazas(RecipeBook& receptKonyv, AlapanyagKonyv& alapanyagKonyv, HozzavalokLista& hozzavalokLista) {
    for (const auto& r : receptKonyv.getReceptek()) {
        r.print(cout);
        cout << "  Hozzavalok:\n";
        hozzavalokLista.listForRecipe(r.getId(), alapanyagKonyv.getAlapanyagok(), cout);
    }
}

void receptKereses(RecipeBook& receptKonyv, AlapanyagKonyv& alapanyagKonyv, HozzavalokLista& hozzavalokLista) {
    string name;
    cout << "Keresett nev: "; clearInput(); getline(cin, name);
    vector<Recipe*> res = receptKonyv.searchByName(name);
    if (res.empty()) { cout << "Nincs talalat.\n"; return; }
    for (auto r : res) {
        r->print(cout);
        cout << "  Hozzavalok:\n";
        hozzavalokLista.listForRecipe(r->getId(), alapanyagKonyv.getAlapanyagok(), cout);
    }
}

void receptModositas(RecipeBook& receptKonyv, AlapanyagKonyv& alapanyagKonyv, HozzavalokLista& hozzavalokLista) {
    int id; cout << "Modositando Recept ID: "; cin >> id;
    if (!receptKonyv.searchById(id)) { cout << "Nincs ilyen ID!\n"; return; }

    // alap adatok modositasa
    string newName; cout << "Uj nev: "; clearInput(); getline(cin, newName);
    receptKonyv.editName(id, newName);
    string newDesc; cout << "Uj leiras: "; clearInput(); getline(cin, newDesc);
    receptKonyv.editDescription(id, newDesc);
    string newKatStr; cout << "Uj kategoria (REGGELI/EBED/VACSORA): "; cin >> newKatStr;
    receptKonyv.editKategoria(id, Recipe::stringToKategoria(newKatStr));
    int newIdo; cout << "Uj elkeszitesi ido (perc): "; cin >> newIdo;
    receptKonyv.editElkeszitesiIdo(id, newIdo);

    // opcionalis hozzavalo modositas
    cout << "Szeretne a hozzavalokat is modositani? (i/n): ";
    char modH; cin >> modH;
    if (modH == 'i' || modH == 'I') {
        cout << "Jelenlegi hozzavalok:\n";
        hozzavalokLista.listForRecipe(id, alapanyagKonyv.getAlapanyagok(), cout);
        cout << "1. Hozzaadas/Modositas  2. Torles\nValasztas: ";
        int mOpt; cin >> mOpt;
        if (mOpt == 1) {
            bekerHozzavalok(id, alapanyagKonyv, hozzavalokLista);
        } else if (mOpt == 2) {
            int hId; cout << "  Torlendo alapanyag ID: "; cin >> hId;
            hozzavalokLista.removeHozzavalo(id, hId);
            cout << "  Hozzavalo torolve.\n";
        }
    }
    cout << "Sikeres modositas.\n";
}

void receptTorles(RecipeBook& receptKonyv, HozzavalokLista& hozzavalokLista) {
    int id; cout << "Torlendo Recept ID: "; cin >> id;
    receptKonyv.removeRecipe(id);
    hozzavalokLista.removeAllForRecipe(id); // a hozzavalokat is torolni kell!
    cout << "Recept es hozzavaloi torolve.\n";
}

// --- ALAPANYAG MUVELETEK ---

void alapanyagHozzaadas(AlapanyagKonyv& alapanyagKonyv) {
    string name, unit;
    cout << "Nev: "; clearInput(); getline(cin, name);
    cout << "Mertekegyseg (pl. g, ml, db): "; cin >> unit;
    alapanyagKonyv.addAlapanyag(name, unit);
    cout << "Alapanyag hozzaadva!\n";
}

void alapanyagKereses(AlapanyagKonyv& alapanyagKonyv) {
    string name;
    cout << "Keresett nev: "; clearInput(); getline(cin, name);
    vector<Ingridient*> res = alapanyagKonyv.searchByName(name);
    if (res.empty()) { cout << "Nincs talalat.\n"; return; }
    for (auto a : res) a->print(cout);
}

void alapanyagModositas(AlapanyagKonyv& alapanyagKonyv) {
    int id; cout << "Alapanyag ID: "; cin >> id;
    if (!alapanyagKonyv.searchById(id)) { cout << "Nincs ilyen ID!\n"; return; }
    string newName; cout << "Uj nev: "; clearInput(); getline(cin, newName);
    alapanyagKonyv.editName(id, newName);
    string newUnit; cout << "Uj mertekegyseg: "; clearInput(); getline(cin, newUnit);
    alapanyagKonyv.editUnit(id, newUnit);
    cout << "Sikeres modositas.\n";
}

void alapanyagTorles(AlapanyagKonyv& alapanyagKonyv) {
    int id; cout << "Alapanyag ID: "; cin >> id;
    alapanyagKonyv.removeAlapanyag(id);
    cout << "Alapanyag torolve.\n";
}

// --- AJANLAT ---

// visszaadja a felhasznalo altal megadott elerheto alapanyag ID-kat
// ha -1-et ad meg, ures listát kapunk (minden alapanyag megfelel)
vector<int> bekerElerhetoAlapanyagok(AlapanyagKonyv& alapanyagKonyv) {
    vector<int> ids;
    cout << "Elerheto alapanyagok:\n";
    alapanyagKonyv.listAlapanyagok(cout);
    cout << "Add meg az elerheto alapanyagok ID-jait (0 = kesz, -1 = mindet elfogadom):\n";
    int aId; cin >> aId;
    if (aId == -1) return ids;
    while (aId != 0) { ids.push_back(aId); cin >> aId; }
    return ids;
}

void handleAjanlat(RecipeBook& receptKonyv, AlapanyagKonyv& alapanyagKonyv, HozzavalokLista& hozzavalokLista) {
    vector<int> elerhetoIds = bekerElerhetoAlapanyagok(alapanyagKonyv);

    cout << "Ajanlat tipusa:\n1. Kategoria es Ido ajanlat\n2. Heti Menu ajanlat\nValasztas: ";
    int aOpt; cin >> aOpt;

    string katStr;
    cout << "Kategoria (REGGELI/EBED/VACSORA vagy ISMERETLEN = mindegy): "; cin >> katStr;

    if (aOpt == 1) {
        int maxIdo;
        cout << "Max elkeszitesi ido (0 = mindegy): "; cin >> maxIdo;
        KategoriaIdoAjanlat ajanlat(
            receptKonyv.getReceptek(), hozzavalokLista.getHozzavalok(), alapanyagKonyv.getAlapanyagok(),
            Recipe::stringToKategoria(katStr), maxIdo, elerhetoIds
        );
        bekerTiltottAlapanyagok(ajanlat);
        printAjanlottak(ajanlat.ajanlatKeszit(), hozzavalokLista, alapanyagKonyv);

    } else if (aOpt == 2) {
        HetisMenuAjanlat ajanlat(
            receptKonyv.getReceptek(), hozzavalokLista.getHozzavalok(), alapanyagKonyv.getAlapanyagok(),
            Recipe::stringToKategoria(katStr), elerhetoIds
        );
        bekerTiltottAlapanyagok(ajanlat);
        ajanlat.bekerHetesMenu();
        printAjanlottak(ajanlat.ajanlatKeszit(), hozzavalokLista, alapanyagKonyv);

    } else {
        cout << "Ervenytelen valasztas!\n";
    }
}

// --- MENU KEZELOK ---

void handleReceptMenu(MenuSystem& menu, RecipeBook& receptKonyv,
                      AlapanyagKonyv& alapanyagKonyv, HozzavalokLista& hozzavalokLista) {
    while (true) {
        menu.printReceptMenu();
        switch (menu.getMenuChoice()) {
        case 0: return;
        case 1: receptHozzaadas(receptKonyv, alapanyagKonyv, hozzavalokLista); break;
        case 2: receptListazas(receptKonyv, alapanyagKonyv, hozzavalokLista);  break;
        case 3: receptKereses(receptKonyv, alapanyagKonyv, hozzavalokLista);   break;
        case 4: receptModositas(receptKonyv, alapanyagKonyv, hozzavalokLista); break;
        case 5: receptTorles(receptKonyv, hozzavalokLista);                    break;
        default: cout << "Ervenytelen menupont.\n";
        }
    }
}

void handleAlapanyagMenu(MenuSystem& menu, AlapanyagKonyv& alapanyagKonyv) {
    while (true) {
        menu.printAlapanyagMenu();
        switch (menu.getMenuChoice()) {
        case 0: return;
        case 1: alapanyagHozzaadas(alapanyagKonyv);   break;
        case 2: alapanyagKonyv.listAlapanyagok(cout); break;
        case 3: alapanyagKereses(alapanyagKonyv);     break;
        case 4: alapanyagModositas(alapanyagKonyv);   break;
        case 5: alapanyagTorles(alapanyagKonyv);      break;
        default: cout << "Ervenytelen menupont.\n";
        }
    }
}

int main() {
    // adatstrukturaink
    RecipeBook      receptKonyv;
    AlapanyagKonyv  alapanyagKonyv;
    HozzavalokLista hozzavalokLista;
    FileManager     fm;
    MenuSystem      menu;

    // beolvassuk a mentett adatokat indulaskor
    vector<Recipe>     beolvasottReceptek;
    vector<Ingridient> beolvasottAlapanyagok;
    vector<HozzaValok> beolvasottHozzavalok;
    fm.readReceptek("receptek.txt",     beolvasottReceptek);
    fm.readAlapanyagok("alapanyag.txt", beolvasottAlapanyagok);
    fm.readHozzavalok("hozzavalok.txt", beolvasottHozzavalok);
    receptKonyv.setReceptek(beolvasottReceptek);
    alapanyagKonyv.setAlapanyagok(beolvasottAlapanyagok);
    hozzavalokLista.setHozzavalok(beolvasottHozzavalok);

    // foprogram ciklus
    while (!menu.getExitingMenu()) {
        menu.printMainMenu();
        switch (menu.getMenuChoice()) {
        case 0:
            menu.exitMenu();
            cout << "Kilepes...\n";
            break;
        case 1: handleReceptMenu(menu, receptKonyv, alapanyagKonyv, hozzavalokLista); break;
        case 2: handleAlapanyagMenu(menu, alapanyagKonyv);                            break;
        case 3: handleAjanlat(receptKonyv, alapanyagKonyv, hozzavalokLista);          break;
        case 9: // mentes fajlba
            fm.writeReceptek("receptek.txt",     receptKonyv.getReceptek());
            fm.writeAlapanyagok("alapanyag.txt", alapanyagKonyv.getAlapanyagok());
            fm.writeHozzavalok("hozzavalok.txt", hozzavalokLista.getHozzavalok());
            cout << "Adatok sikeresen elmentve.\n";
            break;
        default: cout << "Ervenytelen menupont.\n";
        }
    }

    return 0;
}