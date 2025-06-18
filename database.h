#include <filesystem>
#include <string>
#include <iostream>


using namespace std;
class Database{
    private:
        filesystem::path path;
        string sha1(const string& data) {}


        template<typename T>
        bool writeObject(T &obj, string &contentFormat){}

    public:
        Database(filesystem::path path){this->path = path;}

        template<typename T>
        bool store(T &obj){}
        
};