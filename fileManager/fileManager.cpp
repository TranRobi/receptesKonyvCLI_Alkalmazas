#include "fileManager.h"
#include <fstream>
#include <vector>
#include <sstream>

FileManager::FileManager() {}

FileManager::~FileManager() {}

bool FileManager::readAlapanyagok(const string& file, vector<Ingridient>& alapanyagok) {
    ifstream ifs(file);
    if (!ifs.is_open()) return false;
    string line;
    while (getline(ifs, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string idStr, nev, unit;
        getline(ss, idStr, ',');
        getline(ss, nev, ',');
        getline(ss, unit, ',');
        try {
            alapanyagok.push_back(Ingridient(stoi(idStr), nev, unit));
        } catch (...) {}
    }
    return true;
}

bool FileManager::writeAlapanyagok(const string& file, const vector<Ingridient>& alapanyagok) {
    ofstream ofs(file);
    if (!ofs.is_open()) return false;
    for (const auto& a : alapanyagok) {
        ofs << a.getId() << "," << a.getName() << "," << a.getUnit() << "\n";
    }
    return true;
}

bool FileManager::readHozzavalok(const string& file, vector<HozzaValok>& hozzavalok) {
    ifstream ifs(file);
    if (!ifs.is_open()) return false;
    string line;
    while (getline(ifs, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string rIdStr, iIdStr, amountStr;
        getline(ss, rIdStr, ',');
        getline(ss, iIdStr, ',');
        getline(ss, amountStr, ',');
        try {
            hozzavalok.push_back(HozzaValok(stoi(rIdStr), stoi(iIdStr), stoi(amountStr)));
        } catch (...) {}
    }
    return true;
}

bool FileManager::writeHozzavalok(const string& file, const vector<HozzaValok>& hozzavalok) {
    ofstream ofs(file);
    if (!ofs.is_open()) return false;
    for (const auto& h : hozzavalok) {
        ofs << h.getRecipeID() << "," << h.getIngridientID() << "," << h.getAmount() << "\n";
    }
    return true;
}

bool FileManager::readReceptek(const string& file, vector<Recipe>& receptek) {
    ifstream ifs(file);
    if (!ifs.is_open()) return false;
    string line;
    while (getline(ifs, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string idStr, nev, leiras, katStr, idoStr;
        getline(ss, idStr, ',');
        getline(ss, nev, ',');
        getline(ss, leiras, ',');
        getline(ss, katStr, ',');
        getline(ss, idoStr, ',');
        try {
            receptek.push_back(Recipe(stoi(idStr), nev, leiras, Recipe::stringToKategoria(katStr), stoi(idoStr)));
        } catch (...) {}
    }
    return true;
}

bool FileManager::writeReceptek(const string& file, const vector<Recipe>& receptek) {
    ofstream ofs(file);
    if (!ofs.is_open()) return false;
    for (const auto& r : receptek) {
        ofs << r.getId() << "," << r.getName() << "," << r.getDescription() << ","
            << Recipe::kategoriaToString(r.getKategoria()) << "," << r.getElkeszitesiIdo() << "\n";
    }
    return true;
}