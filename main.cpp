#include <iostream>
#include <string>
#include "./menuSystem/menuSystem.h"
using namespace std;
int main(){
    MenuSystem m;
    int opt;
    m.printMenu();
    while(!m.getExitingMenu()){
        cin >> opt;
        switch (opt)
        {
        case 1:
            cout << "Uj recept felvetele";
            break;
        case 2:
            cout << "Összes recept kilistázása";
            break;
        case 3:
            cout << "Recept keresese";
            break;
        case 4:
            cout << "Recept modosítasa";
            break;
        case 5:
            cout << "Recepet torlese";
            break;
        case 9:
            cout << "Mentes fajlba";
            break;
        case 0:
            m.exitMenu();
            break;
        default:
            m.exitMenu();
        }
    }
    
    return 0;
}