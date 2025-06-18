#pragma once
#include <filesystem>
using namespace std;
namespace fs = filesystem;

class Refs{
    private:
        fs::path path;
        fs::path head_path;
        

    public:
        string get_head();
        Refs(fs::path path) : path(path){head_path = path/"HEAD";};


};