#pragma  once
#include <iostream>
#include <vector>
#include "workspace.h"
using namespace std;
#include <algorithm> 

class Tree{
    private:
        vector<Entry> entries;
        
        
    public:
        string mode;
        string type;
        string objectId;

        Tree(std::vector<Entry> new_entries):entries(std::move(new_entries)), type("tree"), mode("100644") {
        std::sort(entries.begin(), entries.end(), [](const Entry& a, const Entry& b) {
        return a.fileName < b.fileName;
    });
}
        string to_string() const;
};