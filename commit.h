#include <iostream>
#include "author.h"
#include "tree.h"
class Commit{
    Tree tree;
    Author author;
    std::string message;
    
    public:
        std::string objectId;
        std::string type = "commit";
        Commit(Tree tree, Author author, std::string message) : tree(tree), author(author), message(message){};   
        std::string to_string() const{}
};