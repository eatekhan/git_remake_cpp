#include <iostream>
#include "author.h"
#include <chrono>
#include <ctime>
#include <sstream>

std::string Author::to_string() const{
        std::stringstream ss;
        ss << name << " <" << email << "> " << timestamp;
        return ss.str();
    }