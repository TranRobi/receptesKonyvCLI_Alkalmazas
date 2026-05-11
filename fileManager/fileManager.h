#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include "ingridient.h"
#include "hozzaValok.h"
#include "recipe.h"

using namespace std;

class FileManager {
    public:
        FileManager();
        ~FileManager();

        // alapanyag.txt: id,nev,unit
        bool readAlapanyagok(const string& file, vector<Ingridient>& alapanyagok);
        bool writeAlapanyagok(const string& file, const vector<Ingridient>& alapanyagok);

        // hozzavalok.txt: recipeID,alapanyagID,amount
        bool readHozzavalok(const string& file, vector<HozzaValok>& hozzavalok);
        bool writeHozzavalok(const string& file, const vector<HozzaValok>& hozzavalok);

        // receptek.txt: id,nev,leiras,kategoria,elkeszitesiIdo
        bool readReceptek(const string& file, vector<Recipe>& receptek);
        bool writeReceptek(const string& file, const vector<Recipe>& receptek);
};

#endif