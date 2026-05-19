#ifndef RECIPEBOOK_H
#define RECIPEBOOK_H

#include <string>
#include <vector>
#include <ostream>
#include "../Recipe/recipe.h"

using namespace std;

// recepteket tarolja es kezeli, CRUD muveletekkel
class RecipeBook {
    private:
        vector<Recipe> receptek;
        int nextId() const;
    public:
        RecipeBook();
        ~RecipeBook();

        void addRecipe(const string& name, const string& desc,
                       Kategoria kat, int elkeszitesiIdo);
        void removeRecipe(int id);

        Recipe*         searchById(int id);
        vector<Recipe*> searchByName(const string& name);
        vector<Recipe*> searchByKategoria(Kategoria kat);

        void editName(int id, const string& newName);
        void editDescription(int id, const string& newDesc);
        void editKategoria(int id, Kategoria newKat);
        void editElkeszitesiIdo(int id, int newIdo);

        const vector<Recipe>& getReceptek() const;
        void setReceptek(const vector<Recipe>& r);
        void listReceptek(ostream& os) const;
};

#endif