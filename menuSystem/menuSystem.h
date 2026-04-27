#ifndef MENUSYSTEM_H
#define MENUSYSTEM_H

class MenuSystem{
    private:
        bool exitingMenu;
    public:
        MenuSystem();
        void printMenu();
        void exitMenu();
        bool getExitingMenu() const;
    
};
#endif