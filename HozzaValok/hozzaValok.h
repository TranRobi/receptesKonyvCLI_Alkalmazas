#ifndef HOZZAVALOK_H
#define HOZZAVALOK_H

#include <ostream>

using namespace std;

class HozzaValok {
    private:
        int recipeID;
        int ingridientID;
        int amount;
    public:
        HozzaValok();
        HozzaValok(int recipeID, int ingridientID, int amount);
        ~HozzaValok();

        int getRecipeID() const;
        int getIngridientID() const;
        int getAmount() const;

        void setRecipeID(int newRecipeID);
        void setIngridientID(int newIngridientID);
        void setAmount(int newAmount);

        // Kiiratas: "recipeID,ingridientID,amount"
        void print(ostream& os) const;
        bool operator==(const HozzaValok& other) const;
};

#endif