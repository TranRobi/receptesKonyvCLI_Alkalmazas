#ifndef MENUSYSTEM_H
#define MENUSYSTEM_H

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
};

#endif