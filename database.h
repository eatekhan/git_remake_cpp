#include <filesystem>
#include "blob.h"
#include <gcrypt.h>
#include <string>
#include <iostream>
#include <fstream>
#include <zlib.h>
using namespace std;
class Database{
    private:
        filesystem::path path;
        string sha1(const string& data) {
            gcry_md_hd_t hd;
            gcry_md_open(&hd, GCRY_MD_SHA1, 0);
            gcry_md_write(hd, data.c_str(), data.size());

            unsigned char* hash = gcry_md_read(hd, GCRY_MD_SHA1);

            ostringstream oss;
            for (int i = 0; i < gcry_md_get_algo_dlen(GCRY_MD_SHA1); ++i)
                oss << hex << setw(2) << setfill('0') << (int)hash[i];

            gcry_md_close(hd);
            return oss.str();
        }

        template<typename T>
        bool writeObject(T &obj, string &contentFormat){
            filesystem::path dir = this->path / obj.objectId.substr(0, 2);
            string objectName = obj.objectId.substr(2, 38);

            if (!filesystem::exists(dir)){
                filesystem::create_directory(dir);
            }
            ofstream file(dir / objectName, ios::binary);
            if (!file){
                cerr << "Failed to create file" << objectName << endl;
                return false;
            }
            // cout << dir << endl;
            file << contentFormat;
            // cout << contentFormat;
            file.close();
            return true;
        }


    public:
        Database(filesystem::path path){
            this->path = path;   
        }

        template<typename T>
        bool store(T &obj){
            string contentFormat = obj.type +" "+ to_string(obj.to_string().size()) + string(1, '\0') + obj.to_string();
            obj.objectId = sha1(contentFormat);
            writeObject(obj, contentFormat);
            return true;
        }
        
};