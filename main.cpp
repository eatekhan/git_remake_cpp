#include <iostream>
#include <string>
#include <filesystem>
#include "workspace.h"
#include "database.h"

using namespace std;
namespace fs = filesystem;

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cerr << "Enter a valid eit command";
        return 1;
    }
    string git_command = argv[1];

    if (git_command == "init")
    {
        fs::path absolutePath = (argc > 2) ? fs::path(argv[2]) : fs::absolute(fs::current_path());
        fs::path gitPath = absolutePath / ".git";
        
        if (fs::exists(gitPath))
        {
            cerr << "Already an eit repository";
            return 1;
        }
        fs::create_directory(gitPath);
        fs::create_directory(gitPath / "objects");
        fs::create_directory(gitPath / "refs");
    }

    if (git_command == "commit")
    {
        fs::path absolutePath = fs::absolute(fs::current_path());
        fs::path gitPath = absolutePath / ".git";
        fs::path databasePath = absolutePath / ".objects";

        EitWorkspace workspace = EitWorkspace(absolutePath);
        Database database = Database(databasePath);

        for(auto const& dir_entries: workspace.getFiles())
        {
            string fileContent = workspace.readFileContent(dir_entries.path().string());
            Blob blob(fileContent);
    
            database.store(blob);
            
        }
        
    }
    return 0;
}