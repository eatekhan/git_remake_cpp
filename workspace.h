#include <filesystem>
#include <vector>
using namespace std;


class EitWorkspace{
    private:
        vector<string> IGNORE = {".", "..", ".git", "eit"};
        filesystem::path path;
    public:
        EitWorkspace(filesystem::path path){
            this->path = path;
        }
        vector<filesystem::directory_entry> getFiles();
        string readFileContent(string filePath);
};