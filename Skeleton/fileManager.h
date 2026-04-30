#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
using namespace std;
class FileManager{
    public:
    void readFile(const string& file);
    void writeFile(const string& file);
    
};
#endif