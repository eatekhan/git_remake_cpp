#pragma once
#include <iostream>
#include <chrono>
#include <ctime>
struct Author {
    std::string name;
    std::string email;
    long long timestamp;

    Author(const char* n, const char* e, long long t): name(n ? n : ""), email(e ? e : ""), timestamp(t) {}

    std::string to_string(){

        std::stringstream ss;
        ss << name << " <" << email << "> " << timestamp;
        return ss.str();

        return 0;
    }
};