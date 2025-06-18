#include "refs.h"
#include <fstream> 
string Refs::get_head(){
    if(fs::exists(head_path))
    {
        ifstream file(head_path);
        ostringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }
    return "";
    
}