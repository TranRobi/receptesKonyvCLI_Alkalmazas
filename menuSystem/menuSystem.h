#ifndef MENUSYSTEM_H
#define MENUSYSTEM_H

#include "../RecipeBook/recipeBook.h"
#include "../AlapanyagKonyv/alapanyagKonyv.h"
#include "../HozzavalokLista/hozzavalokLista.h"
class MenuSystem {
    private:
        bool exitingMenu;
    public:
        MenuSystem();
        ~MenuSystem();

        void printMainMenu() const;
        void printReceptMenu() const;
        void printAlapanyagMenu() const;
        void printKategoriaMenu() const;

        void exitMenu();
        bool getExitingMenu() const;
        int  getMenuChoice() const;

        void handleReceptMenu(RecipeBook& receptKonyv, AlapanyagKonyv& alapanyagKonyv, HozzavalokLista& hozzavalokLista);
        void handleAlapanyagMenu(AlapanyagKonyv& alapanyagKonyv);
        void handleAjanlat(RecipeBook& receptKonyv, AlapanyagKonyv& alapanyagKonyv, HozzavalokLista& hozzavalokLista);

    private:
        void clearInput() const;
        void receptHozzaadas(RecipeBook& receptKonyv, AlapanyagKonyv& alapanyagKonyv, HozzavalokLista& hozzavalokLista);
        void receptListazas(RecipeBook& receptKonyv, AlapanyagKonyv& alapanyagKonyv, HozzavalokLista& hozzavalokLista);
        void receptKereses(RecipeBook& receptKonyv, AlapanyagKonyv& alapanyagKonyv, HozzavalokLista& hozzavalokLista);
        void receptModositas(RecipeBook& receptKonyv, AlapanyagKonyv& alapanyagKonyv, HozzavalokLista& hozzavalokLista);
        void receptTorles(RecipeBook& receptKonyv, HozzavalokLista& hozzavalokLista);
        
        void alapanyagHozzaadas(AlapanyagKonyv& alapanyagKonyv);
        void alapanyagKereses(AlapanyagKonyv& alapanyagKonyv);
        void alapanyagModositas(AlapanyagKonyv& alapanyagKonyv);
        void alapanyagTorles(AlapanyagKonyv& alapanyagKonyv);
};

#endif