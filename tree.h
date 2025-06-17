#pragma  once
#include <iostream>
#include <vector>
#include "workspace.h"
using namespace std;


namespace {
    string hexToBytes(const string& hex){
        string bytes;
        bytes.reserve(hex.length() / 2);

        for(int i=0; i< hex.length(); i+= 2){
            string byteString = hex.substr(i,2);

            char byte = (char)stoul(byteString, nullptr, 16);
            bytes.push_back(byte);
        }
        return bytes;
    }
}
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
        string to_string(){
            stringstream ss;
            for (auto const& entry: entries){
                ss << this->mode << " " << entry.fileName << '\0';            
                string oid_in_bytes = hexToBytes(entry.objectId);
                ss.write(oid_in_bytes.c_str(), oid_in_bytes.size());
            }
            return ss.str();
        }
};