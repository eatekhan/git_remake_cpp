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
            this->type = "Blob";
        }
        string to_string(){ return this->fileContent;}
};