#include <iostream>
#include <string>
#include <filesystem>
#include "workspace.h"
#include "database.h"
#include "tree.h"
#include <chrono>
#include <cstdlib>
#include "author.h"
#include "commit.h"
#include "blob.h"
#include "refs.h"
long long getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::seconds>(duration).count();
}

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
        fs::path databasePath = gitPath / "objects";


        EitWorkspace workspace = EitWorkspace(absolutePath);
        Database database = Database(databasePath);
        Refs refs = Refs(gitPath);

        vector<Entry> entries;
        for(auto const& dir_entries: workspace.getFiles())
        {
            string fileContent = workspace.readFileContent(dir_entries.path().string());
            Blob blob(fileContent);
            database.store(blob);
            
            entries.push_back(Entry(dir_entries.path().filename().string(), blob.objectId));
        }
        Tree tree(entries);
        database.store(tree);
        

        const char* name = std::getenv("GIT_AUTHOR_NAME");
        const char* email = std::getenv("GIT_AUTHOR_EMAIL");

        long long ts = std::chrono::duration_cast<std::chrono::seconds>(
                       std::chrono::system_clock::now().time_since_epoch())
                       .count();
        
        Author author(name, email, ts);
        

        string message;
        getline(cin, message);
        
        string parent = refs.get_head();
        
        Commit commit(tree, author, message, parent);
        database.store(commit);
        
        ofstream file(gitPath/"HEAD");
        file << commit.objectId;


        string first_line;
        stringstream ss(message);
        getline(ss, first_line);

        string is_root = "";
        if (parent == "") {is_root = "(root-commit) "; }
        cout << is_root << commit.objectId << " " << first_line << endl;





    }
    return 0;
}