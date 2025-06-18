#include <filesystem>
#include "blob.h"
#include <gcrypt.h>
#include <string>
#include <iostream>
#include <fstream>
#include <zlib.h>
#include <vector>
using namespace std;



namespace{
    std::string compress(const std::string& data) {
    z_stream strm;
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;

    // Initialize the stream for deflation
    if (deflateInit(&strm, Z_DEFAULT_COMPRESSION) != Z_OK) {
        throw std::runtime_error("deflateInit failed");
    }

    strm.avail_in = data.length();
    // zlib's C API doesn't use const, so we need to cast away constness.
    // This is a known, safe use of const_cast.
    strm.next_in = reinterpret_cast<Bytef*>(const_cast<char*>(data.c_str()));

    // Use a vector to create a dynamic buffer for the output
    std::vector<char> out_buffer(data.length()); // A reasonable starting size
    std::string compressed_data;

    // Compress the data in a loop until it's all processed
    do {
        strm.avail_out = out_buffer.size();
        strm.next_out = reinterpret_cast<Bytef*>(out_buffer.data());

        // Z_FINISH tells zlib this is all the input data
        int ret = deflate(&strm, Z_FINISH);
        if (ret == Z_STREAM_ERROR) {
            deflateEnd(&strm);
            throw std::runtime_error("deflate failed");
        }
        
        // Calculate how many bytes were written and append to our result string
        int have = out_buffer.size() - strm.avail_out;
        compressed_data.append(out_buffer.data(), have);

    } while (strm.avail_out == 0);

    // Clean up the zlib stream
    deflateEnd(&strm);

    return compressed_data;
}

}


class Database{
    private:
        filesystem::path path;
        string sha1(const string& data);


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

            string compressed_data = compress(contentFormat);
            file << compressed_data;
            // cout << compressed_data;
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