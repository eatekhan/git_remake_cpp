#include "commit.h"
std::string Commit::to_string() const{
            std::stringstream ss;
            ss << "tree " <<  tree.objectId << "\n";
            if (!parent.empty()) {
                ss << "parent " << parent << "\n";
            }
            ss << "author " << author.to_string() << "\n";
            ss << "committer " << author.to_string() << "\n";
            ss << "\n";
            ss << message << "\n";

            return ss.str();
        }