#include "tree.h"

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

string Tree::to_string() const{
        stringstream ss;
        for (auto const& entry: entries){
            ss << "100644" << " " << entry.fileName << '\0';            
            string oid_in_bytes = hexToBytes(entry.objectId);
            ss.write(oid_in_bytes.c_str(), oid_in_bytes.size());
        }
        return ss.str();
    }