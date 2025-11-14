#include "Validator.h"

std::string Validator::trim( std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
    return s;
}

bool Validator::validateName(const std::string& name) {
    std::regex pattern(R"(^[A-Za-zА-Яа-яЁё][A-Za-zА-Яа-яЁё0-9 -]*[A-Za-zА-Яа-яЁё0-9]$)");
    return std::regex_match(name, pattern);
}

bool Validator::validatePhone(const std::string& phone) {
    std::regex pattern(R"(^(\+7|8)\(?\d{3}\)?\d{3}[-]?\d{2}[-]?\d{2}$)");
    return std::regex_match(phone, pattern);
}

bool Validator::validateDate(const std::string& date) {

    std::regex pattern(R"(^(19|20)\d\d-(0[1-9]|1[0-2])-(0[1-9]|[12]\d|3[01])$)");
    if (!std::regex_match(date, pattern))
        return false;

    int year, month, day;
    if (sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day) != 3)
        return false;

    static const int days_in_month[] = {
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };

    int days = days_in_month[month - 1];

    bool isLeap =
        (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (month == 2 && isLeap)
        days = 29;

    if (day < 1 || day > days)
        return false;  

    std::tm t = {};
    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    t.tm_mday = day;

    std::time_t input_time = std::mktime(&t);
    std::time_t now = std::time(nullptr);

    if (input_time > now)
        return false;  

    return true;
}
bool Validator::validateEmail(std::string& s) {

    s.erase(0, s.find_first_not_of(" \t"));

    s.erase(s.find_last_not_of(" \t") + 1);


    size_t at_pos = s.find('@');
    if (at_pos != std::string::npos) {

        while (at_pos > 0 && s[at_pos - 1] == ' ') {
            s.erase(at_pos - 1, 1);
            at_pos--;
        }

        while (at_pos + 1 < s.size() && s[at_pos + 1] == ' ') {
            s.erase(at_pos + 1, 1);
        }
    }

    std::regex pattern(R"(^[A-Za-z0-9]+@[A-Za-z0-9]+$)");
    return std::regex_match(s, pattern);
}