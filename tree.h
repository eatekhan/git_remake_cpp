#pragma  once
#include <iostream>
#include <vector>
#include "workspace.h"
using namespace std;


class Tree{
    private:
        vector<Entry> entries;
        
        
    public:
        string mode;
        string type;
        string objectId;
        Tree(vector<Entry> entries){
            this->entries = entries;
            this->mode = "100644";
            this->type = "Tree";
        }
        string to_string() const {}
};