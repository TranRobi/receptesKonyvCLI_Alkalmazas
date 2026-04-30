#include "menuSystem.h"
#include <string>
#include <iostream>


MenuSystem::MenuSystem():exitingMenu(false){}
void MenuSystem::printMenu() {
    std::cout << "===========================================" << std::endl;
    std::cout << "        RECEPT KONYV - DIGITALIS NAPLO     " << std::endl;
    std::cout << "===========================================" << std::endl;
    std::cout << " [1]  Uj recept felvetele" << std::endl;      
    std::cout << " [2]  Osszes recept kilistazasa" << std::endl; 
    std::cout << " [3]  Recept keresese" << std::endl;          
    std::cout << " [4]  Recept modositasa" << std::endl;        
    std::cout << " [5]  Recept torlese" << std::endl;           
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << " [9]  Mentes fajlba (recipes.txt)" << std::endl; 
    std::cout << " [0]  Kilepes a programbol" << std::endl;     
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << " Valasszon egy opciot: ";
}

void MenuSystem::exitMenu(){
    exitingMenu = true;
}

bool MenuSystem::getExitingMenu() const{
    return exitingMenu;
}