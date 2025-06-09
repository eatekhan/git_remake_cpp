#include <filesystem>
#include "blob.h"
#include <gcrypt.h>
#include <string>
#include <iostream>
class Database{
    private:
        std::filesystem::path path;
        std::string sha1(const std::string& data) {
            gcry_md_hd_t hd;
            gcry_md_open(&hd, GCRY_MD_SHA1, 0);
            gcry_md_write(hd, data.c_str(), data.size());

            unsigned char* hash = gcry_md_read(hd, GCRY_MD_SHA1);

            std::ostringstream oss;
            for (int i = 0; i < gcry_md_get_algo_dlen(GCRY_MD_SHA1); ++i)
                oss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];

            gcry_md_close(hd);
            return oss.str();
        }
    public:
        Database(std::filesystem::path path){
            this->path = path;   
        }
        bool store(Blob blob){
            string contentFormat = "#blob" + std::to_string(blob.fileContent.size()) + string(1, '\0') + blob.fileContent;
            blob.objectId = sha1(contentFormat);
        }
        
};