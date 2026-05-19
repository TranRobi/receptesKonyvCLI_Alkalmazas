#include <iostream>
#include "menuSystem.h"
#include "../memtrace.h"

using namespace std;

MenuSystem::MenuSystem() : exitingMenu(false) {}

MenuSystem::~MenuSystem() {}

void MenuSystem::printMainMenu() const {
    cout << "\n=== FO MENU ===\n"
         << "1. Receptek kezelese\n"
         << "2. Alapanyagok kezelese\n"
         << "3. Ajanlatok megtekintese\n"
         << "9. Mentes\n"
         << "0. Kilepes\n";
}

void MenuSystem::printReceptMenu() const {
    cout << "\n--- RECEPT MENU ---\n"
         << "1. Uj recept hozzaadasa\n"
         << "2. Osszes recept listazasa\n"
         << "3. Recept keresese nev szerint\n"
         << "4. Recept modositasa\n"
         << "5. Recept torlese\n"
         << "0. Vissza a fo menube\n";
}

void MenuSystem::printAlapanyagMenu() const {
    cout << "\n--- ALAPANYAG MENU ---\n"
         << "1. Uj alapanyag hozzaadasa\n"
         << "2. Osszes alapanyag listazasa\n"
         << "3. Alapanyag keresese nev szerint\n"
         << "4. Alapanyag modositasa\n"
         << "5. Alapanyag torlese\n"
         << "0. Vissza a fo menube\n";
}

void MenuSystem::printKategoriaMenu() const {
    cout << "\n--- KATEGORIA MENU ---\n"
         << "1. REGGELI\n"
         << "2. EBED\n"
         << "3. VACSORA\n"
         << "0. ISMERETLEN\n";
}

void MenuSystem::exitMenu() {
    exitingMenu = true;
}

bool MenuSystem::getExitingMenu() const {
    return exitingMenu;
}

int MenuSystem::getMenuChoice() const {
    int choice;
    cout << "Valasztas: ";
    cin >> choice;
    return choice;
}

#include <limits>
#include "../Ajanlat/KategoriaIdoAjanlat/kategoriaIdoAjanlat.h"
#include "../Ajanlat/HetisMenuAjanlat/hetisMenuAjanlat.h"

void MenuSystem::clearInput() const {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void MenuSystem::receptHozzaadas(RecipeBook& receptKonyv, AlapanyagKonyv& alapanyagKonyv, HozzavalokLista& hozzavalokLista) {
    string name, desc, katStr;
    int ido;
    cout << "Nev: "; clearInput(); getline(cin, name);
    cout << "Leiras: "; getline(cin, desc);
    cout << "Kategoria (REGGELI/EBED/VACSORA): "; cin >> katStr;
    cout << "Elkeszitesi ido (perc): "; cin >> ido;
    receptKonyv.addRecipe(name, desc, Recipe::stringToKategoria(katStr), ido);
    int ujId = receptKonyv.getReceptek().back().getId();
    hozzavalokLista.bekerHozzavalokConsole(ujId, alapanyagKonyv);
    cout << "Recept hozzaadva!\n";
}

void MenuSystem::receptListazas(RecipeBook& receptKonyv, AlapanyagKonyv& alapanyagKonyv, HozzavalokLista& hozzavalokLista) {
    for (const auto& r : receptKonyv.getReceptek()) {
        r.print(cout);
        cout << "  Hozzavalok:\n";
        hozzavalokLista.listForRecipe(r.getId(), alapanyagKonyv.getAlapanyagok(), cout);
    }
}

void MenuSystem::receptKereses(RecipeBook& receptKonyv, AlapanyagKonyv& alapanyagKonyv, HozzavalokLista& hozzavalokLista) {
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

void MenuSystem::receptModositas(RecipeBook& receptKonyv, AlapanyagKonyv& alapanyagKonyv, HozzavalokLista& hozzavalokLista) {
    int id; cout << "Modositando Recept ID: "; cin >> id;
    if (!receptKonyv.searchById(id)) { cout << "Nincs ilyen ID!\n"; return; }

    string newName; cout << "Uj nev: "; clearInput(); getline(cin, newName);
    receptKonyv.editName(id, newName);
    string newDesc; cout << "Uj leiras: "; clearInput(); getline(cin, newDesc);
    receptKonyv.editDescription(id, newDesc);
    string newKatStr; cout << "Uj kategoria (REGGELI/EBED/VACSORA): "; cin >> newKatStr;
    receptKonyv.editKategoria(id, Recipe::stringToKategoria(newKatStr));
    int newIdo; cout << "Uj elkeszitesi ido (perc): "; cin >> newIdo;
    receptKonyv.editElkeszitesiIdo(id, newIdo);

    cout << "Szeretne a hozzavalokat is modositani? (i/n): ";
    char modH; cin >> modH;
    if (modH == 'i' || modH == 'I') {
        cout << "Jelenlegi hozzavalok:\n";
        hozzavalokLista.listForRecipe(id, alapanyagKonyv.getAlapanyagok(), cout);
        cout << "1. Hozzaadas/Modositas  2. Torles\nValasztas: ";
        int mOpt; cin >> mOpt;
        if (mOpt == 1) {
            hozzavalokLista.bekerHozzavalokConsole(id, alapanyagKonyv);
        } else if (mOpt == 2) {
            int hId; cout << "  Torlendo alapanyag ID: "; cin >> hId;
            hozzavalokLista.removeHozzavalo(id, hId);
            cout << "  Hozzavalo torolve.\n";
        }
    }
    cout << "Sikeres modositas.\n";
}

void MenuSystem::receptTorles(RecipeBook& receptKonyv, HozzavalokLista& hozzavalokLista) {
    int id; cout << "Torlendo Recept ID: "; cin >> id;
    receptKonyv.removeRecipe(id);
    hozzavalokLista.removeAllForRecipe(id);
    cout << "Recept es hozzavaloi torolve.\n";
}

void MenuSystem::alapanyagHozzaadas(AlapanyagKonyv& alapanyagKonyv) {
    string name, unit;
    cout << "Nev: "; clearInput(); getline(cin, name);
    cout << "Mertekegyseg (pl. g, ml, db): "; getline(cin, unit);
    alapanyagKonyv.addAlapanyag(name, unit);
    cout << "Alapanyag hozzaadva!\n";
}

void MenuSystem::alapanyagKereses(AlapanyagKonyv& alapanyagKonyv) {
    string name;
    cout << "Keresett nev: "; clearInput(); getline(cin, name);
    vector<Ingridient*> res = alapanyagKonyv.searchByName(name);
    if (res.empty()) { cout << "Nincs talalat.\n"; return; }
    for (auto a : res) a->print(cout);
}

void MenuSystem::alapanyagModositas(AlapanyagKonyv& alapanyagKonyv) {
    int id; cout << "Alapanyag ID: "; cin >> id;
    if (!alapanyagKonyv.searchById(id)) { cout << "Nincs ilyen ID!\n"; return; }
    string newName; cout << "Uj nev: "; clearInput(); getline(cin, newName);
    alapanyagKonyv.editName(id, newName);
    string newUnit; cout << "Uj mertekegyseg: "; clearInput(); cin >> newUnit;
    alapanyagKonyv.editUnit(id, newUnit);
    cout << "Sikeres modositas.\n";
}

void MenuSystem::alapanyagTorles(AlapanyagKonyv& alapanyagKonyv) {
    int id; cout << "Alapanyag ID: "; cin >> id;
    alapanyagKonyv.removeAlapanyag(id);
    cout << "Alapanyag torolve.\n";
}

void MenuSystem::handleReceptMenu(RecipeBook& receptKonyv, AlapanyagKonyv& alapanyagKonyv, HozzavalokLista& hozzavalokLista) {
    while (true) {
        printReceptMenu();
        switch (getMenuChoice()) {
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

void MenuSystem::handleAlapanyagMenu(AlapanyagKonyv& alapanyagKonyv) {
    while (true) {
        printAlapanyagMenu();
        switch (getMenuChoice()) {
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

void MenuSystem::handleAjanlat(RecipeBook& receptKonyv, AlapanyagKonyv& alapanyagKonyv, HozzavalokLista& hozzavalokLista) {
    cout << "Ajanlat tipusa:\n1. Kategoria es Ido ajanlat\n2. Heti Menu ajanlat\nValasztas: ";
    int aOpt; cin >> aOpt;

    string katStr;
    cout << "Kategoria (REGGELI/EBED/VACSORA vagy ISMERETLEN = mindegy): "; cin >> katStr;

    if (aOpt == 1) {
        int maxIdo;
        cout << "Max elkeszitesi ido (0 = mindegy): "; cin >> maxIdo;
        KategoriaIdoAjanlat ajanlat(
            receptKonyv.getReceptek(), hozzavalokLista.getHozzavalok(), alapanyagKonyv.getAlapanyagok(),
            Recipe::stringToKategoria(katStr), maxIdo, vector<int>()
        );
        ajanlat.bekerElerhetoAlapanyagokConsole(alapanyagKonyv);
        ajanlat.bekerTiltottAlapanyagokConsole();
        cout << "\n--- AJANLOTT RECEPTEK ---\n";
        ajanlat.listAjanlatok(cout);

    } else if (aOpt == 2) {
        HetisMenuAjanlat ajanlat(
            receptKonyv.getReceptek(), hozzavalokLista.getHozzavalok(), alapanyagKonyv.getAlapanyagok(),
            Recipe::stringToKategoria(katStr), vector<int>()
        );
        ajanlat.bekerElerhetoAlapanyagokConsole(alapanyagKonyv);
        ajanlat.bekerTiltottAlapanyagokConsole();
        ajanlat.bekerHetesMenu();
        cout << "\n--- AJANLOTT RECEPTEK ---\n";
        ajanlat.listAjanlatok(cout);

    } else {
        cout << "Ervenytelen valasztas!\n";
    }
}