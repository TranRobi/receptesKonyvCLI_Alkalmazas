#include "menuSystem.h"
#include <iostream>

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