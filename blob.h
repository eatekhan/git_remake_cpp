#pragma  once
#include <filesystem>
using namespace std;

class Blob{
    private:
        
        
    public:
        string fileContent;
        string objectId;
        string type;
        Blob(string &fileContent){
            this->fileContent = fileContent;
            this->type = "blob";
        }
        string to_string(){ return this->fileContent;}
};