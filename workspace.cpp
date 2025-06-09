#include "workspace.h"
#include <fstream>
#include <iostream>
#include <algorithm> 
using namespace std;

vector<filesystem::directory_entry> EitWorkspace::getFiles(){
    vector<filesystem::directory_entry> entries;
    for (auto const& dir_entry  : filesystem::directory_iterator{path})
    {
        if (find(IGNORE.begin(), IGNORE.end(), dir_entry.path().filename().string()) == IGNORE.end() )
        {
            entries.push_back(dir_entry);
        }
    }
    return entries;
}

string EitWorkspace::readFileContent(string filePath){
    ifstream file(filePath);
    if (!file.is_open()){
        cerr << "Failed to open file " << filePath << endl;
    }
    
    ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}