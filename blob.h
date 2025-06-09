#include <filesystem>
using namespace std;

class Blob{
    private:
        
        string objectType;
    public:
        string fileContent;
        string objectId;
        Blob(string fileContent){
            this->fileContent = fileContent;
            this->objectType = "Blob";
        }
};