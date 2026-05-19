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
#include "gtest_lite.h"
#include "memtrace.h"

/*

using namespace std;

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
        case 1: menu.handleReceptMenu(receptKonyv, alapanyagKonyv, hozzavalokLista); break;
        case 2: menu.handleAlapanyagMenu(alapanyagKonyv);                            break;
        case 3: menu.handleAjanlat(receptKonyv, alapanyagKonyv, hozzavalokLista);    break;
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
}*/

int main(){
    TEST(FileManagerTest, LOAD){
        vector<Recipe>     beolvasottReceptek;
        vector<Ingridient> beolvasottAlapanyagok;
        vector<HozzaValok> beolvasottHozzavalok;
        FileManager fm;
        RecipeBook      receptKonyv;
        AlapanyagKonyv  alapanyagKonyv;
        HozzavalokLista hozzavalokLista;
        fm.readReceptek("receptek.txt",     beolvasottReceptek);
        fm.readAlapanyagok("alapanyag.txt", beolvasottAlapanyagok);
        fm.readHozzavalok("hozzavalok.txt", beolvasottHozzavalok);
        receptKonyv.setReceptek(beolvasottReceptek);
        alapanyagKonyv.setAlapanyagok(beolvasottAlapanyagok);
        hozzavalokLista.setHozzavalok(beolvasottHozzavalok);
        EXPECT_FALSE(beolvasottAlapanyagok.empty());
        EXPECT_FALSE(beolvasottHozzavalok.empty());
        EXPECT_FALSE(beolvasottReceptek.empty());
        fm.~FileManager();
    }END
    return 0;
}
