#pragma once
#include <iostream>
struct Author {
    std::string name;
    std::string email;
    long long timestamp;

    Author(const char* n, const char* e, long long t): name(n ? n : ""), email(e ? e : ""), timestamp(t) {}
    std::string to_string() const;
};