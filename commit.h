#include <iostream>
#include "author.h"
class Commit{
    Tree tree;
    Author author;
    std::string message;
    
    

    public:
        std::string objectId;
        std::string type = "commit";
        Commit(Tree tree, Author author, std::string message) : tree(tree), author(author), message(message){};
    
        string to_string(){
            std::stringstream ss;
            ss << "tree " <<  tree.objectId << "\n";
            ss << "author " << author.to_string() << "\n";
            ss << "committer " << author.to_string() << "\n";
            ss << "\n";
            ss << message;

            return ss.str();
        }
};