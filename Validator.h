#pragma once
#include <string>
#include <regex>
#include <cctype>
#include <algorithm>

class Validator {
public:
    static bool validateName(const std::string& name);
    static bool validatePhone(const std::string& phone);
    static bool validateDate(const std::string& date);
    static bool validateEmail( std::string& s);

    static std::string trim( std::string& s);
};

