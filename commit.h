#pragma  once
#include <iostream>
#include "author.h"
#include "tree.h"
class Commit{
    Tree tree;
    Author author;
    std::string message;
    std::string parent;
    
    public:
        std::string objectId;
        std::string type = "commit";
        Commit(Tree tree, Author author, std::string message, std::string parent) : tree(tree), author(author), message(message), parent(parent){};   
        std::string to_string() const;
};